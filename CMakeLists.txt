cmake_minimum_required(VERSION 3.27)
project(scop DESCRIPTION "a small 3D object loader")

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)

include(FetchContent)

# Setup Glfw
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # tag/3.4
)
FetchContent_GetProperties(glfw)
if (NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message(STATUS "Enabling Debug mode")
    set(SCOP_DEBUG ON)
else ()
    message(STATUS "Disabling Debug mode")
    set(SCOP_DEBUG OFF)
endif ()

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE SHADERS "shaders/*.frag" "shaders/*.vert" LIST_DIRECTORIES ON)

add_custom_command(
        OUTPUT ${SHADERS}
        COMMAND bash
        ARGS ${CMAKE_SOURCE_DIR}/shaders/compile.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/shaders
)
add_custom_target(shaders ALL DEPENDS ${SHADERS})

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
add_dependencies(${CMAKE_PROJECT_NAME} shaders)
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wall -Wextra)

if (${SCOP_DEBUG})
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEBUG=true)
else ()
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC DEBUG=false)
    target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Werror)
endif ()

target_include_directories(${CMAKE_PROJECT_NAME}
        PRIVATE include
        PUBLIC ${Vulkan_INCLUDE_DIRS})

target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE ${Vulkan_LIBRARIES}
        PRIVATE glfw
        PRIVATE glm::glm)

add_subdirectory(doxygen)
