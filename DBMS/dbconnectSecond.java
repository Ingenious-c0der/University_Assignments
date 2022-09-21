
import java.sql.* ;
import java.util.Scanner;


public class Main{
    public static boolean tableExist(Connection conn, String tableName) throws SQLException {
        boolean tExists = false;
        try (ResultSet rs = conn.getMetaData().getTables(null, null, tableName, null)) {
            while (rs.next()) {
                String tName = rs.getString("TABLE_NAME");
                if (tName != null && tName.equals(tableName)) {
                    tExists = true;
                    break;
                }
            }
        }
        return tExists;
    }

    public static void main(String[] args) {
        try{


            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/db","root","***");
            Statement smt = con.createStatement() ;
            boolean tExists = tableExist(con, "studentjdbc") ;
            Scanner sc = new Scanner(System.in);
            boolean loop = true;
            if(!tExists)
            {
                System.out.println("Table does not exist yet , creating the table" );
                smt.execute("create Table studentjdbc (name varchar(20), class int , rollno int NOT NULL,marks  int,PRIMARY KEY (rollno));");
            }
            while(loop)
            {
                System.out.println("*****MENU******\n1.Insert Student\n2.Update Student\n3.Delete Student\n4.View Students\n5.Exit\n: ");
                int choice = sc.nextInt();
                switch(choice)
                {
                    case 1:
                        System.out.println("Enter name of the student :");
                        sc.nextLine();
                        String name = sc.nextLine();
                        System.out.println("Enter class of the Student ");
                        int Class = sc.nextInt();
                        System.out.println("Enter Roll Number of the Student ");
                        int rollNo = sc.nextInt();
                        System.out.println("Enter Marks Number of the Student ");
                        int marks = sc.nextInt();
                        smt.execute("insert into studentjdbc values('"+name+"',"+Class+","+rollNo+","+marks+")");
                        break;
                    case 2:
                        System.out.println("Enter Roll Number of the Student ");
                        rollNo = sc.nextInt();
                        System.out.println("Enter new name of the student :");
                        sc.nextLine();
                        name = sc.nextLine();
                        System.out.println("Enter new class of the Student ");
                        Class = sc.nextInt();
                        System.out.println("Enter new Marks Number of the Student ");
                        try {
                            marks = sc.nextInt();
                            smt.execute("update studentjdbc set name = '" + name + "' , class = " + Class + " , marks = " + marks + " where rollno = " + rollNo + " ;");
                        }
                        catch(SQLException e)
                        {
                            System.out.println(e);
                        }

                        break;
                    case 3:
                        System.out.println("Enter Roll Number of the Student to be deleted");
                        rollNo = sc.nextInt();
                        smt.execute("delete from studentjdbc where rollno = "+rollNo+" ;");
                        break;
                    case 4:
                        ResultSet rs = smt.executeQuery("select * from studentjdbc");
                        while(rs.next())
                        {
                            System.out.println("Name : "+rs.getString(1) + " Class :" + rs.getInt(2) + " Roll No : "+rs.getInt(3) + " Marks : "+rs.getInt(4) );
                        }
                        break;
                    case 5:
                        loop = false;
                        break;


                }
            }
            sc.close();
            con.close();


        }catch(Exception e )
        {
            System.out.println(e);
        }
    }


}