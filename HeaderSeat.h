#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;
#ifndef FINAL_H_Seat
#define FINAL_H_Seat

class Seat{
	private:
		int seat_num;
		char seat_letter;
			
	public:
		void set_seat_num(int a) {seat_num = a;}
		void set_seat_letter(char a) {seat_letter = a;}
		int get_seat_num()const {return seat_num;}
		char get_seat_letter()const {return seat_letter;}
};

#endif