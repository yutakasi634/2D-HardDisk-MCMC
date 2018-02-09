#ifndef TWO_D_HARDDISK_MCMC_FUNC_FOR_DISK
#define TWO_D_HARDDISK_MCMC_FUNC_FOR_DISK

#include <cmath>
#include <iostream>
#include "Disk.hpp"

template<typename N_type>
N_type adjust_distance(N_type distance, N_type box_size){
    N_type result = distance;
    if(distance * 2 > box_size)
	result = box_size - distance;
    return result;
}

template<typename N_type>
N_type calc_distance(const Disk<N_type>& disk_a,const Disk<N_type>& disk_b, N_type box_size){
    N_type dist_x = adjust_distance<N_type>(disk_a.coordinate[0] - disk_b.coordinate[0], box_size);
    N_type dist_y = adjust_distance<N_type>(disk_a.coordinate[1] - disk_b.coordinate[1], box_size);
    N_type distance = std::pow(dist_x * dist_x + dist_y * dist_y, 0.5);
    return distance;
}

template<typename N_type>
bool acceptable(const Disk<N_type>& new_disk,const std::vector<Disk<N_type> >& system,
		N_type sigma, N_type box_size){
    bool result = false;
    for(auto disk_itr = system.begin(); disk_itr != system.end(); ++disk_itr){
	if(calc_distance(new_disk, *disk_itr, box_size) < sigma){
	    break;
	}
	if(disk_itr == --system.end())
	    result = true;
    }
    return result;
}

template<typename N_type>
Disk<N_type> adjust_coordinate(const Disk<N_type>& disk, N_type box_size){
    N_type new_x = disk.coordinate[0];
    N_type new_y = disk.coordinate[1];
    if(std::abs(new_x) * 2 > box_size)
	new_x -= std::copysign(box_size, new_x);
    if(std::abs(new_y) * 2 > box_size)
	new_y -= std::copysign(box_size, new_y);
    return { new_x, new_y };
}

template<typename N_type>
Disk<N_type> move_disk(const Disk<N_type>& disk,const std::vector<N_type>& vec_b){
    N_type new_x = disk.coordinate[0] + vec_b[0];
    N_type new_y = disk.coordinate[1] + vec_b[1];
    return { new_x, new_y };
}

template<typename N_type>
void print_disk(const Disk<N_type>& disk){
    std::cout << "disk coordinate is";
    for(N_type coord : disk.coordinate)
	std::cout << " " << coord;
    std::cout << std::endl;
}

#endif /* 2D_HARDDISK_MCMC_FUNC_FOR_DISK */
