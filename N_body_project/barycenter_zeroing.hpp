#include<vector>
#ifndef BARYCENTER_ZEROING_HPP
#define BARYCENTER_ZEROING_HPP

struct Particle;
struct r;

void BarycenterZeroing(std::vector<Particle>& pars, std::pair<r, r> barycenter);


#endif //BARYCENTER_ZEROING_HPP