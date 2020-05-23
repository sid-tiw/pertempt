package JAVA;

import java.util.*;

class Person {
	String name, userName, img, about, locUniv;

	Person() {
		name = new String("");
		userName = new String("");
		img = new String("");
		about = new String("");
		locUniv = new String("");
	}

	Person(Scanner sc) {
		name = sc.nextLine();
		userName = sc.nextLine();
		img = sc.nextLine();
		about = sc.nextLine();
		locUniv = sc.nextLine();
	}

	void inititalize(Scanner sc) {
		name = sc.nextLine();
		userName = sc.nextLine();
		img = sc.nextLine();
		about = sc.nextLine();
		locUniv = sc.nextLine();
	}
}