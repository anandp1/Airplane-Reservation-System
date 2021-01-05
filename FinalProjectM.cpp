#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;
#include "HeaderFlight.h"
#include "HeaderPassenger.h"
#include "HeaderSeat.h"

void pressEnter();
void cleanStandardInputStream(void); //needed to clear input stream

/*
FUNCTIONS NEEDED FOR THIS PROJECT
*/

void displayHeader();
int populate_flight(string text, Flight& flight);
void add_passenger(Flight& f);
void remove_passenger(Flight &f);
void save_infor(string text, Flight &f);
void displayPassengers(Flight &f);
int menu();

//variable needed to help with resizing vector when a new passenger is added
int j; 
//varialble is needed to help with formatting "display passengers"
int extra_size = 0;
int main(){
	Flight f;
	displayHeader();

	populate_flight("Flight.txt", f);
	


	int choice;
		while((choice = menu())){
			switch(choice){
				case 1:
				f.show_seat_map();
				pressEnter();
				break;
				case 2:
				displayPassengers(f);
				pressEnter();
				break;
				case 3:
				add_passenger(f);
				break;
				case 4: 
				remove_passenger(f);
				break;
				case 5:
				save_infor("Flight.txt", f);
				break;
				case 6:
				exit(1);
				break;
				
			}
		}
		return 0;
}












int menu(){
	int choice;
	cout<<"Please select one of the following options"<<endl;
	cout<<"1. Display Flight Seat Map."<<endl;
	cout<<"2. Display Passenger Information."<<endl;
	cout<<"3. Add a New Passenger."<<endl;
	cout<<"4. Remove an Existing Passenger"<<endl;
	cout<<"5. Save data"<<endl;
	cout<<"6. Quit."<<endl<<endl;
	cout<<"Enter your choice: (1, 2, 3, 4, 5 or 6) ";
	cin>>choice;
	return choice;
	
}
void pressEnter(){
	cout<<"\n<<<Press Return to Continue>>>>\n";
	cleanStandardInputStream();
	cin.get();
}
void displayHeader(){
	cout<<"Version: 1.0"<<endl;
	cout<<"Term Project - Flight Management Program in C++"<<endl;
	cout<<"Produced by: Anand Patel"<<endl;
	pressEnter();
}
void cleanStandardInputStream(void){
	int leftover;
	do{
		leftover = cin.get();
	} while (leftover!='\n' && leftover != EOF);
}
	

int populate_flight(string text, Flight &flight){
	string f_name;
	string l_name;
	string phone_number;
	int seat_num;
	char seat_l;
	int id;
	int col;
	int row;
	string flight_name;
	
	int i = 0;
	

	ifstream file;
	file.open (text);
	if(file.fail()){
		cout<<"Error operning file"<<endl;
		exit(1);
	}
	
	
	while(1){
		
		if(file.eof()){
			break;
		}
		else if(file.fail()){
			cout<<"Something went wrong when reading input from "<<text;
			exit(1);
		}
		if(file.is_open()){
			file>>flight_name>>row>>col;
			flight.set_flight_name(flight_name);
			flight.set_row(row);
			flight.set_column(col);
			file.ignore(80, '\n'); // go to next line
		}
		//resize the string to hold characters read from file
		string line;
		line.resize(100);
		f_name.resize(21);
		l_name.resize(21);
		phone_number.resize(21);
		
		if(file.is_open()){
			while(1){
				
				
				getline(file, line);
				
				if(file.eof()){
					break;
				}
				//copy first name
				for(int i = 0; i<20; i++){
					f_name[i] = line[i];
				}
			
				int replace = 0;
				//copy last name
				for(int i = 20; i<40; i++){
					
					l_name[replace] = line[i];
					replace++;
				}
				
				replace = 0;
				//copy phone number
				for(int i = 40; i<60; i++){
					phone_number[replace] = line[i];
					replace++;
				}
				
				replace = 0;
				//copy row (seat number)
				for(int i = 60; i<61; i++){
					seat_num = line[i];
					seat_num = seat_num - 48;
					//check if the next letter is another number or not for rows higher than 9
					if(line[i+1] >= 48 && line[i+1] <= 57){ 
						seat_num = (seat_num*10) + (line[i+1] - 48);
					}	
				}
				
				//for reading seat column (seat letter)
				if(seat_num<9){
					for(int i = 61; i<62; i++){
						seat_l = line[i];
					}
				}
				else if(seat_num>9){
					for(int i = 62; i<63; i++){
						seat_l = line[i];
					}
				}
				
				//copy id
				for(int i = 64; i<69; i++){
					id += line[i];
					id = id - 48;
					if(i<68){
					id = id * 10;
					}
				}
				
				
				
				
				flight.passenger.resize(i+1);
			
				flight.passenger[i].set_first_name(f_name);
				flight.passenger[i].set_last_name(l_name);
				flight.passenger[i].set_phone_number(phone_number);
				flight.passenger[i].set_id(id);
				flight.passenger[i].seat.set_seat_num(seat_num);
				flight.passenger[i].seat.set_seat_letter(seat_l);
				i++;
				
				line.clear();
				id = 0;
				
				
			}
			j = i;
			break;
		}
		
	}
	file.close();
	return 0;
}

/*
DISPLAY PASSENGERS(OPTION 2)
*/
void displayPassengers(Flight &f){
	
	cout<<"First Name\t    Last Name\t        Phone\t\t   Row\t   Seat\t     ID"<<endl;
	cout<<"---------------------------------------------------------------------------------"<<endl;
	for(int i = 0; i<j; i++){
		cout<<left<<setw(17)<<f.passenger[i].get_first_name();
		if(i == j - extra_size){
			cout<<"   ";
		}
		cout<<left<<setw(17)<<f.passenger[i].get_last_name();
		if(i == j - extra_size){
			cout<<"   ";
		}
		cout<<left<<setw(17)<<f.passenger[i].get_phone_number();
		if(i == j - extra_size){
			cout<<"   ";
		}
		cout<<setw(8)<<f.passenger[i].seat.get_seat_num();
		cout<<setw(8)<<f.passenger[i].seat.get_seat_letter();
		cout<<setw(8)<<f.passenger[i].get_id()<<endl;
		cout<<"---------------------------------------------------------------------------------"<<endl;
	}
}	
/*
ADD PASSENGER(OPTION 3)
*/
void add_passenger(Flight& f){

	int id;
	string f_name;
	string l_name;
	string phone_num;
	int row;
	char seat;
	char seat_point[50];
	cout<<"Please enter the passenger id: ";
	cin>>id;
	//Make sure user enters a integer value
	while(!cin.good()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Please enter an integer: ";
		cin>>id;
	}
	// Make sure the id doesn't already exist
	for(int i = 0; i<f.passenger.size(); i++){
		if(id == f.passenger[i].get_id()){
			while(id == f.passenger[i].get_id()){
			cin.clear();
			cout<<"Please enter a different id: ";
			cin>>id;
			}
		}
		
	}

	cout<<endl;

	cout<<"Please enter the passenger first name: ";
	
	cleanStandardInputStream();
	getline(cin, f_name);
	cout<<endl;

	cout<<"Please enter the passenger last name: ";
	getline(cin, l_name);
	cout<<endl;

	
	cout<<"Please enter the passenger phone number: ";
	getline(cin, phone_num);
	while(phone_num.size() != 12){
		cout<<"Please enter a valid phone number in a correct format ###-###-####: ";
		cin.clear();
		getline(cin, phone_num);
	}
	cout<<endl<<endl;
	


	cout<<"Enter the passenger's desired row: ";
	cin>>row;
	//Make sure user enters a integer value
	while(!cin.good()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Please enter an integer: ";
		cin>>row;
	}
	
	while(row < 0 || row > f.get_row()){
		cout<<"Please enter a row between 0 and "<<f.get_row()<<":";
		cin>>row;
	}
	cout<<endl;


	cout<<"Enter the passenger's desired seat: ";
	cleanStandardInputStream();
	cin.get(seat_point, 50);
	int max_column = 65;

	for(int i = 0; i<f.get_column(); i++){
		max_column++;
	}
	
	while(1){
		if(seat_point[0] >=97 && seat_point[0] <= 122){ //convert the character into a uppercase
			seat_point[0] = seat_point[0] - 32;
		}
		//the character must be between A and the max amount of columns (F)
		if(seat_point[0] < 65 || seat_point[0] >= max_column){ 
			cout<<"Please enter a valid seat: ";
			cleanStandardInputStream();
			cin.get(seat_point,50);
			continue;
		}
		//the input must only be one character
		if(seat_point[1] == 0){
			break;
		}
		else
			cout<<"Please enter a valid seat: ";
			cleanStandardInputStream();
			cin.get(seat_point,50);
			
	}
	
	//check if the seat is taken
	for(int i = 0; i<f.passenger.size(); i++){
		if(seat_point[0] == f.passenger[i].seat.get_seat_letter() && row == f.passenger[i].seat.get_seat_num()){
			while(seat_point[0] == f.passenger[i].seat.get_seat_letter()){
				cleanStandardInputStream();
				cout<<"That seat is taken, please select a different seat: ";
				cin.get(seat_point,50);
				if(seat_point[0] >=97 && seat_point[0] <= 122){
					seat_point[0] = seat_point[0] - 32;
				}
			}
		}
	}
		

	seat = seat_point[0];

	cout<<endl;

	f.passenger.resize(j+1);

	f.passenger[j].set_id(id);
	f.passenger[j].set_first_name(f_name);
	f.passenger[j].set_last_name(l_name);
	f.passenger[j].set_phone_number(phone_num);
	f.passenger[j].seat.set_seat_letter(seat);
	f.passenger[j].seat.set_seat_num(row);
	j++;
	extra_size++;
}
/*
REMOVE A PASSENGER(OPTION 4)
*/
void remove_passenger(Flight &f){
	
	
	int id;
	cout<<"Please enter the id of the passenger that needs to be removed : ";
	cin>>id;
	//Make sure user enters a integer value
	while(!cin.good()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout<<"Please enter an integer: ";
		cin>>id;
	}
	int flag = 0;
	for(int i  = 0; i<f.passenger.size(); i++){
		if(id == f.passenger[i].get_id()){
			flag = 1;
			
		}
			
	}
	/*
	If the flag is 0; a incorrect id was entered.
	This code will print out all the valid id's and prompt to enter a new id
	*/
	if(flag == 0){
		cout<<"You did not enter a valid id "<<endl;
		cout<<"Here is the list of valid id's:"<<endl;
		for(int i  = 0; i<f.passenger.size(); i++){
			cout<<"- "<<f.passenger[i].get_id()<<endl;
		}
		cout<<"Please enter a valid id: ";
		cin>>id;
		//make sure user enters a integer
		while(!cin.good()){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout<<"Please enter an integer: ";
			cin>>id;
		}
	}
	cout<<endl;
	
	
	
	for(int i = 0; i<j; i++){
		if(f.passenger[i].get_id() == id){
			j--; 
			for(int k =  i; k<j; k++){
				f.passenger[k] = f.passenger[k+1];
			}
			
		}
		
		f.passenger.resize(j);
	}	
}
/*
SAVES INFO INTO FILE(OPTION 5)
*/
void save_infor(string text, Flight &f){
	char answer;
	cout<<"Do you want to save the data in the 'flight.txt'? Please answer <Y or N> ";
	cin>>answer;
	if(answer == 'Y'){
		fstream file(text, ios::in | ios::out | ios::trunc); //ios::trunc deletes all info the file 

		if(!file.is_open()){
			cout<<"Error while opening the file"<<endl;
		}
		//populates the file with the new data
		file<<f.get_flight_name()<<"\t"<<f.get_row()<<"\t"<<f.get_column()<<endl;
		for(int i = 0; i<j; i++){
			file << f.passenger[i].get_first_name()<<"\t"<<f.passenger[i].get_last_name()<<"\t"<<f.passenger[i].get_phone_number()<<"\t"<<f.passenger[i].seat.get_seat_num()<<f.passenger[i].seat.get_seat_letter()<<"\t"<<f.passenger[i].get_id()<<endl;
		}
	}
	else
		return;
}



















	
	
	
	
	








				