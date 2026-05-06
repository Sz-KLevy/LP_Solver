cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)
set(CMAKE_CXX_STANDARD 20)

project(LPSolver VERSION 1.0)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(solver
    src/main.cpp
    src/Monom.cpp
    src/Feltetel.cpp
    src/Celfuggveny.cpp
)

target_link_libraries(solver PRIVATE Qt6::Widgets)
