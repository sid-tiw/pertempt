package JAVA;

import java.util.*;
import java.io.FileReader;
import java.io.IOException;

class Main {
	public static void main(String[] arg) throws IOException, InterruptedException {
		Scanner stdin = new Scanner(System.in);
		String userName, toSearch;
		System.out.print("Enter your gh user-name: ");
		userName = stdin.nextLine();
		System.out.print("Enter the name to search: ");
		toSearch = stdin.nextLine();
		Process pr = Runtime.getRuntime().exec("./CPP/pertempt " + userName);
		pr.waitFor();
		FileReader mainFile = new FileReader("/home/sidtiw/Desktop/stlist.imd");
		Person pers = new Person(mainFile);
		pers.printDetails();
		mainFile.close();
		stdin.close();
	}
}