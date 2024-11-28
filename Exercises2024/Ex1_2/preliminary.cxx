#include <iostream>
#include <cmath>

float calculateMagnitude(float x, float y){
    return std::sqrt(x*x + y*y);
}

int main(){

  std::cout << "Hello World!" << std::endl;

  float x = 2.3;
  float y = 4.5;
  float magnitude_II = std::sqrt(x*x + y*y);
  std::cout << "II) The magnitude of the vector is: " << magnitude_II << std::endl;
  
  float magnitude_III = calculateMagnitude(x,y);
  std::cout << "III) The magnitude of the vector is: " << magnitude_III << std::endl;
  
  return 0;

}