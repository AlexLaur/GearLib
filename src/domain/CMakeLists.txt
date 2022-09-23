add_subdirectory(dto)
add_subdirectory(ports)

add_library(
	Domain
	"${CMAKE_CURRENT_SOURCE_DIR}/libraryConverter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/libraryConverter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/tracksLibrary.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/tracksLibrary.cpp"
)
