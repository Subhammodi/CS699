#include "func_def.hpp"

//./a.out N mu sigma no_of_seq
int main(int argc, char *argv[]) {
	bid_count = atoi(argv[1]);
	initialize_gen_seq(argv[2], argv[3]);
	for(int i=0; i<atoi(argv[4]); i++)
		normalDist(i+1);
	return 0;
}