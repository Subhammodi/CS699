#include "valid_compact_config_header.hpp"

int main(int argc, char *argv[]) {
	if(atoi(argv[1]) != 27) {
		printf("Input 27 as length of protein. Only 27 is accepted. Exiting\n");
		return 0;
	}
	outfile.open("Valid_compact_configurations/27_valid.txt");
	initialize();
    intialize_valid_directions_1();
	visited[1] = true;
	dfs_valid(1, 1);
	visited[1] = false;

    intialize_valid_directions_2();
	visited[5] = true;
	dfs_valid(5, 1);
	visited[5] = false;
	outfile.close();
	return 0;
}
