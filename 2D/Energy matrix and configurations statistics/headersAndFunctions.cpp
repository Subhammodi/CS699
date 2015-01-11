#include "headersAndFunctions.h"

//totalValidConfCount counts spatially symmetrical configurations as distinct
int chain_length,mean,stddev,totalValidConfCount=0;
int x[100],y[100];
float minEnergy=0,energy[100][100];
//stores number of configurations having a given number of contacts.
map<int,int> contactFrequency; 
//stores the min energy configurations and their number of contacts
vector<pair<string,int> > minEnergyConfigurations;
char directions[4] = {'l','r','u','d'};
ofstream outfile1, outfile2, outfile3, outfile4, outfile5;

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
}

void normalDist (){
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator (seed);

	normal_distribution<double> distribution (mean,stddev);

	for(int i=1;i<=chain_length;++i){
		for(int j=1;j<=chain_length;++j){
			if(i==j){energy[i][j]=0;continue;}
			energy[i][j] = distribution(generator); 		
		}
	}
}

void setCoordinates(int n,string &tempConfiguration){
	x[1]=0;
	y[1]=0;

	int currX = 0;
	int currY = 0;

	for(int i=1;i<n;i++){
		if(tempConfiguration[i]=='l'){
			x[i+1]=--currX;
			y[i+1]=currY;
		}
		else if(tempConfiguration[i]=='r'){
			x[i+1]=++currX;
			y[i+1]=currY;
		}
		else if(tempConfiguration[i]=='d'){
			x[i+1]=currX;
			y[i+1]=--currY;
		}
		else if(tempConfiguration[i]=='u'){
			x[i+1]=currX;
			y[i+1]=++currY;
		}
	}
}

bool isValid(int n){
	bool valid = true;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i!=j && x[i]==x[j] && y[i]==y[j]){
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
			if(abs(i-j)>1 && (abs(x[i]-x[j]) + abs(y[i]-y[j])==1)){
				nContacts++;
				currEnergy+=energy[i][j];
			}
		}
	}
	currEnergy/=2;
	nContacts/=2;
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
				minEnergy = currEnergy;
				minEnergyConfigurations.clear();
				minEnergyConfigurations.push_back(make_pair(tempConfiguration,nContacts));
			}
			else if(currEnergy==minEnergy){
				minEnergyConfigurations.push_back(make_pair(tempConfiguration,nContacts));	
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
	if(index==n){
		setCoordinates(n,tempConfiguration);
		if(isValid(n)){
			validConfigurationsFile << tempConfiguration << endl;
			//cout << tempConfiguration << endl;
		}
		return;
	}
	
	for(int i=0;i<4;i++){
		tempConfiguration[index]=directions[i];
		printValidConfs(index+1,n,validConfigurationsFile,tempConfiguration);
	}
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
    
    return;
}

void file_close() {
	outfile1.close();
	outfile2.close();
	outfile3.close();
	outfile4.close();
	outfile5.close();
	return;
}