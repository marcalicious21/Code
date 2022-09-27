#include"noble.h"
#include<iostream>

using namespace std;
// Q2b: Define displayBook() for Noble class (5 points)
// Define the function displayBook() that you declared within the Noble class in the header file
// See expected output in question file.
void Noble::displayBook() {
	cout << "\nBook name: " << getName() << endl;
	cout << "Price: " << getPrice() << endl;
	if (getLibraryType() == 0) {
		cout << "Library: Hayden" << endl<< endl;
	}
	else {
		cout << "Library: Noble" << endl<< endl;
	}

}


// (displayList() function in hw10.cpp should call this function.)
// Include necessary header files
