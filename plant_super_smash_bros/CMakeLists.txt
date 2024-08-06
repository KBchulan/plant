cmake_minimum_required(VERSION 3.15)

project(plant_super_smash_bros)
set(CMAKE_CXX_STANDARD 11)

#修改路径
set(EASYX_INCLUDE_DIR "easyX/include")
set(EASYX_LIBRARY_DIR "easyX/lib")

file(GLOB_RECURSE SRC_LIST ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB RESOURCES "${PROJECT_SOURCE_DIR}/resources/*.mp3" "${PROJECT_SOURCE_DIR}/resources/*.png" "${PROJECT_SOURCE_DIR}/resources/*.wav" "${PROJECT_SOURCE_DIR}/resources/*.ttf")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(plant ${SRC_LIST} ${RESOURCES})
# sadd_library(plant SHARED ${SRC_LIST} ${RESOURCES})

target_link_libraries(plant PUBLIC ${EASYX_INCLUDE_DIR})
target_link_directories(plant PUBLIC ${EASYX_LIBRARY_DIR})
