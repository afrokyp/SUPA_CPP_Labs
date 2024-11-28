// Name: Afroditi Kyprianou, 13.11.2024

#include "CustomFunctions.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

// Read Data
void readData(std::ifstream& file, std::vector<float>& xvalues, std::vector<float>& yvalues){
    std::string line;

    // To skip the first line that contains "x,y", the header
    std::getline(file,line);

    while (std::getline(file, line)) {
        // Find where the comma is in the line string
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            // Extract x and y as strings first
            std::string x_string = line.substr(0, commaPos);
            std::string y_string = line.substr(commaPos + 1);

            // Convert strings to floats
            
            float x = std::stof(x_string);
            float y = std::stof(y_string);
            xvalues.push_back(x);
            yvalues.push_back(y);
        } else {
            std::cerr << "Invalid line format: " << line << std::endl;
        }
    }

}


// Print data
/* //1st part
void printData(const std::vector<float>& xvalues, const std::vector<float>& yvalues, int n) {
    int totalPoints = xvalues.size();

    if (n > totalPoints) {
        std::cerr << "Requested number of lines exceeds data size. Printing first 5 lines." << std::endl;
        n = 5;
    }

    for (int i = 0; i < n && i < totalPoints; ++i) {
        std::cout << xvalues[i] << ", " << yvalues[i] << std::endl;
    }
}
*/
// 8) Printing functions - Writing overloads
// Overloaded for xvalues and yvalues
void printData(const std::vector<float>& xvalues, const std::vector<float>& yvalues, int n) {
    int totalPoints = xvalues.size();

    if (n > totalPoints) {
        std::cerr << "Requested number of lines exceeds data size. Printing first 5 lines." << std::endl;
        n = 5;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << xvalues[i] << ", " << yvalues[i] << std::endl;
    }
}

// Overloaded for magnitudes or x^y -> vector form
void printData(const std::vector<float>& values, int n) {
    int totalPoints = values.size();

    if (n > totalPoints) {
        std::cerr << "Requested number of lines exceeds data size. Printing available lines." << std::endl;
        n = totalPoints; // because for the rest of the functions we assume we always want to analyse the full dataset
    }

    for (int i = 0; i < n; ++i) {
        std::cout << values[i] << std::endl;
    }
}

// Overloaded for number, in case of chi-square/ndf
void printData(float chiSquare, int ndf) {
    std::cout << "Chi-square/NDF = " << chiSquare / ndf << std::endl;
}

// Overloaded for string, in case of lineFunction
void printData(std::string lineFunction) {
    std::cout << "The straight line equation is: " << lineFunction << std::endl;
}

std::vector<float> calculateMagnitudes(const std::vector<float>& xvalues, const std::vector<float>& yvalues) {
    std::vector<float> magnitudes;

    for (size_t i = 0; i < xvalues.size(); ++i) {
        float magnitude = std::sqrt(xvalues[i] * xvalues[i] + yvalues[i] * yvalues[i]);
        magnitudes.push_back(magnitude);

        // Print magnitude to the terminal
        //std::cout << "Magnitude of point (" << xvalues[i] << ", " << yvalues[i] << ") = " << magnitude << std::endl;

    }

    //Print them using the print function, overload method
    printData(magnitudes, xvalues.size());

    return magnitudes;
}

/*
std::string fitStraightLine(const std::vector<float>& xvalues, const std::vector<float>& yvalues) {
    size_t num = xvalues.size();

    float sumX = 0.0f;
    float sumY = 0.0f;
    float sumXY = 0.0f;
    float sumX2 = 0.0f;

    // Sums for the least squarea method
    for (size_t i = 0; i < num; ++i) {
        sumX += xvalues[i];
        sumY += yvalues[i];
        sumXY += xvalues[i] * yvalues[i];
        sumX2 += xvalues[i] * xvalues[i];
    }

    // Calculating slope and intercepr
    float p = (num * sumXY - sumX * sumY) / (num * sumX2 - sumX * sumX);
    float q = (sumX2 * sumY - sumXY * sumX)/ (num * sumX2 - sumX * sumX);

    // Format the result
    std::string lineFunction = "y = " + std::to_string(p) + "x + " + std::to_string(q);

    // Print the result
    std::cout << "Fitted straight line: " << lineFunction << std::endl;

    return lineFunction;
}
*/

// Read errors from the file "error2D_float.txt" -> I am later not using this, but the readData function since it's doing the same thing
void readErrorData(std::ifstream& file, std::vector<float>& xErrors, std::vector<float>& yErrors) {
    std::string line;
    std::getline(file, line); // Skip header, 1st line
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos) {
            std::string xErrorStr = line.substr(0, commaPos);
            std::string yErrorStr = line.substr(commaPos + 1);

            float xError = std::stof(xErrorStr);
            float yError = std::stof(yErrorStr);

            xErrors.push_back(xError);
            yErrors.push_back(yError);
        } else {
            std::cerr << "Invalid line format in error file: " << line << std::endl;
        }
    }
}

float calculateChiSquare(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& errorX, const std::vector<float>& errorY, float p, float q) {

    size_t num = x.size();
    float chiSquare = 0.0f;

    // Calculate chi-squared 
    for (size_t i = 0; i < num; ++i) {
        float yFit = p * x[i] + q;  // The fitted y value using the line equation
        
        // Propagation
        float combinedError = std::sqrt(std::pow(p * errorX[i], 2) + std::pow(errorY[i], 2));

        if (combinedError == 0) {
            std::cerr << "Warning: Combined error is zero at index " << i << ". Skipping this point." << std::endl;
            continue; // To avoid division by 0
        }

        // Calculate chi-square contribution for each poi nt
        chiSquare += std::pow((y[i] - yFit) / combinedError, 2);
    }

    return chiSquare;
}

std::string fitStraightLine(const std::vector<float>& xvalues, const std::vector<float>& yvalues,
                            const std::vector<float>& xErrors, const std::vector<float>& yErrors,
                            float& chiSquare, int& ndf) {
    size_t num = xvalues.size();
    float sumX = 0.0f, sumY = 0.0f, sumXY = 0.0f, sumX2 = 0.0f;
    
    // Sums for the least squarea method
    for (size_t i = 0; i < num; ++i) {
        sumX += xvalues[i];
        sumY += yvalues[i];
        sumXY += xvalues[i] * yvalues[i];
        sumX2 += xvalues[i] * xvalues[i];
    }

    // Calculating slope and intercepr
    float p = (num * sumXY - sumX * sumY) / (num * sumX2 - sumX * sumX);
    float q = (sumX2 * sumY - sumXY * sumX) / (num * sumX2 - sumX * sumX);

    // Call calculateChiSquare to compute chi-square
    chiSquare = calculateChiSquare(xvalues, yvalues, xErrors, yErrors, p, q);
    ndf = num - 2; // Degrees of freedom: N - 2 (parameters p and q)

    std::string lineFunction = "y = " + std::to_string(p) + "x + " + std::to_string(q);
    
    printData(lineFunction);
    printData(chiSquare, ndf);

    return lineFunction;
}


// 10) Calculate x^y for each data point with y rounded to nearest whole number
std::vector<float> calculateXtotheY(const std::vector<float>& x, const std::vector<float>& y) {
    std::vector<float> results;

    for (size_t i = 0; i < x.size(); ++i) {
        // Round y to the nearest integer
        int roundedY = std::round(y[i]);

        // Calculate x^y using the exp and log functions
        float result = std::exp(roundedY * std::log(x[i]));

        results.push_back(result);

        // Print the result for this data point to the terminal
        //std::cout << "x = " << x[i] << ", y = " << y[i] << " (rounded to " << roundedY << ") => x^y = " << result << std::endl;
    }
    //Using the overload print function to print the x^y to the terminal
    printData(results, x.size());

    return results;
}

// 1. Write a single vector (magnitudes or x^y results)
void writeResultsToFile(const std::string& filename, const std::vector<float>& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }
    for (const auto& value : data) {
        file << value << std::endl;
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

// 2. Write two vectors (x and y coordinates)
void writeResultsToFile(const std::string& filename, const std::vector<float>& x, const std::vector<float>& y) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }
    for (size_t i = 0; i < x.size(); ++i) {
        file << x[i] << ", " << y[i] << std::endl;
    }
    file.close();
    std::cout << "Data saved to " << filename << std::endl;
}

// 3. Write the least-squares result (slope, intercept, chi-square/NDF)
void writeResultsToFile(const std::string& filename, const std::string& lineEquation, float chiSquare, int ndf) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }
    file << lineEquation << std::endl;
    file << "Chi-square/NDF: " << chiSquare / ndf << std::endl;
    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}