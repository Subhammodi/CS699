#include "header.hpp"

void initialize(char *bid_count_arg, char *seq_filename) {
	bid_count = atoi(bid_count_arg);

	x_coord = new int[bid_count];
	y_coord = new int[bid_count];
	z_coord = new int[bid_count];

	stringstream ss;
	ss << "sequences/" << seq_filename;
	string inputfilename = ss.str();

	char temp[100];
	FILE *fp_energy = fopen(inputfilename.c_str(), "r");
	energy_matrix = new float*[bid_count];
	for(int i=0; i<bid_count; i++) {
		energy_matrix[i] = new float[bid_count];
		for(int j=0; j<bid_count; j++) {
			fscanf(fp_energy,"%s",temp);
			energy_matrix[i][j] = atof(temp);
		}
	}
	return;
}

void initialize_gen_seq(char *mu_arg, char *sigma_arg) {
	energy_matrix = new float*[bid_count];
	for(int i=0; i<bid_count; i++)
		energy_matrix[i] = new float[bid_count];

	mu = atof(mu_arg);
	sigma = atof(sigma_arg);
	return;
}

void initialize_X_given_T(char *temp_arg) {
	T = atof(temp_arg);
	return;
}

void initialize_T_given_X(char *X_arg) {
	X = atof(X_arg);
	return;
}

void initialize_seq_stats() {
	outfile1.open("Output_sequences_statistics/min_energy.txt");
	outfile2.open("Output_sequences_statistics/min_energy_confs_stats.txt");
	outfile3.open("Output_sequences_statistics/second_min_energy.txt");
	outfile4.open("Output_sequences_statistics/second_min_energy_confs_stats.txt");
	return;
}

void normalDist (int i){
	stringstream ss;
	ss << "sequences/" << i << "_" << bid_count << "_matrix.txt";
	outfile1.open(ss.str());

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	normal_distribution<double> distribution(mu,sigma);

	for(int i=0; i<bid_count; ++i){
		for(int j=0; j<bid_count; ++j){
			if(i == j)
				energy_matrix[i][j]=0;
			else {
				energy_matrix[i][j] = distribution(generator);
				energy_matrix[j][i] = energy_matrix[i][j];
			}
		}
	}

	for(int i=0; i<bid_count; ++i)
		for(int j=0; j<bid_count; ++j)
			outfile1 << energy_matrix[i][j] << '\n';

	outfile1.close();
	return;
}

void set_coordinates(string config) {
	x_coord[0] = 0;
	y_coord[0] = 0;
	z_coord[0] = 0;
	int x=0, y=0, z=0, i=0;
	for(i=0; i<bid_count-1; i++) {
		if(config[i] == 'l') {
			x_coord[i+1] = --x;
			y_coord[i+1] = y;
			z_coord[i+1] = z;
		}
		else if(config[i] == 'r') {
			x_coord[i+1] = ++x;
			y_coord[i+1] = y;
			z_coord[i+1] = z;
		}
		else if(config[i] == 'd') {
			y_coord[i+1] = --y;
			x_coord[i+1] = x;
			z_coord[i+1] = z;
		}
		else if(config[i] == 'u') {
			y_coord[i+1] = ++y;
			x_coord[i+1] = x;
			z_coord[i+1] = z;
		}
		else if(config[i] == 'i') {
			y_coord[i+1] = y;
			x_coord[i+1] = x;
			z_coord[i+1] = --z;
		}
		else if(config[i] == 'o') {
			y_coord[i+1] = y;
			x_coord[i+1] = x;
			z_coord[i+1] = ++z;
		}
	}
	return;
}

void energy_calc(float &store_var) {
	store_var = 0;

	for(int i=0; i<bid_count; i++) {
		for(int j=0; j<bid_count; j++) {
			if(abs(i-j)>1 && (abs(x_coord[i]-x_coord[j]) + abs(y_coord[i]-y_coord[j]) + abs(z_coord[i]-z_coord[j])==1))
				store_var += energy_matrix[i][j];
		}
	}
	store_var /= 2;
	return;
}

float calculate_X(char *valid_filename) {
	float energy_sum = 0, energy2_sum = 0;
	stringstream ss;
	ss << "Valid_compact_configurations/" << valid_filename;
	string curr_config, inputfilename = ss.str();
  	ifstream inputfile(inputfilename.c_str());
  	if (inputfile.is_open()){
    	while(getline(inputfile,curr_config)){
    		set_coordinates(curr_config);
    		energy_calc(curr_energy);
    		curr_energy = exp(-1.0*(double)(curr_energy/(Kb*T)));
    		energy_sum += curr_energy;
    		energy2_sum += curr_energy*curr_energy;
    	}

  		inputfile.close();
  		return (1 - ((double)energy2_sum/(energy_sum*energy_sum)));
  	}
  	else {
  		cout << "Unable to open file\n";
  		return -1;
  	}
}

float calculate_T(char *valid_filename) {
	float start= 0, end = 64;
	T = 65;
	if(X > calculate_X(valid_filename))
		return -1;

	while((end-start) >= 0.1) {
    	T = (start + end)/2;
    	if(fabs(X - calculate_X(valid_filename)) <= 0.000005)
    		break;
    	else if(X > calculate_X(valid_filename))
    		start = T;
    	else
    		end = T;
  	}
	return T;
}

float calculate_prob(char *valid_filename) {
	float temp = 0;
	float energy_sum = 0;
	stringstream ss;
	ss << "Valid_compact_configurations/" << valid_filename;
	string curr_config, inputfilename = ss.str();
  	ifstream inputfile(inputfilename.c_str());
  	if (inputfile.is_open()){
    	while(getline(inputfile,curr_config)){
    		set_coordinates(curr_config);
    		energy_calc(curr_energy);
		if(curr_energy < temp)
			temp = curr_energy;
    		curr_energy = exp(-1.0*(double)(curr_energy/(Kb*T)));
    		energy_sum += curr_energy;
    	}
  		inputfile.close();
    		temp = exp(-1.0*(double)(temp/(Kb*T)));
  		return (temp/energy_sum);
  	}
  	else {
  		cout << "Unable to open file\n";
  		return -1;
  	}
}

void countValidConfAndFindMin(char *valid_filename){
	stringstream ss;
	ss << "Valid_compact_configurations/" << valid_filename;
	string curr_config, inputfilename = ss.str();
  	ifstream inputfile (inputfilename.c_str());
  	if (inputfile.is_open()){
    	while (getline(inputfile,curr_config)){
			set_coordinates(curr_config);
			energy_calc(curr_energy);
			if(curr_energy < minEnergy){
				secondMinEnergy = minEnergy;
				minEnergy = curr_energy;
				secondMinEnergyConfigurations = minEnergyConfigurations;
				minEnergyConfigurations.clear();
				minEnergyConfigurations.push_back(curr_config);
			}
			else if(curr_energy == minEnergy){
				minEnergyConfigurations.push_back(curr_config);
			}
			else if(curr_energy < secondMinEnergy && curr_energy > minEnergy){
				secondMinEnergy = curr_energy;
				secondMinEnergyConfigurations.clear();
				secondMinEnergyConfigurations.push_back(curr_config);
			}
			else if(curr_energy == secondMinEnergy){
				secondMinEnergyConfigurations.push_back(curr_config);
			}
  		}
  		inputfile.close();
  	}
  	else
  		cout << "Unable to open file"; 
	return;	
}

void writeOutputToFiles(){	
	outfile1 << minEnergy << endl;

	for (int i=0;i<minEnergyConfigurations.size();i++)
    	outfile2 << minEnergyConfigurations[i] << '\n';

    outfile3 << secondMinEnergy << endl;

	for (int i=0;i<secondMinEnergyConfigurations.size();i++)
    	outfile4 << secondMinEnergyConfigurations[i] << '\n';    
    return;
}

void file_close() {
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	return;
}
