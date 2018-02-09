#ifndef TWO_D_HARDDISK_MCMC_ANALYZER
#define TWO_D_HARDDISK_MCMC_ANALYZER

#include <string>
#include <fstream>
#include <string>
#include "Disk.hpp"
#include "func_for_disk.hpp"

template<typename N_type>
using disk_type = Disk<N_type>;

template<typename N_type>
using system_type = std::vector<disk_type<N_type> >;

template<typename N_type>
using trajectory_type = std::vector<system_type<N_type> >;

template<typename numerical_type>
void output_xyz(const trajectory_type<numerical_type>& trajectory,
		const std::string& output_file_name){
    std::fstream fs;
    fs.open(output_file_name, std::ios::out);
    if(! fs.is_open())
	throw "program cannot open file.";
    for(const system_type<numerical_type>& snap_shot : trajectory){
	fs << snap_shot.size() << std::endl;
	fs << std::endl;
	for(std::size_t idx = 0; idx < snap_shot.size(); idx++){
	    fs << "disk" << idx << " "
	       << snap_shot[idx].coordinate[0] << " "
	       << snap_shot[idx].coordinate[1] << " "
	       << 0 << std::endl;
	}
    }
    fs.close();    
    return;
}

template<typename numerical_type>
numerical_type calculate_diffusion_coeff(const trajectory_type<numerical_type>& trajectory,
					 const std::string& output_file_name,
					 numerical_type box_size){
    std::size_t diffusion_time_step = 50;
    std::size_t total_step = trajectory.size();
    std::size_t disk_num = trajectory[0].size();
    std::size_t total_dispersion = 0;
    for(std::size_t window_num = 0; diffusion_time_step < total_step - diffusion_time_step;
	++diffusion_time_step){
	std::size_t window_dispersion = 0;
	const system_type<numerical_type>& before_snap = trajectory[window_num];
	const system_type<numerical_type>& after_snap = trajectory[window_num + diffusion_time_step];
	for(std::size_t disk_idx = 0; disk_idx < disk_num; ++disk_idx){
	    numerical_type distance = calc_distance(before_snap[disk_idx], after_snap[disk_idx], box_size);
	    std::cout << "distance " << distance << std::endl;
	    window_dispersion += distance * distance;
	}
	window_dispersion /= disk_num;
	total_dispersion += window_dispersion;
    }
    total_dispersion /= (total_step - diffusion_time_step);
    return total_dispersion;
}

#endif /* TWO_D_HARDDISK_MCMC_ANALYZER */
