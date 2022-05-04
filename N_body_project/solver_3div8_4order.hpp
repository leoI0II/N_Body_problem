#include<vector>
#include<fstream>
#ifndef SOLVER_3DIV8_4ORDER_HPP
#define SOLVER_3DIV8_4ORDER_HPP

struct Particle;

void Method_3DIV8(std::vector<Particle>& pars,
            double T, double stepH, std::ofstream& inv, std::vector<std::ofstream*>& logPars);

#endif //SOLVER_3DIV8_4ORDER_HPP