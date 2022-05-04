#include<iostream>
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include"coords.hpp"

struct Particle{

    Particle(double _mass = 0., 
             const vec& _vec = vec(0., 0., 0.), 
             const vel& _vel = vel(0., 0., 0.))
                : mass(_mass), position(_vec), velocity(_vel) {/*std::cout << "Constuctor called!" << std::endl;*/}


    double mass;
    vec position;
    vel velocity;

};



#endif //PARTICLE_HPP