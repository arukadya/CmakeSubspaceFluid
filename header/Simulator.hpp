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
struct Slab
{
    float* src_texture;
    float* dst_texture;
    GLuint src_ssbo;
    GLuint dst_ssbo;
    void swap_src_dst()
    {
        std::swap(src_texture,dst_texture);
    }
    Slab(){}
    Slab(unsigned int width,unsigned int height,unsigned int depth)
    {
        src_texture = (float*)malloc(sizeof(float) * depth * width * height);
        dst_texture = (float*)malloc(sizeof(float) * depth * width * height);
    }
};

struct Simulator{
    //FluidVariables
    static float timestep;
    static float dx;
    Slab x_velocity;
    Slab y_velocity;
    Slab z_velocity;
    Slab x_force;
    Slab y_force;
    Slab z_force;
    Slab pressure;
    Slab rho;
    Slab templature;
    Slab test;
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
