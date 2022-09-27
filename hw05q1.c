// CSE240 Spring 2022 HW5
// Marc Sagario
// Write the compiler used: Visual studio

// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of employees, like employees' record.
// Each record has this information: employee's name, supervisors's name, department of the employee, room number.
// The struct 'employeeRecord' holds information of one employee. Department is enum type.
// An array of structs called 'list' is made to hold the list of employees.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// You should not modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// WRITE COMMENTS FOR IMPORANT STEPS IN YOUR CODE.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_EMPLOYEES 15
#define MAX_NAME_LENGTH 25

typedef enum { HR = 0, Marketing, IT } departmentType;	// enum type 

struct employeeRecord {									// struct for emplyee details
	char employeeName[MAX_NAME_LENGTH];
	char supervisorName[MAX_NAME_LENGTH];
	departmentType department;
	unsigned int idNumber;
	unsigned int roomNumber;
};

struct employeeRecord list[MAX_EMPLOYEES];				// declare list of employees
int count = 0;											// the number of employees currently stored in the list (initialized to 0)

// functions already implmented
void flushStdIn();
void executeAction(char);
void save(char* fileName);

// functions that need implementation:
int add(char* employeeName_input,
	char* supervisorName_input,
	char* department_input,
	unsigned int idNumber_input,
	unsigned int roomNumber_input);		// 20 points
void sort();								// 10 points
int delete(unsigned int idNumber_input);	// 10 points
void load(char* fileName);					// 10 points
void display();								// given


int main()
{
	char* fileName = "Employee_List.txt";
	load(fileName);							// load list of employees from file (if it exists). Initially there will be no file.
	char choice = 'i';						// initialized to a dummy value
	do
	{
		printf("\nEnter your selection:\n");
		printf("\t a: add a new employee\n");
		printf("\t d: display employee list\n");
		printf("\t r: remove an employee from list\n");
		printf("\t s: sort employee list by ID\n");
		printf("\t q: quit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != 'q');

	save(fileName);							// save list of employees to file (overwrites file, if it exists)
	return 0;
}

// flush out leftover '\n' characters
void flushStdIn()
{
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c)
{
	char employeeName_input[MAX_NAME_LENGTH], supervisorName_input[MAX_NAME_LENGTH];
	unsigned int roomNumber_input, idNumber_input, add_result = 0;
	char department_input[20];
	switch (c)
	{
	case 'a':
		// input employee record from user
		printf("\nEnter employee name: ");
		fgets(employeeName_input, sizeof(employeeName_input), stdin);
		employeeName_input[strlen(employeeName_input) - 1] = '\0';				// discard the trailing '\n' char
		printf("Enter supervisor name: ");
		fgets(supervisorName_input, sizeof(supervisorName_input), stdin);
		supervisorName_input[strlen(supervisorName_input) - 1] = '\0';			// discard the trailing '\n' char
		printf("Enter whether employee is in 'HR' or 'Marketing' or 'IT': ");
		fgets(department_input, sizeof(department_input), stdin);
		department_input[strlen(department_input) - 1] = '\0';					// discard the trailing '\n' char
		printf("Please enter employee ID number: ");
		scanf("%d", &idNumber_input);
		printf("Please enter room number: ");
		scanf("%d", &roomNumber_input);
		flushStdIn();

		// add the employee to the list
		add_result = add(employeeName_input, supervisorName_input, department_input, idNumber_input, roomNumber_input);
		if (add_result == 0)
			printf("\nEmployee is already on the list! \n\n");
		else if (add_result == 1)
			printf("\nEmployee successfully added to the list! \n\n");
		else
			printf("\nUnable to add. Employee list is full! \n\n");

		break;
	case 'r':
		printf("Please enter ID number of employee to be deleted: ");
		scanf("%d", &idNumber_input);
		flushStdIn();
		int delete_result = delete(idNumber_input);
		if (delete_result == 0)
			printf("\nEmployee not found in the list! \n\n");
		else
			printf("\nEmployee deleted successfully! \n\n");
		break;
	case 'd': display();	break;
	case 's': sort();		break;

	case 'q': break;
	default: printf("%c is invalid input!\n", c);
	}
}

// Q1 : add (20 points)
// This function is used to add a employee into the list. You can simply add the new employee to the end of list (array of structs).
// Do not allow the employee to be added to the list if it already exists in the list. You can do that by checking employee names OR IDs already in the list.
// If the employee already exists then return 0 without adding it to the list. If the employee does not exist in the list then add the employee at the end of the list and return 1.
// If employee list is full, then do not add new employee to the list and return 2.
// NOTE: Notice how return type of add() is checked in case 'a' of executeAction()
// NOTE: You must convert the string 'department_input' to an enum type and store it in the list because the department has enum type (not string type).
// The list should be case sensitive. For instance, 'Roger' and 'roger' should be considered two different names.
// Hint: the global variable 'count' holds the number of employees currently in the list
int add(char* employeeName_input, char* supervisorName_input, char* department_input, unsigned int idNumber_input, unsigned int roomNumber_input)
{
	// Write the code below.
	int i;
	list[count].roomNumber = roomNumber_input;		//inputing values from parameters
	list[count].idNumber = idNumber_input;
	strcpy(list[count].employeeName, employeeName_input);
	strcpy(list[count].supervisorName, supervisorName_input);
	
	for (i = 0; i < count; ++i) {		//counts hold the number of employes currently in the list. 
		if (strcmp(list[i].employeeName, employeeName_input) == 0) {
			return 0;         //employee exist already
		}
	}
	if (MAX_EMPLOYEES == count) {	//if employes list is full then return 2.
		return 2;
	 
	}
	if (strcmp(department_input, "Marketing")) {
		list[i].department = IT;
	}
	else if(strcmp(department_input, "IT")){
		list[i].department = Marketing;
	}
	else {
		list[i].department = HR;
	}

	//increment number of elements in list after employee is added
	count++;
	return 1; //edit this line as needed

}



// This function displays the employee list with the details (struct elements) of each employee. 
void display()
{
	char* departmentString = "HR";									// dummy init

	for (int i = 0; i < count; i++)									// iterate through the list
	{
		printf("\nEmployee name: %s", list[i].employeeName);		// display employee's name
		printf("\nSupervisor name: %s", list[i].supervisorName);	// display supervisor's name

		if (list[i].department == HR)								// find what to display for department
			departmentString = "HR";
		else if (list[i].department == Marketing)
			departmentString = "Marketing";
		else
			departmentString = "IT";
		printf("\nDepartment: %s", departmentString);				// display department
		printf("\nID Number: %d", list[i].idNumber);				// display employee's ID
		printf("\nRoom number: %d", list[i].roomNumber);			// display employee's room number
		printf("\n");
	}

}

// Q2 : sort (10 points)
// This function is used to sort the list(array of structs) numerically by employee's ID.
// Parse the list and compare the employee IDs to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new array of structs having sorted employees.
// Hint: Use a temp struct (already declared) if you need to swap two structs in your logic
void sort()
{
	struct employeeRecord employeeTemp;	// needed for swapping structs. Not absolutely necessary to use.
	// Write the code below.
	int i, j, k;
	
	for (int m = 0; m < count - 1; ++m) {
		for (i = 0; i < count - 1; ++i) {
			k = list[i].idNumber;
			j = list[i + 1].idNumber;
			if (k > j) {		//compares the two employee's 
				employeeTemp = list[i + 1];			//swaps
				list[i + 1] = list[i];
				list[i] = employeeTemp;
			}

		}
	}
	
	// display message for user to check the result of sorting.
	printf("\nEmployee list sorted! Use display option 'd' to view sorted list.\n");
}

// save() is called at the end of main()
// This function saves the array of structures to file. It is already implemented.
// You should read and understand how this code works. It will help you with 'load()' function.
// save() is called at end of main() to save the employee list to a file.
// The file is saved at the same place as your C file. 
// You can simply delete the file to 'reset the list' or to avoid loading from it.
void save(char* fileName)
{
	FILE* file;
	int i, departmentValue = 0;
	file = fopen(fileName, "wb");		// open file for writing

	fwrite(&count, sizeof(count), 1, file);		// First, store the number of employees in the list

	// Parse the list and write employee record to file
	// 
	for (i = 0; i < count; i++)
	{
		fwrite(list[i].employeeName, sizeof(list[i].employeeName), 1, file);
		fwrite(list[i].supervisorName, sizeof(list[i].supervisorName), 1, file);
		// convert enum to a number for storing
		if (list[i].department == HR)
			departmentValue = 0;		// 0 for HR
		else if (list[i].department == Marketing)
			departmentValue = 1;		// 1 for Marketing
		else
			departmentValue = 2;		// 2 for ITs

		fwrite(&departmentValue, sizeof(departmentValue), 1, file);
		fwrite(&list[i].idNumber, sizeof(list[i].idNumber), 1, file);
		fwrite(&list[i].roomNumber, sizeof(list[i].roomNumber), 1, file);
	}

	fclose(file);			// close the file after writing
}

// Q3 : delete (10 points)
// This function is used to delete an employee by ID.
// Parse the list and compare the employee IDs to check which one should be deleted.
// Restore the array structure after removal of the employee record.
// Return 0 if the specified ID was not found. Return 1 upon successful removal of a record.
int delete(unsigned int idNumber_input)
{
	struct employeeRecord employeeTemp;	// needed for swapping structs. Not absolutely necessary to use.
	for (int i = 0; i < count; ++i)
	{
		if (list[i].idNumber == idNumber_input) {
			employeeTemp = list[i];
			list[i] = list[i + 1];
			list[i + 1] = employeeTemp;
			count--;//Shift the elements in the array from the point onwards of the deletion by 1
			
		}
		return 1;
		
	}
 // edit this line as needed

}

// Q4:  load (10 points)
// This function is called in the beginning of main().
// This function reads the employee list from the saved file and builds the array of structures 'list'. 
// In the first run of the program, there will be no saved file because save() is called at the end of program.
// So at the begining of this function, write code to open the file and check if it exists. If file does not exist, then return from the function.
// (See expected output of add() in homework question file. It displays "Employee_List.txt not found" because the file did not exist initially.)
// If the file exists, then parse the employee list to read the employee details from the file.
// Use the save function given above as an example of how to write this function. Notice the order in which the struct elements are saved in save()
// You need to use the same order to read the list back.
// NOTE: The saved file is not exactly readable because all elements of the struct are not string or char type.
//       So you need to implement load() similar to how save() is implemented. Only then the 'list' will be loaded correctly.
//		You can simply delete the file to 'reset the list' or to avoid loading from it.
void load(char* fileName)
{
	// Write the code below.
	FILE* f;						//creates a pointer
	f = fopen(fileName, "rb");
	int i;
	
	if (f) {									//checks if file exist
		fread(&count, sizeof(count), 1, f);
		for (i = 0; i < count, sizeof(count); ++i) {
			fread(list[i].employeeName, sizeof(list[i].employeeName), 1, f);
			fread(list[i].supervisorName, sizeof(list[i].supervisorName), 1, f);
			fread(&list[i].department, sizeof(list[i].department), 1, f);
			fread(&list[i].roomNumber, sizeof(list[i].roomNumber), 1, f);
		}
		printf("Employees record loaded from Employee_List.txt\n");
		fclose(f);
	}
	else {
		printf("Employee_List.txt not found\n");
	}

	
}
