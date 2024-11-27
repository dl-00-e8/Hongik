package edu.hongik.assignment;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataAccessException;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Repository;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

@Repository
public class MainJDBCRepository {

    @Autowired
    private JdbcTemplate jdbcTemplate;

    public void createStudentsTable() {
        String sql = "CREATE TABLE IF NOT EXISTS students(" +
            "sid SERIAL PRIMARY KEY," +
            "name VARCHAR(100) NOT NULL," +
            "email VARCHAR(255) NOT NULL," +
            "degree VARCHAR(255) NULL," +
            "graduation INT NOT NULL" +
            ")";
        jdbcTemplate.execute(sql);
    }

    public List<Student> getDegreeByStudentName(String name) {
        String sql = "SELECT name, email, degree, graduation FROM students WHERE name = ?";
        try {
            return jdbcTemplate.query(sql, new RowMapper<Student>() {
                @Override
                public Student mapRow(ResultSet rs, int rowNum) throws SQLException {
                    Student student = new Student();
                    student.setName(rs.getString("name"));
                    student.setEmail(rs.getString("email"));
                    student.setDegree(rs.getString("degree"));
                    student.setGraduation(rs.getInt("graduation"));
                    return student;
                }
            }, name);
        } catch (DataAccessException e) {
            return null;
        }
    }

    public List<Student> getEmailByStudentName(String name) {
        String sql = "SELECT name, email, degree, graduation FROM students WHERE name = ?";
        try {
            return jdbcTemplate.query(sql, new RowMapper<Student>() {
                @Override
                public Student mapRow(ResultSet rs, int rowNum) throws SQLException {
                    Student student = new Student();
                    student.setName(rs.getString("name"));
                    student.setEmail(rs.getString("email"));
                    student.setDegree(rs.getString("degree"));
                    student.setGraduation(rs.getInt("graduation"));
                    return student;
                }
            }, name);
        } catch (DataAccessException e) {
            return null;
        }
    }

    public String getCountByDegree(String degree) {
        String sql = "SELECT COUNT(*) FROM students WHERE degree = ?";
        return jdbcTemplate.queryForObject(sql, String.class, degree);
    }

    public List<Student> getStudentByNameAndEmailAndDegreeAndGraduation(String name, String email, String degree, int graduation) {
        String sql = "SELECT name, email, degree, graduation " +
                "FROM students " +
                "WHERE name = ? AND email = ? AND degree = ? AND graduation = ?";
        try {
            return jdbcTemplate.query(sql, new RowMapper<Student>() {
                @Override
                public Student mapRow(ResultSet rs, int rowNum) throws SQLException {
                    Student student = new Student();
                    student.setName(rs.getString("name"));
                    student.setEmail(rs.getString("email"));
                    student.setDegree(rs.getString("degree"));
                    student.setGraduation(rs.getInt("graduation"));
                    return student;
                }
            }, name, email, degree, graduation);
        } catch (EmptyResultDataAccessException e) {
            return null;
        }
    }

    public void registerStudent(String name, String email, String degree, int graduation) {
        String insert_sql = "INSERT INTO students(name, email, degree, graduation) " +
                "VALUES(?, ?, ?, ?)";
        jdbcTemplate.update(insert_sql, name, email, degree, graduation);
    }
}