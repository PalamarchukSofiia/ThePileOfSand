#pragma once

#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <iterator>
#include <sstream>
#include <cmath>
#include <cstring>




std::string Name_File;
std:: string path_to_file;
int name_for_BMP = 0;

uint64_t max_iter = pow(2,60);
uint64_t freq = 0;

bool f_input = false;
bool f_output = false;
bool f_maxiter = false;
bool f_freq = false;

const std::string ShortInArg = "-i";
const std::string LongInArg = "--input=";
const std::string ShortOutArg = "-o";
const std::string LongOutArg = "--output=";
const std::string ShorMaxArg = "-m";
const std::string LongMaxArg = "--max-iter";
const std::string ShortFreqArg = "-f";
const std::string LongFreqArg = "--freq=";


#pragma pack(push, 1)

struct BITMAPFILEHEADER {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BITMAPINFOHEADER {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

#pragma pack(pop)


bool Num(const std::string str);

bool startswith(const std::string& str, const std::string& arg);

bool endswith(const std::string& str, const std::string& arg);

void Up_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y);

void Down_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y);

void left_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y);

void Right_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y);

void safe_BMP_format(const std::string filename, uint64_t** matrix, int height, int width);