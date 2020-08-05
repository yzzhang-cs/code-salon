#include "cpp_stylist.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

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
		if(option_value.size() != 2) {
			cerr << "CppStylist:ERROR: Incorrect format for option string" << endl;
			exit(1);
		}
		string option = option_value[0];
		string value = option_value[1];
		result[option] = value;
	}
	return result;
}

CppStylist::CppStylist(string options) : CppStylist::CppStylist(string_to_options(options)) {}



// determine if the current character is the start of a line-comment (comment with //)
bool line_comment_start(string s, int i) {
	if(s[i+1] == '\0') {
		return false;
	}
	if(s[i] == '/' && s[i+1] == '/') {
		return true;
	}
}

// determine if the current character is the start of a block of multi-line comment (comment with /* */)
bool comment_start(string s, int i) {
	if(s[i+1] == '\0') {
		return false;
	}
	if(s[i] == '/' && s[i+1] == '*') {
		return true;
	}
}

// determine if the current character is the end of a block of multi-line comment (comment with /* */)
bool comment_end(string s, int i) {
	if(s[i+1] == '\0') {
		return false;
	}
	if(s[i] == '*' && s[i+1] == '/') {
		return true;
	}
}

// copy the line.
// in other words, copy all the characters until '\n' or '\0' is found
void copy_line(string s, int &i, string &result) {
	while(s[i+1] != '\0' && s[i] != '\n') {
		result.append(1, s[i++]);
	}
	result.append(1, s[i++]);
	return;
}

// copy everything until the end of comment is reached ('*/')
void copy_comment(string s, int &i, string &result) {
	while(s[i+1] != '\0' && !comment_end(s, i)) {
		result.append(1, s[i++]);
	}
	result.append(1, s[i++]); // append '*'
	result.append(1, s[i++]); // append '/'
	return;
}


bool string_end(string s, int i) {
	if(! s[i-1]) { // who put a '"' at the beginning of a .cpp file? I don't know but I will handle this.
		return false;
	}
	if(s[i-1] != '\\' && s[i] == '"') {
		return true;
	}
	return false;
}
bool tab_char(string s, int i) {
	if(s[i+1] != '\0' && s[i] == '\\' && s[i+1] == 't') {
		return true;
	}
	return false;
}
bool newline_char(string s, int i) {
	if(s[i+1] != '\0' && s[i] == '\\' && s[i+1] == 'n') {
		return true;
	}
	return false;
}
// copy everything until the end of a string (")
void copy_string(string s, int &i, string &result) {
	while(s[i] != '\0' && !string_end(s, i)) {
		result.append(1, s[i++]);
	}
	result.append(1, '"');
	i++;
}

// this function may be changed if we want to handle "spaces as tab" cases
// TODO:                                       ^
void add_tab(string &result) {
	result.append(1, '\t');
}
// insert a new line
void insert_tabs(string &result, int level) {
	while(level > 0) {
		add_tab(result);
		level--;
	}
}

string CppStylist::style(string s) {
	int i = 0; // i is always the NEXT character to process
	int indent_level = 0; // indentation level. for example, this line of code is level 1 since it has 1 tab in front.
	string result = "";
	
	// for loop until the end of the string
	while(s[i] != '\0') {
		
		// case for line comments (//)
		if(line_comment_start(s, i)) {
			copy_line(s, i, result);
			insert_tabs(result, indent_level);
		}
		// case for block comments (/*...*/)
		else if(comment_start(s, i)) {
			copy_comment(s, i, result);
		}
		// cases like #include ??????, simply copy the line
		else if(s[i] == '#') {
			copy_line(s, i, result);
		}
		// start of a string
		else if(s[i] == '"') {
			result.append(1, s[i++]);
			copy_string(s, i, result);
		}
		else if(s[i] == '{') {
			indent_level++;
			if(new_line) {
				result.append(1, '\n');
				insert_tabs(result, indent_level - 1);
				result.append(1, '{');
				result.append(1, '\n');
				insert_tabs(result, indent_level);
			}
			else {
				result.append(1, ' ');
				result.append(1, '{');
				result.append(1, '\n');
				insert_tabs(result, indent_level);
			}
			i++;
		}
		else if(s[i] == '}') {
			indent_level--;
			if(s[i-1] != '\t' && s[i-1] != '\n') {
				result.append(1, '\n');
				insert_tabs(result, indent_level);
			}
			result.append(1, '}');
			result.append(1, '\n');
			i++;
			
			while(s[i] == '}') {
				indent_level--;
				insert_tabs(result, indent_level);
				result.append(1, '}');
				result.append(1, '\n');
				i++;
			}
			insert_tabs(result, indent_level);
		}
		else if(s[i] == '\n') {
			result.append(1, '\n');
			i++;
			
			while(s[i] == '}') {
				indent_level--;
				insert_tabs(result, indent_level);
				result.append(1, '}');
				result.append(1, '\n');
				i++;
			}
			insert_tabs(result, indent_level);
		}
		// default case, simply copy the character
		else {
			result.append(1, s[i++]);
		}
	}
	return result;
}

// ostream& operator<<(ostream& out, const CppStylist& stylist) {
	// out << "(" << stylist.new_line << ", " << stylist.space_before_parentheses << ", " << stylist.indent << ")" << endl;
	// return out;
// }