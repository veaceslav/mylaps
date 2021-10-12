#pragma once
#include <iostream>
#include <optional>
#include <sstream>

struct laps_data {
    std::uint8_t m_cart_nr;
    std::uint64_t m_seconds;
};


struct racing_data {
    std::uint8_t m_cart;
    std::uint64_t m_lap_nr;
    std::uint64_t m_best_lap;
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

    return laps_data { static_cast<std::uint8_t>(kart_nr), hour*3600+minutes*60+seconds };
}
