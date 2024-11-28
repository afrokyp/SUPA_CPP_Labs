// Name: Afroditi Kyprianou, 13.11.2024

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include "CustomFunctions.h"

using namespace std;

int main(){

    // Creating an ifstream object
    ifstream myInput;
    vector<float> xvalues;
    vector<float> yvalues;
    // 9)
    //ifstream myErrors;
    

    // Open the existing file
    myInput.open("input2D_float.txt");
    // adding the errors file -> putting it inside switch
    //myErrors.open("error2D_float.txt");

    // //(1) commending this to go to (2)
    // // Read the contents line by line and prin them out to the terminal:
    // string line; // since we still don't know what the data look like, we print it as a string first to check
    // while(!myInput.eof()){
    //    getline(myInput, line);
    //    cout << line << endl;
    //}

    // we now know how the data looks like so we know how to handle them:
    readData(myInput, xvalues, yvalues);

    // Asking user what function they would like to use
    /* //Adding other functions 
    std::string action;
    std::cout << "Enter the action ('print' or 'magnitude'): ";
    std::cin >> action;
    */
   
    bool running = true;
    while (running) {
        std::cout << "Choose an action:\n";
        std::cout << "1. Print data\n";
        std::cout << "2. Calculate magnitudes\n";
        std::cout << "3. Fit least squares\n";
        std::cout << "4. Calculate x^y\n";
        std::cout << "5. Exit\n";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                std::cout << "Enter the number of lines to print: ";
                std::cin >> n;
                printData(xvalues, yvalues, n);
                break;
            }
            case 2: {
                std::vector<float> magnitudes = calculateMagnitudes(xvalues, yvalues);  // this will be used to write out the results to the file
                writeResultsToFile("magnitudes_xy_output.txt", magnitudes);
                break;
            }
            case 3: {
                // 9)
                // Fit a straight line and calculate chi-square
                // Ensure the error file is open and readable
                std::ifstream myErrors("error2D_float.txt");
                if (!myErrors.is_open()) {
                    std::cerr << "Error: Could not open error file 'error2D_float.txt'!" << std::endl;
                    break;
                }

                // Vectors for x and y errors
                std::vector<float> xErrors;
                std::vector<float> yErrors;

                // Read the errors from the file
                //readErrorData(myErrors, xErrors, yErrors); // to use the same function since the files are of the same structure
                readData(myErrors,xErrors,yErrors);
                myErrors.close();


                float chiSquare;
                int ndf;
                std::string lineFunction = fitStraightLine(xvalues, yvalues, xErrors, yErrors, chiSquare, ndf);

                // Print to terminal -> changed it with the print function
                //std::cout << "The straight line equation is: " << lineFunction << std::endl;
                //std::cout << "Chi-square/NDF = " << chiSquare / ndf << std::endl;

                writeResultsToFile("fit_results_with_errors.txt", lineFunction, chiSquare, ndf);
                break;
            }
            case 4: {
                // Calculate x^y for each data point 
                std::vector<float> xToTheY = calculateXtotheY(xvalues, yvalues);
                writeResultsToFile("xy_results.txt", xToTheY);
                break;
            }
            case 5:
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    myInput.close();
    return 0;

}