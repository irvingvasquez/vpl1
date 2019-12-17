/*
    Copyright 2013 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include <vpl1/vprfreeflyer.h>



vprFreeFlyer::vprFreeFlyer(): vpRobot()
{
  configurationDim = 6;
  info.assign("Name: FreeFlyer");
}


void vprFreeFlyer::getPoseFromConfiguration(octomap::pose6d& pose, std::vector<double> q)
{
    // octomap: Tait-Bryan angles roll, pitch, and yaw
    octomap::pose6d p(q[0],q[1],q[2],q[5],q[4],q[3]);
    pose = p;
}


//void vprFreeFlyer::getPoseFromConfiguration(mrpt::poses::CPose3D& pose, std::vector< double > q)
//{
//  pose.setFromValues(q[0],q[1],q[2],q[3],q[4],q[5]);
//}


void vprFreeFlyer::getCurrentHTM(BoostMatrix& HTM)
{
  std::vector<double> q;
  this->getCurrentConfiguration(q);
  this->getHTMfromConfiguration(HTM,q);
}


void vprFreeFlyer::getHTMfromConfiguration(BoostMatrix& HTM, std::vector< double, std::allocator< double > > q)
{
  if(q.size() != configurationDim)
  {
    return;
  }
  
  double x,y,z,yaw,pitch,roll;
  
  x = (double) q[0];
  y = (double) q[1];
  z = (double) q[2];
  yaw = (double) q[3];
  pitch = (double) q[4];
  roll = (double) q[5];
  
  BoostMatrix Robot(4,4);
  
  Robot(0,0) = cos(yaw)*cos(pitch);
  Robot(0,1) = cos(yaw)*sin(pitch)*sin(roll)-sin(yaw)*cos(roll);  
  Robot(0,2) = cos(yaw)*sin(pitch)*cos(roll)+sin(yaw)*sin(roll);
  Robot(0,3) = x;
  
  Robot(1,0) = sin(yaw)*cos(pitch);
  Robot(1,1) = sin(yaw)*sin(pitch)*sin(roll)+cos(yaw)*cos(roll);  
  Robot(1,2) = sin(yaw)*sin(pitch)*cos(roll)-cos(yaw)*sin(roll);
  Robot(1,3) = x;
  
  Robot(2,0) = -sin(pitch);
  Robot(2,1) = cos(pitch)*sin(roll);
  Robot(2,2) = cos(pitch)*cos(roll);
  Robot(2,3) = z;
  
  Robot(3,0) = 0;
  Robot(3,1) = 0;
  Robot(3,2) = 0;
  Robot(3,3) = 1;
  
  HTM = Robot;
}



float vprFreeFlyer::executeTrajectory(std::vector< std::vector< double > > controls, double delta_t, std::vector< double > goal_q)
{
  currentConfig = goal_q;
  return true;
}


float vprFreeFlyer::executeMovement()
{

}


bool vprFreeFlyer::setVelocities(std::vector< double > velocities)
{
  return true;
}


bool vprFreeFlyer::moveToConfiguration(std::vector< double, std::allocator< double > > configuration)
{
  if(configuration.size() == configurationDim){
    std::cout << "FreeFlyer moving to " << std::endl;
    //PMUtils::printVector(configuration);
    std::cout << "x: " <<  configuration[0] << "mts" << std::endl;
    std::cout << "y: " <<  configuration[1] << "mts" << std::endl;
    std::cout << "z: " <<  configuration[2] << "mts" << std::endl;
    std::cout << "yaw: " <<  configuration[3] << " = " << configuration[3] * 180/M_PI <<  std::endl;
    std::cout << "pitch: " << configuration[4] << " = " << configuration[4] * 180/M_PI << std::endl;
    std::cout << "roll: " << configuration[5] << " = " << configuration[5] * 180/M_PI << std::endl;
    currentConfig = configuration;
    return true;
  } else
  {
    return false;
  }
}



void vprFreeFlyer::getCurrentConfiguration(std::vector< double, std::allocator< double > >& q)
{
  q.clear();
  q = currentConfig;
}



bool vprFreeFlyer::init()
{
  currentConfig.resize(6);
  currentConfig[0] = 0;
  currentConfig[1] = 0;
  currentConfig[2] = 0;
  currentConfig[3] = 0;
  currentConfig[4] = 0;
  currentConfig[5] = 0;
    
  ready = true;
  return true;
}



void vprFreeFlyer::generatePointedViews(std::list< ViewStructure > &viewList, std::string points_file, std::vector< double > object_center, double radio)
{
  std::vector< std::vector<double> > points;
  std::vector< std::vector<double> >::iterator point_it;
  
  // read the target positions
  vpFileReader reader;
  reader.readDoubleCoordinates(points_file, points);
  
  viewList.clear();
  /// unit sphere point
  std::vector<double> usp(3); 
  
  /// view sphere point
  std::vector<double> vsp(3);
  
  std::vector<double> pointing_v(3);
  
  std::vector<double> config(6);
  
  std::vector<double> coordinates(6);
  
  double x,y,z;
  double yaw, pitch, roll;
  double norm;
  BoostMatrix Robot(4,4);
  
  //mrpt::math::CMatrixDouble44 htm_p;
  
  for(point_it = points.begin(); point_it != points.end(); point_it++){
    if(point_it->size() != 3){
      std::cout << "Error in points " << std::endl;
      exit(0);
    }
    
    usp[0] = (*point_it)[0];
    usp[1] = (*point_it)[1];
    usp[2] = (*point_it)[2];
    
    x = (*point_it)[0];
    y = (*point_it)[1];
    z = (*point_it)[2];
    
    // expandir el punto al radio indicado; 
    usp[0] = radio * usp[0];
    usp[1] = radio * usp[1];
    usp[2] = radio * usp[2];
        
    // trasladar el punto con respecto al centro del objeto
    if(object_center.size() != 3){
      std::cout << "Error in object point " << std::endl;
      exit(0);
    }
    vsp[0] = object_center[0] + usp[0];
    vsp[1] = object_center[1] + usp[1];
    vsp[2] = object_center[2] + usp[2];
    
    // calcular el vector que apunta al objeto
    pointing_v[0] = object_center[0] - vsp[0];
    pointing_v[1] = object_center[1] - vsp[1];
    pointing_v[2] = object_center[2] - vsp[2];
    
    // calcular los angulos de rotación
    yaw = atan2(pointing_v[1], pointing_v[0]);
    
    //norm = sqrt( pow(pointing_v[0],2) + pow(pointing_v[1],2) + pow(pointing_v[2],2) );
    norm = radio;
    pitch = asin( pointing_v[2] / norm);
    pitch = -pitch; // I did this because the positive angles lie before the x-y plane.  
    roll = 0;
   
    // determinar la configuración
    config[0] = (double) (vsp[0] * 1000);
    config[1] = (double) (vsp[1] * 1000);
    config[2] = (double) (vsp[2] * 1000);
    config[3] = (double) (yaw * 180/M_PI);
    config[4] = (double) (pitch * 180/M_PI);
    config[5] = (double) (roll * 180/M_PI);
    
    coordinates[0] = vsp[0];
    coordinates[1] = vsp[1];
    coordinates[2] = vsp[2];
    coordinates[3] = yaw;
    coordinates[4] = pitch;
    coordinates[5] = roll;
    
    // determinar la pose
    octomap::pose6d pose(x,y,z,roll,pitch,yaw);
    
    // determinar la matriz de transformación homogenea    
    BoostMatrix Robot(4,4);
  
    Robot(0,0) = cos(yaw)*cos(pitch);
    Robot(0,1) = cos(yaw)*sin(pitch)*sin(roll)-sin(yaw)*cos(roll);  
    Robot(0,2) = cos(yaw)*sin(pitch)*cos(roll)+sin(yaw)*sin(roll);
    Robot(0,3) = x;
    
    Robot(1,0) = sin(yaw)*cos(pitch);
    Robot(1,1) = sin(yaw)*sin(pitch)*sin(roll)+cos(yaw)*cos(roll);  
    Robot(1,2) = sin(yaw)*sin(pitch)*cos(roll)-cos(yaw)*sin(roll);
    Robot(1,3) = x;
    
    Robot(2,0) = -sin(pitch);
    Robot(2,1) = cos(pitch)*sin(roll);
    Robot(2,2) = cos(pitch)*cos(roll);
    Robot(2,3) = z;
    
    Robot(3,0) = 0;
    Robot(3,1) = 0;
    Robot(3,2) = 0;
    Robot(3,3) = 1;
    
    // llenar la vista
    ViewStructure v;
    v.q = config;
    v.HTM = Robot;
    v.sensor_pose = pose;
    
    viewList.push_back(v);
  }
}


// void vprFreeFlyer::updateRobotLocalization(mrpt::poses::CPose3D transformation)
// {
// 
// }
