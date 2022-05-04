#include<vector>
#include<fstream>
#ifndef SYSTEMS_ENERGY_HPP
#define SYSTEMS_ENERGY_HPP

struct Particle;

void EnergySum(std::vector<Particle>& pars, std::ofstream& log);

#endif // SYSTEMS_ENERGY_HPP
