#include<iostream>
#include"coords.hpp"
#include"particle.hpp"
#include"barycenter.hpp"
#include"barycenter_zeroing.hpp"
#include"barycenter_velocity.hpp"
#include"angular_momentum.hpp"
#include"grav_func.hpp"
#include"systems_energy.hpp"
#include"solver_rk4.hpp"
#include"solver_3div8_4order.hpp"
#include"solver_Adams_Bashforth.hpp"
#include<fstream>
#include<iomanip>
#include<cstring>
#include<functional>

const double G = 6.6743E-11;

enum class NM
{
    RK4,
    _3div_8,
    AB4,
    none
};

int main(int argc, char* argv[]){

    if (argc < 2){
        std::cerr << "You have to insert options. Check help info. Enter ./app help. Good luck." << std::endl;
        return 1;
    }

    std::vector<std::ofstream*> logsPars;
    std::vector<Particle> pars;
    double T, h;
    NM choice = NM::none;
    std::function<void(std::vector<Particle>&, double, 
                double, std::ofstream&, std::vector<std::ofstream*>&)> method;

    Particle _earth(5.972E24,
                    vec{-136472175.245111*1000, 55837254.170584*1000, 24235587.684174*1000},
                    vel{-12.660841*1000, -25.066969*1000, -10.864918*1000});
    Particle _sun(1.98892E30,
                  vec(-1308916.355519*1000, 384563.286798*1000, 196214.364776*1000),
                  vel(-0.004877*1000, -0.013735*1000, -0.005697*1000));
    Particle _moon(7.35E22,
                   vec{-136549298.434639*1000, 55510804.069186*1000, 24080727.301207*1000},
                   vel{-11.623594*1000, -25.217370*1000, -11.023526*1000});
    Particle _mercury(3.285E23,
                      vec{-29483692.090134*1000, -56789774.365311*1000, -27425915.708345*1000},
                      vel{34.715079*1000, -14.137087*1000, -11.149058*1000});
    Particle _jupiter(1.898E27,
                      vec{714552676.124432*1000, -183328571.266408*1000, -95973555.247690*1000},
                      vel{3.469710*1000, 12.131540*1000, 5.115524*1000});
    Particle _saturn(5.683E26,
                     vec{1069518043.876941*1000, -929783743.298180*1000, -430113243.967558*1000},
                     vel{6.140032*1000, 6.528374*1000, 2.432063*1000});
    Particle _mars(6.39E23,
                   vec{-19809082.687995*1000, -198417865.393635*1000, -90491021.689962*1000},
                   vel{25.049849*1000, 0.266288*1000, -0.553267*1000});

    if (!strcmp(argv[1], "help")){
        std::cout << "Use: ./app [NUMERICAL_METHOD] [T=NUM](period) [h=NUM](time step) [PLANET_NAME]..." << std::endl;
        std::cout << "First argument have to be a numerical method: RK4, 3div8 or AB4." << std::endl;
        std::cout << "Second argument is period time, ex: T=100000." << std::endl;
        std::cout << "Third argument is time step, ex: h=100." << std::endl;
        std::cout << "Last arguments are planets, ex: sun earth moon." << std::endl;
        return 0;
    }

    std::vector<std::string> just_ = {"RK4", "3/8 method", "AB4"};

    if (!strcmp(argv[1], "RK4")){
        choice = NM::RK4;
        method = ClassicRK4;
    }
    else if (!strcmp(argv[1], "3div8")){
        choice = NM::_3div_8;
        method = Method_3DIV8;
    }
    else if (!strcmp(argv[1], "AB4")){
        choice = NM::AB4;
        method = Adams_Bashforth;
    }
    if (choice == NM::none){
        std::cerr << "You have to choose a numerical method. Check help info." << std::endl;
        return 1;
    }

    std::cout << "Your setup: " << std::endl;
    std::cout << "\tNum method: " << just_[static_cast<int>(choice)];
    {
        char* ptr;
        if (argv[2][0] == 'T'){
            ptr = argv[2]; ptr += 2;
            T = std::atol(ptr);
        }
        else if (argv[2][0] == 'h'){
            ptr = argv[2]; ptr += 2;
            h = std::atol(ptr);
        }
        if (argv[3][0] == 'T'){
            ptr = argv[3]; ptr += 2;
            T = std::atol(ptr);
        }
        else if (argv[3][0] == 'h'){
            ptr = argv[3]; ptr += 2;
            h = std::atol(ptr);
        }
    }

    std::cout << ", period T = " << T << ", step h = " << h;
    std::cout << ", planets/bodies: ";

    for (size_t i = 4; i < argc; ++i){
        if (!strcmp(argv[i], "sun")){
            pars.push_back(_sun);
            logsPars.push_back(new std::ofstream("sun.txt"));
            if (i == argc-1){
                std::cout << "sun." << std::endl; continue;
            }
            std::cout << "sun, ";
        }
        else if (!strcmp(argv[i], "earth")){
            pars.push_back(_earth);
            logsPars.push_back(new std::ofstream("earth.txt"));
            if (i == argc-1){
                std::cout << "earth." << std::endl; continue;
            }
            std::cout << "earth, ";
        }
        else if (!strcmp(argv[i], "moon")){
            pars.push_back(_moon);
            logsPars.push_back(new std::ofstream("moon.txt"));
            if (i == argc-1){
                std::cout << "moon." << std::endl; continue;
            }
            std::cout << "moon, ";
        }
        else if (!strcmp(argv[i], "mercury")){
            pars.push_back(_mercury);
            logsPars.push_back(new std::ofstream("mercury.txt"));
            if (i == argc-1){
                std::cout << "mercury." << std::endl; continue;
            }
            std::cout << "mercury, ";
        }
        else if (!strcmp(argv[i], "jupiter")){
            pars.push_back(_jupiter);
            logsPars.push_back(new std::ofstream("jupiter.txt"));
            if (i == argc-1){
                std::cout << "jupiter." << std::endl; continue;
            }
            std::cout << "jupiter, ";
        }
        else if (!strcmp(argv[i], "saturn")){
            pars.push_back(_saturn);
            logsPars.push_back(new std::ofstream("saturn.txt"));
            if (i == argc-1){
                std::cout << "saturn." << std::endl; continue;
            }
            std::cout << "saturn, ";
        }
        else if (!strcmp(argv[i], "mars")){
            pars.push_back(_mars);
            logsPars.push_back(new std::ofstream("mars.txt"));
            if (i == argc-1){
                std::cout << "mars." << std::endl; continue;
            }
            std::cout << "mars, ";
        }
    }

    if (pars.size() < 2){
        std::cerr << "You must enter at least two bodies." << std::endl;
        return 1;
    }


    std::ofstream inv("inv.txt");
    inv << std::fixed << std::right << std::setw(10) << "TIME" << std::setw(10) 
        << "#BRvec" << std::setw(10) << "#BRvel" 
        << std::setw(10) << "#AngMom" << std::setw(10) << "#TotEnergy" << std::endl;

    // double T = 86400, h = 20;       //10*3.14159265358979323846/std::sqrt(G)/4         86400
    BarycenterZeroing(pars, Barycenter(pars, inv, 0));
    method(pars, T, h, inv, logsPars);

    for (size_t i = 0; i < logsPars.size(); ++i){
        logsPars[i]->close();
    }
    inv.close();


    return 0;
}
