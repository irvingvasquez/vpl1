
/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef RANGESENSOR_H
#define RANGESENSOR_H

#include <vector>
#include <string>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <octomap/octomap.h>

#include <vpl1/vpfilereader.h>
#include <vpl1/INIReader.h>


/**
 * Defines a Range Sensor. 
 * It abstracs the communication with the device.
 * Returns a sensor reading as a set of poins in the 3D space with respect to the sensor's reference frame.
 * All units must be in mts and rads; 
 * It also provides the sensor model.
 */

class RangeSensor
{

public:
    
RangeSensor();

    virtual bool init();
    
    /**
   * Returns the set of rays which define the sensor
   */
    virtual void getRays(std::vector< std::vector<double> > &rays);
    
    bool saveRays(std::string filename);
    
    /**
    * Returns information about the sensor
    */
    void getInfo(std::string &txt);
  
    void setConfigFolder(std::string folder);
  
    void setDataFolder(std::string folder);
  
    octomap::point3d getDirectorRay();
  
protected:
    double h_aperture;
    double v_aperture;
  
    int h_points;
    int v_points;
  
    std::string info;
    bool ready;
  
    std::string configFolder;
    std::string dataFolder;
  
    //std::vector<double> director_ray;
    octomap::point3d director_ray;

private:
  //vector< std::vector<double> > rays;
  
};

#endif // RANGESENSOR_H
