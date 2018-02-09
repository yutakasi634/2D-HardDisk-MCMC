#include <fstream>
#include <iostream>
#include "harddisk_montecalro.hpp"
#include "trajectory_analyzer.hpp"

using numerical_type = float;
numerical_type box_size = 100; // box size is [- box_size/2, + box_size/2] about xy.
numerical_type sigma = 5.0;
numerical_type initial_del = 0.5;
numerical_type del_step = 0.5;
numerical_type max_del = 0.5;
numerical_type max_step = 10000;
std::size_t particle_num = 20;
std::string trajectory_file_prefix = "output";
std::string del_diffusion_coeff_file = "del_diffusion.dat";

int main(){
    std::fstream fs;
    fs.open(del_diffusion_coeff_file, std::ios::out);
    if(! fs.is_open())
	throw "program cannot open file.";
    for(numerical_type del = initial_del; del <= max_del; del += del_step){
	trajectory_type<numerical_type> trajectory =
	    simulation<numerical_type>(box_size, sigma, del, max_step,
				       particle_num);

	output_xyz(trajectory,
		   trajectory_file_prefix + std::to_string(del) + std::string(".xyz"));
	
	fs << del << " "
	   << calculate_diffusion_coeff(trajectory, del_diffusion_coeff_file, box_size)
	   << std::endl;
    }
    fs.close();
    return 0;
}

    
