#include"coords.hpp"


r::r(const double& _x, const double& _y, const double& _z) : 
        x(_x), y(_y), z(_z) {}

r::r(const r& copy) : x(copy.x), y(copy.y), z(copy.z) {}

r& r::operator=(const r& pos){
    if (this == &pos) return *this;
    x = pos.x; y = pos.y; z = pos.z;
    return *this;
}

void r::data(const std::string& msg){
        std::cout << msg << std::endl;
        std::cout << std::fixed << std::left;
        std::cout << std::setw(15) << "X:" << std::setw(15) << "Y:" << std::setw(15) << "Z:" << std::endl
                  << std::setw(15) << std::setprecision(8) << x
                  << std::setw(15) << std::setprecision(8) << y
                  << std::setw(15) << std::setprecision(8) << z << std::endl;
    }

double r::length() const {
    return std::sqrt(x*x + y*y + z*z);
}

double r::distance(const r& pos){
    return (r(pos.x - x, pos.y - y, pos.z - z)).length();
}

r r::operator -(){
    return r{-x, -y, -z};
}

r& r::operator +=(const r& pos){
    x += pos.x; y += pos.y; z += pos.z;
    return *this;
}

r& r::operator -=(const r& pos){
    x -= pos.x; y -= pos.y; z -= pos.z;
    return *this;
}
