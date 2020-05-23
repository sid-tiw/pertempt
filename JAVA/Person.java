package JAVA;

import java.io.FileReader;
import java.io.IOException;

class Person {
	String name, userName, img, about, locUniv;

	Person() {
		name = new String("");
		userName = new String("");
		img = new String("");
		about = new String("");
		locUniv = new String("");
	}

	String parse(FileReader flst) throws IOException {
		String temp = new String("");
		int ch;
		ch = flst.read();
		while (ch != '\n') {
			temp += (char) ch;
			ch = flst.read();
		}
		return temp;
	}

	Person(FileReader sc) throws IOException {
		name = parse(sc);
		userName = parse(sc);
		img = parse(sc);
		about = parse(sc);
		locUniv = parse(sc);
	}

	void inititalize(FileReader sc) throws IOException{
		name = parse(sc);
		userName = parse(sc);
		img = parse(sc);
		about = parse(sc);
		locUniv = parse(sc);
	}

	void printDetails() {
		System.out.println("--------------------");
		System.out.println("Name: " + name);
		System.out.println("userid: " + userName);
		System.out.println("img: " + img);
		System.out.println("--------------------");
	}
}