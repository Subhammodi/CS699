----------
Files description:
1. headersAndFunctions.h
	header file including all the headers and fuction signature
2. headersAndFunctions.cpp
	utility file containing global variables and the body for all the functions specified in headersAndFunctions.h
3. energyMatrixAndMinEnergyConf_2D.cpp. Includes headersAndFunctions.h
	Main file to find min configuration, energy_matrix and some statistics regarding contact points.
----------
Building, compilation and executing commands:

1. g++ -std=c++11 energyMatrixAndMinEnergyConf_2D.cpp headersAndFunctions.cpp
2. ./a.out sizeofchain mean stddev

--sizeofchain - length of the protein chain
--mean        - mean for the normal distribution for energy
--stddev      - standard deviation for the distribution
----------
Output file description:
1. Output/energy_matrix.txt          - file containing the energy matrix produced
2. Output/min_energy.txt             - file containing the min energy value
3. Output/contact_frequencies.txt    - file containing 2 columns first being the number of contacts and second being the number of valid configurations which had that many contacts.
4. Output/min_energy_confs_stats.txt - file containing stats about min energy configurations. First column being the configuration and the second being the number of contacts in the configuration.
5. Output/total_valid_conf_count.txt - file containing the total number of valid configurations.
----------
