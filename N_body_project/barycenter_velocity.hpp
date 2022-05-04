#include<vector>
#include<fstream>

#ifndef BARYCENTER_VELOCITY_HPP
#define BARYCENTER_VELOCITY_HPP

struct Particle;

void BarycenterVelocity(const std::vector<Particle>& par, std::ofstream& log);

#endif //BARYCENTER_VELOCITY_HPP
