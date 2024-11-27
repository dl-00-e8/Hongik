package edu.hongik.assignment;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
@Transactional(readOnly=true)
public class MainService {

    @Autowired
    private final MainJDBCRepository mainJDBCRepository;

    public MainService(MainJDBCRepository mainJDBCRepository) {
        this.mainJDBCRepository = mainJDBCRepository;
    }

    public String getDegreeByStudentName(String name) {
        List<Student> studentList = mainJDBCRepository.getDegreeByStudentName(name);

        if(studentList.isEmpty()) {
            throw new IllegalArgumentException("No such student");
        } else if(studentList.size() > 1) {
            throw new IllegalArgumentException("There are multiple students with the same name. Please provide an email address instead.");
        }

        return name + " : " + studentList.get(0).getDegree();
    }

    public String getEmailByStudentName(String name) {
        List<Student> studentList = mainJDBCRepository.getEmailByStudentName(name);

        if(studentList.isEmpty()) {
            throw new IllegalArgumentException("No such student");
        } else if(studentList.size() > 1) {
            throw new IllegalArgumentException("There are multiple students with the same name. Please contact the administrator by phone.");
        }

        // Response
        return name + " : " + studentList.get(0).getEmail();
    }

    public String getCountByDegree(String degree) {
        String count = mainJDBCRepository.getCountByDegree(degree);

        // Response
        return "Number of " + degree + " student : " + count;
    }

    @Transactional
    public String registerStudent(String name, String email, String degree, int graduation) {
        // Validation - 모든 데이터가 일치하면 동일인으로 간주
        List<Student> studentList = mainJDBCRepository.getStudentByNameAndEmailAndDegreeAndGraduation(name, email, degree, graduation);
        if(!studentList.isEmpty()) {
            throw new IllegalArgumentException("Already registered");
        }

        // Business Logic
        mainJDBCRepository.registerStudent(name, email, degree, graduation);

        // Response
        return "Registration successful";
    }
}