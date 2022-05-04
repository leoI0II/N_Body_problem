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

void Adams_Bashforth(std::vector<Particle>& pars,
            double T, double stepH, std::ofstream& inv, std::vector<std::ofstream*>& logPars)
{
    BarycenterZeroing(pars, Barycenter(pars, inv, 0));

    std::vector<Particle> initCp    (pars.size(), 0);
    std::vector<Particle> tempPars  (pars.size(), 0);
    std::vector<Particle> parsDer   (pars.size(), 0);
    double currTime = 0.;
    bool _final = 0;
    initCp = pars;

    keplerElems ke;
    std::ofstream keplersFile("kepler.txt");
    
    std::vector<Particle> k1        (pars.size(), 0);
    std::vector<Particle> k2        (pars.size(), 0);
    std::vector<Particle> k3        (pars.size(), 0);
    std::vector<Particle> k4        (pars.size(), 0);

    std::vector<Particle> prevK3    (pars.size(), 0);
    std::vector<Particle> prevK2    (pars.size(), 0);
    std::vector<Particle> prevK1    (pars.size(), 0);


    //log initial
    for (size_t i = 0; i < initCp.size(); ++i){
        *logPars[i] << initCp[i].position << std::endl;;
    }

    if (initCp.size() == 2){
        cartesianToKeplerian(ke, initCp[0].mass + initCp[1].mass, initCp[0].position - initCp[1].position, initCp[0].velocity - initCp[1].velocity);
    }

    //initial invar
    inv << currTime << " ";
    Barycenter(initCp, inv, 1);
    AngularMomentum(initCp, inv);
    EnergySum(initCp, inv);
    if (initCp.size() == 2){
        inv << keplerianToCartesian(ke, currTime, keplersFile).distance(initCp[0].position - initCp[1].position);
    }
    inv << std::endl;


    for (size_t i = 0; i < 3; ++i){

        GravFunction(initCp, k1);
        // k1 = parsDer;
        tempPars = initCp;
        for (size_t j = 0; j < tempPars.size(); ++j){
            tempPars[j].position += stepH / 2. * k1[j].position;
            tempPars[j].velocity += stepH / 2. * k1[j].velocity;
        }

        GravFunction(tempPars, k2);
        // k2 = parsDer;
        tempPars = initCp;
        for (size_t j = 0; j < tempPars.size(); ++j){
            tempPars[j].position += stepH / 2. * k2[j].position;
            tempPars[j].velocity += stepH / 2. * k2[j].velocity;
        }

        GravFunction(tempPars, k3);
        // k3 = parsDer;
        tempPars = initCp;
        for (size_t j = 0; j < tempPars.size(); ++j){
            tempPars[j].position += stepH * k3[j].position;
            tempPars[j].velocity += stepH * k3[j].velocity;
        }

        GravFunction(tempPars, k4);
        // k4 = parsDer;
        for (size_t j = 0; j < tempPars.size(); ++j){
            initCp[j].position += stepH * 1./6. * (k1[j].position + 
                            2 * k2[j].position + 2 * k3[j].position + k4[j].position);
            initCp[j].velocity += stepH * 1./6. * (k1[j].velocity + 
                            2 * k2[j].velocity + 2 * k3[j].velocity + k4[j].velocity);
        }

        if (i == 0){
            for (size_t j = 0; j < initCp.size(); ++j){
                prevK3[j].position = k1[j].position;
                prevK3[j].velocity = k1[j].velocity;
            }
        }
        else if (i == 1){
            for (size_t j = 0; j < initCp.size(); ++j){
                prevK2[j].position = k1[j].position;
                prevK2[j].velocity = k1[j].velocity;
            }
        }
        else if (i == 2){
            for (size_t j = 0; j < initCp.size(); ++j){
                prevK1[j].position = k1[j].position;
                prevK1[j].velocity = k1[j].velocity;
            }
        }


        //log pars
        for (size_t i = 0; i < initCp.size(); ++i){
            *logPars[i] << initCp[i].position << std::endl;;
        }

        currTime += stepH;

        inv << currTime << " ";
        Barycenter(initCp, inv, 1);
        AngularMomentum(initCp, inv);
        EnergySum(initCp, inv);
        if (initCp.size() == 2){
            inv << keplerianToCartesian(ke, currTime, keplersFile).distance(initCp[0].position - initCp[1].position);
        }
        inv << std::endl;;

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

    while (!_final){
        if (currTime + stepH >= T){
            _final = 1;
        }

        GravFunction(initCp, k1);                           //k1 = current
        for (size_t i = 0; i < pars.size(); ++i){
            initCp[i].position += stepH /24. * (k1[i].position * 55 - 
                            59 * prevK1[i].position + 37 * prevK2[i].position - 9. * prevK3[i].position);
            initCp[i].velocity += stepH /24. * (k1[i].velocity * 55 - 
                            59 * prevK1[i].velocity + 37 * prevK2[i].velocity - 9. * prevK3[i].velocity);

        }

        prevK3 = prevK2;
        prevK2 = prevK1;
        prevK1 = k1;

        //log pars
        for (size_t i = 0; i < pars.size(); ++i){
            *logPars[i] << initCp[i].position << std::endl;;
        }

        currTime += stepH;

        inv << currTime << " ";
        Barycenter(initCp, inv, 1);
        AngularMomentum(initCp, inv);
        EnergySum(initCp, inv);
        if (initCp.size() == 2){
            inv << keplerianToCartesian(ke, currTime, keplersFile).distance(initCp[0].position - initCp[1].position);
        }
        inv << std::endl;
        for (auto& el: k1){
            el.position = r{0, 0, 0};
            el.velocity = r{0, 0, 0};
        }

    }

    keplersFile.close();

}