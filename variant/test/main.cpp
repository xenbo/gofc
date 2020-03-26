#include <sstream>
#include <iostream>
#include "../export_c.h"

template<class T>
std::string ConvertToString11(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}
template<class Type>
Type stringToNum11(const std::string &str) {
    std::istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}


int main() {


    auto v = SetString("xxxx",3);
    std::cout << GetType(v) << std::endl;

    char tmp[100] = {0};
    int
    l = GetString(v, tmp, 100);
    std::cout << tmp  << "," <<l<< std::endl;

    std::cout << ConvertToString11(11.5) <<std::endl;

    std::cout << stringToNum11<double>("1.5") <<std::endl;;


    return 0;
}