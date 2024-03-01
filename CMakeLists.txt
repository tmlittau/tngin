cmake_minimum_required(VERSION 3.25)
project(tngin_engine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# add external libraries
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(raylib REQUIRED)

file(GLOB SOURCES "src/*.cpp", "src/*/*.cpp", "src/*/*/*.cpp", "src/*/*/*/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC 
        glm::glm
        OpenGL::GL
        GLEW::GLEW
        raylib
    PRIVATE
        glfw
)

# Copy over the shaders to target directory
ADD_CUSTOM_TARGET(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    ${CMAKE_CURRENT_BINARY_DIR}/../../shaders
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    COMMENT "Copying shaders"
)

ADD_DEPENDENCIES(${PROJECT_NAME} copy_shaders)