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


#include <vpl1/rangesensor.h>

RangeSensor::RangeSensor():
director_ray(1,0,0)
{
  ready = false;
}


bool RangeSensor::saveRays(std::string filename)
{
    vpFileReader writer;
    std::vector< std::vector< double > > rays;
    this->getRays(rays);
    return writer.saveDoubleCoordinates(filename, rays);
}


void RangeSensor::getInfo(std::string& txt)
{
    txt = info;
}


bool RangeSensor::init()
{
    std::string config_file(configFolder);
    config_file.append("/");
    config_file.append("rangeSensor.ini");
    

    INIReader reader(config_file.c_str());
    
    if (reader.ParseError() < 0) {
        std::cout << "Can't load " << config_file.c_str() << "\n";
        return false;
    }
    
    h_aperture = reader.GetReal("rangeSensor", "h_aperture", 1);
    
    v_aperture = reader.GetReal("rangeSensor", "v_aperture", 1);
    
    h_points = reader.GetInteger("rangeSensor", "h_points", 1);
    
    v_points = reader.GetInteger("rangeSensor", "v_points", 1);
  
    info.clear();
    info.assign( reader.Get("rangeSensor", "info", "No information found"));
  
    float x = reader.GetReal("directorRay", "x", -1);
    float y = reader.GetReal("directorRay", "y", -1);
    float z = reader.GetReal("directorRay", "z", -1);
    octomap::point3d p(x,y,z);
    director_ray = p;
    
    std::cout << "\n---------- Range sensor -------" << std::endl;
    std::cout << "Horizontal aperture: " << h_aperture << std::endl;
    std::cout << "Vertial aperture: " << v_aperture << std::endl;
    std::cout << "horizontal points:" << h_points << std::endl;
    std::cout << "Vertial points:" << v_points << std::endl;
    std::cout << "Director ray: [" << director_ray.x() << ", " << director_ray.y() << ", " << director_ray.z() << "]" << std:: endl;
  
    return true;
}


octomap::point3d RangeSensor::getDirectorRay()
{
    return director_ray;
}


void RangeSensor::setConfigFolder(std::string folder)
{
    configFolder = folder;
}


void RangeSensor::setDataFolder(std::string folder)
{
  dataFolder = folder;
}


void RangeSensor::getRays(std::vector<std::vector<double> >& rays)
{
    rays.clear();
  
  std::vector<double> ray(3);
  double d;
  int i, j;
  double alpha, beta;
  
  double increment_h_a, increment_v_a;
  
  //compute increments
  increment_h_a = h_aperture / (h_points -1); 
  increment_v_a = v_aperture / (v_points -1);
  
  alpha = -h_aperture/2;
  for(j=0;j<h_points;j++){
    beta = -v_aperture/2;
    for(i=0;i<v_points;i++){
      ray[1] = sin(beta);
      d = cos(beta);
      ray[2] = d * cos(alpha);
      ray[0] = d * sin(alpha);
      
      rays.push_back(ray);
      
      beta = beta + increment_v_a;
      
    }
    alpha = alpha + increment_h_a;
  }
  
  return;
}
