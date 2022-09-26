file(GLOB ADAPTERS_HEADERS *.hpp)
file(GLOB ADAPTERS_IMPLEMENTATIONS *.cpp)

add_library(
	Adapters
	${ADAPTERS_HEADERS}
	${ADAPTERS_IMPLEMENTATIONS}
)

# Use pugixml and cxxurl in adapters
target_link_libraries(
    Adapters
    PUBLIC pugixml cxxurl
)
