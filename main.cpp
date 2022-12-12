#include <iostream>
#include <unordered_set>
#include <fstream>
#include "TimeLogger.h"


struct TwoIntNum{
};

class MyHashFunction{
private:
    static int M;
    static int K;
public:
    size_t operator()(const std::string str_) const{
        long long sum = 0;
        long long mult = 1;
        for (char c: str_){
            sum += c * mult;
            mult *= static_cast<long long>(K);
        }
        return sum % M;
    }
};

typedef std::unordered_set<std::string, MyHashFunction> MySet;

int MyHashFunction::K = 128;
int MyHashFunction::M = 97;
const int k = 128;
const int m = 97;

int main() {
    const std::string path_to_write_1 = "Results_k128_m97.txt";
    const std::string path_elems = "Elems_k128_m97.txt";

    std::unordered_set<std::string, MyHashFunction> my_set;

    std::ifstream read_file("dostoevsky.txt");
    TimeLogger logger_r(path_to_write_1);
    std::string buffer;
    logger_r.start_measuring_time();
    read_file >> buffer;
    while (!read_file.eof()){
        my_set.insert(buffer);
        read_file >> buffer;
    }
    read_file.close();
    logger_r.end_measuring_time();
    logger_r.log("unordered_set", "read", "K, M", 0);
    logger_r.reset();

    logger_r.start_measuring_time();
    my_set.find("выразить");
    logger_r.end_measuring_time();
    logger_r.log("unordered_set", "find", "K, M", 0);
    logger_r.reset();

    std::ofstream write(path_elems);
    write << "hash; elems" << std::endl;
    for (size_t i = 0; i < m; i++){
        write << i << ";" << my_set.bucket_size(i) << std::endl;
    }
    write.close();
    return 0;

}
//    while (!my_file.eof()){
//        std::cout << buffer << std::endl;
//        my_file >> buffer;
//    }
//    std::cout << std::endl;