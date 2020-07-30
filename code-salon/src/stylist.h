#include <string>
#include <fstream>

#ifndef STYLIST_H
#define STYLIST_H

class Stylist {
    public:
		// takes an input file stream, process line-by-line and turn it into a single string
		// virtual std::string clean(std::ifstream *fin) = 0;
		
		// take the cleaned string, process it char-by-char into the destinated style
        virtual std::string style(std::string s) = 0;
};

#endif