#include<vector>

#ifndef GRAV_FUNC_HPP
#define GRAV_FUNC_HPP

struct Particle;

void GravFunction(std::vector<Particle>& pars, std::vector<Particle>& parsDer);

#endif //GRAV_FUNC_HPP