#ifndef Simulator_hpp
#define Simulator_hpp
#define TEXWIDTH 64
#define TEXHEIGHT 64
#define TEXDEPTH 64

#include "Eigen/Core"
#include <iostream>
#include <vector>
#include <string>
#include "ComputeCommand.hpp"
#include "ShaderCommand.hpp"
struct Simulator{
    //FluidVariables
    static float timestep;
    static float dx;
    float* x_velocityTexture;
    float* y_velocityTexture;
    float* z_velocityTexture;
    float* x_forceTexture;
    float* y_forceTexture;
    float* z_forceTexture;
    float* pressureTexture;
    float* rhoTexture;
    float* templatureTexture;
    float* testTexture;
    
    Simulator();
    //FluidFunctions
    void testCompute();
    //SolidFunctions
    void inputTXT(std::string &InputFileName);
private:
//    void makeSDF();
    //test
    
    void testSDF();
};
#endif /* Simulator_hpp */
