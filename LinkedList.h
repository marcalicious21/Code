// ASU CSE310 Fall 2022 Assignment #1
// Name: Marc Sagario
// ASU ID: 122002095
// Email: mcsagari@asu.edu
// Description: Header file for the linked list 

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Car represents a Car information
struct Car
{
    string model, make;
    int vin;            //vehicle identification number
    double price;
    struct Car* next;
};

//class LinkedList will contains a linked list of Cars
class LinkedList
{
private:
    struct Car* head;

public:
    LinkedList();
    ~LinkedList();
    bool findCar(int aVin);
    bool addCar(string model, string make, int vin, double price);
    bool removeByVin(int aVin);
    bool removeByModelAndMake(string model, string make);
    bool changeCarInfo(int aVin, string newModelAndMake);
    bool updateCarPrice(int aVin, double newPrice);
    void printCarListByMake(string make);
    void printCarList();
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    //add your own code
    //----
    head = nullptr;  //initailized an empty linked list, head will be equall to null pointer
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
    //add your own code
    //----
    int carCount = 0;           //initializing the car count 
    while (head != nullptr) {   //while loop to track and delete memory occupied by the link list
        carCount++;
        Car* cur = head; //deletes the head using a pointer
        head = head->next;
        delete cur;
    }
    cout << "The number of deleted Car is: " << carCount << "\n";
}

//A function to identify if the parameterized Car is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::findCar(int aVin)
{
    //add your own code
    //----
    Car* cur = head;
    while (cur != nullptr) {
        if (cur->vin == aVin) {
            return true;  //returns true if the vin exist 
        }
        cur = cur->next;
    }
    return false;  //false otherwise
}

//Creates a new Car and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of Cars by their make and model, i.e.
//first by make, if two cars have same makes, then we will list them by model. Note: each Car
//has a unique vin, the vehicle identification number, but may have the same make and model.
//In case two Cars have same make and model, they should be inserted according to the
//increasing order of their vins.
//Return value: true if it is successfully inserted and false in case of failures.
bool LinkedList::addCar(string model, string make, int vin, double price)
{
    //if the Car already exist, return false
    //add your own code
    //----
    if (findCar(vin)) { //uses the findCar fundtion to see if the car already exist
        return false;      //returns false if the car does already exist in the list
    }

   //add your own code
   //----
    Car* newCar = new Car();  //creates a new car to be added
    newCar->model = model;
    newCar->make = make;
    newCar->vin = vin;
    newCar->price = price;
    Car* cur = head;  //intializes two pointers which points to the current positions and previous position
    Car* prev = cur;

    if (head == nullptr) {      //this checks if the list is already empty
        head = newCar;
        return true;
    }


    while (cur != nullptr) {
        if (newCar->make.compare(cur->make) < 0) {  //compares the make of the car 
            if (head == cur) {
                head = newCar;
                newCar->next = cur;
            }
            else {
                prev->next = newCar;
                newCar->next = cur;
            }
            return true;
        }
        else if (newCar->make.compare(cur->make) == 0) {  //checks if the the car is the same make
            if (newCar->model.compare(cur->model) < 0) { //will sort using the model if the car is the same make
                if (head == cur) {
                    head = newCar;
                    newCar->next = cur;
                }
                else {
                    prev->next = newCar;
                    newCar->next = cur;
                }
                return true;
            }
            else if (newCar->model.compare(cur->model) == 0) {  //in case the cars are the same make and model they will be sorted using their vin number
                if (newCar->vin < cur->vin) {   //compares the vin numebrs
                    if (head == cur) {
                        head = newCar;
                        newCar->next = cur;
                    }
                    else {
                        prev->next = newCar;
                        newCar->next = cur;
                    }
                    return true;
                }
            }
        }
        prev = cur;        //sets the pointers
        cur = cur->next;
    }
    prev->next = newCar;
    return true;
}

//Removes the specified Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise.
bool LinkedList::removeByVin(int aVin) 
{
    //add your own code
    //----
    Car* cur = head;
    Car* prev = cur;

    while (cur != nullptr) {     // loops while the the pointer does not equal null
        if (cur->vin == aVin) {  //checks if it is the right vin
            if (cur == head) {       //removes the car and updates the pointer
                head = cur->next;
                delete cur;
            }
            else {
                prev->next = cur->next;
                delete cur;
            }
            return true;   //retuns true meaning that the process was done correctly
        }
        prev = cur;
        cur = cur->next;
    }
    return false;  //retruns false if uncesseful
}

//Removes the given Car from the list, releases the memory and updates pointers.
//Return true if it is successfully removed, false otherwise. Note: all Cars with
//the same model and make should be removed from the list.
bool LinkedList::removeByModelAndMake(string model, string make)
{
    //add your own code
    //----
    bool removed = false;   //intializing variables and pointer 
    Car* cur = head;
    Car* prev = cur;
    
    while (cur != nullptr) {   //goes through the list until the end 
        if (cur->make.compare(make) == 0 && cur->model.compare(model) == 0) {  //compares the make and model user input to the list and sorts them
            if (cur == head) {
                head = cur->next;   //deletes
                delete cur;
                cur = head;
            }
            else {
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }
            removed = true;        //sets removed to true
            continue;
        }
        prev = cur;
        cur = cur->next;
    }
    return removed;  //returns either true of false depending if it was removed
}

//Modifies the data of the given Car. Return true if it modifies successfully and
//false otherwise. Note: after changing a Car model and make, the linked list must still
//maintain the alphabetical order.
bool LinkedList::changeCarInfo(int aVin, string newModelAndMake)
{
    //split newModelAndMake string to get model and make accordingly
    //add your own code
    //----
    Car* cur = head;
    double curPrice;
    string carName[2];

    if (!findCar(aVin)) {  //this first checks if the car exists in the list
        return false;
    }

    for (int i = 0, m = 0; i < newModelAndMake.length(); i++) {
        if (newModelAndMake[i] == ' ') {
            m++;
            continue;
        }
        carName[m] += newModelAndMake[i];
    }
    
    //add your own code
    //----

    while (cur->vin != aVin) {    //sets the price
        cur = cur->next;
    }
    curPrice = cur->price;

    
    if (!removeByVin(aVin)) {   //checks if it is correct vin
        return false;
    }

    if (!addCar(carName[0], carName[1], aVin, curPrice)) {
        return false;
    }
    return true;
}

bool LinkedList::updateCarPrice(int aVin, double newPrice)
{
    //add your own code
    //----
    Car* cur = head;

    if (!findCar(aVin)) {
        cout << "Car is NOT inside the list, cannot change its price.\n";
        return false;
    }
    else {
        while (cur->vin != aVin) {     //moves the pointer and updates the price
            cur = cur->next;
        }
        cur->price = newPrice;
        return true;
    }

   
}

//Prints all Cars in the list with the same make.
void LinkedList::printCarListByMake(string make)
{
    //add your own code
    //----
    Car* temp = head;   //intialized head to temp since it is what is given
    bool found = false;

    if (head == NULL) {    //returns cout if the list is empty
        cout << "The list is empty\n";
        return;
    }

    while (temp != nullptr) {
        if (temp->make.compare(make) == 0) {  //traverses through the list 
            cout << left << setw(12) << temp->model
                << left << setw(12) << temp->make
                << right << setw(8) << temp->vin
                << setw(10) << fixed << setprecision(2) << temp->price << "\n";
            found = true;
        }
        temp = temp->next;  //moves the pointer
    }
    if (!found) {
        cout << "No Cars with the specified make found.\n";
    }

}

//Prints all Cars in the linked list starting from the head node.
void LinkedList::printCarList()
{
    //add your own code
    //----
    Car* temp = head;

    if (head == NULL) {  //if the list empty, cout
        cout << "The list is empty\n";
        return;
    }

    while (temp != nullptr) {
        cout << left << setw(12) << temp->model
            << left << setw(12) << temp->make
            << right << setw(8) << temp->vin
            << setw(10) << fixed << setprecision(2) << temp->price << "\n";
        temp = temp->next;
    }
}
