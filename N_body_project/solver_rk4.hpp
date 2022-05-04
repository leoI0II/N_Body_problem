#include<vector>
#include<fstream>
#ifndef SOLVER_RK4_HPP
#define SOLVER_RK4_HPP

struct Particle;

void ClassicRK4(std::vector<Particle>& pars,
                double T, double stepH, std::ofstream& inv, std::vector<std::ofstream*>& logPars);

#endif //SOLVER_RK4_HPP
