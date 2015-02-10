#include "metropolis_function.hpp"

int main(int argc, char *argv[]) {
	foldicity = 0;
	for(int i=0; i<atoi(argv[5]); i++) {
		initialize_main(argv[1], argv[2], argv[3], argv[4]);
		file_open(i+1);
		metropolis_algo(i+1);
		file_close();
	}

	printf("-------\nFoldicity = %f\n", foldicity/atof(argv[5]));
	cout << "-------\nCompilation and output to file successful\n-------\n";

	return 0;
}