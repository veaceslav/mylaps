#include <iostream>
#include <optional>
#include "logic.hpp"


void REQUIRED(bool value, int line ){
    if(!value){
        std::cout << "Line:" << line << "Expression not satistfied" << std::endl;
        exit(1);
    }
}
template<typename T>
void TEST(T const& a, T const& b, int line ){
    if(a != b){
        std::cout << "Line:" << line << "Value " << a << " != " << b << std::endl;
        exit(1);
    }
}

// Template specialization because uint8t does not print property
template<>
void TEST(uint8_t const& a, uint8_t const& b, int line ){
    if(a != b){
        std::cout << "Line:" << line << "Value " << (int)a << " != " << (int)b << std::endl;
        exit(1);
    }
}

void test_validation(){

   auto lap_time = parse_line("1,12:34:15");

   REQUIRED(lap_time.operator bool(), __LINE__);

   TEST(lap_time->m_cart_nr, static_cast<std::uint8_t>(1), __LINE__);
   TEST(lap_time->m_seconds, static_cast<std::uint64_t>(12*3600+34*60+15), __LINE__);

   // check bad minutes
   lap_time = parse_line("1,12:64:15");
   REQUIRED(!lap_time.operator bool(), __LINE__);

   // check bad hours
   lap_time = parse_line("1,24:64:15");
   REQUIRED(!lap_time.operator bool(), __LINE__);

}

int main(){
    test_validation();

    std::cout << "All tests passed" << std::endl;
    return 0;
}
