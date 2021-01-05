#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include "HeaderFlight.h"
#include "HeaderPassenger.h"
#include "HeaderSeat.h"
using namespace std;

/*
SHOWS SEAT MAP(OPTION 1)
*/
void Flight::show_seat_map(){
	
	
	vector<int> m(row+1); 
	

	cout<<endl;
	cout<<setw(24)<<"Aircraft Seat Map"<<endl<<endl;
	
	
	
	char col_char = 'A';
	cout<<" ";
	for(int i = 0; i<column; i++){
		cout<<setw(4)<<col_char;
		col_char++;
	}
	cout<<endl;
	
	
	
	/*
	Needed to check which column the passenger is assigned to
	*/
	char col1 = 'A';
	
	/*
	Flag is used to indicate wheather a passenger in a specific row and column has been found...
	If a passenger is found, the program will output a X in the correct spot, if no passenger is found...
	the program will continue to output the box's without the X.
	*/
	int flag = 1; 
	
	int num = 0;
	int i = 0;
	int c = 0;
	int k;
	int how_many = 0; //variable is used to indicate whether the last column has been reached (output extra | at end)
	int found = 0; // used to indicate whether a seat has been taken
	
	for(i = 0; i<row+1; i++){
		
		cout<<endl;
		cout<<"  ";
		while(how_many < column){
		cout<<"+---";
		how_many++;
		}
		
		how_many = 0;
		cout<<"+"<<endl;
		
		
		m[i] = num;
		num++;
		if(i<10){
		cout<<m[i]<<" ";
		}
		else
		cout<<m[i];
	
		
	
		while(how_many < column){
			for(k = 0; k<passenger.size(); k++){
				if(i==passenger[k].seat.get_seat_num() && col1 == passenger[k].seat.get_seat_letter()){
					
					if(how_many == column - 1){
						cout<<"| X |";
						found = 1;
					}
					else
						cout<<"| X ";
						found = 1;
				}
			}
			if(found == 0){
				if(how_many == column - 1){
					cout<<"|   |";
				}
				else
					cout<<"|   ";
			}
			else{
				found = 0;
			}
			col1++;
			how_many++;
		}
			
		how_many = 0;
		col1 = 'A';
		
		
	} 
	
	//closes the seats off with one more sequence of +---
	int how_many1 = 0;
	cout<<endl;
	cout<<"  ";
	while(how_many1 < column){
		cout<<"+---";
		how_many1++;
	}
	cout<<"+"<<endl;
	
	
}
		

		
void Passenger::set_phone_number(string a){
	//Add dashes if the phone number was entered without dashes
	if(a[3] != '-' || a[7] != '-'){
		a[3] = '-';
		a[7] = '-';
		phone_number = a;
	}
	else
		phone_number = a;

}	
	






















