#include "cpp_stylist.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool process_args(int argc, char *argv[], ifstream *fin, ofstream *fout) {
	for(int i = 1; i < argc; i++) {
		char* arg = argv[i];
		
		if(arg[0] == '-') {
			switch(arg[1]) {
				case 'i':
					fin->open(argv[++i]);
					break;
				case 'o':
					fout->open(argv[++i]);
					break;
				case '-':
					cout << "handle options not implemented" << endl;
					return false;
				default:
					return false;
			}
		}
	}
	if(!fin->is_open() || !fout->is_open()) {
		return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	ifstream fin;
	ofstream fout;
	if(!process_args(argc, argv, &fin, &fout)) {
		cout << "Usage: cpp_salon -i <input_file> -o <output_file> [--options]" << endl;
		return 0;
	}
	
	
}