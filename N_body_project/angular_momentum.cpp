#include<vector>
#include"particle.hpp"
#include<fstream>
#include<iomanip>

void AngularMomentum(const std::vector<Particle>& pars, std::ofstream& log){

    vec angMom;
    
    for (const auto& par: pars){
        angMom += par.position ^ (par.velocity * par.mass);
    }

    //to log: AngMom

    log << std::setprecision(10) << angMom.length() << " ";

}
