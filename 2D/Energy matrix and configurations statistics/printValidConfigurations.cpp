#include "headersAndFunctions.h"

int main(int argc,char *argv[]){
	int n = atoi(argv[1]);
	ofstream validConfigurationsFile;
	stringstream ss;
	ss << "ValidConfigurations/" << n << "_validConfigurations.txt";
	string outfilename = ss.str();
	validConfigurationsFile.open(outfilename);
	string tempConfiguration;
	tempConfiguration.resize(n);
	printValidConfs(1,n,validConfigurationsFile,tempConfiguration);
	validConfigurationsFile.close();
    cout << "-------\nCompilation and output to file successful\n-------\n";
}