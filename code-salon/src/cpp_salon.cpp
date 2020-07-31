#include "cpp_stylist.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

/* process the command line arguments, and open the input file and the output file.
	* return true if the file streams are successfully opened.
	* return false otherwise.
*/
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
					cerr << "handle options not implemented" << endl;
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

vector<string> split_string(string s, char d) {
	vector<string> result;
	string buffer = "";
	for(int i = 0; s[i] != '\0'; i++) {
		char c = s[i];
		if(c == d) {
			result.push_back(buffer);
			buffer = "";
		}
		else {
			buffer.append(1, c);
		}
	}
	result.push_back(buffer);
	return result;
}

/* Convert a string of options to a map of options, which will be the argument for Stylists.
*/
map<string, string> string_to_options(string s) {
	vector<string> options_values = split_string(s, ';');
	map<string, string> result;
	for(int i = 0; i < options_values.size(); i++) {
		vector<string> option_value = split_string(options_values[i], '=');
		string option = option_value[0];
		string value = option_value[1];
		result[option] = value;
	}
	return result;
}

// Interface for Python to use
/* Process the string and turn in into the style specified by [options].
	* parameters:
		s - the "cleaned" source code
		out_file - the string contains the output filename
		options - the options for styling. Must be in this format: "option1=value1;option2=value2;...;option_n=value_n"
	* return
		true if the process is succeeded, otherwise return false
*/
bool style_source_code(string s, string out_file, string options) {
	
	Stylist *stylist = CppStylist(string_to_options(options))
	
}

// Interface for Go's exec() to use(maybe)
// Or maybe just used for testing
int main(int argc, char *argv[]) {
	ifstream fin;
	ofstream fout;
	if(!process_args(argc, argv, &fin, &fout)) {
		cout << "Usage: cpp_salon -i <input_file> -o <output_file> [--options]" << endl;
		return 0;
	}	
	// string s = "new_line=1;space_before_parentheses=1;indent=6";
	// auto m = string_to_options(s);
	// for(auto it = m.begin(); it != m.end(); it++) {
		// cout << "(" << it->first << ", " << it->second << ")" << endl;
	// }
	// CppStylist stylist(m);
	// cout << stylist << endl;
	return 0;
}