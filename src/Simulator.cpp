//
//  Simulator.cpp
//  OpenGLTest
//
//  Created by 須之内俊樹 on 2024/05/26.
//
#include "Simulator.hpp"
Simulator::Simulator()
{
    x_velocity = Slab(TEXWIDTH+1,TEXHEIGHT,TEXDEPTH);
    x_velocity = Slab(TEXWIDTH,TEXHEIGHT+1,TEXDEPTH);
    x_velocity = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH+1);
    x_force = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH);
    y_force = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH);
    z_force = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH);
    pressure = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH);
    rho = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH);
    templature = Slab(TEXWIDTH,TEXHEIGHT,TEXDEPTH);
    test = Slab(TEXWIDTH,TEXHEIGHT,1);
}
void Simulator::testCompute()
{
    //GPUに置きっぱなしのデータにアクセスしたい。
    //CPUで利用ー＞時系列データの作成。GPUで利用ー＞ほぼこれ。シミュレーションやレンダリングに利用
    uint32_t num = TEXWIDTH * TEXHEIGHT;
    GLuint shader_program = loadComputeProgram("../../shader/test.comp");

    glUseProgram(shader_program);
    
    GLuint uniform_element_size = glGetUniformLocation(shader_program, "element_size");
    GLuint texwidth = glGetUniformLocation(shader_program, "texwidth");
    //Bufferの宣言のイメージ。第一引数に指定した数をまとめて宣言できる。
    glGenBuffers(1, &test.src_ssbo);
    //Bufferの型を決める。
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, test.src_ssbo);
    //BufferにデータをCPUからGPUに転送する。
    glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(float), nullptr, GL_DYNAMIC_COPY);
    // glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(float), testTexture, GL_DYNAMIC_DRAW);
    glUniform1ui(uniform_element_size, num);
    glUniform1ui(texwidth, TEXWIDTH);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, test.src_ssbo);
    glDispatchCompute(num / 64 + 1, 1, 1);

    

    GLuint shader_program_2 = loadComputeProgram("../../shader/test2.comp");

    glUseProgram(shader_program_2);
    
    GLuint uniform_element_size_2 = glGetUniformLocation(shader_program_2, "element_size");
    GLuint texwidth_2 = glGetUniformLocation(shader_program_2, "texwidth");
    //Bufferの宣言のイメージ。第一引数に指定した数をまとめて宣言できる。
    glGenBuffers(1, &test.dst_ssbo);
    //Bufferの型を決める。
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, test.dst_ssbo);
    //BufferにデータをCPUからGPUに転送する。
    // glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(float), nullptr, GL_DYNAMIC_COPY);
    glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(float), test.src_texture, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, test.src_ssbo);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, test.dst_ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, num * sizeof(float), nullptr, GL_DYNAMIC_COPY);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, test.dst_ssbo);


    glUniform1ui(uniform_element_size_2, num);
    glUniform1ui(texwidth_2, TEXWIDTH);
    glDispatchCompute(num / 64 + 1, 1, 1);
    

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, test.dst_ssbo);
    //GPUからBufferを取得
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, num * sizeof(float), test.dst_texture);
    test.swap_src_dst();
    glDeleteBuffers(1, &test.src_ssbo);
    deleteComputeShaderProgram(shader_program);
    glDeleteBuffers(2, &test.dst_ssbo);
    deleteComputeShaderProgram(shader_program_2);
}
void Simulator::inputTXT(std::string &InputFileName)
{
    float max = 0;
    rho.src_texture = (float*)malloc(sizeof(float) * TEXDEPTH * TEXWIDTH * TEXHEIGHT);
    FILE *ifp = fopen(InputFileName.c_str(),"r");
    for(int k=0;k<TEXDEPTH;++k){
        for(int j=0;j<TEXHEIGHT;++j){
            for(int i=0;i<TEXWIDTH;++i){
                float value;
                fscanf(ifp, "%f", &value);
                rho.src_texture[resequence3to1(i, TEXHEIGHT - j, k, TEXWIDTH, TEXHEIGHT, TEXDEPTH)] = value;
            }
        }
    }
    fclose(ifp);
}