# mylaps

## Building
The program supports CMake build system
and requires a C++17 compatible compiler
Tested to work both under linux and windows(with QtCreator)
In the current folder:
$ mkdir build && cd build
$ cmake ..

## Running
After building, we get the mylaps executable:
$ ./mylaps karttimes.csv

## Example output
in case that csv file does not contain any errors:
kart nr: 2 best lap: 1

## Running unit tests
Cmake also builds the unit tests executable.
To run the unit tests:
$ ./unit_tests

## Solution description
To parse the csv, I used simple sstream parsing, which is not very error-prone.
A better solution would be to also match the time with a regex, to check if it's in the proper format

When calculating the winner and the best lap, I will only check for the best lap when any kart would make 
the next lap. All the best laps that are made after one kart completed all laps, will be discarded

The logic has been implemented in logic.hpp because it's being used by both main file and the unit_tests.
If needed implementation can also be moved to logic.cpp. 

The solution uses free functions, because the problem was quite small and encapsulating in classes would have produced
less readable code.
