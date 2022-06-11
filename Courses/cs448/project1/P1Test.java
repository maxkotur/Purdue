package simpledb.buffer;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;


import simpledb.server.SimpleDB;
import simpledb.file.*;

import javax.swing.*;
import java.io.PrintWriter;
import java.util.*;

public class P1Test {
   private static Map<BlockId,Buffer> buffs = new HashMap<>();
   private static BufferMgr bm;
   
   public static void main(String args[]) throws Exception {

//      pinBuffer(0); pinBuffer(1); pinBuffer(2); pinBuffer(3);
//      pinBuffer(4); pinBuffer(5); pinBuffer(6); pinBuffer(7);
////      bm.printStatus();
//      unpinBuffer(2); unpinBuffer(0); unpinBuffer(5); unpinBuffer(4);
////      bm.printStatus();
//      pinBuffer(8); pinBuffer(5); pinBuffer(7);
////      bm.printStatus();
      try {
         FileWriter fw = new FileWriter("original.csv",true);
         BufferedWriter bw = new BufferedWriter(fw);
         PrintWriter pw = new PrintWriter(bw);
         pw.println("Intial Pin,Second Pin,Final Unpin");
         for (int num = 0; num < 10; num++){
            SimpleDB db = new SimpleDB("buffermgrtest", 400, 1000);
            bm = db.bufferMgr();
            long start_firstpin = System.currentTimeMillis();
            for (int i = 0; i < 1000; i++) {
               pinBuffer(i);
            }
            long end_firstpin = System.currentTimeMillis();
            long start_searchpin = System.currentTimeMillis();
            for (int i = 0; i < 1000; i++) {
               pinBuffer(i);
            }
            long end_searchpin = System.currentTimeMillis();
            long start_unpin = System.currentTimeMillis();
            for (int i = 0; i < 1000; i++) {
               unpinBuffer(i);
            }
            long end_unpin = System.currentTimeMillis();
            long totalfirst = end_firstpin - start_firstpin;
            long totalsearch = end_searchpin - start_searchpin;
            long totalunpin = end_unpin - start_unpin;
//         System.out.println("First pin: "+totalfirst);
//         System.out.println("Search pin: "+totalsearch);
//         System.out.println("Final unpin: "+totalunpin);
            pw.println(totalfirst+","+totalsearch+","+totalunpin);
         }
         pw.flush();
         pw.close();
         JOptionPane.showMessageDialog(null, "saved");
      }
      catch (Exception e) {
         JOptionPane.showMessageDialog(null, "failed");
      }

   }
   
   private static void pinBuffer(int i) {
      BlockId blk = new BlockId("test", i);
      Buffer buff = bm.pin(blk);
      buffs.put(blk, buff);
      System.out.println("Pin block " + i);
   }
   
   private static void unpinBuffer(int i) {
      BlockId blk = new BlockId("test", i);
      Buffer buff = buffs.remove(blk);
      bm.unpin(buff);
      System.out.println("Unpin block " + i);
   }
}
