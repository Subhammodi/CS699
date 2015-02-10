#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <vector>
#define Kb 50

using namespace std;

vector<string> minEnergyConfigurations, secondMinEnergyConfigurations;
int bid_count, *x_coord, *y_coord, *z_coord;
float curr_energy, T, X, mu, sigma, **energy_matrix, minEnergy=0, secondMinEnergy=1;
ofstream outfile1, outfile2, outfile3, outfile4;

void initialize(char *, char *);
void initialize_gen_seq(char *, char *);
void initialize_X_given_T(char *);
void initialize_T_given_X(char *);
void initialize_seq_stats(void);
void normalDist(int);
void set_pair_energy(char *);
void set_coordinates(string);
void energy_calc(float &);
float calculate_X(char *);
float calculate_T(char *);
float calculate_prob(char *);
void countValidConfAndFindMin(char *);
void writeOutputToFiles();
void file_close(void);
