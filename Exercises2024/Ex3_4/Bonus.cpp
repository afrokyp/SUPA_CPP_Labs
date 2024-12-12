// Afroditi Kyprianou, 27.11.2024

#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>

int main(int argc, char* argv[]) { // the user gives the radius and then the number of random points (e.g 1 million) when running the program: e.g.: ./BonusProgram 1 1000000
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <radius> <nrandom>" << std::endl;
        return 1;
    }

    double radius = std::stod(argv[1]);
    int nrandom = std::stoi(argv[2]);

    if (radius <= 0 || nrandom <= 0) {
        std::cerr << "Both radius and nrandom must be positive." << std::endl;
        return 1;
    }

    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-radius, radius);

    int inside_circle = 0;

    for (int i = 0; i < nrandom; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= radius * radius) {
            ++inside_circle;
        }
    }

    double pi_estimate = 4.0 * inside_circle / nrandom;

    // Output π with 10 decimal places
    std::cout << std::fixed << std::setprecision(10) << "Estimated π: " << pi_estimate << std::endl;

    return 0;
}
