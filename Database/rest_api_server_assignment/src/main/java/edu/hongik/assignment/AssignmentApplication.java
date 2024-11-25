package edu.hongik.assignment;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.util.ArrayList;
import java.util.List;

@SpringBootApplication
public class AssignmentApplication implements CommandLineRunner {

	@Autowired
	private MainJDBCRepository mainJDBCRepository;

	public static void main(String[] args) {
		SpringApplication.run(AssignmentApplication.class, args);
	}

	// 모든 Bean 초기화 및 의존성 주입이 완료된 이후에 호출되는 메소드
	@Override
	public void run(String... args) throws Exception {
		// 데이터베이스 테이블 생성
		mainJDBCRepository.createStudentsTable();

		// Jsoup 라이브러리를 사용하여 웹 페이지 파싱
		List<Student> students = new ArrayList<>();
		String url = "https://apl.hongik.ac.kr/lecture/dbms";
		Document document = Jsoup.connect(url).get();

		// <div> 파싱
		Elements elements = document.selectXpath("/html/body/div[1]/div[2]/div[2]/div[3]/div/div[1]/section[3]/div[2]/div/div/div/div/div/div/div/div");
		Elements h2Elements = elements.select("h2");
		Elements ulElements = elements.select("ul");
		if(h2Elements.size() == ulElements.size()) {
			// Elements 사이즈마다 학생 정보 파싱하여 구조체 생성
			for(int i = 0; i < h2Elements.size(); i++) {
				String h2Text = h2Elements.get(i).text();
				String degree = switch (h2Text) {
					case "PhD Students" -> "PhD";
					case "Master Students" -> "Master's";
					case "Undergraduate Students" -> "Undergraduate";
                    default -> throw new IllegalStateException("Unexpected value: " + h2Text);
                };

				// <li> 파싱해서 Student 객체 생성 및 ArrayList 추가
				Elements liElements = ulElements.get(i).select("li");
				for(Element liElement : liElements) {
					String liText = liElement.text();
					String[] studentInfo = liText.split(", ");

					Student student = new Student();
					student.setName(studentInfo[0]);
					student.setEmail(studentInfo[1]);
					student.setDegree(degree);
					student.setGraduation(Integer.parseInt(studentInfo[2]));
					students.add(student);
				}

			}
		}

		// Parsing 학생 정보 DB 삽입
		for(Student student : students) {
			mainJDBCRepository.registerStudent(student.getName(), student.getEmail(), student.getDegree(), student.getGraduation());
		}

		System.out.println("Jsoup parsing and DB insertion complete");
	}
}
