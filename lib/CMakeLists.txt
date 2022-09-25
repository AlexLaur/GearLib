# Google Test
add_subdirectory(googletest)

# PugiXML
add_subdirectory(pugixml)

# Argparse
add_subdirectory(argparse)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC argparse/include)

# CxxUrl
# add_subdirectory(CxxUrl)