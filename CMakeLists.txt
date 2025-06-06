cmake_minimum_required(VERSION 3.30)
project(ERB_LIB)

set(CMAKE_CXX_STANDARD 20)


option(ERB_BUILD_COREUTILS "Build coreutils module" ON)  # Usually always needed


if(ERB_BUILD_COREUTILS)
    add_subdirectory(src/coreutils)
endif()


add_library(erb INTERFACE)
add_library(erb::erb ALIAS erb)
if(ERB_BUILD_COREUTILS)
    target_link_libraries(erb INTERFACE erb::coreutils)
endif()

# Include directories for the main interface
target_include_directories(erb INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)