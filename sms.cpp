#include <iostream> //for std::cout, std::cin, std::endl, std::invalid_argument
#include <cstdlib>
#include <string> //for std::stoi (string to integer), used for converting a string to an integer
#include <vector> //for implementing a vector (dynamic array)
#include <cctype> //for tolower()
using namespace std;

class Student
{
private:
	int age, id;
	string name;

public:
	Student(int iId, string iName, int iAge) : id(iId), name(iName), age(iAge) {}
	void setAge(int newAge) { age = newAge; }
	void setId(int newId) { id = newId; }
	void setName(string newName) { name = newName; }

	int getAge(void) const { return age; }
	int getId(void) const { return id; }
	string getName(void) const { return name; }
	friend ostream& operator<<(ostream& outstream, const Student& student);

};
void displayMenu(void);
void addStudent(vector<Student>& students);
void displayAllStudents(const vector<Student>& students);
void searchStudent(const vector<Student>& students, string search);
void updateStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);

ostream& operator<<(ostream& outstream, const Student& student); //overloads the << operator to output all info of a particular student.

int main(int argc, char* argv[])
{
	vector<Student> students;
	int choice{}; // list initialization: to prevent narrowing conversions
	string student_info;
	//students.push_back(Student(1, "Mojami", 19));
	//cout << students.at(0);
	do
	{
		displayMenu();
		while ((cout << "Enter Your Choice: ") && (!(cin >> choice) || (choice < 1) || (choice > 6)))
		{
			cout << "Invalid input! Try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

		}
		switch (choice)
		{
		case 1:
			char repeat;
			do
			{
				addStudent(students);
				cout << students.back();
				cout << "Would you like to add another student? (y/n): ";
				while (!(cin >> repeat) || tolower(repeat) != 'y' && tolower(repeat) != 'n')
				{
					cout << "Invalid input! Please try again: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			} while (repeat == 'y'); //allows user to repeatedly add students in one go rather than one at a time.
			break;

		case 2:
			displayAllStudents(students); // displays all students with a line of asteriks separating each of them.
			break;
		case 3:
			cout << "Please enter the name or id of the student you are searching for: ";
			cin >> student_info;
			searchStudent(students, student_info);
			break;
		case 4:
			updateStudent(students);
			break;
		case 5:
			deleteStudent(students);
		}


	} while (choice != 6);

	return 0;
}

void displayMenu(void)
{
	cout << "******** Student Management System ********" << endl;
	cout << "1: Add New Student" << endl;
	cout << "2: Display All Students" << endl;
	cout << "3: Search Student" << endl;
	cout << "4: Update Student Info" << endl;
	cout << "5. Delete Student From System" << endl;
	cout << "6. Exit" << endl;
}

ostream& operator<<(ostream& outstream, const Student& student) 
{
	outstream << "ID: " << student.getId() << endl << "Name: " << student.getName() << endl << "Age: " << student.getAge() << endl;
	return outstream;
}

void addStudent(vector<Student>& students)
{
	int age, id;
	string name;
	cout << "Enter new student's ID: ";
	cin >> id;
	cout << "Enter new student's name: ";
	cin >> name;
	cout << "Enter new student's age: ";
	cin >> age;
	Student newStudent(id, name, age);
	students.push_back(newStudent);
	cout << "Student added successfully." << endl;

}

void displayAllStudents(const vector<Student>& students)
{
	for (auto student : students) 
	{
		cout << "********" << endl;
		cout << student;
	}
	return;
}
void searchStudent(const vector<Student>& students, string search)
{
	bool found = false;
	cout << "Initiating student search..." << endl;
	try //first takes the input and attempts to read it as an integer (if the user inputted an ID number)
	{
		int id = stoi(search);
		for (auto student : students)
		{
			if (id == student.getId())
			{
				cout << "Student found!" << endl << student; //displays all students with that name/id
				found = true;
			}
		}
	}
	catch (invalid_argument&) // if an error is thrown (the user inputted a string), it is caught and this block of code runs instead (reads input as a string and compares name to all names in database).
	{
		for (auto student : students)
		{
			if (search == student.getName())
			{
				cout << "Student found!" << endl << student;
				found = true;
			}
		}
	}

	if (!found) cout << "No student found with the name or ID: " << search << endl;
	return;

}
void updateStudent(vector<Student>& students)
{
	int id;
	int choice{};
	int newId;
	int newAge;
	string newName;
	bool found = false;

	cout << "Enter ID of student whose info you'd like to change: ";
	cin >> id;
	for ( auto& student : students)
	{
		if (id == student.getId())
		{
			found = true;
			cout << "Student found:" << endl << student;
			cout << "1. Update ID" << endl;
			cout << "2. Update Name" << endl;
			cout << "3. Update Age" << endl;
			while (cout << "Enter your choice: " && !(cin >> choice) || (choice > 3 && choice < 1))
			{
				cout << "Invalid input! Try again: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			switch (choice)
			{
			case 1:
				cout << "Enter new ID: ";
				cin >> id;
				student.setId(id);
				break;
			case 2:
				cout << "Enter new name: ";
				cin >> newName;
				student.setName(newName);
				break;
			case 3:
				cout << "Enter new age: ";
				cin >> newAge;
				student.setAge(newAge);
				break;
			}
		}
	}
	if (!found) cout << "Student not found..." << endl;
	return;

}
void deleteStudent(vector<Student>& students)
{
	bool found = false;
	int id;
	char choice;
	cout << "Please enter ID of student you'd like to delete from our system: ";
	cin >> id;
	for (int i = 0; i < students.size(); i++)
	{
		if (id == students.at(i).getId())
		{
			found = true;
			cout << "Student found!" << endl << students.at(i);
			cout << "Are you sure you'd like to delete this student? (y/n)";
			cin >> choice;
			while (tolower(choice) != 'y' && tolower(choice) != 'n')
			{
				cout << "Invalid input. (y/n): ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> choice;
			}
			if (tolower(choice) == 'y')
			{
				students.erase((students.begin() + i));
			}
		}
	}
	if (!found) cout << "Student not found..." << endl;
	return;
}