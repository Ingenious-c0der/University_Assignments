<%@ page import = "java.io.*,java.util.*,java.sql.*"%>
<%@ page import = "jakarta.servlet.http.*,jakarta.servlet.*" %>

<!DOCTYPE html>
<html>
<head>
<meta charset="ISO-8859-1">
<title>First Servlet!</title>
 <head>
 </head>
 <body>
  <%
  String url = "jdbc:mysql://localhost:3306/db";
	String username = "root";
	String password = "**********";
  Class.forName("com.mysql.cj.jdbc.Driver"); 
  Connection con = DriverManager.getConnection(
		  url,username,password
		  );
      
  String sql = "select * from tomcat_user_table;"; 
  Statement st = con.createStatement();
  ResultSet rs = st.executeQuery(sql); 

  
  %>
  <% while (rs.next())
  {
	  %>
	   Roll no : <%= rs.getString(1) %> <br>
 	   Name : <%=rs.getString(2) %> <br>
	  <%
  }	  
  %>

 </body>
</html>