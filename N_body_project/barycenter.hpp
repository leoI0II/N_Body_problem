#include<vector>
#include<fstream>

#ifndef BARYCENTER_HPP
#define BARYCENTER_HPP

struct Particle;
struct r;
std::pair<r, r> Barycenter(const std::vector<Particle>& p, std::ofstream& log, bool out);

#endif //BARYCENTER_HPP
