#ifndef TWO_D_HARDDISK_MCMC_MONTECALRO
#define TWO_D_HARDDISK_MCMC_MONTECALRO

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include "Disk.hpp"
#include "func_for_disk.hpp"

template<typename N_type>
using disk_type = Disk<N_type>;

template<typename N_type>
using system_type = std::vector<disk_type<N_type> >;

template<typename N_type>
using trajectory_type = std::vector<system_type<N_type> >;
    
template<typename numerical_type>
trajectory_type<numerical_type> simulation(numerical_type box_size, numerical_type sigma,
					   numerical_type del, numerical_type max_step,
					   std::size_t particle_num){

    std::mt19937 mt(42);
    std::uniform_real_distribution<numerical_type>
	dist_box(- box_size / 2, box_size / 2);

    //system generate.
    std::cout << "system genaration start." << std::endl;
    system_type<numerical_type> system = { disk_type<numerical_type>(dist_box(mt), dist_box(mt)) };
    while(system.size() < particle_num){
	std::size_t system_size = system.size();
	disk_type<numerical_type> new_disk(dist_box(mt), dist_box(mt));
	if(acceptable(new_disk, system, sigma, box_size)){
	    system.push_back(new_disk);
	    if(system.size() % 10 == 0)
		std::cout << "system size is " << system.size() << std::endl;
	}
    }
    std::cout << "system genaration finish." << std::endl;

    //motecalro
    std::vector<numerical_type> move_vector = { 0, 0 };
    disk_type<numerical_type> new_coord_disk(0, 0);
    std::normal_distribution<numerical_type> dist_move(0, del);
    trajectory_type<numerical_type> trajectory;
    std::vector<std::size_t> indices(system.size());
    std::iota(indices.begin(), indices.end(), 0);
    
    for(std::size_t step = 0; step < max_step; step++){
	std::shuffle(indices.begin(), indices.end(), mt);
	for(std::size_t index : indices){
	    for(numerical_type& coord : move_vector)
		coord = dist_move(mt);
	    new_coord_disk = move_disk(system[index], move_vector);
	    new_coord_disk = adjust_coordinate(new_coord_disk, box_size);
	    for(std::size_t partner_idx = 0; partner_idx < system.size(); ++partner_idx){
		if(calc_distance(new_coord_disk, system[partner_idx], box_size) < sigma &&
		   partner_idx != index)
		    break;
		if(partner_idx == system.size() - 1)
		    system[index] = new_coord_disk;
	    }
	}
	trajectory.push_back(system);
    }
    return trajectory;
}
    
#endif /* TWO_D_HARDDISK_MCMC_MONTECALRO */
