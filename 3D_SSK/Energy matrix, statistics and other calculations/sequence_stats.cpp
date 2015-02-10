#include "func_def.hpp"

//./a.out 27_valid seuence_27_1 N
int main(int argc, char *argv[]) {
	initialize(argv[3], argv[2]);
	initialize_seq_stats();
	countValidConfAndFindMin(argv[1]);
	writeOutputToFiles();
    file_close();
	cout << "-------\nCompilation and output to file successful\n-------\n";
	return 0;
}