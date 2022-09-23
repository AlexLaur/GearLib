add_executable (gearlib main.cpp)

target_link_libraries(gearlib PRIVATE Adapters Dto Interfaces Domain)