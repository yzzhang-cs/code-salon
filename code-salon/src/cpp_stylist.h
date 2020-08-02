#include "stylist.h"
#include <string>
#include <map>

#ifndef CPP_STYLIST_H
#define CPP_STYLIST_H

class CppStylist : public Stylist {
    public:
		// default constructor
		// 	- no new line before parentheses
		//	- 1 space before parentheses
		//	- 4-space indent
        CppStylist() {
            new_line = false;
            space_before_parentheses = true;
            indent = 4;
        }
		// constructor that takes a map of options.
		//	the map must be <string, string>
		CppStylist(std::map<std::string, std::string> options) {
			if(options.count("new_line") > 0) {
				new_line = (bool)stoi(options.find("new_line")->second);
			}
			if(options.count("space_before_parentheses") > 0) {
				space_before_parentheses = (bool)stoi(options.find("space_before_parentheses")->second);
			}
			if(options.count("indent") > 0) {
				indent = stoi(options.find("indent")->second);
			}
		}
		CppStylist(std::string options);
        
        std::string style(std::string s);
		// std::string clean(std::ifstream *fin);
		
		// for testing
		// friend std::ostream& operator<<(std::ostream& out, const CppStylist& stylist);
        
    private:
        bool new_line;
        bool space_before_parentheses;
        int indent;
};

#endif