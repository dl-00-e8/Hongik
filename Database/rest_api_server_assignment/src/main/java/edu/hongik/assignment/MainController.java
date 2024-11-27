package edu.hongik.assignment;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MainController {

    @Autowired
    private final MainService mainService;

    public MainController(MainService mainService) {
        this.mainService = mainService;
    }

    @GetMapping("/students/degree")
    public String getDegreeByStudentName(@RequestParam(value = "name") String name) {
        try {
            return mainService.getDegreeByStudentName(name);
        } catch (IllegalArgumentException e) {
            return e.getMessage();
        }
    }
    
    @GetMapping("/students/email")
    public String getEmailByStudentName(@RequestParam(value = "name") String name) {
        try {
            return mainService.getEmailByStudentName(name);
        } catch (IllegalArgumentException e) {
            return e.getMessage();
        }
    }

    @GetMapping("/students/stat")
    public String getCountByDegree(@RequestParam(value = "degree") String degree) {
        try {
            return mainService.getCountByDegree(degree);
        } catch (IllegalArgumentException e) {
            return e.getMessage();
        }
    }

    @PutMapping("/students/register")
    public String registerStudent(@RequestParam(value = "name") String name,
                                  @RequestParam(value = "email") String email,
                                  @RequestParam(value = "degree") String degree,
                                  @RequestParam(value = "graduation") int graduation) {
        try {
            return mainService.registerStudent(name, email, degree, graduation);
        } catch (IllegalArgumentException e) {
            return e.getMessage();
        }
    }
}