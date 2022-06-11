package simpledb.plan;

import simpledb.metadata.MetadataMgr;
import simpledb.parse.QueryData;
import simpledb.query.Scan;
import simpledb.record.Schema;
import simpledb.tx.Transaction;

/** A Plan class corresponding to the <i>product</i>
  * relational algebra operator that determines the
  * most efficient ordering of its inputs.
  * @author Edward Sciore
  */
public class OptimizedProductPlan implements Plan {
   private Plan bestplan;

   public OptimizedProductPlan(Plan p1, Plan p2, QueryData data) {
   		Plan prod1 = new ProductPlan(p1, p2);
   		Plan prod2 = new ProductPlan(p2, p1);
   		Plan prod3 = new ProductPlan2(p1,p2, data.pred().getTerms());
   		int b1 = prod1.blocksAccessed();
   		int b2 = prod2.blocksAccessed();
   		int b3 = prod3.blocksAccessed();
   		bestplan = prod3;
         // bestplan = (b1 < b2) ? prod1 : prod2;
        // bestplan = prod3;   //find the best plan comparing between b1,b2 and b3
       //System.out.println("blocks accessed b2: " + b2);
       //System.out.println("blocks accessed b3: " + b3);
   }

   public Scan open() {
      return bestplan.open();
   }
   
   public int blocksAccessed() {
      return bestplan.blocksAccessed();
   }

   public int recordsOutput() {
      return bestplan.recordsOutput();
   }

   public int distinctValues(String fldname) {
      return bestplan.distinctValues(fldname);
   }

   public Schema schema() {
      return bestplan.schema();
   }

    @Override
    public String getTblname() {
        return null;
    }
}
