#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, char> > directions[28];
bool *visited;
string temp_valid;
vector<string> valid_config, all_perm;
ofstream outfile;
int lrud = 0;

void initialize() {
	visited = new bool[28];
	memset(visited, 0, 28*sizeof(bool));
	temp_valid = "xxxxxxxxxxxxxxxxxxxxxxxxxx";
	return;
}

void intialize_valid_directions_1() {
	directions[1].push_back(make_pair(2,'r'));
	directions[2].push_back(make_pair(1,'l'));
	directions[2].push_back(make_pair(3,'r'));
	directions[2].push_back(make_pair(5,'u'));
	directions[2].push_back(make_pair(17,'o'));
	directions[3].push_back(make_pair(2,'l'));
	directions[3].push_back(make_pair(4,'u'));
	directions[3].push_back(make_pair(16,'o'));
	directions[4].push_back(make_pair(3,'d'));
	directions[4].push_back(make_pair(5,'l'));
	directions[4].push_back(make_pair(9,'u'));
	directions[4].push_back(make_pair(15,'o'));
	directions[5].push_back(make_pair(2,'d'));
	directions[5].push_back(make_pair(4,'r'));
	directions[5].push_back(make_pair(6,'l'));
	directions[5].push_back(make_pair(8,'u'));
	directions[5].push_back(make_pair(14,'o'));
	directions[6].push_back(make_pair(1,'d'));
	directions[6].push_back(make_pair(5,'r'));
	directions[6].push_back(make_pair(7,'u'));
	directions[6].push_back(make_pair(13,'o'));
	directions[7].push_back(make_pair(6,'d'));
	directions[7].push_back(make_pair(8,'r'));
	directions[7].push_back(make_pair(12,'o'));
	directions[8].push_back(make_pair(5,'d'));
	directions[8].push_back(make_pair(7,'l'));
	directions[8].push_back(make_pair(9,'r'));
	directions[8].push_back(make_pair(11,'o'));
	directions[9].push_back(make_pair(4,'d'));
	directions[9].push_back(make_pair(8,'l'));
	directions[9].push_back(make_pair(10,'o'));
	directions[10].push_back(make_pair(9,'i'));
	directions[10].push_back(make_pair(11,'l'));
	directions[10].push_back(make_pair(15,'d'));
	directions[10].push_back(make_pair(27,'o'));
	directions[11].push_back(make_pair(8,'i'));
	directions[11].push_back(make_pair(10,'r'));
	directions[11].push_back(make_pair(12,'l'));
	directions[11].push_back(make_pair(14,'d'));
	directions[11].push_back(make_pair(26,'o'));
	directions[12].push_back(make_pair(7,'i'));
	directions[12].push_back(make_pair(11,'r'));
	directions[12].push_back(make_pair(13,'d'));
	directions[12].push_back(make_pair(25,'o'));
	directions[13].push_back(make_pair(6,'i'));
	directions[13].push_back(make_pair(12,'u'));
	directions[13].push_back(make_pair(14,'r'));
	directions[13].push_back(make_pair(18,'d'));
	directions[13].push_back(make_pair(24,'o'));
	directions[14].push_back(make_pair(5,'i'));
	directions[14].push_back(make_pair(11,'u'));
	directions[14].push_back(make_pair(13,'l'));
	directions[14].push_back(make_pair(15,'r'));
	directions[14].push_back(make_pair(17,'d'));
	directions[14].push_back(make_pair(23,'o'));
	directions[15].push_back(make_pair(4,'i'));
	directions[15].push_back(make_pair(10,'u'));
	directions[15].push_back(make_pair(14,'l'));
	directions[15].push_back(make_pair(16,'d'));
	directions[15].push_back(make_pair(22,'o'));
	directions[16].push_back(make_pair(3,'i'));
	directions[16].push_back(make_pair(15,'u'));
	directions[16].push_back(make_pair(17,'l'));
	directions[16].push_back(make_pair(21,'o'));
	directions[17].push_back(make_pair(2,'i'));
	directions[17].push_back(make_pair(14,'u'));
	directions[17].push_back(make_pair(16,'r'));
	directions[17].push_back(make_pair(18,'l'));
	directions[17].push_back(make_pair(20,'o'));
	directions[18].push_back(make_pair(1,'i'));
	directions[18].push_back(make_pair(13,'u'));
	directions[18].push_back(make_pair(17,'r'));
	directions[18].push_back(make_pair(19,'o'));
	directions[19].push_back(make_pair(18,'i'));
	directions[19].push_back(make_pair(20,'r'));
	directions[19].push_back(make_pair(24,'u'));
	directions[20].push_back(make_pair(17,'i'));
	directions[20].push_back(make_pair(19,'l'));
	directions[20].push_back(make_pair(21,'r'));
	directions[20].push_back(make_pair(23,'u'));
	directions[21].push_back(make_pair(16,'i'));
	directions[21].push_back(make_pair(20,'l'));
	directions[21].push_back(make_pair(22,'u'));
	directions[22].push_back(make_pair(15,'i'));
	directions[22].push_back(make_pair(21,'d'));
	directions[22].push_back(make_pair(23,'l'));
	directions[22].push_back(make_pair(27,'u'));
	directions[23].push_back(make_pair(14,'i'));
	directions[23].push_back(make_pair(20,'d'));
	directions[23].push_back(make_pair(22,'r'));
	directions[23].push_back(make_pair(24,'l'));
	directions[23].push_back(make_pair(26,'u'));
	directions[24].push_back(make_pair(13,'i'));
	directions[24].push_back(make_pair(19,'d'));
	directions[24].push_back(make_pair(23,'r'));
	directions[24].push_back(make_pair(25,'u'));
	directions[25].push_back(make_pair(12,'i'));
	directions[25].push_back(make_pair(24,'d'));
	directions[25].push_back(make_pair(26,'r'));
	directions[26].push_back(make_pair(11,'i'));
	directions[26].push_back(make_pair(23,'d'));
	directions[26].push_back(make_pair(25,'l'));
	directions[26].push_back(make_pair(27,'r'));
	directions[27].push_back(make_pair(10,'i'));
	directions[27].push_back(make_pair(22,'d'));
	directions[27].push_back(make_pair(26,'l'));
	return;
}

void intialize_valid_directions_2() {
    for(int i=1; i<=27; i++)
        directions[i].clear();
	directions[1].push_back(make_pair(2,'r'));
	directions[1].push_back(make_pair(6,'u'));
	directions[1].push_back(make_pair(18,'o'));
	directions[2].push_back(make_pair(1,'l'));
	directions[2].push_back(make_pair(3,'r'));
	directions[2].push_back(make_pair(5,'u'));
	directions[2].push_back(make_pair(17,'o'));
	directions[3].push_back(make_pair(2,'l'));
	directions[3].push_back(make_pair(4,'u'));
	directions[3].push_back(make_pair(16,'o'));
	directions[4].push_back(make_pair(3,'d'));
	directions[4].push_back(make_pair(5,'l'));
	directions[4].push_back(make_pair(9,'u'));
	directions[4].push_back(make_pair(15,'o'));
	directions[5].push_back(make_pair(2,'d'));
	directions[5].push_back(make_pair(14,'o'));
	directions[6].push_back(make_pair(1,'d'));
	directions[6].push_back(make_pair(5,'r'));
	directions[6].push_back(make_pair(7,'u'));
	directions[6].push_back(make_pair(13,'o'));
	directions[7].push_back(make_pair(6,'d'));
	directions[7].push_back(make_pair(8,'r'));
	directions[7].push_back(make_pair(12,'o'));
	directions[8].push_back(make_pair(5,'d'));
	directions[8].push_back(make_pair(7,'l'));
	directions[8].push_back(make_pair(9,'r'));
	directions[8].push_back(make_pair(11,'o'));
	directions[9].push_back(make_pair(4,'d'));
	directions[9].push_back(make_pair(8,'l'));
	directions[9].push_back(make_pair(10,'o'));
	directions[10].push_back(make_pair(9,'i'));
	directions[10].push_back(make_pair(11,'l'));
	directions[10].push_back(make_pair(15,'d'));
	directions[10].push_back(make_pair(27,'o'));
	directions[11].push_back(make_pair(8,'i'));
	directions[11].push_back(make_pair(10,'r'));
	directions[11].push_back(make_pair(12,'l'));
	directions[11].push_back(make_pair(14,'d'));
	directions[11].push_back(make_pair(26,'o'));
	directions[12].push_back(make_pair(7,'i'));
	directions[12].push_back(make_pair(11,'r'));
	directions[12].push_back(make_pair(13,'d'));
	directions[12].push_back(make_pair(25,'o'));
	directions[13].push_back(make_pair(6,'i'));
	directions[13].push_back(make_pair(12,'u'));
	directions[13].push_back(make_pair(14,'r'));
	directions[13].push_back(make_pair(18,'d'));
	directions[13].push_back(make_pair(24,'o'));
	directions[14].push_back(make_pair(5,'i'));
	directions[14].push_back(make_pair(11,'u'));
	directions[14].push_back(make_pair(13,'l'));
	directions[14].push_back(make_pair(15,'r'));
	directions[14].push_back(make_pair(17,'d'));
	directions[14].push_back(make_pair(23,'o'));
	directions[15].push_back(make_pair(4,'i'));
	directions[15].push_back(make_pair(10,'u'));
	directions[15].push_back(make_pair(14,'l'));
	directions[15].push_back(make_pair(16,'d'));
	directions[15].push_back(make_pair(22,'o'));
	directions[16].push_back(make_pair(3,'i'));
	directions[16].push_back(make_pair(15,'u'));
	directions[16].push_back(make_pair(17,'l'));
	directions[16].push_back(make_pair(21,'o'));
	directions[17].push_back(make_pair(2,'i'));
	directions[17].push_back(make_pair(14,'u'));
	directions[17].push_back(make_pair(16,'r'));
	directions[17].push_back(make_pair(18,'l'));
	directions[17].push_back(make_pair(20,'o'));
	directions[18].push_back(make_pair(1,'i'));
	directions[18].push_back(make_pair(13,'u'));
	directions[18].push_back(make_pair(17,'r'));
	directions[18].push_back(make_pair(19,'o'));
	directions[19].push_back(make_pair(18,'i'));
	directions[19].push_back(make_pair(20,'r'));
	directions[19].push_back(make_pair(24,'u'));
	directions[20].push_back(make_pair(17,'i'));
	directions[20].push_back(make_pair(19,'l'));
	directions[20].push_back(make_pair(21,'r'));
	directions[20].push_back(make_pair(23,'u'));
	directions[21].push_back(make_pair(16,'i'));
	directions[21].push_back(make_pair(20,'l'));
	directions[21].push_back(make_pair(22,'u'));
	directions[22].push_back(make_pair(15,'i'));
	directions[22].push_back(make_pair(21,'d'));
	directions[22].push_back(make_pair(23,'l'));
	directions[22].push_back(make_pair(27,'u'));
	directions[23].push_back(make_pair(14,'i'));
	directions[23].push_back(make_pair(20,'d'));
	directions[23].push_back(make_pair(22,'r'));
	directions[23].push_back(make_pair(24,'l'));
	directions[23].push_back(make_pair(26,'u'));
	directions[24].push_back(make_pair(13,'i'));
	directions[24].push_back(make_pair(19,'d'));
	directions[24].push_back(make_pair(23,'r'));
	directions[24].push_back(make_pair(25,'u'));
	directions[25].push_back(make_pair(12,'i'));
	directions[25].push_back(make_pair(24,'d'));
	directions[25].push_back(make_pair(26,'r'));
	directions[26].push_back(make_pair(11,'i'));
	directions[26].push_back(make_pair(23,'d'));
	directions[26].push_back(make_pair(25,'l'));
	directions[26].push_back(make_pair(27,'r'));
	directions[27].push_back(make_pair(10,'i'));
	directions[27].push_back(make_pair(22,'d'));
	directions[27].push_back(make_pair(26,'l'));
	return;
}

string to_lowest(string config) {
	string temp[48];
	for(int i=0; i<48; i++)
		temp[i] = "";

	for(int i=0; i<26; i++) {
		if(config[i] == 'l') {
			temp[0] += 'l';
			temp[1] += 'l';
			temp[2] += 'l';
			temp[3] += 'l';
			temp[4] += 'l';
			temp[5] += 'l';
			temp[6] += 'l';
			temp[7] += 'l';
			temp[8] += 'r';
			temp[9] += 'r';
			temp[10] += 'r';
			temp[11] += 'r';
			temp[12] += 'r';
			temp[13] += 'r';
			temp[14] += 'r';
			temp[15] += 'r';
			temp[16] += 'd';
			temp[17] += 'd';
			temp[18] += 'd';
			temp[19] += 'd';
			temp[20] += 'd';
			temp[21] += 'd';
			temp[22] += 'd';
			temp[23] += 'd';
			temp[24] += 'u';
			temp[25] += 'u';
			temp[26] += 'u';
			temp[27] += 'u';
			temp[28] += 'u';
			temp[29] += 'u';
			temp[30] += 'u';
			temp[31] += 'u';
			temp[32] += 'o';
			temp[33] += 'o';
			temp[34] += 'o';
			temp[35] += 'o';
			temp[36] += 'o';
			temp[37] += 'o';
			temp[38] += 'o';
			temp[39] += 'o';
			temp[40] += 'i';
			temp[41] += 'i';
			temp[42] += 'i';
			temp[43] += 'i';
			temp[44] += 'i';
			temp[45] += 'i';
			temp[46] += 'i';
			temp[47] += 'i';
		}
		else if(config[i] == 'r') {
			temp[0] += 'r';
			temp[1] += 'r';
			temp[2] += 'r';
			temp[3] += 'r';
			temp[4] += 'r';
			temp[5] += 'r';
			temp[6] += 'r';
			temp[7] += 'r';
			temp[8] += 'l';
			temp[9] += 'l';
			temp[10] += 'l';
			temp[11] += 'l';
			temp[12] += 'l';
			temp[13] += 'l';
			temp[14] += 'l';
			temp[15] += 'l';
			temp[16] += 'u';
			temp[17] += 'u';
			temp[18] += 'u';
			temp[19] += 'u';
			temp[20] += 'u';
			temp[21] += 'u';
			temp[22] += 'u';
			temp[23] += 'u';
			temp[24] += 'd';
			temp[25] += 'd';
			temp[26] += 'd';
			temp[27] += 'd';
			temp[28] += 'd';
			temp[29] += 'd';
			temp[30] += 'd';
			temp[31] += 'd';
			temp[32] += 'i';
			temp[33] += 'i';
			temp[34] += 'i';
			temp[35] += 'i';
			temp[36] += 'i';
			temp[37] += 'i';
			temp[38] += 'i';
			temp[39] += 'i';
			temp[40] += 'o';
			temp[41] += 'o';
			temp[42] += 'o';
			temp[43] += 'o';
			temp[44] += 'o';
			temp[45] += 'o';
			temp[46] += 'o';
			temp[47] += 'o';
		}
		else if(config[i] == 'd') {
			temp[0] += 'd';
			temp[1] += 'd';
			temp[2] += 'u';
			temp[3] += 'u';
			temp[4] += 'o';
			temp[5] += 'o';
			temp[6] += 'i';
			temp[7] += 'i';
			temp[8] += 'd';
			temp[9] += 'd';
			temp[10] += 'u';
			temp[11] += 'u';
			temp[12] += 'o';
			temp[13] += 'o';
			temp[14] += 'i';
			temp[15] += 'i';
			temp[16] += 'l';
			temp[17] += 'l';
			temp[18] += 'r';
			temp[19] += 'r';
			temp[20] += 'o';
			temp[21] += 'o';
			temp[22] += 'i';
			temp[23] += 'i';
			temp[24] += 'l';
			temp[25] += 'l';
			temp[26] += 'r';
			temp[27] += 'r';
			temp[28] += 'o';
			temp[29] += 'o';
			temp[30] += 'i';
			temp[31] += 'i';
			temp[32] += 'l';
			temp[33] += 'l';
			temp[34] += 'r';
			temp[35] += 'r';
			temp[36] += 'd';
			temp[37] += 'd';
			temp[38] += 'u';
			temp[39] += 'u';
			temp[40] += 'l';
			temp[41] += 'l';
			temp[42] += 'r';
			temp[43] += 'r';
			temp[44] += 'd';
			temp[45] += 'd';
			temp[46] += 'u';
			temp[47] += 'u';
		}
		else if(config[i] == 'u') {
			temp[0] += 'u';
			temp[1] += 'u';
			temp[2] += 'd';
			temp[3] += 'd';
			temp[4] += 'i';
			temp[5] += 'i';
			temp[6] += 'o';
			temp[7] += 'o';
			temp[8] += 'u';
			temp[9] += 'u';
			temp[10] += 'd';
			temp[11] += 'd';
			temp[12] += 'i';
			temp[13] += 'i';
			temp[14] += 'o';
			temp[15] += 'o';
			temp[16] += 'r';
			temp[17] += 'r';
			temp[18] += 'l';
			temp[19] += 'l';
			temp[20] += 'i';
			temp[21] += 'i';
			temp[22] += 'o';
			temp[23] += 'o';
			temp[24] += 'r';
			temp[25] += 'r';
			temp[26] += 'l';
			temp[27] += 'l';
			temp[28] += 'i';
			temp[29] += 'i';
			temp[30] += 'o';
			temp[31] += 'o';
			temp[32] += 'r';
			temp[33] += 'r';
			temp[34] += 'l';
			temp[35] += 'l';
			temp[36] += 'u';
			temp[37] += 'u';
			temp[38] += 'd';
			temp[39] += 'd';
			temp[40] += 'r';
			temp[41] += 'r';
			temp[42] += 'l';
			temp[43] += 'l';
			temp[44] += 'u';
			temp[45] += 'u';
			temp[46] += 'd';
			temp[47] += 'd';
		}
		else if(config[i] == 'o') {
			temp[0] += 'o';
			temp[1] += 'i';
			temp[2] += 'o';
			temp[3] += 'i';
			temp[4] += 'd';
			temp[5] += 'u';
			temp[6] += 'd';
			temp[7] += 'u';
			temp[8] += 'o';
			temp[9] += 'i';
			temp[10] += 'o';
			temp[11] += 'i';
			temp[12] += 'd';
			temp[13] += 'u';
			temp[14] += 'd';
			temp[15] += 'u';
			temp[16] += 'o';
			temp[17] += 'i';
			temp[18] += 'o';
			temp[19] += 'i';
			temp[20] += 'l';
			temp[21] += 'r';
			temp[22] += 'l';
			temp[23] += 'r';
			temp[24] += 'o';
			temp[25] += 'i';
			temp[26] += 'o';
			temp[27] += 'i';
			temp[28] += 'l';
			temp[29] += 'r';
			temp[30] += 'l';
			temp[31] += 'r';
			temp[32] += 'd';
			temp[33] += 'u';
			temp[34] += 'd';
			temp[35] += 'u';
			temp[36] += 'l';
			temp[37] += 'r';
			temp[38] += 'l';
			temp[39] += 'r';
			temp[40] += 'd';
			temp[41] += 'u';
			temp[42] += 'd';
			temp[43] += 'u';
			temp[44] += 'l';
			temp[45] += 'r';
			temp[46] += 'l';
			temp[47] += 'r';
		}
		else if(config[i] == 'i') {
			temp[0] += 'i';
			temp[1] += 'o';
			temp[2] += 'i';
			temp[3] += 'o';
			temp[4] += 'u';
			temp[5] += 'd';
			temp[6] += 'u';
			temp[7] += 'd';
			temp[8] += 'i';
			temp[9] += 'o';
			temp[10] += 'i';
			temp[11] += 'o';
			temp[12] += 'u';
			temp[13] += 'd';
			temp[14] += 'u';
			temp[15] += 'd';
			temp[16] += 'i';
			temp[17] += 'o';
			temp[18] += 'i';
			temp[19] += 'o';
			temp[20] += 'r';
			temp[21] += 'l';
			temp[22] += 'r';
			temp[23] += 'l';
			temp[24] += 'i';
			temp[25] += 'o';
			temp[26] += 'i';
			temp[27] += 'o';
			temp[28] += 'r';
			temp[29] += 'l';
			temp[30] += 'r';
			temp[31] += 'l';
			temp[32] += 'u';
			temp[33] += 'd';
			temp[34] += 'u';
			temp[35] += 'd';
			temp[36] += 'r';
			temp[37] += 'l';
			temp[38] += 'r';
			temp[39] += 'l';
			temp[40] += 'u';
			temp[41] += 'd';
			temp[42] += 'u';
			temp[43] += 'd';
			temp[44] += 'r';
			temp[45] += 'l';
			temp[46] += 'r';
			temp[47] += 'l';
		}
	}

	for(int i=0; i<47; i++)
		all_perm.push_back(temp[i]);

	sort(all_perm.begin(), all_perm.end());
	string lowest = all_perm[0];
	all_perm.clear();
	return lowest;
}

void dfs_valid(int curr, int count) {
	if(count == 27) {
        string tempp = to_lowest(temp_valid);
        for(vector<string>::iterator it = valid_config.begin(); it != valid_config.end(); it++) {
            if(tempp == *it)
                return;
        }
        cout << ++lrud << endl;
		valid_config.push_back(tempp);
		outfile << tempp << endl;
		return;
	}
	for(vector<pair<int, char> >::iterator it = directions[curr].begin(); it != directions[curr].end(); it++)
        if(!visited[(*it).first]) {
                visited[(*it).first] = true;
                temp_valid[count-1] = (*it).second;
                dfs_valid((*it).first, count+1);
                visited[(*it).first] = false;
        }
	return;
}
