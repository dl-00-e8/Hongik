package student;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

class StudentManagerTest {
	
	StudentManager studentManager;

	@BeforeEach
	void setUp() throws Exception {
		studentManager = new StudentManager();
	}

	@Test
	void testAdd() {
		// given
		String studentName = "test";
		
		// when
		studentManager.addStudent(studentName);
		
		// then
		assertTrue(studentManager.hasStudent(studentName));
	}
	
	@Test
	void testRemove() {
		// given
		String studentName = "test";
		studentManager.addStudent(studentName);
		
		// when
		studentManager.removeStudent(studentName);
		
		// then
		assertFalse(studentManager.hasStudent(studentName));
		
	}
	
	@Test
	void testDuplicate() {
		// given
		String studentName = "test";
//		studentManager.addStudent(studentName);
		
		// when & then
		assertThrows(IllegalArgumentException.class,() -> {
			studentManager.addStudent(studentName);
		}, "Exception이 발생하지 않았습니다.");
	}
	
	@Test
	void testNotfound() {
		// given
		String studentName = "test";
		studentManager.addStudent(studentName);
		
		// when
		assertThrows(IllegalArgumentException.class,() -> {
			studentManager.removeStudent(studentName);
		}, "Exception이 발생하지 않았습니다.");
	}

}
