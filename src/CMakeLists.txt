add_library(Library STATIC chatgpt.cxx)

# Find packages
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

target_include_directories(
    Library PUBLIC "./"
)

target_link_libraries(Library ${CURL_LIBRARIES})
target_link_libraries(Library nlohmann_json::nlohmann_json)