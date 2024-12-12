// Afroditi Kyprianou,  27.11.2024

// since we want one .h and one .cc file for the set of the 3 functions we have created CustomFunctions.h and CustomFunctions.cxx and Test_CustomFunctions.cxx to test it. 

#include "CustomFunctions.h"
#include <cmath>
#include <iostream>
#include <random>

// Normal Distribution Implementation
NormalFunction::NormalFunction(double mean, double sigma, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_mean(mean), m_sigma(sigma) {}

double NormalFunction::callFunction(double x) {
    double norm_factor = 1.0 / (m_sigma * std::sqrt(2 * M_PI));
    double exponent = -0.5 * std::pow((x - m_mean) / m_sigma, 2);
    return norm_factor * std::exp(exponent);
}

void NormalFunction::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Normal Distribution: mean = " << m_mean << ", sigma = " << m_sigma << std::endl;
}


// Cauchy-Lorentz Distribution Implementation
CauchyLorentzFunction::CauchyLorentzFunction(double x0, double gamma, double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_x0(x0), m_gamma(gamma) {}

double CauchyLorentzFunction::callFunction(double x) {
    double denom = M_PI * m_gamma * (1 + std::pow((x - m_x0) / m_gamma, 2));
    return 1.0 / denom;
}

void CauchyLorentzFunction::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Cauchy-Lorentz Distribution: x0 = " << m_x0 << ", gamma = " << m_gamma << std::endl;
}


// Negative Crystal Ball Distribution Implementation
NegativeCrystalBallFunction::NegativeCrystalBallFunction(double x_bar, double sigma, double alpha, double n,
                                                         double range_min, double range_max, std::string outfile)
    : FiniteFunction(range_min, range_max, outfile), m_x_bar(x_bar), m_sigma(sigma), m_alpha(alpha), m_n(n) {
    calculateParameters();
}

void NegativeCrystalBallFunction::calculateParameters() {
    // Compute constants A, B and N
    m_A = std::pow(m_n / std::fabs(m_alpha), m_n) * std::exp(-0.5 * std::fabs(m_alpha) * std::fabs(m_alpha));
    m_B = m_n / std::fabs(m_alpha) - std::fabs(m_alpha);

    double C = (m_n / std::fabs(m_alpha)) * (1.0 / (m_n - 1.0)) * std::exp(-0.5 * std::fabs(m_alpha) * std::fabs(m_alpha));
    double D = std::sqrt(M_PI / 2.0) * (1 + std::erf(std::fabs(m_alpha) / std::sqrt(2.0)));
    m_N = 1.0 / (m_sigma * (C + D));
}

double NegativeCrystalBallFunction::callFunction(double x) {
    double t = (x - m_x_bar) / m_sigma;
    if (t > -m_alpha) {
        return m_N * std::exp(-0.5 * t * t);
    } else {
        return m_N * m_A * std::pow(m_B - t, -m_n);
    }
}

void NegativeCrystalBallFunction::printInfo() {
    FiniteFunction::printInfo();
    std::cout << "Negative Crystal Ball Distribution: x_bar = " << m_x_bar
              << ", sigma = " << m_sigma << ", alpha = " << m_alpha
              << ", n = " << m_n << std::endl;
}


// Metropolis sampling method in base class
std::vector<double> FiniteFunction::sampleMetropolis(int num_samples, double step_size) {
    std::vector<double> samples;
    std::random_device rd;
    std::mt19937 gen(42); // using a specific seed and not random so I can check how everything changes when adjusting the width of the gaussian -> as in the lecture I chose 42
    std::uniform_real_distribution<> uniform_dist(m_RMin, m_RMax);
    std::normal_distribution<> normal_dist(0.0, step_size); // for the standard deviation part, step_size -> the value of step_size determines the spread of the normal distribution

    // Initial random starting poinr
    double x = uniform_dist(gen);

    for (int i = 0; i < num_samples; ++i) {
        // Generate proposal point y centred on x_i
        double y = x + normal_dist(gen);

        // Ensure y is within bounds
        if (y < m_RMin || y > m_RMax) {
            samples.push_back(x); // reject out-of-bounds numbers
            continue;
        }

        // Calculate acceptance ratip
        double acceptance_ratio = std::min(callFunction(y) / callFunction(x), 1.0);
        
        // to check if it calls the correct function
        // std::cout << "Current x: " << x << ", Proposed y: " << y << ", f(x): " << callFunction(x) << ", f(y): " << callFunction(y) << std::endl;

        // Since the callFunction method is virtual, it is overridden by each class so this ensures that when we call sampleMetropolis on a NegativeCrystalBallFunction object, the overridden callFunction from NegativeCrystalBallFunction is executed

        // Generate random threshold T & to ensure it is between 0-1
        std::uniform_real_distribution<> uniform_dist(0.0, 1.0);
        double T = uniform_dist(gen);

        // Accept or reject the proposal
        if (T < acceptance_ratio) {
            x = y; // accept y
        }
        // x remains unchanged otherwise

        samples.push_back(x); // record the samplw
    }

    return samples;
}
