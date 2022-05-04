#include<vector>
#include"particle.hpp"
#include<fstream>
#include<iomanip>
#include<cmath>
const double G = 6.6743E-11;

void EnergySum(std::vector<Particle>& pars, std::ofstream& log){
    
    double potentialEnergy_tot = 0.;
    double potentialEnergy_curr = 0.;

    double kineticEnergy = 0.;

    for (size_t i = 0; i < pars.size(); ++i){
        for (size_t j = i+1; j < pars.size(); ++j){
            potentialEnergy_curr += pars[j].mass / pars[i].position.distance(pars[j].position);
        }
        potentialEnergy_curr *= -G * pars[i].mass;
        potentialEnergy_tot += potentialEnergy_curr;
        potentialEnergy_curr = 0.;
    }

    for (const auto& par: pars){
        kineticEnergy += par.mass * std::pow(par.velocity.length(), 2) / 2.;
    }

    double totalEnergy = potentialEnergy_tot + kineticEnergy;

    //to log: TotEnergy
    log << std::setprecision(10) << totalEnergy << " ";

}
