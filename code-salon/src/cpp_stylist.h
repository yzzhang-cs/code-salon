#include "stylist.h"
#include <string>
#include <fstream>

#ifndef CPP_STYLIST_H
#define CPP_STYLIST_H

class CppStylist : public Stylist {
    public:
        CppStylist() {
            new_line = false;
            space_before_parentheses = true;
            indent = 4;
        }
        
        CppStylist(bool nl, bool space, int ind) {
            new_line = nl;
            space_before_parentheses = space;
            indent = ind;
        }
        
        std::string style(std::string s);
		// std::string clean(std::ifstream *fin);
        
    private:
        bool new_line;
        bool space_before_parentheses;
        int indent;
};

#endif