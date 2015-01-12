#include "header.hpp"

void initialize_main(char *len, char *conf, char *iter) {
	bid_count = atoi(len);
	curr_config = string(conf);
	iter_count = atoi(iter);

	char temp[100];
	FILE *fp_minenergy = fopen("../Energy matrix and configurations statistics/Output/min_energy.txt", "r");
	fscanf(fp_minenergy, "%s", temp);
	min_energy = atof(temp);

	FILE *fp_energy = fopen("../Energy matrix and configurations statistics/Output/energy_matrix.txt", "r");
	energy_matrix = new float*[bid_count];
	for(int i=0; i<bid_count; i++) {
		energy_matrix[i] = new float[bid_count];
		for(int j=0; j<bid_count; j++) {
			fscanf(fp_energy,"%s",temp);
			energy_matrix[i][j] = atof(temp);
		}
	}

	x_coord = new int[bid_count];
	y_coord = new int[bid_count];
	contact_freq = new long long int[(int)(pow(sqrt(bid_count)-1, 2))+1];
	memset(contact_freq, 0, ((int)(pow(sqrt(bid_count)-1, 2))+1)*sizeof(long long int));

	srand(time(NULL));
	return;
}

void file_open() {
	outfile1.open("Output/iterations.txt");
	outfile1 << "Iteration_Number  Configuration  Energy  Contact_count\n";
	outfile2.open("Output/min_energy_config_stats.txt");
	outfile2 << "Iteration_Number  Configuration  Energy  Contact_count\n";
	outfile3.open("Output/max_contact_config_stats.txt");
	outfile3 << "Iteration_Number  Configuration  Energy  Contact_count\n";
	outfile4.open("Output/contact_frequency_stats.txt");
	outfile4 << "Contact_count Configuration_count\n";
	outfile5.open("Output/backend_check1.txt");
	outfile5 << "Iteration_Number Randon_Choice Neighbour_Count\n";
	outfile6.open("Output/backend_check2.txt");
	outfile6 << "Iteration_Number Probability\n";
}

void initialize_iteration() {
	curr_energy = 0.0;
	neigh_energy = 0.0;
	curr_contact_no = 0;
	curr_neighbour.clear();
	neigh_neighbour.clear();
	return;
}

void set_coordinates(string config) {
	x_coord[0] = 0;
	y_coord[0] = 0;
	int x=0, y=0, i=0;
	for(i=0; i<bid_count-1; i++) {
		if(config[i] == 'l') {
			x_coord[i+1] = --x;
			y_coord[i+1] = y;
		}
		else if(config[i] == 'r') {
			x_coord[i+1] = ++x;
			y_coord[i+1] = y;
		}
		else if(config[i] == 'd') {
			y_coord[i+1] = --y;
			x_coord[i+1] = x;
		}
		else if(config[i] == 'u') {
			y_coord[i+1] = ++y;
			x_coord[i+1] = x;
		}
	}
	return;
}

int energy_calc(float &store_var) {
	int temp_contact_count = 0;
	float distance;

	for(int i=0; i<bid_count; i++) {
		for(int j=0; j<bid_count; j++) {
			distance=(float)(sqrt((x_coord[i]-x_coord[j])*(x_coord[i]-x_coord[j])+(y_coord[i]-y_coord[j])*(y_coord[i]-y_coord[j])));
			if(distance <= 1.0 && (i-j!=1) && (j-i!=1) && (i!=j)) {
				temp_contact_count += 1;
				store_var += energy_matrix[i][j];
			}
		}
	}
	store_var /= 2;
	return (temp_contact_count/2);
}

int check_coordinates() {
	for(int i=0; i<bid_count; i++)
		for(int j=i+1; j<bid_count; j++)
			if((x_coord[i] == x_coord[j]) && (y_coord[i] == y_coord[j]))
				return 0;
	return 1;
}

void transformations_1(vector<string> &temp_neighbour, string config) {
	string temp = config;

	if(config[0] != 'l') {
		temp[0]='l';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[0] != 'r') {
		temp[0]='r';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[0] != 'd') {
		temp[0]='d';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[0] != 'u') {
		temp[0]='u';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}

	temp = config;
	if(config[bid_count-2] != 'l') {
		temp[bid_count-2]='l';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[bid_count-2] != 'r') {
		temp[bid_count-2]='r';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[bid_count-2] != 'd') {
		temp[bid_count-2]='d';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[bid_count-2] != 'u') {
		temp[bid_count-2]='u';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	return;
}

void transformations_2(vector<string> &temp_neighbour, string config) {
	string temp = config;
	char temp_char;
	for(int i=0; i<bid_count-2; i++) {
		if((temp[i]=='r' || temp[i]=='l') && (temp[i+1]=='d' || temp[i+1]=='u')) {
			temp_char=temp[i];
			temp[i]=temp[i+1];
			temp[i+1]=temp_char;
			set_coordinates(temp);
			if(check_coordinates())
				temp_neighbour.push_back(temp);
			temp = config;
		}
		else if((temp[i]=='d' || temp[i]=='u') && (temp[i+1]=='r' || temp[i+1]=='l')) {
			temp_char=temp[i];
			temp[i]=temp[i+1];
			temp[i+1]=temp_char;
			set_coordinates(temp);
			if(check_coordinates())
				temp_neighbour.push_back(temp);
			temp = config;
		}
	}
	return;
}

string next_config(string &permuted_config) {
	set_coordinates(permuted_config);
	if( (x_coord[0]-x_coord[bid_count-1]) == 1)
		permuted_config = permuted_config.substr(1) + "r";
	else if( (x_coord[0]-x_coord[bid_count-1]) == -1)
		permuted_config = permuted_config.substr(1) + "l";
	else if( (y_coord[0]-y_coord[bid_count-1]) == 1)
		permuted_config = permuted_config.substr(1) + "u";
	else
		permuted_config = permuted_config.substr(1) + "d";
	return permuted_config;

}

string reversal(string permuted_config) {
	reverse(permuted_config.begin(), permuted_config.end());
	for(int i=0; i<permuted_config.size(); i++) {
		if(permuted_config[i] == 'l')
			permuted_config[i] = 'r';
		else if(permuted_config[i] == 'r')
			permuted_config[i] = 'l';
		else if(permuted_config[i] == 'd')
			permuted_config[i] = 'u';
		else
			permuted_config[i] = 'd';
	}
	return permuted_config;
}

void transformations_3(vector<string> &temp_neighbour, string config) {
	string config_temp = config;
	set_coordinates(config_temp);
	if(bid_count > 2 && curr_contact_no == (int)(pow(sqrt(bid_count)-1, 2)) && 
		(abs(x_coord[0]-x_coord[bid_count-1]) == 1 && y_coord[0] == y_coord[bid_count-1] ) ||
		(abs(y_coord[0]-y_coord[bid_count-1]) == 1 && x_coord[0] == x_coord[bid_count-1])) {
		for(int i=0; i<(bid_count-1); i++)
			temp_neighbour.push_back(next_config(config_temp));
	}
	
	config_temp = config;
	set_coordinates(config_temp);
	for(int i=2; i<(bid_count-1); i++) {
		if( (x_coord[0]-x_coord[i]) == 1 && y_coord[0] == y_coord[i])
			temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "l" + config_temp.substr(i));
		else if( (x_coord[0]-x_coord[i]) == -1 && y_coord[0] == y_coord[i])
			temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "r" + config_temp.substr(i));
		else if( (y_coord[0]-y_coord[i]) == 1 && x_coord[0] == x_coord[i])
			temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "d" + config_temp.substr(i));
		else
			if( (y_coord[0]-y_coord[i]) == -1 && x_coord[0] == x_coord[i])
				temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "u" + config_temp.substr(i));
	}
	for(int i=1; i<(bid_count-2); i++) {
		if( (x_coord[bid_count-1]-x_coord[i]) == 1 && y_coord[bid_count-1] == y_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "r" + reversal(config_temp.substr(i+1)));
		else if( (x_coord[bid_count-1]-x_coord[i]) == -1 && y_coord[bid_count-1] == y_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "l" + reversal(config_temp.substr(i+1)));
		else if( (y_coord[bid_count-1]-y_coord[i]) == 1 && x_coord[bid_count-1] == x_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "u" + reversal(config_temp.substr(i+1)));
		else
			if( (y_coord[bid_count-1]-y_coord[i]) == -1 && x_coord[bid_count-1] == x_coord[i])
				temp_neighbour.push_back(config_temp.substr(0, i) + "d" + reversal(config_temp.substr(i+1)));
	}
	return;
}

int random_num(int low,int high) {
	return(int)(low+rand()%(high-low));
}

float random_num_float(float high) {
	return ((float)rand()/(float)(RAND_MAX))*(float)high;
}

void file_close() {
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();
	outfile6.close();
	return;
}

void metropolis_algo() {
	for(int i=0; i<iter_count; i++) {
		printf("Iteration %d\n", i+1);
		initialize_iteration();
		set_coordinates(curr_config);
		curr_contact_no = energy_calc(curr_energy);

		curr_energy = floorf(curr_energy * 10) / 10;
		min_energy = floorf(min_energy*10)/10;


		outfile1 << i+1 << " " << curr_config << " " << curr_energy << " " << curr_contact_no << endl;

		if(curr_energy<=min_energy)
			outfile2 << i+1 << " " << curr_config << " " << curr_energy << " " << curr_contact_no << endl;

		if(curr_contact_no == (int)(pow(sqrt(bid_count)-1, 2)))
			outfile3 << i+1 << " " << curr_config << " " << curr_energy << " " << curr_contact_no << endl;

		contact_freq[curr_contact_no]++;

		transformations_1(curr_neighbour, curr_config);
		transformations_2(curr_neighbour, curr_config);
		transformations_3(curr_neighbour, curr_config);

		random_choice=random_num(0,curr_neighbour.size());;
		outfile5 << i+1 << " " << random_choice << " " << curr_neighbour.size() << endl;

		set_coordinates(curr_neighbour[random_choice]);
		energy_calc(neigh_energy);
		transformations_1(neigh_neighbour, curr_neighbour[random_choice]);
		transformations_2(neigh_neighbour, curr_neighbour[random_choice]);
		transformations_3(neigh_neighbour, curr_neighbour[random_choice]);

		if(neigh_energy < curr_energy)
			curr_config = curr_neighbour[random_choice];
		else {
			prob = (((float)(curr_neighbour.size()))*exp(-1*(neigh_energy-curr_energy)/(Kb*T)))/((float)(neigh_neighbour.size()));
			outfile6 << i+1 << " " << prob << endl;
			if(random_num_float(1.0) <= prob)
				curr_config = curr_neighbour[random_choice];
		}
	}

	for(int i=0; i<(int)(pow(sqrt(bid_count)-1, 2))+1; i++)
		outfile4 << i << " " << contact_freq[i] << endl;
	return;
}