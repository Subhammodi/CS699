#include "func_def.hpp"

//./a.out 27_valid sequence_27_1 N T
int main(int argc, char *argv[]) {
	initialize(argv[3], argv[2]);
	initialize_X_given_T(argv[4]);
	printf("X = %Lf\n", calculate_X(argv[1]));
	return 0;
}
