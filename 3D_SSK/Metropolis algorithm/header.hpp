#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <climits>
#include <time.h>
#include <fstream>
#define Kb 50

using namespace std;

string curr_config;
int min_energy_block_size, curr_contact_no, bid_count, iter_count, *x_coord, *y_coord, *z_coord, random_choice;
long double **energy_matrix, min_energy, curr_energy, neigh_energy, prob, min_energy_till_now, T, foldicity;
long long int *contact_freq;
vector<string> curr_neighbour, neigh_neighbour;
ofstream outfile1, outfile2, outfile3, outfile4;

void initialize_main(char *, char *, char *, char *, char *);
void file_open(int);
void initialize_iteration();
void set_coordinates(string);
int energy_calc(long double &);
int check_coordinates();
void transformations_1(vector<string> &, string);
void transformations_2(vector<string> &, string);
string next_config(string &);
string reversal(string );
void transformations_3(vector<string> &, string);
void transformations_4(vector<string> &, string);
int random_num(int, int);
long double random_num_float(long double);
void file_close();
void metropolis_algo(int);
