package simpledb.tx.concurrency;

import java.util.*;
import simpledb.file.BlockId;
import simpledb.tx.Transaction;

/**
 * The lock table, which provides methods to lock and unlock blocks.
 * If a transaction requests a lock that causes a conflict with an
 * existing lock, then that transaction is placed on a wait list.
 * There is only one wait list for all blocks.
 * When the last lock on a block is unlocked, then all transactions
 * are removed from the wait list and rescheduled.
 * If one of those transactions discovers that the lock it is waiting for
 * is still locked, it will place itself back on the wait list.
 * @author Edward Sciore
 */
class LockTable {
   private static final long MAX_TIME = 10000; // 10 seconds
   
   private Map<BlockId,LinkedList<Transaction>> locks = new HashMap<BlockId,LinkedList<Transaction>>();
   
   /**
    * Grant an SLock on the specified block.
    * If an XLock exists when the method is called,
    * then the calling thread will be placed on a wait list
    * until the lock is released.
    * If the thread remains on the wait list for a certain 
    * amount of time (currently 10 seconds),
    * then an exception is thrown.
    * @param blk a reference to the disk block
    */
   public synchronized void sLock(BlockId blk, Transaction tx) {
      try {
         long timestamp = System.currentTimeMillis();
         LinkedList<Transaction> list = getLockVal(blk);
         if (!list.isEmpty() && hasXlock(blk)) {
            if (Math.abs(list.getFirst().getLocknum()) > Math.abs(tx.getLocknum()))
               wait(MAX_TIME);
            else if (Math.abs(list.getFirst().getLocknum()) < Math.abs(tx.getLocknum())) {
               notifyAll();
               throw new LockAbortException();
            }
         }
         list.add(tx);
         locks.put(blk, list);
      }
      catch(InterruptedException e) {
         throw new LockAbortException();
      }
   }
   
   /**
    * Grant an XLock on the specified block.
    * If a lock of any type exists when the method is called,
    * then the calling thread will be placed on a wait list
    * until the locks are released.
    * If the thread remains on the wait list for a certain 
    * amount of time (currently 10 seconds),
    * then an exception is thrown.
    * @param blk a reference to the disk block
    */
   synchronized void xLock(BlockId blk, Transaction tx) {

      try {
         long timestamp = System.currentTimeMillis();
         LinkedList<Transaction> list = getLockVal(blk);
         if (!list.isEmpty()) {
            if ((hasXlock(blk) || hasOtherSLocks(blk, tx)) && Math.abs(list.getFirst().getLocknum()) > Math.abs(tx.getLocknum()))
               wait(MAX_TIME);
            else if (Math.abs(list.getFirst().getLocknum()) < Math.abs(tx.getLocknum())){
               notifyAll();
               throw new LockAbortException();
            }
         }
         tx.setLocknum(tx.getLocknum()*(-1));
         list.add(tx);
         locks.put(blk, list);
      }
      catch(InterruptedException e) {
         throw new LockAbortException();
      }
   }
   
   /**
    * Release a lock on the specified block.
    * If this lock is the last lock on that block,
    * then the waiting transactions are notified.
    * @param blk a reference to the disk block
    */
   synchronized void unlock(BlockId blk, Transaction tx) {
      LinkedList<Transaction> val = getLockVal(blk);
      Iterator<Transaction> it = val.iterator();
      while (it.hasNext()) {
         if (Math.abs(it.next().getLocknum()) == Math.abs(tx.getLocknum())) {
            it.remove();
         }
         else {
            locks.remove(blk);
            notifyAll();
         }
      }
   }
   
   private boolean hasXlock(BlockId blk) {
      return !getLockVal(blk).isEmpty() && getLockVal(blk).getFirst().getLocknum() < 0;
   }
   
   private boolean hasOtherSLocks(BlockId blk, Transaction tx) {
      LinkedList<Transaction> val = getLockVal(blk);
      Iterator<Transaction> it = val.iterator();
      while (it.hasNext()) {
         if (it.next().getLocknum() < tx.getLocknum()) {
            return true;
         }
      }
      return false;
   }
   
   private boolean waitingTooLong(long starttime) {
      return System.currentTimeMillis() - starttime > MAX_TIME;
   }
   
   private LinkedList<Transaction> getLockVal(BlockId blk) {
      LinkedList<Transaction> ival = locks.get(blk);
      return (ival == null) ? new LinkedList<Transaction>() : ival;
   }
}
