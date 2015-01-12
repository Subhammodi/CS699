#include "metropolis_function.hpp"

int main(int argc, char *argv[]) {
	initialize_main(argv[1], argv[2], argv[3]);
	file_open();
	metropolis_algo();
	file_close();
	cout << "-------\nCompilation and output to file successful\n-------\n";
	return 0;
}