#include "cpp_stylist.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

string CppStylist::style(string s) {
    return "abcdefg";
}

// string CppStylist::clean(ifstream *fin) {
    // string s = "aa";
	// return s;
// }

ostream& operator<<(ostream& out, const CppStylist& stylist) {
	out << "(" << stylist.new_line << ", " << stylist.space_before_parentheses << ", " << stylist.indent << ")" << endl;
	return out;
}