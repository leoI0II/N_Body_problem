#include<vector>
#include"particle.hpp"
#include<fstream>
#include<iomanip>

//System's barycenter
std::pair<r, r> Barycenter(const std::vector<Particle>& p, std::ofstream& log, bool out){

    // static int i = 0;

    double M = 0.;
    vec Rvec;
    vel Rvel;

    for (const auto& par: p){
        Rvec    += par.mass * par.position;
        Rvel    += par.mass * par.velocity;
        M       += par.mass;
    }

    // if (i < 10){
    //     std::cout << Rvec << std::endl << Rvel << std::endl;
    //     std::cout << M << std::endl;
    // }

    Rvec = Rvec / M;
    Rvel = Rvel / M;

    // if (i < 10){
    //     std::cout << Rvec << std::endl << Rvel << std::endl;
    //     std::cout << Rvec.length() << " " << Rvel.length() << std::endl;
    //     ++i;
    // }

    //to log: Rvec, Rvel
    if (out){
        log << std::setprecision(10) << Rvec.length() << " ";
        log << std::setprecision(10) << Rvel.length() << " ";
    }

    return std::pair<r, r>(Rvec, Rvel);
    // log.print("Rvec ").print(Rvec.length()).print("\n");
    // log.print("Rvel ").print(Rvel.length()).print("\n");
}
