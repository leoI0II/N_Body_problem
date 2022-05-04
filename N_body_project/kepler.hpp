#include<fstream>
#ifndef KEPLER_HPP
#define KEPLER_HPP

struct keplerElems{
    double a            = 0;                //большая полуось
    double e            = 0;                //эксцентриситет
    double i            = 0;                //наклонение
    double omega        = 0;                //долгота восходящего узла
    double w            = 0;                //аргумент перицентра
    double M0           = 0;                //средняя аномалия
    
    double mean_motion  = 0;                //среднее движение
    double mu           = 0;                //standard gravitational parameter
    double v            = 0;                //true anomaly ν [rad]
    double E            = 0;                //the eccentric anomaly E
};
struct Particle;
struct r;

void cartesianToKeplerian(keplerElems& ke, double M, r r_, r rDer);
r keplerianToCartesian(keplerElems& ke, double t, std::ofstream& file);


#endif //KEPLER_HPP