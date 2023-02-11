#include<iostream>
#include<fstream>
#include<iomanip>
#include<stdlib.h>
#include<string>

using namespace std;

/*
  Author: Justin Montagne
  Version: 2/4/23

  Program to demonstrate an employee manager that allows for adding employee records, viewing those records and deleting records within files. 

  The program uses a simple interface on the console and takes numbered input to determine what actions to make. 
*/

class Employee{
  private:
  int IDNum;
  string name;
  string title;
  string number;
  string email;

  public:
    void getData();
    void showData(int enteredNum);
    int getID(){
      return IDNum;
    }
}e;

//Functions
  void run();
  void addData();
  void deleteData();
  void displayData();
  void getDeletedData();
  void clearDeleted();

  bool foundEmployee = false;

int main() {
  run();
  return 0;
}

//Function to run the program
void run(){
  //Number entered by user
  int in;

  do{
      
				

			system("clear");
			cout << endl << "***** Employee Manager *****" << endl;
			cout << endl << "Select Options ";
			cout << endl << "1. Add Employee data";
      cout << endl << "2. Read Employee data";
			cout << endl << "3. Delete Employee data";
			cout << endl << "4. Get Deleted Records";
      cout << endl << "5. Clear Deleted Records";
      cout << endl << "6. Exit" << endl;
      cin >> in;						
      cin.get();
      system("clear");
      switch(in){
        case 1: 
          addData();
          break;

        case 2:
          displayData();
          break;
        case 3:
          deleteData();
          break;
        case 4:
          getDeletedData();
          break;
        case 5:
          clearDeleted();
          break;
        case 6:
          system("clear");
          exit(0);
      }
    }while(true);
  
}

//Other functions

/*
  Function to get all data from the user
*/
void Employee::getData(){
  cout << "\n\n*******Enter Employee Information*******\n";

	cout << "ID Number: "; cin >> IDNum;
  
  if(IDNum == 0){
    do{
      cin.clear();
      cout << "ID Number cannot be 0 and must be an integer\nEnter ID Number Again: "; cin.ignore(); cin >> IDNum;
    }while(IDNum == 0);
  }

	cout << "Full Name: "; cin.ignore(); getline(cin, name);

	cout << "Employee Title: "; getline(cin, title);

	cout << "Employee Phone Number: "; cin >> number;
  if(number.length() != 10){
    do{
      cout << "Number must be 10 digits\nEmployee Phone Number: "; cin >> number;
    }while(number.length() != 10);
  }

	cout << "Employee email: "; cin >> email;

	cout << endl;
  }

/*
  Function to display data from file
  Parameter: A number that will represent the ID of the user's information to be displayed. (If number is 0, display all data).
*/
void Employee::showData(int enteredNum){
  if(enteredNum == IDNum || enteredNum == 0){
    if(enteredNum == IDNum){
      cout << "\n\n*******Employee " << name <<"'s Information*******\n";
    }

    foundEmployee = true;
    
  	cout << "ID Number: " << IDNum << endl;
  
  	cout << "Full Name: " << name << endl;
  
  	cout << "Employee Title: " << title << endl;
  
  	cout << "Employee Phone Number: " << number << endl;
  
  	cout << "Employee email: " << email << endl;
  
  	cout << endl;
  
    
    
  }
}
/*
  Helper function to open a file and then run the getData function to get the data from the user
*/
void addData(){
  ofstream fout; 

	fout.open("info.txt", ios::out | ios::app | ios::binary);// open file in append mode

  //Get Data from user
	e.getData();
  cin.get();
  //Write data to file
  fout.write((char*)&e, sizeof(e));

  fout.close();

  cout << "\n\n******Employee Data Successfully Saved******\n   Press 'enter' to return to main menu";

  cin.get();
  
}

/*
  Helper function for showData function that opens a file in order to provide the data to the showData function
*/
void displayData(){
  ifstream fin;

  fin.open("info.txt", ios::in | ios::binary);
  
  int enteredID;
  cout << "Enter employee's ID number you would like to view.\nOr enter 0 to view all employees: ";
  cin >> enteredID;

  if(enteredID == 0){
    cout << "\n*******Displaying All Employee Data*******\n\n";
  }
  while(fin.read((char*)&e, sizeof(e))){
    e.showData(enteredID);
  }
  cin.get();
  fin.close();
  if(!foundEmployee && enteredID != 0){
    cout << "\nNo employee listed with ID number: " << enteredID << endl;
  }
  else{
    foundEmployee = false;
  }
  cout << "\n\nPress 'enter' to return to main menu";
  cin.get(); //hold window
}

/*
  Deletes the data of one employee if a correct ID is provided. Uses a temp file to store non deleted employee information and store deleted data into a trash file
*/
void deleteData(){
  int ID;
  bool found = false;
  //In stream for info
  ifstream fin;

  //Out stream for trash and temp
	ofstream fout, tout;

  fin.open("info.txt", ios::in | ios::binary); 

	fout.open("temp.txt", ios::out | ios::app | ios::binary); 

	tout.open("trash.txt", ios::out | ios::app | ios::binary); 

	cout << "Enter Employee ID Number you would like to remove: ";

	cin >> ID;
  cin.get();
  while(fin.read((char*)&e, sizeof(e)) && !found){
    
      if(ID == e.getID()){
        cout << "The record " << ID << " has been removed" << endl;
  
        tout.write((char*)&e, sizeof(e)); // write data to trash.txt
  
  			found = true;
  
        
      }

      else{
        fout.write((char*)&e, sizeof(e)); // write date to temp.txt
      }
      
    }
  fout.close();

	tout.close();

	fin.close();

  if (!found)
		cout << "No Record found for ID Number: " << ID << endl;

	remove("info.txt"); // delete info.txt

	rename("temp.txt", "info.txt"); // rename temp.txt - info.txt

  cout<< "Press 'enter' to return to main menu";
  cin.get(); // Hold window
  
}

/*
  Uses the showData function to display all deleted records from the trash.txt file
*/
void getDeletedData(){
  ifstream fin; // open file in input mode

	fin.open("trash.txt", ios::in | ios::binary);

  cout<< "******Deleted Records******\n\n";
	while (fin.read((char*)&e, sizeof(e)))
	{

		e.showData(0); // input 0 to display all data

	}

	fin.close();

	cout << "\n\nPress 'enter' to return to main menu";

  cin.get();
}

/*
  Asks if the user actually meant to clear the data first and then clears the trash.txt file by simply opening it without append mode and closing it.
*/
void clearDeleted(){
  char c;
  cout << "Are you sure you want to clear the deleted records? y/n: ";
  cin >> c;
  cin.get();
  if(c == 'y' || c == 'Y'){
    ofstream file;
  
  	file.open("trash.txt");
    file.close();
  
    cout << "Deleted Records Have Been Cleared\n";
    }
  else{
    cout << "Data has not been deleted\n";
  }

  cout << "Press 'enter' to return to main menu";
  cin.get();
}
