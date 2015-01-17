#include "headersAndFunctions.h"

//totalValidConfCount counts spatially symmetrical configurations as distinct
int chain_length,mean,stddev,totalValidConfCount=0;
int x[100],y[100],z[100];
float minEnergy=0,secondMinEnergy=1,energy[100][100];
//stores number of configurations having a given number of contacts.
map<int,int> contactFrequency; 
//stores the min energy configurations and their number of contacts
vector<pair<string,int> > minEnergyConfigurations,secondMinEnergyConfigurations;
char directions[6] = {'l','r','d','u','i','o'};
ofstream outfile1, outfile2, outfile3, outfile4, outfile5,outfile6,outfile7;

void initialize_main(char *n,char *mu,char *sigma){
	chain_length = atoi(n);
	mean = atoi(mu);
	stddev = atoi(sigma);
	outfile1.open("Output/energy_matrix.txt");
	outfile2.open("Output/min_energy.txt");
	outfile3.open("Output/contact_frequency.txt");
	outfile3 << "Contact_count Configuration_count\n";
	outfile4.open("Output/min_energy_confs_stats.txt");
	outfile4 << "Configuration contact_count\n";
	outfile5.open("Output/total_valid_conf_count.txt");
	outfile6.open("Output/second_min_energy.txt");
	outfile7.open("Output/second_min_energy_confs_stats.txt");
	outfile7 << "Configuration contact_count\n";
	return;
}

void normalDist (){
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);

	normal_distribution<double> distribution (mean,stddev);

	for(int i=1;i<=chain_length;++i){
		for(int j=1;j<=chain_length;++j){
			if(i==j)
				energy[i][j]=0;
			else {
				energy[i][j] = distribution(generator);
				energy[j][i] = energy[i][j];
			}
		}
	}
	return;
}

void setCoordinates(int n,string &tempConfiguration){
	x[1]=0;
	y[1]=0;
	z[1]=0;

	int currX = 0;
	int currY = 0;
	int currZ = 0;

	for(int i=1;i<=n-1;i++){
		switch(tempConfiguration[i-1]){
    		case 'l':
    			x[i+1] = --currX;
				y[i+1] =   currY;
				z[i+1] =   currZ;
				break;
			case 'r':
    			x[i+1] = ++currX;
				y[i+1] =   currY;
				z[i+1] =   currZ;
				break;
			case 'd':
    			x[i+1] =   currX;
				y[i+1] = --currY;
				z[i+1] =   currZ;
				break;
			case 'u':
    			x[i+1] =   currX;
				y[i+1] = ++currY;
				z[i+1] =   currZ;
				break;
			case 'i':
    			x[i+1] =   currX;
				y[i+1] =   currY;
				z[i+1] = --currZ;
				break;
			case 'o':
    			x[i+1] =   currX;
				y[i+1] =   currY;
				z[i+1] = ++currZ;
				break;
		}
	}
	return;
}

bool isValid(int n){
	bool valid = true;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j && x[i]==x[j] && y[i]==y[j] && z[i]==z[j]){
				valid = false;
				break;
			}
		}
	}
	return valid;
}

void countContactsAndFindEnergy(int n,float &currEnergy,int &nContacts){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(abs(i-j)>1 && (abs(x[i]-x[j]) + abs(y[i]-y[j]) + abs(z[i]-z[j])==1)){
				nContacts++;
				currEnergy+=energy[i][j];
			}
		}
	}
	currEnergy/=2;
	nContacts/=2;
	return;
}

void countValidConfAndFindMin(){
	int n = chain_length;
	stringstream ss;
	ss << "ValidConfigurations/" << n << "_validConfigurations.txt";
	string inputfilename = ss.str();
	string tempConfiguration;
  	ifstream inputfile (inputfilename);
  	if (inputfile.is_open()){
    	while (getline(inputfile,tempConfiguration)){
      		totalValidConfCount++;
			int nContacts    = 0;
			float currEnergy = 0;
			setCoordinates(n,tempConfiguration);
			countContactsAndFindEnergy(n,currEnergy,nContacts);
			if(currEnergy < minEnergy){
				secondMinEnergy = minEnergy;
				minEnergy = currEnergy;
				secondMinEnergyConfigurations = minEnergyConfigurations;
				minEnergyConfigurations.clear();
				minEnergyConfigurations.push_back(make_pair(tempConfiguration,nContacts));
			}
			else if(currEnergy==minEnergy){
				minEnergyConfigurations.push_back(make_pair(tempConfiguration,nContacts));	
			}
			else if(currEnergy < secondMinEnergy && currEnergy > minEnergy){
				secondMinEnergy = currEnergy;
				secondMinEnergyConfigurations.clear();
				secondMinEnergyConfigurations.push_back(make_pair(tempConfiguration,nContacts));
			}
			else if(currEnergy == secondMinEnergy){
				secondMinEnergyConfigurations.push_back(make_pair(tempConfiguration,nContacts));
			}

			if(contactFrequency.find(nContacts)==contactFrequency.end()){
				contactFrequency.insert(std::make_pair(nContacts,1));
			}
			else{
				contactFrequency[nContacts]++;
			}
  		}
  		inputfile.close();
  	}
  	else cout << "Unable to open file"; 
	return;	
}

void printValidConfs(int index,int n,ofstream &validConfigurationsFile,string &tempConfiguration){
	if(index==n-1){
		setCoordinates(n,tempConfiguration);
		if(isValid(n)){
			validConfigurationsFile << tempConfiguration << endl;
		}
		return;
	}
	
	for(int i=0;i<6;i++){
		tempConfiguration[index]=directions[i];
		printValidConfs(index+1,n,validConfigurationsFile,tempConfiguration);
	}
	return;
}

void writeOutputToFiles(){
	for(int i=1;i<=chain_length;++i){
		for(int j=1;j<=chain_length;++j){
			outfile1 << energy[i][j] << '\n'; 		
		}
	}
	
	outfile2 << minEnergy << endl;

	for (map<int,int>::iterator it=contactFrequency.begin(); it!=contactFrequency.end(); ++it)
    	outfile3 << it->first << " " << it->second << '\n';

	for (int i=0;i<minEnergyConfigurations.size();i++)
    	outfile4 << minEnergyConfigurations[i].first << " " << minEnergyConfigurations[i].second << '\n';

    outfile5 << totalValidConfCount << endl;
    outfile6 << secondMinEnergy << endl;

	for (int i=0;i<secondMinEnergyConfigurations.size();i++)
    	outfile7 << secondMinEnergyConfigurations[i].first << " " << secondMinEnergyConfigurations[i].second << '\n';    
    return;
}

void file_close() {
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();
	outfile6.close();
	outfile7.close();
	return;
}