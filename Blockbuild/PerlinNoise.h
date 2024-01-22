#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <random>
#include <numeric> 

class PerlinNoise {
public:
    PerlinNoise();
    double noise(double x, double y, double z);
    std::vector<std::vector<double>> generateHeightmap(int width, int height, double scaleX, double scaleY);


private:
    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);

    std::vector<int> p;
};
#endif // PERLINNOISE_H
