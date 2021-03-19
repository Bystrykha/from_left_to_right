#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <regex>

int numbers[3];
std::string one_str_from_file;
std::regex pattern_str("[0-9]+ [0-9]+ [1-9][0-9]+");
std::regex pattern_word("[0-9]+");
unsigned long long q, z;
int n, m;

void from_left_to_right(){
    z = numbers[0];
    m = numbers[2];
    n = 0;
    std::stack <bool> bin_degree;
    for(int i = 0; numbers[1] != 0;){   //перевод в двоичную систему показателя степени
        i = numbers[1] % 2;
        if(i == 0) bin_degree.push(false);
        else bin_degree.push(true);
        numbers[1] = numbers[1] / 2;
        n++;
    }
    bin_degree.pop();
    for(int i = n-1; i > 0; i--){
        z = (z * z) % m;
        if(bin_degree.top()) z = (z * numbers[0]) % m;
        bin_degree.pop();
    }
    std::ofstream out;
    out.open("output.txt", std::ios::app);
    out << z << "\n";
    q = 0;
    z = 0;
    m = 0;
    n = 0;
}

int numb_define(std::string dir){
    std::ifstream file(dir);
    if(file.is_open()){
        while(getline(file, one_str_from_file)) {
            if (std::regex_match(one_str_from_file, pattern_str)) {
                for (int i = 0, j = 0; j < one_str_from_file.length(); j++) {
                    if (one_str_from_file[j] >= '0' && one_str_from_file[j] <= '9') {
                        numbers[i] = numbers[i] * 10 + (one_str_from_file[j] - 48);
                    }
                    else i++;
                }
                from_left_to_right();
            }
            memset(numbers, 0, sizeof(int) * 3);    // обнуление массива
        }
    }
    else return 0;
    return 1;
}

int main(){
    std::string directory = "input.txt";
    int res = numb_define(directory);
    return res;
}
