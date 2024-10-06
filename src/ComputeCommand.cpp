//
//  ComputeCommand.cpp
//  VolumeRendering
//
//  Created by 須之内俊樹 on 2024/07/15.
//

#include "ComputeCommand.hpp"

unsigned int resequence3to1(unsigned int i,unsigned int j,unsigned int k,unsigned int Ni,unsigned int Nj,unsigned int Nk)
{
    return k * Ni*Nj + j * Ni + i;
}
void Timer::startWithMessage(const char* s){
    startTime = std::chrono::system_clock::now();
    str = s;
}
double Timer::end(){
    endTime = std::chrono::system_clock::now();
    double time = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
    std::cout << str << ":" << time << "ms" << std::endl;
    return time;
    //std::cout << std::endl;
}

