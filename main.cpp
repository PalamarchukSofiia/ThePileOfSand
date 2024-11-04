#include "main.h"

int main(int argc, char* argv[]){

    std::string cur_arg;
    std::string next_arg;
    for (int i = 1;i < argc;++i) {

        cur_arg = argv[i];

//output

        if (cur_arg == ShortOutArg) {
            next_arg = argv[i+1];
            if (next_arg.size() >= 1 && next_arg[0] == '-') {
                std::cerr << "No output file" << std::endl;
                exit(EXIT_FAILURE);
            }
            f_output = true;
            path_to_file = next_arg;
            ++i;
        }else if (startswith(cur_arg, LongOutArg)) {
            path_to_file = cur_arg.substr(9);
            f_output = true;

//input

        }else if (cur_arg == ShortInArg) {
            next_arg = argv[i+1];
            if (next_arg.size() >= 1 && next_arg[0] == '-') {
                std::cerr << "No input file" << std::endl;
                exit(EXIT_FAILURE);
            }
            f_input = true;
            Name_File = next_arg;
            ++i;
        }else if (startswith(cur_arg, LongInArg)) {
            Name_File = cur_arg.substr(8);
            f_input = true;

//max

        }else if (cur_arg == ShorMaxArg) {
            next_arg = argv[i+1];
            if (!Num(next_arg)) {
                std::cerr << "The argument for max_iter is not a number" << std::endl;
                exit(EXIT_FAILURE);
            }
            max_iter = std::stoll(next_arg);
            f_maxiter = true;
            ++i;


        }else if (startswith(cur_arg, LongMaxArg)) {
            cur_arg = cur_arg.substr(11);
            if (!Num(cur_arg)) {
                std::cerr << "The argument for max_iter is not a number" << std::endl;
                exit(EXIT_FAILURE);
            }
            max_iter = std::stoll(cur_arg);
            f_maxiter = true;

//freq

        }else if (cur_arg == ShortFreqArg) {
            next_arg = argv[i+1];
            if (!Num(next_arg)) {
                std::cerr << "The argument for freq is not a number" << std::endl;
                exit(EXIT_FAILURE);
            }
            freq = std::stoll(next_arg);
            f_freq = true;
            ++i;


        }else if (startswith(cur_arg, LongFreqArg)) {
            cur_arg = cur_arg.substr(7);
            if (!Num(cur_arg)) {
                std::cerr << "The argument for freq is not a number" << std::endl;
                exit(EXIT_FAILURE);
            }
            freq = std::stoll(cur_arg);
            f_freq = true;
        }

    }


    std::ifstream file_len(Name_File);
    std::string str;

    uint16_t len_file = 0;

    while(getline(file_len,str)){
        len_file++;
    }
    file_len.close();

    std::ifstream file(Name_File);
    std::string cell;

    int16_t x_arr[len_file];
    int16_t y_arr[len_file];
    uint16_t count_sand[len_file];
    uint64_t counter = 0;

    while (getline(file, cell)){


        int x, y, count_s;

        std::stringstream ss(cell);

        ss >> x >> y >> count_s;

        x_arr[counter] = x;
        y_arr[counter] = y;
        count_sand[counter] = count_s;
       
        counter++;

    }

    int32_t len_x = 0;
    int32_t len_y = 0;

    for (int i = 0; i < len_file; i++){
        
        if (fabs(x_arr[i]) * 2 + 1 > len_x)
            len_x = fabs(x_arr[i]) * 2 + 1;
        
        if (fabs(y_arr[i]) * 2 + 1 > len_y)
            len_y = fabs(y_arr[i]) * 2 + 1;
        
    }

    uint64_t** sand_box = new uint64_t*[len_y]; 
    for (int y = 0; y < len_y; ++y) {
        sand_box[y] = new uint64_t[len_x];
    }


    for (int32_t y = 0; y < len_y; ++y) {
        for (int32_t x = 0; x < len_x; ++x) {
            sand_box[y][x] = 0;
        }
    }

    for (int i = 0; i < len_file ; ++i){
        
        sand_box[((len_y - 1)/2) - y_arr[i]][((len_x - 1)/2) + x_arr[i]] = count_sand[i]; 

    }

    bool f_up = 0;
    bool f_down = 0;
    bool f_left = 0;
    bool f_right = 0;

    uint64_t freq_uwu = 0;

    while (max_iter != 0){

        bool f_up = 0;
        bool f_down = 0;
        bool f_left = 0;
        bool f_right = 0;

        bool f_iter = false;
 
        for (int64_t y = 0; y < len_y; ++y){

            for (int64_t x = 0; x < len_x; ++x){

                if (sand_box[y][x] >= 4){

                    if (x == 0)
                        f_left = 1;
                    if (x == len_x - 1)
                        f_right = 1;
                    if (y == 0)
                        f_up = 1;
                    if (y == len_y - 1)
                        f_down = 1;

                }
            }
        }

        if (f_up == 1){
            Up_exp(sand_box, len_x, len_y);
        }
        if (f_right == 1){
            Right_exp(sand_box, len_x, len_y);
        }
        if (f_down == 1){
            Down_exp(sand_box, len_x, len_y);
        }
        if (f_left == 1){
            left_exp(sand_box, len_x, len_y);
        }

        uint64_t** sand_uwu = new uint64_t*[len_y]; 
        for (int y = 0; y < len_y; ++y) {
            sand_uwu[y] = new uint64_t[len_x];
        }

        for (int y = 0; y < len_y; ++y) {
            for (int x = 0; x < len_x; ++x) {
                sand_uwu[y][x] = 0; 
            }
        }

        for (int64_t y = 0; y < len_y; ++y){

            for (int64_t x = 0; x < len_x; ++x){

                if (sand_box[y][x] >= 4){

                    sand_uwu[y][x] += sand_box[y][x] - 4;
                    
                    sand_uwu[y + 1][x]++;
                    sand_uwu[y - 1][x]++;
                    sand_uwu[y][x + 1]++;
                    sand_uwu[y][x - 1]++;

                    f_iter = true;

                }else
                    sand_uwu[y][x] += sand_box[y][x];
            }
        }
        for (int64_t i = 0; i < len_y; ++i){
            delete sand_box[i];
        }
        delete[] sand_box;

        sand_box = sand_uwu;
        sand_uwu = nullptr;

        max_iter--;

        if (f_iter){

            if (f_freq == true && freq != 0){

                freq_uwu++;
                
                if (freq == freq_uwu){

                    std::string a = std::to_string(name_for_BMP);
                    std::string filename = path_to_file + a + ".bmp";

                    name_for_BMP++;

                    safe_BMP_format(filename, sand_box, len_y, len_x);

                    freq_uwu = 0;
                } 
            }        
        }else{
            
            max_iter = 0;

            std::string a = std::to_string(name_for_BMP);
            std::string filename = path_to_file + a + ".bmp";

            name_for_BMP++;
            std::cout << filename;

            safe_BMP_format(filename, sand_box, len_y, len_x);
        }
    }
}







bool Num(const std::string str) {

    for (size_t i = 0; i < str.length(); ++i) {
        if (!std::isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

bool startswith(const std::string& str, const std::string& arg) {
    if (arg.size() > str.size()) {
        return false; 
    }
    return str.substr(0, arg.size()) == arg;
}

bool endswith(const std::string& str, const std::string& arg) {
    if (arg.size() > str.size()) {
        return false; 
    }
    return str.substr(str.size() - arg.size()) == arg; 
}

void Up_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y){

    uint64_t** sand_uwu = new uint64_t*[len_y + 1]; 
    for (int i = 0; i < len_y + 1; ++i) {
        sand_uwu[i] = new uint64_t[len_x];
    }

    for (int y = 0; y < len_y + 1; ++y) {
        for (int x = 0; x < len_x; ++x) {
            sand_uwu[y][x] = 0; 
        }
    }

    for (int y = 0; y < len_y; ++y) {
        for (int x = 0; x < len_x; ++x) {
            sand_uwu[y + 1][x] = sand_box[y][x]; 
        }
        delete[] sand_box[y];
    }
    delete[] sand_box;

    sand_box = sand_uwu;

    len_y++; 
    

}

void Down_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y){

    uint64_t** sand_uwu = new uint64_t*[len_y + 1]; 
    for (int i = 0; i < len_y + 1; ++i) {
        sand_uwu[i] = new uint64_t[len_x];
    }

    for (int y = 0; y < len_y + 1; ++y) {
        for (int x = 0; x < len_x; ++x) {
            sand_uwu[y][x] = 0; 
        }
    }

    for (int y = 0; y < len_y; ++y) {
        for (int x = 0; x < len_x; ++x) {
            sand_uwu[y][x] = sand_box[y][x]; 
        }
        delete[] sand_box[y];
    }
    delete[] sand_box;

    sand_box = sand_uwu;

    len_y++; 
    

}

void left_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y){

    uint64_t** sand_uwu = new uint64_t*[len_y]; 
    for (int i = 0; i < len_y; ++i) {
        sand_uwu[i] = new uint64_t[len_x + 1];
    }

    for (int y = 0; y < len_y; ++y) {
        for (int x = 0; x < len_x + 1; ++x) {
            sand_uwu[y][x] = 0; 
        }
    }

    for (int y = 0; y < len_y; ++y) {
        for (int x = 0; x < len_x; ++x) {
            sand_uwu[y][x + 1] = sand_box[y][x]; 
        }
        delete[] sand_box[y];
    }
    delete[] sand_box;

    sand_box = sand_uwu;

    len_x++; 
    

}

void Right_exp(uint64_t** &sand_box, int32_t &len_x, int32_t &len_y){

    uint64_t** sand_uwu = new uint64_t*[len_y]; 
    for (int i = 0; i < len_y; ++i) {
        sand_uwu[i] = new uint64_t[len_x + 1];
    }

    for (int y = 0; y < len_y; ++y) {
        for (int x = 0; x < len_x + 1; ++x) {
            sand_uwu[y][x] = 0; 
        }
    }

    for (int y = 0; y < len_y; ++y) {
        for (int x = 0; x < len_x; ++x) {
            sand_uwu[y][x] = sand_box[y][x]; 
        }
        delete[] sand_box[y];
    }
    delete[] sand_box;

    sand_box = sand_uwu;

    len_x++;
    

}

void safe_BMP_format(const std::string filename, uint64_t** matrix, int height, int width) {

    int row_size = ((width + 1) / 2 + 3) & ~3;
    int padding_size = (4 - (row_size % 4)) % 4;
    int data_size = (row_size + padding_size) * height;

    BITMAPFILEHEADER file_of_headers;
    file_of_headers.bfType = 0x4D42;
    file_of_headers.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 5 * 4 + data_size;
    file_of_headers.bfReserved1 = 0;
    file_of_headers.bfReserved2 = 0;
    file_of_headers.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 5 * 4;

    BITMAPINFOHEADER info_of_headers;
    info_of_headers.biSize = sizeof(BITMAPINFOHEADER);
    info_of_headers.biWidth = width;
    info_of_headers.biHeight = height;
    info_of_headers.biPlanes = 1;
    info_of_headers.biBitCount = 4;
    info_of_headers.biCompression = 0;
    info_of_headers.biSizeImage = data_size;
    info_of_headers.biXPelsPerMeter = 2000;
    info_of_headers.biYPelsPerMeter = 2000;
    info_of_headers.biClrUsed = 16;
    info_of_headers.biClrImportant = 5;

    std::ofstream file_of_bmp(filename, std::ios::out | std::ios::binary);

    file_of_bmp.write(reinterpret_cast<const char*>(&file_of_headers), sizeof(file_of_headers));
    file_of_bmp.write(reinterpret_cast<const char*>(&info_of_headers), sizeof(info_of_headers));

    uint8_t colors[5][4] = { 
        {255, 255, 255 ,0},       // белый
        {153, 255, 153, 0},     // зеленый
        {255, 153, 255, 0},     // фиолетовый
        {153, 255, 255, 0},     // желтый
        {0, 0, 0, 0},   // черный
    };

    for (int i = 0; i < 5; ++i)
        file_of_bmp.write(reinterpret_cast<const char*>(colors[i]), 4);

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x += 2) {
            
            uint8_t byte = 0;

            int sandCount1 = matrix[y][x];
            byte = (sandCount1 > 3 ? 4 : sandCount1) << 4;

            if (x + 1 < width) {
                int sandCount2 = matrix[y][x + 1];
                byte |= (sandCount2 > 3 ? 4 : sandCount2) & 0x0F;
            }

            file_of_bmp.put(byte);
        }

        for (int p = 0; p < row_size - (width + 1) / 2; p++) 
            file_of_bmp.put(0);
    }

    file_of_bmp.close();
}
