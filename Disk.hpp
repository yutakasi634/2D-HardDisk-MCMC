#ifndef TWO_D_HARDDISK_MCMC_DISK
#define TWO_D_HARDDISK_MCMC_DISK

#include <vector>

template<typename N_type>
struct Disk
{
    using coordinate_type = std::vector<N_type>;
    
    Disk(N_type x ,N_type y){
	coordinate.push_back(x);
	coordinate.push_back(y);
    };

    Disk(coordinate_type vec):coordinate(vec){};
    
    coordinate_type coordinate;
};

#endif /* 2D_HARDDISK_MCMC_DISK */
