// Name: Afroditi Kyprianou, 13.11.2024

#pragma once

#include <vector>
#include <string>

// Read data and store it in vectors
void readData(std::ifstream& file, std::vector<float>& x, std::vector<float>& y);

// Print n lines of data to the terminal, overload
void printData(const std::vector<float>& x, const std::vector<float>& y, int n);

void printData(const std::vector<float>& values, int n);

void printData(float chiSquare, int ndf);

void printData(std::string lineFunction);

// Calculate the magnitude of each (x, y) coordinate
std::vector<float> calculateMagnitudes(const std::vector<float>& x, const std::vector<float>& y);

// Read error data
void readErrorData(std::ifstream& file, std::vector<float>& xErrors, std::vector<float>& yErrors);

// Fit a line to the data using least squares method
std::string fitStraightLine(const std::vector<float>& xvalues, const std::vector<float>& yvalues, const std::vector<float>& xErrors, const std::vector<float>& yErrors, float& chiSquare, int& ndf);

// Calculate chi-square
float calculateChiSquare(const std::vector<float>& x, const std::vector<float>& y, const std::vector<float>& errorX, const std::vector<float>& errorY, float p, float q);

// Calculate x^y for each data point with y rounded to nearest whole number
std::vector<float> calculateXtotheY(const std::vector<float>& x, const std::vector<float>& y);

// Write results to a file, Overload
void writeResultsToFile(const std::string& filename, const std::vector<float>& data);

void writeResultsToFile(const std::string& filename, const std::string& lineEquation, float chiSquare, int ndf);

void writeResultsToFile(const std::string& filename, const std::vector<float>& x, const std::vector<float>& y);
