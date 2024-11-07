package edu.hongik.dbms;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.jdbc.core.JdbcTemplate;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

@SpringBootApplication
public class DbmsApplication implements CommandLineRunner {

	@Autowired
	private JdbcTemplate jdbcTemplate;

	private String url;
	private Connection conn;

	public DbmsApplication() {
		url = "jdbc:postgresql://localhost:5432/hongik?user=postgres&password=1234&ssl=false";
		try {
			conn = DriverManager.getConnection(url);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		SpringApplication.run(DbmsApplication.class, args);
	}

	@Override
	public void run(String... args) throws Exception {
		Statement st = conn.createStatement();
		ResultSet rs = st.executeQuery("SELECT * FROM students");
		while(rs.next()) {
			System.out.println("Column 1 returned");
			System.out.println(rs.getString(1));
		}
		rs.close();
		st.close();

		String sql1 = "INSERT INTO students (name, email) VALUSE ("
				+ "'Nam Ha Minh', 'nam@codejava.net')";
		String sql2 = "SELECT COUNT(*) FROM students";

		int numOfStudents = jdbcTemplate.queryForObject(sql2, Integer.class);
		System.out.println("Total students: " + numOfStudents);

		int rows = jdbcTemplate.update(sql1);
		if (rows > 0) {
			System.out.println("A new row has been inserted.");
		}
	}
}
