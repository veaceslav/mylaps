#pragma once
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>


/**
 * @brief The laps_data struct defines the input data
 */
struct laps_data {
    std::uint8_t m_cart_nr;
    std::uint64_t m_seconds;
};

std::int64_t MAX_INT = 0x7FFFFFFFFFFFFFFF;

/**
 * @brief The racing_data struct contains information about
 * all karts best times, and it's used to compute the final result
 */
struct racing_data {
    std::uint8_t m_cart{0};
    std::int64_t m_lap_nr{0};
    std::int64_t m_prev_passing{-1};
    std::int64_t m_best_lap_time{MAX_INT};
    std::int64_t m_best_lap{-1};
};



std::optional<laps_data> parse_line(std::string const& line){

    std::stringstream ss(line);
    char delim;
    std::uint64_t kart_nr, hour, minutes, seconds;
    // Note: this is not the most reliable parser, we should instead get the time
    // string and also validate that it's in hh:mm::ss format
    ss >> kart_nr >> delim >> hour >> delim >> minutes >> delim >> seconds;


    if( kart_nr > 5 || hour  > 23 || minutes > 59 || seconds > 59){
        return std::nullopt;
    }

    return laps_data { static_cast<std::uint8_t>(kart_nr), (hour*3600)+(minutes*60)+seconds };
}


void calculate_winner(std::vector<racing_data>& racing_data,
                      struct racing_data& final_result,
                      laps_data const& lap_time){

    auto& current_kart = racing_data[lap_time.m_cart_nr-1];
    if(current_kart.m_prev_passing == -1){
        current_kart.m_prev_passing = lap_time.m_seconds;
        current_kart.m_cart = lap_time.m_cart_nr;
        return;
    }

    current_kart.m_lap_nr++;
    std::int64_t best_lap = lap_time.m_seconds - current_kart.m_prev_passing;
    if(best_lap < current_kart.m_best_lap_time){
        current_kart.m_best_lap_time = best_lap;
        current_kart.m_best_lap = current_kart.m_lap_nr;
    }
    current_kart.m_prev_passing = lap_time.m_seconds;

    // everytime a kart will do a new lap, check and store the best lap
    if(final_result.m_lap_nr < current_kart.m_lap_nr){
        for(auto& data :  racing_data){
            if(data.m_best_lap_time < final_result.m_best_lap_time){

                final_result.m_best_lap_time = data.m_best_lap_time;
                final_result.m_cart = data.m_cart;
                final_result.m_best_lap = data.m_best_lap;
            }
        }
        final_result.m_lap_nr++;
    }

}
