// Afroditi Kyprianou, 27.11.2024

#include <iostream>
#include <fstream>
#include <vector>
#include "FiniteFunctions.h"


int main() {
    // Initialize FiniteFunction object with default settings in the class [-5,5] and default output name
    FiniteFunction function; 

    // Set range limits to make the function approximately finite
    function.setRangeMin(-10.0); // Larger range for better representation (i first plotted from -5 to 5 and this looks better)
    function.setRangeMax(10.0);

    // Read data points from "MysteryDataXXXXX.txt" -> in my case MysteryData02322.txt was created in the preliminary section
    std::vector<double> dataPoints;
    std::ifstream inputFile("Outputs/data/MysteryData02322.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open MysteryData02322.txt" << std::endl;
        return 1;
    }

    double value;
    while (inputFile >> value) {
        dataPoints.push_back(value); // Collect data points from file
    }
    inputFile.close();

    // Plot the function and data points
    function.plotFunction();                     // Enable plotting of the function

    // Print function infp
    function.printInfo(); // Output range and integral details based on the class

    // Destructor of FiniteFunction will generate and save the plot automatically
    std::cout << "Plot and data visualization complete. Check the output files." << std::endl;

    return 0;
}

