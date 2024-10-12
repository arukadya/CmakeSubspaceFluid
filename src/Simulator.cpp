//
//  Simulator.cpp
//  OpenGLTest
//
//  Created by 須之内俊樹 on 2024/05/26.
//
#include "Simulator.hpp"
Simulator::Simulator()
{
    x_velocityTexture = (float*)malloc(sizeof(float) * TEXDEPTH * (TEXWIDTH+1) * TEXHEIGHT);
    y_velocityTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * (TEXHEIGHT+1));
    z_velocityTexture = (float*)malloc(sizeof(float) * (TEXDEPTH+1) * TEXWIDTH * TEXHEIGHT);
    x_forceTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    y_forceTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    z_forceTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    pressureTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    templatureTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    rhoTexture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    testTexture = (float*)malloc(sizeof(float) * 1 * TEXWIDTH * TEXHEIGHT);
}
void Simulator::testCompute()
{
    //GPUに置きっぱなしのデータにアクセスしたい。
    //CPUで利用ー＞時系列データの作成。GPUで利用ー＞ほぼこれ。シミュレーションやレンダリングに利用
    uint32_t num = TEXWIDTH * TEXHEIGHT;
    GLuint shader_program = loadComputeProgram("../../shader/test.comp");

    
    GLuint uniform_element_size = glGetUniformLocation(shader_program, "element_size");
    GLuint texwidth = glGetUniformLocation(shader_program, "texwidth");
    GLuint ssbo;
    //Bufferの宣言のイメージ。第一引数に指定した数をまとめて宣言できる。
    glGenBuffers(1, &ssbo);
    //Bufferの型を決める。
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    //BufferにデータをCPUからGPUに転送する。
    glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(float), nullptr, GL_DYNAMIC_COPY);
    //リセット？なくてもいい気がする。
    //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    glUseProgram(shader_program);

    glUniform1ui(uniform_element_size, num);
    glUniform1ui(texwidth, TEXWIDTH);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, ssbo);

    // glDispatchCompute(num / 256 + 1, 1, 1);
    glDispatchCompute(num / 64 + 1, 1, 1);

    glUseProgram(0);

    //std::vector<float> data(num);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    //GPUからBufferを取得
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, num * sizeof(float), testTexture);
    //glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

    // for (auto v : data) { std::cout << v << '\n'; }

    glDeleteBuffers(1, &ssbo);

    deleteComputeShaderProgram(shader_program);
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
