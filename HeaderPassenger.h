#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "HeaderSeat.h"
using namespace std;
#ifndef FINAL_H_Passenger
#define FINAL_H_Passenger

class Passenger{
	private:
		string first_name;
		string last_name;
		string phone_number;
		int id;
	public:
		void set_first_name(string a) {first_name = a;}
		void set_last_name(string a) {last_name = a;}
		void set_phone_number(string a);
		void set_id(int a) {id = a;}
		string get_first_name()const {return first_name;}
		string get_last_name()const {return last_name;}
		string get_phone_number()const {return phone_number;}
		int get_id()const {return id;}
		Seat seat;
};

#endif