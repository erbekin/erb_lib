
add_library(erb_coreutils STATIC Logger.cpp)
add_library(erb::coreutils ALIAS erb_coreutils)

# Include directories
target_include_directories(erb_coreutils PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
        $<INSTALL_INTERFACE:include>
)

# Link system libraries (Logger needs threading)
find_package(Threads REQUIRED)
target_link_libraries(erb_coreutils PUBLIC Threads::Threads)

# Set properties
set_target_properties(erb_coreutils PROPERTIES
        OUTPUT_NAME "erb_coreutils"
        EXPORT_NAME "coreutils"
)