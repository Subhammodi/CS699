----------
Files description:
1. header.hpp
	header file including all the headers, global variables and function signature
2. func_def.hpp
	utility file containing the body of all the functions specified in header.hpp
3. valid_compact_config.cpp
	Code to output the valid compact configurations for a given chain length and store them in a file. All valid compact configuration files will be stored in the subdirectory "Valid_compact_configuration".
4. calculating_T_given_X.cpp
	Finds the value of the temperature satisfying the relevant equation for a given X, sequence and valid compact configurations
5. calculating_X_given_T.cpp
	Finds the value of X satisfying the relevant equation for a given T, sequence and valid compact configurations
6. calculating_prob_native.cpp
	Finds the probabality of native configuration of a give sequence at a given temperature
7. generating_Sequence.cpp
	generates a sequence of energy for given mean, std and length of chain
8. sequence_stats.cpp
	Main file to find energy spectrum of a given sequence and configurations related to it.

----------
Building, compilation and executing commands:

(First two steps are optional, if the "Valid_compact_configuration" folder is available)

1. g++ -std=c++11 valid_compact_config.cpp
2. ./a.out sizeofchain

--sizeofchain - length of the protein chain

3. g++ -std=c++11 calculating_T_given_X.cpp
4. ./a.out valid_config sequence sizeofchain X

--sizeofchain - length of the protein chain
--valid_config- name of file containing valid compact configuration
--sequence    - name of file containing sequence
--X    	      - Value of X at which T needs to be calculated

5. g++ -std=c++11 calculating_X_given_T.cpp
6. ./a.out valid_config sequence sizeofchain T

--sizeofchain - length of the protein chain
--valid_config- name of file containing valid compact configuration
--sequence    - name of file containing sequence
--T    	      - Value of T at which X needs to be calculated

7. g++ -std=c++11 calculating_prob_native.cpp
8. ./a.out valid_config sequence sizeofchain T

--valid_config- name of file containing valid compact configuration
--sequence    - name of file containing sequence
--sizeofchain - length of the protein chain
--T    	      - Value of temperature

9. g++ -std=c++11 generate_Sequence.cpp
10. ./a.out sizeofchain mean stddev no_of_seq

--sizeofchain - length of the protein chain
--mean        - mean for the normal distribution for energy
--stddev      - standard deviation for the distribution
--no_of_seq	  - number of sequence to be generated

11. g++ -std=c++11 sequence_stats.cpp
12. ./a.out valid_config sequence sizeofchain

--sizeofchain - length of the protein chain
--valid_config- name of file containing valid compact configuration
--sequence    - name of file containing sequence

----------
Output file description:

Steps 1 and 2 result in generation of a file "n_valid.txt" which stores the valid compact configurations for chain of length n in "Valid_compact_configuration" folder.

Steps 3 and 4 prints the value of T satisfying the relevant equation.
Steps 5 and 6 prints the value of X satisfying the relevant equation.
Steps 7 and 8 prints the probability of native configuration.
Steps 9 and 10 results in the following files:

1. sequences/i_n_matrix.txt          - file containing i's energy matrix produced for a chain of length n

Steps 11 and 12 results in the following files:

1. Output_sequences_statistics/min_energy.txt             - file containing the min energy value
2. Output_sequences_statistics/min_energy_confs_stats.txt - file containing stats about min energy configurations.
3. Output_sequences_statistics/second_min_energy.txt      - file containing the second to minimum energy.
4. Output_sequences_statistics/second_min_energy_confs_stats.txt - file containing stats about second min energy configurations.
----------
