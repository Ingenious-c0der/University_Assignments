
import java.sql.*; 
import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.*;
/**
 * Servlet implementation class SubmitServlet
 */
public class SubmitServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private Connection con; 
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public SubmitServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see Servlet#init(ServletConfig)
	 */
	public void init(ServletConfig config) throws ServletException {
		// TODO Auto-generated method stub

	}
	/**
	 * @see Servlet#destroy()
	 */
	public void destroy() {
		// TODO Auto-generated method stub
	}

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
//		PrintWriter pw = response.getWriter();
//		String sqlQuery = "select * from tomcat_user_table where username = "+ request.getParameter("t1");
//		String url = "jdbc:mysql://localhost:3306/db";
//		String username = "root";
//		String password = "Snowbell2002$";
//		try {
//			String dbDriver = "com.mysql.cj.jdbc.Driver";
//			Class.forName(dbDriver);
//			this.con = DriverManager.getConnection(url,username,password);
//			PreparedStatement ps = this.con.prepareStatement(sqlQuery);
//			ResultSet rs = ps.executeQuery();
//			if(rs.next())
//			{
//				if(request.getParameter("p1") == rs.getString(2))
//				{
//					
//					pw.println("<h1>User "+request.getParameter("t1")+" logged in successfully!</h1>") ;
//				}
//				else {
//					pw.println("<h1> Incorrect Password Provided </h1>");
//				}
//			}
//			else
//			{
//				String s = request.getParameter("t1");
//				pw.println("<h1>User with user name "+ s +"not found</h1>");
//			}
//		} catch (SQLException | ClassNotFoundException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} 
//		
//		pw.close();
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		PrintWriter pw = response.getWriter();
		String username = request.getParameter("t1");
		String sqlQuery = "select * from tomcat_user_table where username = \""+username+"\"";
		String url = "jdbc:mysql://localhost:3306/db";
		String admin_username = "root";
		String password = "********";
		try {
			String dbDriver = "com.mysql.cj.jdbc.Driver";
			Class.forName(dbDriver);
			this.con = DriverManager.getConnection(url,admin_username,password);
			PreparedStatement ps = this.con.prepareStatement(sqlQuery);
			ResultSet rs = ps.executeQuery();
			if(rs.next())
			{
				String password_given = request.getParameter("p1"); 
				String password_actual = rs.getString(3);

				if(password_given.equals(password_actual))
				{
					pw.println("<h1>User "+request.getParameter("t1")+" logged in successfully!</h1>") ;
				}
				else {
					pw.println("<h1> look at this  "+password_given.compareTo(password_actual)+"</h1>");
					pw.println("<h1> "+rs.getString(3)+" </h1>");
					pw.println("<h1> "+request.getParameter("p1")+" </h1>");
					pw.println("<h1> Incorrect Password Provided </h1>");
				}
			}
			else
			{
				String s = request.getParameter("t1");
				pw.println("<h1>User with user name "+ s +" not found</h1>");
			}
		} catch (SQLException | ClassNotFoundException e) {
			// TODO Auto-generated catch block
			pw.println("Error lol");
			e.printStackTrace();
		} 
		
		pw.close();
	}

}
