#include "header.hpp"

void initialize_main(char *len, char *conf, char *iter) {
	min_energy_block_size = 100;
	min_energy_till_now   = 0.0;
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
	z_coord = new int[bid_count];
	contact_freq = new long long int[(int)(2*bid_count - 3*pow((bid_count*bid_count), (double)1/3) + 1)+1];
	memset(contact_freq, 0, ((int)(2*bid_count - 3*pow((bid_count*bid_count), (double)1/3) + 1)+1)*sizeof(long long int));

	srand(time(NULL));
	return;
}

void file_open() {
	outfile1.open("Output/iterations.txt");
	outfile1 << "Iteration_Number  Configuration  Energy  Contact_count\n";
	outfile2.open("Output/min_energy_config_stats.txt");
	outfile2 << "Iteration_Number  Configuration  Energy  Contact_count\n";
	outfile3.open("Output/contact_frequency_stats.txt");
	outfile3 << "Contact_count Configuration_count\n";
	outfile4.open("Output/min_energy_till_this_block_stats.txt");
	outfile4 << "Number Min_till_this_block\n";
	return;
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

int energy_calc(float &store_var) {
	int temp_contact_count = 0;

	for(int i=0; i<bid_count; i++) {
		for(int j=0; j<bid_count; j++) {
			if(abs(i-j)>1 && (abs(x_coord[i]-x_coord[j]) + abs(y_coord[i]-y_coord[j]) + abs(z_coord[i]-z_coord[j])==1)){
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
			if((x_coord[i] == x_coord[j]) && (y_coord[i] == y_coord[j]) && (z_coord[i] == z_coord[j]))
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
	if(config[0] != 'i') {
		temp[0]='i';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[0] != 'o') {
		temp[0]='o';
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
	if(config[bid_count-2] != 'i') {
		temp[bid_count-2]='i';
		set_coordinates(temp);
		if(check_coordinates())
				temp_neighbour.push_back(temp);
	}
	if(config[bid_count-2] != 'o') {
		temp[bid_count-2]='o';
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
		else if((temp[i]=='l' || temp[i]=='r') && (temp[i+1]=='i' || temp[i+1]=='o')) {
			temp_char=temp[i];
			temp[i]=temp[i+1];
			temp[i+1]=temp_char;
			set_coordinates(temp);
			if(check_coordinates())
				temp_neighbour.push_back(temp);
			temp = config;
		}
		else if((temp[i]=='i' || temp[i]=='o') && (temp[i+1]=='l' || temp[i+1]=='r')) {
			temp_char=temp[i];
			temp[i]=temp[i+1];
			temp[i+1]=temp_char;
			set_coordinates(temp);
			if(check_coordinates())
				temp_neighbour.push_back(temp);
			temp = config;
		}
		else if((temp[i]=='d' || temp[i]=='u') && (temp[i+1]=='i' || temp[i+1]=='o')) {
			temp_char=temp[i];
			temp[i]=temp[i+1];
			temp[i+1]=temp_char;
			set_coordinates(temp);
			if(check_coordinates())
				temp_neighbour.push_back(temp);
			temp = config;
		}
		else if((temp[i]=='i' || temp[i]=='o') && (temp[i+1]=='d' || temp[i+1]=='u')) {
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

/*string next_config(string &permuted_config) {
	set_coordinates(permuted_config);
	if( (x_coord[0]-x_coord[bid_count-1]) == 1)
		permuted_config = permuted_config.substr(1) + "r";
	else if( (x_coord[0]-x_coord[bid_count-1]) == -1)
		permuted_config = permuted_config.substr(1) + "l";
	else if( (y_coord[0]-y_coord[bid_count-1]) == 1)
		permuted_config = permuted_config.substr(1) + "u";
	else if( (y_coord[0]-y_coord[bid_count-1]) == -1)
		permuted_config = permuted_config.substr(1) + "d";
	else if( (z_coord[0]-z_coord[bid_count-1]) == 1)
		permuted_config = permuted_config.substr(1) + "o";
	else
		permuted_config = permuted_config.substr(1) + "i";
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
		else if(permuted_config[i] == 'u')
			permuted_config[i] = 'd';
		else if(permuted_config[i] == 'i')
			permuted_config[i] = 'o';
		else
			permuted_config[i] = 'i';
	}
	return permuted_config;
}

void transformations_3(vector<string> &temp_neighbour, string config) {
	string config_temp = config;
	set_coordinates(config_temp);
	if(bid_count > 2 && curr_contact_no == (int)(2*bid_count - 3*cbrt(bid_count*bid_count) + 1) && 
		((abs(x_coord[0]-x_coord[bid_count-1]) == 1 && y_coord[0] == y_coord[bid_count-1] && z_coord[0] == z_coord[bid_count-1]) ||
		(abs(y_coord[0]-y_coord[bid_count-1]) == 1 && x_coord[0] == x_coord[bid_count-1] && z_coord[0] == z_coord[bid_count-1]) ||
		(abs(z_coord[0]-z_coord[bid_count-1]) == 1 && x_coord[0] == x_coord[bid_count-1] && y_coord[0] == y_coord[bid_count-1])))
		for(int i=0; i<(bid_count-1); i++)
			temp_neighbour.push_back(next_config(config_temp));
	
	config_temp = config;
	set_coordinates(config_temp);
	for(int i=2; i<(bid_count-1); i++) {
		if( (x_coord[0]-x_coord[i]) == 1 && y_coord[0] == y_coord[i] && z_coord[0] == z_coord[i])
			temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "l" + config_temp.substr(i));
		else if( (x_coord[0]-x_coord[i]) == -1 && y_coord[0] == y_coord[i] && z_coord[0] == z_coord[i])
			temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "r" + config_temp.substr(i));
		else if( (y_coord[0]-y_coord[i]) == 1 && x_coord[0] == x_coord[i] && z_coord[0] == z_coord[i])
			temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "d" + config_temp.substr(i));
		else if( (y_coord[0]-y_coord[i]) == -1 && x_coord[0] == x_coord[i] && z_coord[0] == z_coord[i])
				temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "u" + config_temp.substr(i));
		else if( (z_coord[0]-z_coord[i]) == 1 && x_coord[0] == x_coord[i] && y_coord[0] == y_coord[i])
				temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "i" + config_temp.substr(i));
		else
			if( (z_coord[0]-z_coord[i]) == -1 && x_coord[0] == x_coord[i] && y_coord[0] == y_coord[i])
				temp_neighbour.push_back(reversal(config_temp.substr(0,i-1)) + "o" + config_temp.substr(i));
	}
	for(int i=1; i<(bid_count-2); i++) {
		if( (x_coord[bid_count-1]-x_coord[i]) == 1 && y_coord[bid_count-1] == y_coord[i] && z_coord[bid_count-1] == z_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "r" + reversal(config_temp.substr(i+1)));
		else if( (x_coord[bid_count-1]-x_coord[i]) == -1 && y_coord[bid_count-1] == y_coord[i] && z_coord[bid_count-1] == z_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "l" + reversal(config_temp.substr(i+1)));
		else if( (y_coord[bid_count-1]-y_coord[i]) == 1 && x_coord[bid_count-1] == x_coord[i] && z_coord[bid_count-1] == z_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "u" + reversal(config_temp.substr(i+1)));
		else if( (y_coord[bid_count-1]-y_coord[i]) == -1 && x_coord[bid_count-1] == x_coord[i] && z_coord[bid_count-1] == z_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "d" + reversal(config_temp.substr(i+1)));
		else if( (z_coord[bid_count-1]-z_coord[i]) == 1 && x_coord[bid_count-1] == x_coord[i] && y_coord[bid_count-1] == y_coord[i])
			temp_neighbour.push_back(config_temp.substr(0, i) + "o" + reversal(config_temp.substr(i+1)));
		else
			if( (z_coord[bid_count-1]-z_coord[i]) == -1 && x_coord[bid_count-1] == x_coord[i] && y_coord[bid_count-1] == y_coord[i])
				temp_neighbour.push_back(config_temp.substr(0, i) + "i" + reversal(config_temp.substr(i+1)));
	}
	return;
}*/

void transformations_4(vector<string> &temp_neighbour, string config) {
	string temp;
	for(int i=2; i<bid_count-1; i++) {
		set_coordinates(config);
		temp = config;
		if(x_coord[i-2] == x_coord[i-1] && x_coord[i-1] == x_coord[i] && x_coord[i] == x_coord[i+1]) {
			if(z_coord[i-2]==z_coord[i-1] && z_coord[i]==z_coord[i+1]) {
				if(z_coord[i]-z_coord[i-1] == 1) {
					if(y_coord[i-1] - y_coord[i-2] == 1 && y_coord[i] - y_coord[i+1] == 1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(y_coord[i-1] - y_coord[i-2] == -1 && y_coord[i] - y_coord[i+1] == -1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
				}
				if(z_coord[i]-z_coord[i-1] == -1) {
					if(y_coord[i-1] - y_coord[i-2] == 1 && y_coord[i] - y_coord[i+1] == 1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(y_coord[i-1] - y_coord[i-2] == -1 && y_coord[i] - y_coord[i+1] == -1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}	
				}
			}
			if(y_coord[i-2]==y_coord[i-1] && y_coord[i]==y_coord[i+1]) {
				if(y_coord[i]-y_coord[i-1] == 1) {
					if(z_coord[i-1] - z_coord[i-2] == 1 && z_coord[i] - z_coord[i+1] == 1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(z_coord[i-1] - z_coord[i-2] == -1 && z_coord[i] - z_coord[i+1] == -1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
				}
				if(y_coord[i]-y_coord[i-1] == -1) {
					if(z_coord[i-1] - z_coord[i-2] == 1 && z_coord[i] - z_coord[i+1] == 1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(z_coord[i-1] - z_coord[i-2] == -1 && z_coord[i] - z_coord[i+1] == -1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}	
				}
			}
		}
		if(y_coord[i-2] == y_coord[i-1] && y_coord[i-1] == y_coord[i] && y_coord[i] == y_coord[i+1]) {
			if(z_coord[i-2]==z_coord[i-1] && z_coord[i]==z_coord[i+1]) {
				if(z_coord[i]-z_coord[i-1] == 1) {
					if(x_coord[i-1] - x_coord[i-2] == 1 && x_coord[i] - x_coord[i+1] == 1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(x_coord[i-1] - x_coord[i-2] == -1 && x_coord[i] - x_coord[i+1] == -1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
				}
				if(z_coord[i]-z_coord[i-1] == -1) {
					if(x_coord[i-1] - x_coord[i-2] == 1 && x_coord[i] - x_coord[i+1] == 1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(x_coord[i-1] - x_coord[i-2] == -1 && x_coord[i] - x_coord[i+1] == -1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}	
				}
			}
			if(x_coord[i-2]==x_coord[i-1] && x_coord[i]==x_coord[i+1]) {
				if(x_coord[i]-x_coord[i-1] == 1) {
					if(z_coord[i-1] - z_coord[i-2] == 1 && z_coord[i] - z_coord[i+1] == 1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(z_coord[i-1] - z_coord[i-2] == -1 && z_coord[i] - z_coord[i+1] == -1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
				}
				if(x_coord[i]-x_coord[i-1] == -1) {
					if(z_coord[i-1] - z_coord[i-2] == 1 && z_coord[i] - z_coord[i+1] == 1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(z_coord[i-1] - z_coord[i-2] == -1 && z_coord[i] - z_coord[i+1] == -1 && z_coord[i] == z_coord[i-1]) {
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}	
				}
			}	
		}
		if(z_coord[i-2] == z_coord[i-1] && z_coord[i-1] == z_coord[i] && z_coord[i] == z_coord[i+1]) {
			if(x_coord[i-2]==x_coord[i-1] && x_coord[i]==x_coord[i+1]) {
				if(x_coord[i]-x_coord[i-1] == 1) {
					if(y_coord[i-1] - y_coord[i-2] == 1 && y_coord[i] - y_coord[i+1] == 1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(y_coord[i-1] - y_coord[i-2] == -1 && y_coord[i] - y_coord[i+1] == -1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
				}
				if(x_coord[i]-x_coord[i-1] == -1) {
					if(y_coord[i-1] - y_coord[i-2] == 1 && y_coord[i] - y_coord[i+1] == 1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'd';
						temp[i] = 'u';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(y_coord[i-1] - y_coord[i-2] == -1 && y_coord[i] - y_coord[i+1] == -1 && y_coord[i] == y_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'u';
						temp[i] = 'd';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}	
				}
			}
			if(y_coord[i-2]==y_coord[i-1] && y_coord[i]==y_coord[i+1]) {
				if(y_coord[i]-y_coord[i-1] == 1) {
					if(x_coord[i-1] - x_coord[i-2] == 1 && x_coord[i] - x_coord[i+1] == 1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(x_coord[i-1] - x_coord[i-2] == -1 && x_coord[i] - x_coord[i+1] == -1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
				}
				if(y_coord[i]-y_coord[i-1] == -1) {
					if(x_coord[i-1] - x_coord[i-2] == 1 && x_coord[i] - x_coord[i+1] == 1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'l';
						temp[i] = 'r';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}
					if(x_coord[i-1] - x_coord[i-2] == -1 && x_coord[i] - x_coord[i+1] == -1 && x_coord[i] == x_coord[i-1]) {
						temp[i-2] = 'i';
						temp[i] = 'o';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'o';
						temp[i] = 'i';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						temp[i-2] = 'r';
						temp[i] = 'l';
						set_coordinates(temp);
						if(check_coordinates())
							temp_neighbour.push_back(temp);
						continue;
					}	
				}
			}
		}
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
	return;
}

void metropolis_algo() {
	for(int i=1; i<=iter_count; i++) {
		printf("Iteration %d\n", i);
		initialize_iteration();
		set_coordinates(curr_config);
		curr_contact_no = energy_calc(curr_energy);

		outfile1 << i << " " << curr_config << " " << curr_energy << " " << curr_contact_no << endl;

		if((curr_energy-min_energy) <= 0.001)
			outfile2 << i << " " << curr_config << " " << curr_energy << " " << curr_contact_no << endl;

		if(curr_energy < min_energy_till_now)
			min_energy_till_now = curr_energy;

		if(i%min_energy_block_size == 0)
			outfile4 << i/min_energy_block_size << " " << min_energy_till_now << endl;

		contact_freq[curr_contact_no]++;

		transformations_1(curr_neighbour, curr_config);
		transformations_2(curr_neighbour, curr_config);
		//transformations_3(curr_neighbour, curr_config);
		transformations_4(curr_neighbour, curr_config);

		random_choice=random_num(0,curr_neighbour.size());;

		set_coordinates(curr_neighbour[random_choice]);
		energy_calc(neigh_energy);
		transformations_1(neigh_neighbour, curr_neighbour[random_choice]);
		transformations_2(neigh_neighbour, curr_neighbour[random_choice]);
		//transformations_3(neigh_neighbour, curr_neighbour[random_choice]);
		transformations_4(neigh_neighbour, curr_neighbour[random_choice]);

		if(neigh_energy < curr_energy)
			curr_config = curr_neighbour[random_choice];
		else {
			prob = (((float)(curr_neighbour.size()))*exp(-1*(neigh_energy-curr_energy)/(Kb*T)))/((float)(neigh_neighbour.size()));
			if(random_num_float(1.0) <= prob)
				curr_config = curr_neighbour[random_choice];
		}
	}

	for(int i=0; i<(int)(2*bid_count - 3*pow((bid_count*bid_count), (double)1/3) + 1)+1; i++)
		outfile3 << i << " " << contact_freq[i] << endl;
	return;
}