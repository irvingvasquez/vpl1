
#include <iostream>
#include <string>

#include <octomap/octomap.h>

using namespace std;


/* 
 * This program creates an octomap. Then it is updated with a scan simulated from blensor.
 * Blensor must be configured before testing this program.
 */


int main(int argc, char **argv) {
    std::cout << "Consejo Nacional de Ciencia y Tecnología" << std::endl;
    std::cout << "View planning library" << std::endl;
  
    /// this values are set according eith the partialmodel file, it is refered to the bounding box
    octomap::point3d x_min = {-0.083216,-0.083216,-0.083216};  
    octomap::point3d x_max = {0.083216,0.083216,0.083216};
  
    return 0;
}

