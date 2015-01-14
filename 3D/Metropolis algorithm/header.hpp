#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <climits>
#include <time.h>
#include <fstream>
#define T 1
#define Kb 1

using namespace std;

string curr_config;
int min_energy_block_size, curr_contact_no, bid_count, iter_count, *x_coord, *y_coord, *z_coord, random_choice;
float **energy_matrix, min_energy, curr_energy, neigh_energy, prob, min_energy_till_now;
long long int *contact_freq;
vector<string> curr_neighbour, neigh_neighbour;
ofstream outfile1, outfile2, outfile3, outfile4, outfile5, outfile6, outfile7;

void initialize_main(char *, char *, char *);
void file_open();
void metropolis_algo();
void initialize_iteration();
void set_coordinates(string);
int energy_calc(float &);
int check_coordinates();
void transformations_1(vector<string> &, string);
void transformations_2(vector<string> &, string);
string next_config(string &);
string reversal(string );
void transformations_3(vector<string> &, string);
void transformations_4(vector<string> &, string);
int random_num(int, int);
float random_num_float(float);
void file_close();