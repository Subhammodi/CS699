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

using namespace std;

void initialize_main(char *,char *,char *);
void normalDist(void);
void setCoordinates(int n);
bool isValid(int n);
void countContactsAndFindEnergy(int n,float &energy,int &nContacts);
void countValidConfAndFindMin(int index);
void writeOutputToFiles();
void file_close(void);
#endif


