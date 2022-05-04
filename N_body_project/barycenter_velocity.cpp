#include<vector>
#include"particle.hpp"
#include<fstream>
#include<iomanip>

void BarycenterVelocity(const std::vector<Particle>& par, std::ofstream& log){

    double M = 0;
    vec impulseSum;

    for (const auto& p: par){
        impulseSum += p.mass * p.velocity;
        M += p.mass;
    }

    vec bVel = impulseSum/M;

    //to log: BVel
    log << bVel.length() << " ";
    // log.print("BVel ").print(bVel).print("\n");

}
