#include <iostream>

int main(int argc, char* argv[]) {
	int sum = 0;
	for(int i = 0; i < argc; i++) {
		int x = atoi(argv[i]);
		sum += x;
	}
	std::cout << sum << std::endl;
	return 0;
}