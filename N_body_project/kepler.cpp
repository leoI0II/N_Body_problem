#include"coords.hpp"
#include<cmath>
#include<fstream>

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

const double G = 6.6743E-11;

void cartesianToKeplerian(keplerElems& ke, double M, vec r, vec rDer){
    
    ke.mu = M * G;

    vec h = r ^ rDer;
    vec e_vec = ((rDer ^ h)/ke.mu) - (r / r.length());
    vec n = vec(0, 0, 1) ^ h;

    if (r * rDer >= 0){
        ke.v = std::acos((e_vec * r)/(e_vec.length()*r.length()));
    }
    else{
        ke.v = 2 * M_PI - std::acos((e_vec * r)/(e_vec.length()*r.length()));
    }

    ke.i = std::acos(h.z / h.length());
    ke.e = e_vec.length();
    
    // std::cout << ke.v/2. << " " << (1 + ke.e) << " " << (1 - ke.e) << " " <<
    //             std::sqrt((1 + ke.e)/(1 - ke.e)) << std::endl;
    ke.E = 2. * std::atan(std::tan(ke.v/2.)/std::sqrt((1 + ke.e)/(1 - ke.e)));

    if (n.y >= 0){
        ke.omega = std::acos(n.x/ n.length());
    }
    else{
        ke.omega = 2*M_PI - std::acos(n.x/ n.length());
    }


    if (e_vec.z >= 0){
        ke.w = std::acos((n * e_vec)/ (n.length()*e_vec.length()));
    }
    else{
        ke.w = 2 * M_PI - std::acos((n * e_vec)/ (n.length()*e_vec.length()));;
    }

    ke.M0 = ke.E - std::sin(ke.E) * ke.e;

    ke.a = 1. / (2./r.length() - rDer.length()*rDer.length()/ke.mu);

    ke.mean_motion = std::sqrt(ke.mu / std::pow(ke.a, 3));

}

vec keplerianToCartesian(keplerElems& ke, double t, std::ofstream& file){

    double M_t = ke.M0 + t * ke.mean_motion;

    double E_t = M_t;
    auto f_E = [&]() { return E_t - ke.e * std::sin(E_t) - M_t;};
    for (size_t i = 0; i < 5; ++i){
        E_t = E_t - (f_E() / (1 - ke.e * std::cos(E_t)));
    }

    double v_t = 2 * std::atan2(std::sqrt(1 + ke.e)*std::sin(E_t/2.), std::sqrt(1 - ke.e)*std::cos(E_t/2.));

    double rc_t = ke.a * (1 - ke.e * std::cos(E_t));

    vec o_t {rc_t * std::cos(v_t), rc_t * std::sin(v_t), 0};
    
    // double k = std::sqrt(ke.mu * ke.a) / rc_t;
    // vec o_t_Der {k * (-std::sin(E_t)), k * std::sqrt(1 - ke.e*ke.e)*std::cos(E_t), 0};

    vec r_t {o_t.x * (std::cos(ke.w)*std::cos(ke.omega) - std::sin(ke.w)*std::cos(ke.i)*std::sin(ke.omega)) - 
             o_t.y * (std::sin(ke.w)*std::cos(ke.omega) + std::cos(ke.w)*std::cos(ke.i)*std::sin(ke.omega)),
             o_t.x * (std::cos(ke.w)*std::sin(ke.omega) + std::sin(ke.w)*std::cos(ke.i)*std::cos(ke.omega)) +
             o_t.y * (std::cos(ke.w)*std::cos(ke.omega) * std::cos(ke.i) - std::sin(ke.w)*std::sin(ke.omega)),
             o_t.x * (std::sin(ke.w)*std::sin(ke.i)) + o_t.y *(std::cos(ke.w)*std::sin(ke.i))};

    file << r_t << std::endl;
    return r_t;

}