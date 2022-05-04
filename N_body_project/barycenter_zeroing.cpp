#include<vector>
#include"particle.hpp"

void BarycenterZeroing(std::vector<Particle>& pars, std::pair<r, r> barycenter){

    for (auto& par: pars){
        par.position -= barycenter.first;
        par.velocity -= barycenter.second;
    }

}
