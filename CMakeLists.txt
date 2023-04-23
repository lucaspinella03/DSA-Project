cmake_minimum_required(VERSION 3.24)
project(MarketSimulation)

set(CMAKE_CXX_STANDARD 17)

add_executable(MarketSimulation main.cpp stock.cpp simulation.cpp llrbtree.cpp simulation.h)


set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(MarketSimulation sfml-system sfml-window sfml-graphics sfml-audio)
