#creates library called "Library"
add_library(Library chatgpt.cxx)

# Find packages and load contents, looks for files with name Find<name>.cmake
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

#specifies include directories when compiling specific target, target ehre is "Library"
target_include_directories(
    Library PUBLIC "./"
)

#links items to target
target_link_libraries(Library ${CURL_LIBRARIES})
target_link_libraries(Library nlohmann_json::nlohmann_json)