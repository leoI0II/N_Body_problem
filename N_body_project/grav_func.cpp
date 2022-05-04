#include<vector>
#include"particle.hpp"

const double G = 6.6743e-11;

void GravFunction(std::vector<Particle>& pars, std::vector<Particle>& parsDer){
    
    for (size_t i = 0; i < pars.size(); ++i){
        parsDer[i].position = pars[i].velocity;
    }

    for (size_t i = 0; i < pars.size(); ++i){
        for (size_t j = 0; j < pars.size(); ++j){
            if (j == i) continue;
            parsDer[i].velocity += (G * pars[j].mass * (pars[j].position - pars[i].position)) /
                                    std::pow((pars[j].position - pars[i].position).length(), 3);
        }
    }
}