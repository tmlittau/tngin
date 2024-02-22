cmake_minimum_required(VERSION 3.25)
project(tngin_engine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# add external libraries
add_subdirectory(external/vk-bootstrap)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Vulkan REQUIRED)

file(GLOB SOURCES "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp", "src/*/*/*/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

message(STATUS "Vulkan libraries ${Vulkan_INCLUDE_DIRS}")

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        ${GLM_INCLUDE_DIRS}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Vulkan_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        vk-bootstrap
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        glm::glm
    PRIVATE
        glfw
        vk-bootstrap
)