package simpledb.query;


/**
 * Write your own version of join algorithm here
 */
public class ProductScan2 implements Scan {
   private Scan s1;
   private Scan s2;
    private String fldname1, fldname2;


   public ProductScan2(Scan s1, Scan s2, String fldname1, String fldname2) {
	  this.s1 = s1;
	  this.s2 = s2;
	  this.fldname1 = fldname1;
	  this.fldname2 = fldname2;
      beforeFirst();
   }


   public void beforeFirst() {
	  s1.beforeFirst();
	  s2.beforeFirst();
   }


   public boolean next() {
       boolean hasmore2;
       boolean hasmore1 = s1.next();
       while (hasmore1) {
           s2.beforeFirst();
           hasmore2 = s2.next();
           while (hasmore2) {
               Constant v1 = s1.getVal(fldname1);
               Constant v2 = s2.getVal(fldname2);
               if (v1.compareTo(v2) == 0){
                   return true;
               }
               hasmore2 = s2.next();
           }
           hasmore1 = s1.next();
       }

       return false;
   }


   public int getInt(String fldname) {
       if (s1.hasField(fldname))
           return s1.getInt(fldname);
       else
           return s2.getInt(fldname);
   }

   public String getString(String fldname) {
       if (s1.hasField(fldname))
           return s1.getString(fldname);
       else
           return s2.getString(fldname);
   }

   public Constant getVal(String fldname) {
	  if (s1.hasField(fldname))
	     return s1.getVal(fldname);
	  else
	     return s2.getVal(fldname);   
   }


   public boolean hasField(String fldname) {
      return s1.hasField(fldname) || s2.hasField(fldname);
   }

   public void close() {
      s1.close();
      s2.close();
   }
}
