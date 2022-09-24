add_subdirectory(dto)
add_subdirectory(ports)

file(GLOB DOMAIN_HEADERS *.hpp)
file(GLOB DOMAIN_IMPLEMENTATIONS *.cpp)

add_library(
	Domain
	${DOMAIN_HEADERS}
	${DOMAIN_IMPLEMENTATIONS}
)
