package simpleclient.embedded;

import java.io.FileWriter;
import java.io.IOException;
import java.sql.*;
import java.util.Scanner;

import au.com.bytecode.opencsv.CSVWriter;
import simpledb.jdbc.embedded.EmbeddedDriver;

public class Test_Cases_New {
    public static void main(String[] args) throws IOException {
        int i = 0;
        String csv = "data2.csv";
        String [] record = new String[1000];
        CSVWriter writer = null;
        try {
            writer = new CSVWriter(new FileWriter(csv, true));
        } catch (IOException e) {
            e.printStackTrace();
        }
        while (i!= 10) {
            long start_time = System.currentTimeMillis();
            Driver d = new EmbeddedDriver();
            String url = "jdbc:simpledb:studentdb";
            //creates student table
            /*long create_table_time = */
            System.out.println("Create");
            create_table_test(d, url);
            //selects one column
            /*long select_one_time = */
            System.out.println("Select");
            select_one_test(d, url);
            //selects multiple columns
            /*long select_multi_time = */
            System.out.println("Multi");
            select_multi_test(d, url);
            //does natural join of two tables, and selects multiple columns
            /*long select_join_time = */
            System.out.println("Join");
            cross_join_test(d, url);
            //changes value of Amy in the student table
            /*long update_time = */
            System.out.println("update");
            update_test(d, url);
            //inserts "jacob" into students, so I won't graduation until 2040
            /*long insert_time = */
            System.out.println("insert");
            insert_test(d, url);
            //deletes the entire table
            /*long delete_time = */
            System.out.println("Delete");
            delete_test(d, url);

            i++;
//        System.out.println("Create Time: " + create_table_time);
//        System.out.println("Select One Time: " + select_one_time);
//        System.out.println("Select Multiple Time: " + select_multi_time);
//        System.out.println("Select Join Time: " + select_join_time);
//        System.out.println("Update Time: " + update_time);
//        System.out.println("Insert Time: " + insert_time);
//        System.out.println("Delete Time: " + delete_time);
            long end_time = System.currentTimeMillis();
            long run_time = end_time - start_time;
            writer.writeNext(String.valueOf(run_time));

        }
        writer.close();
    }

    public static void create_table_test(Driver d, String url) {
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement()) {
            String s = "create table STUDENT(SId int, SName varchar(10), MajorId int, GradYear int)";
            stmt.executeUpdate(s);

            s = "insert into STUDENT(SId, SName, MajorId, GradYear) values ";
            String[] studvals = {"(1, 'joe', 10, 2021)",
                    "(2, 'amy', 20, 2020)",
                    "(3, 'max', 10, 2022)",
                    "(4, 'sue', 20, 2022)",
                    "(5, 'bob', 30, 2020)",
                    "(6, 'kim', 20, 2020)",
                    "(7, 'art', 30, 2021)",
                    "(8, 'pat', 20, 2019)",
                    "(9, 'lee', 10, 2021)"};
            for (int i = 0; i < studvals.length; i++)
                stmt.executeUpdate(s + studvals[i]);

            s = "create table DEPT(DId int, DName varchar(8))";
            stmt.executeUpdate(s);

            s = "insert into DEPT(DId, DName) values ";
            String[] deptvals = {"(10, 'compsci')",
                    "(20, 'math')",
                    "(30, 'drama')"};
            for (int i = 0; i < deptvals.length; i++)
                stmt.executeUpdate(s + deptvals[i]);

            s = "create table COURSE(CId int, Title varchar(20), DeptId int)";
            stmt.executeUpdate(s);

            s = "insert into COURSE(CId, Title, DeptId) values ";
            String[] coursevals = {"(12, 'db systems', 10)",
                    "(22, 'compilers', 10)",
                    "(32, 'calculus', 20)",
                    "(42, 'algebra', 20)",
                    "(52, 'acting', 30)",
                    "(62, 'elocution', 30)"};
            for (int i = 0; i < coursevals.length; i++)
                stmt.executeUpdate(s + coursevals[i]);

            s = "create table SECTION(SectId int, CourseId int, Prof varchar(8), YearOffered int)";
            stmt.executeUpdate(s);

            s = "insert into SECTION(SectId, CourseId, Prof, YearOffered) values ";
            String[] sectvals = {"(13, 12, 'turing', 2018)",
                    "(23, 12, 'turing', 2019)",
                    "(33, 32, 'newton', 2019)",
                    "(43, 32, 'einstein', 2017)",
                    "(53, 62, 'brando', 2018)"};
            for (int i = 0; i < sectvals.length; i++)
                stmt.executeUpdate(s + sectvals[i]);

            s = "create table ENROLL(EId int, StudentId int, SectionId int, Grade varchar(2))";
            stmt.executeUpdate(s);

            s = "insert into ENROLL(EId, StudentId, SectionId, Grade) values ";
            String[] enrollvals = {"(14, 1, 13, 'A')",
                    "(24, 1, 43, 'C' )",
                    "(34, 2, 43, 'B+')",
                    "(44, 4, 33, 'B' )",
                    "(54, 4, 53, 'A' )",
                    "(64, 6, 53, 'A' )"};
            for (int i = 0; i < enrollvals.length; i++)
                stmt.executeUpdate(s + enrollvals[i]);


        } catch (SQLException e) {
            e.printStackTrace();
        }

    }


    public static void cross_join_test(Driver d, String url) {
        String major = "math";

        String qry = "select sname, gradyear "
                + "from student, dept "
                + "where did = majorid "
                + "and dname = '" + major + "'";
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(qry)) {
            while (rs.next()) {
                String sname = rs.getString("sname");
                int gradyear = rs.getInt("gradyear");
                System.out.println(sname + "\t" + gradyear);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void select_one_test(Driver d, String url) {

        String major = "math";

        String qry = "select Sname from student";
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(qry)) {
            while (rs.next()) {
                String sname = rs.getString("sname");
                System.out.println(sname);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static void select_multi_test(Driver d, String url) {
        String major = "math";

        String qry = "select Sname, SId from student";
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(qry)) {
            while (rs.next()) {
                String sname = rs.getString("sname");
                int SId = rs.getInt("SId");
                System.out.println(sname + ", " + SId);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static void update_test(Driver d, String url) {
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement()) {
            String cmd = "update STUDENT "
                    + "set MajorId=30 "
                    + "where SName = 'amy'";
            stmt.executeUpdate(cmd);
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static void insert_test(Driver d, String url) {
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement()) {
            String cmd = "insert into STUDENT(SId, SName, MajorId, GradYear) values"
                    + "(21, 'jacob', 10, 2040)";
            stmt.executeUpdate(cmd);
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void delete_test(Driver d, String url) {
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement()) {
            String cmd = "delete from STUDENT";
            stmt.executeUpdate(cmd);
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
