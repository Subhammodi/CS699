----------
Files description:
1. header.hpp
	header file including all the headers and fuction signature
2. metropolis_function.hpp
	utility file containing function prototype as well as body for all the functions specified in header.hpp
3. metropolis_simulation_for_protein_folding_model_3D.cpp. It includes header.hpp file in its body.
	Main file initializing all the required variables and executing call to metropolis algorithm according to the specified input instructions. It includes metropolis_function.hpp file in its body.
----------
Building, compilation and executing commands:
1. g++ metropolis_simulation_for_protein_folding_model_3D.cpp
2. ./a.out sizeofchain sequence starting_configuration T iteration_count no_of_simulation

--sizeofchain - length of the protein chain
--sequence    - name of file containing sequence contained in sequences folder in "Energy matrix, statistics and other calculations" directory
--starting_configuration - (has to be valid) initial configuration from where user wants to initiate metropolis algorithm. Should include |sizeofchain -1| character belonging to {'l', 'r', 'd', 'u', 'i', 'o'}
--T  - Temperature at which metropolis transition probabilities are calculated
--iteration_count - number of times user wants to run metropolis algorithm
--no_of_simulation  - number of simulations of metropolis algorithm each consisiting of iteration_count monte carlo steps

NOTE - Two files are required by metropolis algorithm which are present in "Energy matrix, statistics and other calculations" folder which is present in the parent folder with respect to the current folder
----------
Output file description:
1. Output/iteration_stats.txt - file containing info about the state of metropolis algorithm in each iteration.
	It displays iteration number, configuration, energy and number of contacts for that configuration.
2. Output/min_energy_config_stats.txt - file containing info about those configuration whisch achieved minimum energy specified by minenergy.txt file ininput.
	It displays iteration number, configuration, energy and number of contacts for that configuration.
3. Output/min_energy_till_this_block_stats.txt - file containing info minimum energy achieved by metropolis algorithm till this block. It displays block_number, minimum_energy_till_this_block. Here block number = i denotes minimum energy achieved till i*100 number of iterations.
	It displays iteration number, configuration, energy and number of contacts for that configuration.
4. Output/contact_frequency_stats.txt - file containing 2 columns first being the number of contacts and second being the number of configuration which had that many contacts during the iterations of metropolis algorithm.
----------
