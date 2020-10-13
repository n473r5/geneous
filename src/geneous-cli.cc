#include <stdlib.h>
#include <iostream>
#include "matrix.hh"
#include "vector.hh"

int main(int argc, char *argv[]) {
	while(true) {
		std::cout << "geneous> ";
		std::string input;
		getline(std::cin, input);

		if(input == "exit") {
			exit(EXIT_SUCCESS);
		} else if(input == "help") {
			std::cout << "no commands\n";
		}
	}
	exit(EXIT_SUCCESS);
}