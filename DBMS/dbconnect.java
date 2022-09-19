package com.company;

import java.sql.* ;
import java.util.Random;

public class Main {
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
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/db","root","*****");
        Statement smt = con.createStatement() ;
        boolean tExists = tableExist(con, "newareas") ;

        if(!tExists)
        {
            System.out.println("Table does not exist yet , creating the table" );
            smt.execute("create Table newareas (radius decimal(10,4),area decimal(10,5));");

            Random rand = new Random();

            for(int i  = 0 ; i<100; i++)
            {
                Float radius = rand.nextFloat(1,100);
                double area = 3.14*radius*radius;
                smt.execute("insert into newareas values("+radius+","+area+");");

            }

        }

        ResultSet rs = smt.executeQuery("select * from newareas");
        while(rs.next())
        {
            System.out.println("Radius : "+rs.getDouble(1) + " Area :" + rs.getDouble(2) );
        }
        con.close();


    }catch(Exception e )
    {
        System.out.println(e.getMessage());
    }
    }
}
