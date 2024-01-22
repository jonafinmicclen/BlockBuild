#include "PerlinNoise.h"

PerlinNoise::PerlinNoise() {
    // Initialize permutation table
    p.resize(512);
    std::iota(p.begin(), p.end(), 0);
    std::default_random_engine engine(42);  // Seed for reproducibility
    std::shuffle(p.begin(), p.end(), engine);
    p.insert(p.end(), p.begin(), p.end());  // Duplicate the permutation table to avoid overflow
}

double PerlinNoise::fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b) {
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y, double z) {
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

double PerlinNoise::noise(double x, double y, double z) {
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    double u = fade(x);
    double v = fade(y);
    double w = fade(z);

    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)),
        lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))),
        lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)),
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

std::vector<std::vector<double>> PerlinNoise::generateHeightmap(int width, int height, double scaleX, double scaleY) {
    PerlinNoise perlin;

    std::vector<std::vector<double>> heightmap(height, std::vector<double>(width, 0.0));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            double x = static_cast<double>(j) * scaleX;
            double z = static_cast<double>(i) * scaleY;
            heightmap[i][j] = perlin.noise(x, 0.0, z);
        }
    }

    return heightmap;
}