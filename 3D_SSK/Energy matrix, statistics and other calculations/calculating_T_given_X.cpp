	#include "func_def.hpp"

//./a.out 27_valid seuence_27_1 N X
int main(int argc, char *argv[]) {
	initialize(argv[3], argv[2]);
	initialize_T_given_X(argv[4]);
	printf("T = %Lf\n", calculate_T(argv[1]));
	return 0;
}
