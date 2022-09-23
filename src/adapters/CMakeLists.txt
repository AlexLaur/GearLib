add_library(
	Adapters
	"${CMAKE_CURRENT_SOURCE_DIR}/fileIO.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/fileIO.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/rekordboxAdapter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/rekordboxAdapter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/virtualDJAdapter.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/virtualDJAdapter.cpp"
)

target_include_directories(Adapters PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")