package embedded;

import java.io.FileWriter;
import java.io.IOException;
import java.sql.*;
import java.util.Scanner;

//import au.com.bytecode.opencsv.CSVWriter;
import simpledb.jdbc.embedded.EmbeddedDriver;

public class Project3Tests {
    private static Driver d;
    private static String url;

    public static void main(String[] args) throws IOException {

        d = new EmbeddedDriver();
        url = "jdbc:simpledb:studentdb";
        create_table_test(d, url);
        //

        //
        //long start_time = System.currentTimeMillis();

        test1 t1 = new test1(); new Thread(t1).start();

        test2 t2 = new test2(); new Thread(t2).start();
        test2 t3 = new test2(); new Thread(t3).start();
        test2 t4 = new test2(); new Thread(t4).start();
        //test2 t5 = new test2(); new Thread(t5).start();
        //test2 t6 = new test2(); new Thread(t6).start();
        //test2 t7 = new test2(); new Thread(t7).start();
        //test2 t8 = new test2(); new Thread(t8).start();
        //test2 t9 = new test2(); new Thread(t9).start();

        //long end_time = System.currentTimeMillis();		//TODO: Wait before this?

        //test1 t1 = new test1(); new Thread(t1).start();
    }

    static class test1 implements Runnable {
        public void run() {
            long start_time = System.currentTimeMillis();
            for (int i = 0; i < 10; i++) {
                select_all_test(d, url);
                select_multi_test(d, url);		// if only use reads, this finishes before slowdown
                cross_join_test(d, url);
                update_test(d, url);			// with writes, it finishes after
                insert_test(d, url);
            }
            long end_time = System.currentTimeMillis();
            long time = end_time - start_time;
            System.out.println("long guy done in time: " + time);
        }
    }

    static class test2 implements Runnable {
        public void run() {

            //update_test(d, url);
            //select_one_test(d, url);
            //for (int i = 0; i < 10; i++) {
            insert_test(d, url);
            //}
            //select_multi_test(d, url);

        }
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
                    "(9, 'lee', 10, 2021)",
                    "(12, 'amy', 20, 2020)",
                    "(13, 'max', 10, 2022)",
                    "(14, 'sue', 20, 2022)",
                    "(15, 'bob', 30, 2020)",
                    "(16, 'kim', 20, 2020)",
                    "(17, 'art', 30, 2021)",
                    "(18, 'pat', 20, 2019)",
                    "(22, 'amy', 20, 2020)",
                    "(23, 'max', 10, 2022)",
                    "(24, 'sue', 20, 2022)",
                    "(25, 'bob', 30, 2020)",
                    "(26, 'kim', 20, 2020)",
                    "(27, 'art', 30, 2021)",
                    "(28, 'pat', 20, 2019)",
                    "(32, 'amy', 20, 2020)",
                    "(33, 'max', 10, 2022)",
                    "(34, 'sue', 20, 2022)",
                    "(35, 'bob', 30, 2020)",
                    "(36, 'kim', 20, 2020)",
                    "(37, 'art', 30, 2021)",
                    "(38, 'pat', 20, 2019)",
                    "(39, 'lee', 10, 2021)",
                    "(42, 'amy', 20, 2020)",
                    "(43, 'max', 10, 2022)",
                    "(44, 'sue', 20, 2022)",
                    "(45, 'bob', 30, 2020)",
                    "(46, 'kim', 20, 2020)",
                    "(47, 'art', 30, 2021)",
                    "(48, 'pat', 20, 2019)",
                    "(52, 'amy', 20, 2020)",
                    "(53, 'max', 10, 2022)",
                    "(54, 'sue', 20, 2022)",
                    "(55, 'bob', 30, 2020)",
                    "(56, 'kim', 20, 2020)",
                    "(57, 'art', 30, 2021)",
                    "(58, 'pat', 20, 2019)"};
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
                //System.out.println(sname + "\t" + gradyear);
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
                //System.out.println(sname);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static void select_all_test(Driver d, String url) {

        String qry = "select SId, SName, MajorId, GradYear from student";
        try (Connection conn = d.connect(url, null);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(qry)) {
            while (rs.next()) {
                String sname = rs.getString("sname");
                //System.out.println(sname);
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
                //System.out.println(sname + ", " + SId);
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