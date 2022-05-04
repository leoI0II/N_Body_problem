#include<vector>
#include<fstream>

#ifndef SOLVER_ADAMS_BASHFORTH_HPP
#define SOLVER_ADAMS_BASHFORTH_HPP

struct Particle;

void Adams_Bashforth(std::vector<Particle>& pars,
            double T, double stepH, std::ofstream& inv, std::vector<std::ofstream*>& logPars);

#endif //SOLVER_ADAMS_BASHFORTH_HPP