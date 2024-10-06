//
//  Simulator.cpp
//  OpenGLTest
//
//  Created by 須之内俊樹 on 2024/05/26.
//
#include "Simulator.hpp"
Simulator::Simulator()
{
    
}

void Simulator::inputTXT(std::string &InputFileName)
{
    float max = 0;
    rhoTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    FILE *ifp = fopen(InputFileName.c_str(),"r");
    for(int k=0;k<TEXDEPTH;++k){
        for(int j=0;j<TEXHEIGHT;++j){
            for(int i=0;i<TEXWIDTH;++i){
                float value;
                fscanf(ifp, "%f", &value);
                rhoTexture[resequence3to1(i, TEXHEIGHT - j, k, TEXWIDTH, TEXHEIGHT, TEXDEPTH)] = value;
            }
        }
    }
    fclose(ifp);
}
