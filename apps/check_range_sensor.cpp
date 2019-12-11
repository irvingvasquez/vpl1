
#include <iostream>
#include <string>

#include <octomap/octomap.h>
#include <vpl1/rangesensor.h>

using namespace std;


/* 
 * This program creates an octomap. Then it is updated with a scan simulated from blensor.
 * Blensor must be configured before testing this program.
 */


int main(int argc, char **argv) {
    std::cout << "Consejo Nacional de Ciencia y Tecnología" << std::endl;
    std::cout << "View Planning Library" << std::endl;
  
    if (argc != 2) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
        std::cout << "Usage is ./program <folder> \n Note: The folder must contain inside the folders config and data. \n Example: ./program /home/robot\n"; 
	// Inform the user of how to use the program
        exit(0);
    } 
    
    std::string main_folder(argv[1]);
    
    std::string config_folder(main_folder);
    config_folder.append("/config");
    
    std::string data_folder(main_folder);
    data_folder.append("/data");
    
    std::string rays_file(main_folder);
    rays_file.append("/data/sensorRays.dat");
    
    // ---------------- sensor ----------------------
    RangeSensor *s = new RangeSensor;
    s->setConfigFolder(config_folder);
    s->setDataFolder(data_folder);
    s->init();
    // Set of rays that defines the sensor R
    s->saveRays(rays_file);
  
    return 0;
}

