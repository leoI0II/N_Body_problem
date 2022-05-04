#include<vector>
#include<fstream>

#ifndef ANGULAR_MOMENTUM_HPP
#define ANGULAR_MOMENTUM_HPP

struct Particle;

void AngularMomentum(const std::vector<Particle>& pars, std::ofstream& log);

#endif //ANGULAR_MOMENTUM_HPP
