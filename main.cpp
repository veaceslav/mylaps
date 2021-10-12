#include <iostream>
#include <fstream>
#include <optional>
#include <sstream>
#include <vector>
#include "logic.hpp"


int main(int argc, char** argv){

    if(argc < 2){
        std::cout << "Usage: mylaps karttimes.csv" << std::endl;
        return 1;
    }

    std::fstream laps_file(argv[1], std::ifstream::in);

    if(!laps_file.is_open()){
        std::cout << "Could not open file " << argv[1] << std::endl;
        return 1;
    }
    std::string line;
    std::getline(laps_file, line);


    std::vector<racing_data> racing_data(5);
    struct racing_data final_result;
    while(!laps_file.eof()){
        std::getline(laps_file, line);
        std::optional<laps_data> lap = parse_line(line);
        if(!lap){
            std::cout << "Error parsing line " << line << " laps could not be computed" << std::endl;
            return 1;
        }
        calculate_winner(racing_data, final_result, *lap);
    }

    std::cout << "kart nr: " <<  static_cast<int>(final_result.m_cart) << " best lap: " << final_result.m_best_lap << std::endl;

   return 0;
}
