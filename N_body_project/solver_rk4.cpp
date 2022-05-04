#include<vector>
#include"particle.hpp"
#include"angular_momentum.hpp"
#include"barycenter.hpp"
#include"barycenter_zeroing.hpp"
#include"barycenter_velocity.hpp"
#include"systems_energy.hpp"
#include"grav_func.hpp"
#include<fstream>
#include"kepler.hpp"

void ClassicRK4(std::vector<Particle>& pars,
                double T, double stepH, std::ofstream& logIn, std::vector<std::ofstream*>& logPars){

    // for (size_t i = 0 ; i < logPars.size(); ++i){
    //     std::cout << logPars[i]->good() << " " <<logPars[i]->eof() << " " <<logPars[i]->fail() << " " <<
    //         logPars[i]->bad() << std::endl;
    // }

    std::vector<Particle> initCp        (pars.size());
    std::vector<Particle> tempPars      (pars.size());
    std::vector<Particle> parsDer       (pars.size());
    double currTime = 0.;
    bool _final = 0;
    initCp = pars;
    
    keplerElems ke;
    std::ofstream keplersFile("kepler.txt");

    std::vector<Particle> k1            (pars.size());
    std::vector<Particle> k2            (pars.size());
    std::vector<Particle> k3            (pars.size());
    std::vector<Particle> k4            (pars.size());

    //log initial
    for (size_t i = 0; i < initCp.size(); ++i){
        *logPars[i] << initCp[i].position << std::endl;
    }

    if (initCp.size() == 2){
        cartesianToKeplerian(ke, initCp[1].mass + initCp[0].mass, initCp[0].position - initCp[1].position, initCp[0].velocity - initCp[1].velocity);
    }

    //initial invar
    logIn << currTime << " ";
    Barycenter(initCp, logIn, 1);
    AngularMomentum(initCp, logIn);
    EnergySum(initCp, logIn);
    if (initCp.size() == 2){
        vec a = keplerianToCartesian(ke, currTime, keplersFile);
        // std::cout << a << std::endl;
        logIn << a.distance(initCp[0].position - initCp[1].position);
    }
    logIn << std::endl;


    while(!_final){
        
        if (currTime + stepH >= T){
            _final = 1;
        }

        GravFunction(initCp, k1);
        // k1 = parsDer;
        tempPars = initCp;
        for (size_t i = 0; i < tempPars.size(); ++i){
            tempPars[i].position += stepH / 2. * k1[i].position;
            tempPars[i].velocity += stepH / 2. * k1[i].velocity;

        }

        GravFunction(tempPars, k2);
        // k2 = parsDer;
        tempPars = initCp;
        for (size_t i = 0; i < tempPars.size(); ++i){
            tempPars[i].position += stepH / 2. * k2[i].position;
            tempPars[i].velocity += stepH / 2. * k2[i].velocity;
        }

        GravFunction(tempPars, k3);
        // k3 = parsDer;
        tempPars = initCp;
        for (size_t i = 0; i < tempPars.size(); ++i){
            tempPars[i].position += stepH * k3[i].position;
            tempPars[i].velocity += stepH * k3[i].velocity;
        }

        GravFunction(tempPars, k4);
        // k4 = parsDer;
        for (size_t i = 0; i < tempPars.size(); ++i){
            initCp[i].position += stepH * 1./6. * (k1[i].position + 
                            2 * k2[i].position + 2 * k3[i].position + k4[i].position);
            initCp[i].velocity += stepH * 1./6. * (k1[i].velocity + 
                            2 * k2[i].velocity + 2 * k3[i].velocity + k4[i].velocity);
        }


        //log pars
        for (size_t i = 0; i < initCp.size(); ++i){
            *logPars[i] << initCp[i].position << std::endl;
        }
        
        currTime += stepH;

        logIn << currTime << " ";
        Barycenter(initCp, logIn, 1);
        AngularMomentum(initCp, logIn);
        EnergySum(initCp, logIn);
        if (initCp.size() == 2){
            logIn << keplerianToCartesian(ke, currTime, keplersFile).distance(initCp[0].position - initCp[1].position);
        }
        logIn << std::endl;

        for (auto& el: k1){
            el.position = r{0, 0, 0};
            el.velocity = r{0, 0, 0};
        }
        for (auto& el: k2){
            el.position = r{0, 0, 0};
            el.velocity = r{0, 0, 0};
        }
        for (auto& el: k3){
            el.position = r{0, 0, 0};
            el.velocity = r{0, 0, 0};
        }
        for (auto& el: k4){
            el.position = r{0, 0, 0};
            el.velocity = r{0, 0, 0};
        }
        

    }
    
    keplersFile.close();
    
}
