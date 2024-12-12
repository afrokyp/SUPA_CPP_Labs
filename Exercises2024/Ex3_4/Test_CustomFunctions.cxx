// Afroditi Kyprianou, 27.11.2024

#include "CustomFunctions.h"
#include <fstream>
#include <vector>
#include <iostream>

int main() {
    // Load mystery data
    std::vector<double> dataPoints;
    std::ifstream inputFile("Outputs/data/MysteryData02322.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open MysteryData02322.txt" << std::endl;
        return 1;
    }
    double value;
    while (inputFile >> value) {
        dataPoints.push_back(value);
    }
    inputFile.close();

    // Test Normal Distribution
    NormalFunction normal(0.0, 2.3, -10.0, 10.0, "NormalFunction");
    normal.plotFunction();
    normal.plotData(dataPoints, 200, true);
    normal.printInfo();

    // Test Cauchy-Lorentz Distribution
    CauchyLorentzFunction cauchy(0.0, 2.2, -10.0, 10.0, "CauchyFunction");
    cauchy.plotFunction();
    cauchy.plotData(dataPoints, 200, true);
    cauchy.printInfo();

    // Test Negative Crystal Ball Distribution
    NegativeCrystalBallFunction crystal(0.0, 2.5, 5.0, 10.0, -10.0, 10.0, "CrystalBallFunction");
    std::cout << "Integral (Crystal Ball): " << crystal.integral(1000) << std::endl;
    crystal.plotFunction();
    crystal.plotData(dataPoints, 200, true);
    crystal.printInfo();

    // Playing around with the parameters of each distribution, we can conclude tha the distribution that the data was sampled from is the negative Crystal Ball one.

    // Generate sampled data
    std::vector<double> sampledData = crystal.sampleMetropolis(10000, 0.75); // we adjust the step size to adjust the width in order to check if we can improve it, i think around 0.65-0.75 is the best it can get.

    // Plot sampled data and mystery data
    crystal.plotData(dataPoints, 200, true);       // Plot mystery data
    crystal.plotData(sampledData, 100, false);    // Plot sampled data

    std::cout << "Plots generated. Check the output files." << std::endl;

    // Comments: Based on the adjustments it seems like the metropolis sampling indeed works well, since it seems that the sampled data match well the function and the mystery data as well. 

    return 0;
}
