#include "cpp_stylist.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

// Interface for Python to use
/* Process the string and turn in into the style specified by [options].
	* parameters:
		s - the "cleaned" source code
		options - the options for styling. Must be in this format: "option1=value1;option2=value2;...;option_n=value_n"
	* return
		the styled string
*/
// std::string style_source_code(std::string s, std::string options) {
	// Stylist *stylist = new CppStylist(string_to_options(options));
	// return stylist->style(s);
// }

// std::string style_source_code_no_option(std::string s) {
	// Stylist *stylist = new CppStylist();
	// return stylist->style(s);
// }

// Interface for Go's exec() to use(maybe)
// Or maybe just used for testing
int main(int argc, char *argv[]) {
	// std::string s = style_source_code_no_option(TEST_STRING);
	// std::cout << s << std::endl;
	return 0;
}