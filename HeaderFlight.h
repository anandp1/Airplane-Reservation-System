#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "HeaderPassenger.h"
using namespace std;
#ifndef FINAL_H
#define FINAL_H

class Flight{
	private:
		int row;
		int column;
		string flight_name;
	public:
		void show_seat_map();
		void set_row(int a) {row = a;}
		void set_column(int a) {column = a;}
		int get_row()const {return row;}
		int get_column()const {return column;}
		string get_flight_name()const {return flight_name;}
		void set_flight_name(string a) {flight_name = a;}

		vector <Passenger> passenger;

	
};


#endif
