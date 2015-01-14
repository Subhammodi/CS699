#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <chrono>
#include <random>
#include <map>
#include <fstream>
#include <cmath>      
#include <vector>
#include <string>
#include <utility>  
#include <cstdlib>  
#include <sstream> 

using namespace std;

//------used by printValidConfigurations.cpp
void setCoordinates(int,string &);
bool isValid(int n);
void printValidConfs(int,int,ofstream &,string &);
//------used by energyMAtrixAndMinEnergyConf_3D.cpp
void initialize_main(char *,char *,char *);
void normalDist(void);
void countContactsAndFindEnergy(int n,float &energy,int &nContacts);
void countValidConfAndFindMin(void);
void writeOutputToFiles();
void file_close(void);
#endif


