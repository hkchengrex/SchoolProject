#include "menu.h"
#include <iostream>

using namespace std;

void mainMenu(){
	cout << "Welcome to HKUST Course Registration System" << endl;
	cout << "===========================================" << endl << endl;

	cout << "1:\t" << "Student Menu" << endl;
	cout << "2:\t" << "Course Menu" << endl;
	cout << "3:\t" << "Course Registration" << endl;
	cout << "4:\t" << "Report Generation" << endl;
	cout << "5:\t" << "File I/O" << endl;
	cout << "6:\t" << "Exit" << endl << endl;

	cout << "Enter your choice (1-" << MAIN_MENU_SIZE << "): ";

	int choice = -1;

	do{
		cin >> choice;

		if (choice <= 0 || choice > MAIN_MENU_SIZE){
			cout << "Invalid input, please try again: " << endl;
		}else{
			break;
		}
	}while(true);

	l2_Menu(choice-1);
}

void l2_Menu(int item){
	int max = 0;

	switch(item){
		case 0:
			cout << "Student Menu" << endl;
			cout << "===========================================" << endl << endl;

			cout << "1:\t" << "Insert a new student" << endl;
			cout << "2:\t" << "Modify existing student record" << endl;
			cout << "3:\t" << "Delete an existing student record" << endl;
			cout << "4:\t" << "Search for an existing student" << endl;
			cout << "5:\t" << "Return to main menu" << endl;

			cout << "Enter your choice (1-" << L2_1_MENU_SIZE << "): ";
			max = L2_1_MENU_SIZE;
		break;

		case 1:
			cout << "Course Menu" << endl;
			cout << "===========================================" << endl << endl;

			cout << "1:\t" << "Insert a new course" << endl;
			cout << "2:\t" << "Modify existing course record" << endl;
			cout << "3:\t" << "Delete an existing course record" << endl;
			cout << "4:\t" << "Search for an existing course" << endl;
			cout << "5:\t" << "Return to main menu" << endl;

			cout << "Enter your choice (1-" << L2_2_MENU_SIZE << "): ";
			max = L2_2_MENU_SIZE;
		break;

		case 2:
			cout << "Course Registration" << endl;
			cout << "===========================================" << endl << endl;

			cout << "1:\t" << "Add a course for a student" << endl;
			cout << "2:\t" << "Drop a course for a student" << endl;
			cout << "3:\t" << "Modify the exam mark of a course for a student" << endl;
			cout << "4:\t" << "Search for an registration record" << endl;
			cout << "5:\t" << "Return to main menu" << endl;

			cout << "Enter your choice (1-" << L2_3_MENU_SIZE << "): ";
			max = L2_3_MENU_SIZE;
		break;

		case 3:
			cout << "Report Generation" << endl;
			cout << "===========================================" << endl << endl;

			cout << "1:\t" << "List all student information" << endl;
			cout << "2:\t" << "List all course information" << endl;
			cout << "3:\t" << "List all the courses of a student" << endl;
			cout << "4:\t" << "List all the students of a course" << endl;
			cout << "5:\t" << "Return to main menu" << endl;

			cout << "Enter your choice (1-" << L2_4_MENU_SIZE << "): ";
			max = L2_4_MENU_SIZE;
		break;

		case 4:
			cout << "Report Generation" << endl;
			cout << "===========================================" << endl << endl;

			cout << "1:\t" << "Save all the data in the database to a file" << endl;
			cout << "2:\t" << "Load the data from a file" << endl;
			cout << "3:\t" << "Return to main menu" << endl;

			cout << "Enter your choice (1-" << L2_5_MENU_SIZE << "): ";
			max = L2_5_MENU_SIZE;
		break;

		case 5:
			exit(0);
		break;
	}

	do{
		cin >> choice;

		if (choice <= 0 || choice > MAIN_MENU_SIZE){
			cout << "Invalid input, please try again: " << endl;
		}else{
			break;
		}
	}while(true);
}
