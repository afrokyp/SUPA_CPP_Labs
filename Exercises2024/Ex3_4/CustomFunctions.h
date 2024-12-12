// Afroditi Kyprianou, 27.11.2024

#pragma once
#include "FiniteFunctions.h"
#include <cmath>
#include <iostream>

// Normal Distribution
class NormalFunction : public FiniteFunction {
public:
    NormalFunction(double mean, double sigma, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;

private:
    double m_mean;
    double m_sigma;
};

// Cauchy-Lorentz Distribution
class CauchyLorentzFunction : public FiniteFunction {
public:
    CauchyLorentzFunction(double x0, double gamma, double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;

private:
    double m_x0;
    double m_gamma;
};

// Negative Crystal Ball Distribution
class NegativeCrystalBallFunction : public FiniteFunction {
public:
    NegativeCrystalBallFunction(double x_bar, double sigma, double alpha, double n,
                                double range_min, double range_max, std::string outfile);
    double callFunction(double x) override;
    void printInfo() override;

private:
    double m_x_bar, m_sigma, m_alpha, m_n;
    double m_A, m_B, m_N;

    void calculateParameters();
};
