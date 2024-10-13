#include "ShaderDebugger.hpp"

int buffer_write_png(
    unsigned int buffer_width, unsigned int buffer_height, unsigned int buffer_depth, 
    unsigned int delta_z, float* buffer, std::string &bufferName)
{
    constexpr std::size_t width{ 1024 }, height{ 1024 }; //幅と高さ
    unsigned int magnificate_width = width / buffer_width;
    unsigned int magnificate_height = height / buffer_height;
    std::unique_ptr<RGBA[][width]> rgba(new(std::nothrow) RGBA[height][width]);
    if (!rgba) return -1;
    
    for (unsigned int z = 0; z < buffer_depth; z += delta_z){
        for (std::size_t row{}; row < height; ++row) {
            for (std::size_t col{}; col < width; ++col) {
                int bufnum = resequence3to1(col/magnificate_width, row/magnificate_height, z, buffer_width, buffer_height, buffer_depth);
                rgba[row][col].r = 255 - buffer[bufnum]*255; //赤
                rgba[row][col].g = 255;
                rgba[row][col].b = 255;
                rgba[row][col].a = 255; //不透過
            }
        }
        std::filesystem::create_directories(bufferName);
        std::string fileName = bufferName + "/z" + std::to_string(z) + ".png";
        stbi_write_png(fileName.c_str(), static_cast<int>(width), static_cast<int>(height), static_cast<int>(sizeof(RGBA)), rgba.get(), 0);
    }
    return 0;
}