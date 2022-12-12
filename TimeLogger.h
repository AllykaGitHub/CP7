//
// Created by lyaho on 12.12.2022.
//

#ifndef CP7_TIMELOGGER_H
#define CP7_TIMELOGGER_H


#include<iostream>
#include<chrono>
#include<string>
#include<fstream>

class TimeLogger{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::duration<double> time_value;
    std::ofstream file_results;
public:
    explicit TimeLogger(const std::string& file_name) {
        time_value = std::chrono::seconds(0);
        file_results.open(file_name);
        file_results << "Container;Data_type;Operation;Number of elements;Time_value\n";
    }
    ~TimeLogger(){
        file_results.close();
    }
    void start_measuring_time(){
        if (time_value.count() != 0){
            std::cout << "Please, reset the logger before start new measurement;" << std::endl;
            return;
        }
        start = std::chrono::high_resolution_clock::now();
    }
    void end_measuring_time(){
        end = std::chrono::high_resolution_clock::now();
        time_value = end - start;
    }
    void reset(){
        time_value = std::chrono::seconds(0);
    }
    void log(const std::string &container, const std::string &data_type, const std::string &operation, const int &elements){
        file_results << container << ";" << data_type << ";" << operation <<
                     ";" << elements << ";" << time_value.count() << "\n";
    }
};


#endif //CP7_TIMELOGGER_H
