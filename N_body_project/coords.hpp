#ifndef COORDS_HPP
#define COORDS_HPP

#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>
#include<fstream>

struct r{

    explicit r(const double& _x = 0., const double& _y = 0., const double& _z = 0.);

    r(const r& copy);

    void data(const std::string& msg = "");

    double length() const;

    double distance(const r& pos);

    r& operator=(const r& pos);

    r operator -();


    // r operator /(double num) { return r{x / num, y / num, z / num}; }

    // friend inline r operator +(const r& a, const r& b)
    friend r operator +(const r& a, const r& b){
        return r{a.x + b.x, a.y + b.y, a.z + b.z};
    }

    r& operator +=(const r& pos);
    // friend inline r operator -(const r& a, const r& b);
    friend r operator -(const r& a, const r& b){
        return r{a.x - b.x, a.y - b.y, a.z - b.z};
    }
    r& operator -=(const r& pos);

    // template<class T>
    // friend inline r operator /(const r& pos, T num);
    
    friend r operator /(const r& pos, double num){
        return r{pos.x / num, pos.y / num, pos.z / num};
    }
    // template<class T>
    // friend inline r operator /(T num, const r& pos);
    
    friend r operator /(double num, const r& pos){
        return pos / num;
    }

    r& operator /=(double num){
        x /= num; y /= num; z /= num;
        return *this;
    }

    // template <class T>
    // friend inline r operator *(const r& pos, T num);
    friend r operator *(const r& pos, double num){
        return r{pos.x * num, pos.y * num, pos.z * num};
    }
    // template <class T>
    // friend inline r operator *(T num, const r& pos);
    
    friend r operator *(double num, const r& pos){
        return pos * num;
    }
    // friend inline double operator *(const r& pos1, const r& pos2);
    friend double operator *(const r& pos1, const r& pos2){
        return pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z;
    }
    
    r& operator *=(double num){
        x *= num; y *= num; z *= num;
        return *this;
    }

    // friend inline r operator ^(const r& pos1, const r& pos2);
    friend r operator ^(const r& pos1, const r& pos2){
        return r{pos1.y * pos2.z - pos1.z * pos2.y,
                    pos1.z * pos2.x - pos1.x * pos2.z,
                    pos1.x * pos2.y - pos1.y * pos2.x};
    }

    // friend std::ofstream& operator << (std::ofstream& out, const r& pos);
    friend std::ofstream& operator << (std::ofstream& out, const r& pos){
        out << std::fixed << std::right;
        out /*<< std::setw(15) << "X:" << std::setw(15) << "Y:" << std::setw(15) << "Z:" << std::endl*/
                    << pos.x
                    << ", " << pos.y
                    << ", " << pos.z;

        return out;
    }

    // friend std::ostream& operator << (std::ostream& out, const r& pos);
    friend std::ostream& operator << (std::ostream& out, const r& pos){
       std::cout << std::fixed << std::right;
       std::cout /*<< std::setw(15) << "X:" << std::setw(15) << "Y:" << std::setw(15) << "Z:" << std::endl*/
                   << pos.x
                   << ", " << pos.y
                   << ", " << pos.z;
       return out;
    }

    double x;
    double y;
    double z;

};

// inline r operator +(const r& a, const r& b){
//     return r{a.x + b.x, a.y + b.y, a.z + b.z};
// }
// inline r operator -(const r& a, const r& b){
//     return r{a.x - b.x, a.y - b.y, a.z - b.z};
// }
// template <class T>
// inline r operator *(const r& pos, T num){
//     return r{pos.x * num, pos.y * num, pos.z * num};
// }
// template <class T>
// inline r operator *(T num, const r& pos){
//     return pos * num;
// }
// inline double operator *(const r& pos1, const r& pos2){
//     return pos1.x * pos2.x + pos1.y * pos2.y + pos1.z * pos2.z;
// }

// template<class T>
// inline r operator /(const r& pos, T num){
//     return r{pos.x / num, pos.y / num, pos.z / num};
// }
// template<class T>
// inline r operator /(T num, const r& pos){
//     return pos / num;
// }

// inline r operator ^(const r& pos1, const r& pos2){
//     return r{pos1.y * pos2.z - pos1.z * pos2.y,
//                     pos1.z * pos2.x - pos1.x * pos2.z,
//                     pos1.x * pos2.y - pos1.y * pos2.x};
// }

// std::ofstream& operator << (std::ofstream& out, const r& pos){
//     std::cout << std::fixed << std::left;
//     std::cout /*<< std::setw(15) << "X:" << std::setw(15) << "Y:" << std::setw(15) << "Z:" << std::endl*/
//                 << std::setw(15) << std::setprecision(8) << pos.x
//                 << std::setw(15) << std::setprecision(8) << pos.y
//                 << std::setw(15) << std::setprecision(8) << pos.z;

//     return out;
// }

// std::ostream& operator << (std::ostream& out, const r& pos){
//     std::cout << std::fixed << std::left;
//     std::cout /*<< std::setw(15) << "X:" << std::setw(15) << "Y:" << std::setw(15) << "Z:" << std::endl*/
//                 << std::setw(15) << std::setprecision(8) << pos.x
//                 << std::setw(15) << std::setprecision(8) << pos.y
//                 << std::setw(15) << std::setprecision(8) << pos.z;
//     return out;
// }


using vec = r;
using vel = r;


#endif //COORDS_HPP

// class logLoc{
// public:
//     logLoc(const char* _msg, std::experimental::source_location _loc = 
//         std::experimental::source_location::current()) : msg(_msg), loc(_loc) {}

//     void print(){
//         std::cout << "location error: "
//                   << loc.file_name() << "("
//                   << loc.line() << ":"
//                   << loc.column() << ") "
//                   << loc.function_name() << ": " << msg << std::endl;
//     }
// private:
//     std::experimental::source_location loc;

//     const char* msg;
// };

// void someFunc(){
//     if (1 < 3) throw logLoc("Error: 1 < 3!");
// }
