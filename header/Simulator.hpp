#ifndef Simulator_hpp
#define Simulator_hpp
#define TEXWIDTH 64
#define TEXHEIGHT 64
#define TEXDEPTH 64

#include "Eigen/Core"
#include <iostream>
#include <vector>
#include <string>
//#include "Mesh.hpp"
#include "ComputeCommand.hpp"
//#include "igl/signed_distance.h"

struct Simulator{
    //FluidVariables
    static float timestep;
    static float dx;
    float* rhoTexture;
    //SolidVariables
//    Mesh mesh;
//    Eigen::Matrix3X<double> SDFGridPos;
//    Eigen::MatrixXd SignedDistanceFunction;
//    Eigen::Matrix3X<double> presudoNormals;
//    Eigen::VectorXi AABB_index;
    
    Simulator();
    //FluidFunctions
    
    
    //SolidFunctions
    void inputTXT(std::string &InputFileName);
private:
//    void makeSDF();
    //test
    
    void testSDF();
};
#endif /* Simulator_hpp */
