#include "headersAndFunctions.h"

int main(int argc,char *argv[]){
	initialize_main(argv[1],argv[2],argv[3]);
	normalDist();
	countValidConfAndFindMin(1);
	writeOutputToFiles();
    file_close();
    cout << "-------\nCompilation and output to file successful\n-------\n";
}