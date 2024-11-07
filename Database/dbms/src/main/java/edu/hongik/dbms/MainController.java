package edu.hongik.dbms;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.sql.Connection;
import java.sql.DriverManager;

@Controller
@RequestMapping("/hongik")
public class MainController {

    @Autowired
    private JdbcTemplate jdbcTemplate;
    private String url;
    private Connection conn;

    public MainController() {
        url = "jdbc:postgresql://localhost:5432/hongik?user=postgres&password=1234&ssl=false";
        try {
            conn = DriverManager.getConnection(url);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @GetMapping("/update")
    @ResponseBody
    public String updatePerson(
            @RequestParam(value="x1") String x1,
            @RequestParam(value="x2") String x2
    ) {
        System.out.println("update to updateperson html" + x1 + " " + x2);

        return "updateperson";
    }

    @GetMapping("/hello")
    @ResponseBody
    public String helloWorld() {
        return "Hello, World!";
    }

    @GetMapping("/sqlselect")
    public String response() {
        return "Hello, World!";
    }

    @GetMapping("/getemail")
    @ResponseBody
    public int getEmail() {
        System.out.println("hello email");
        String sql2 = "SELECT COUNT(*) FROM students";

        int numOfStudents = jdbcTemplate.queryForObject(sql2, Integer.class);
        System.out.println("Total students: " + numOfStudents);
        return numOfStudents;
    }
}
