## GoogleTest configuration.
# Make the CMake targets defined by GoogleTest defined and available to the rest of the build.
include(FetchContent)
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

# Force GoogleTest to use same CRT libraries (MT/MD) as the main project to avoid link conflicts.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make GoogleTest headers available for all tests.
include_directories(${gtest_SOURCE_DIR}/include)
include_directories(${gmock_SOURCE_DIR}/include)


file(GLOB SOURCE
    "*.cpp"
)

#if(MSVC)
#    add_compile_options(
#        $<$<CONFIG:>:/MT> #---------|
#        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
#        $<$<CONFIG:Release>:/MT> #--|
#    )
#endif()

## Compile tests.
add_executable(${NAME}_test  
  ${SOURCE}
)

#set(CMAKE_CXX_FLAGS_RELEASE CACHE "/MT" FORCE)
#set(CMAKE_CXX_FLAGS_DEBUG CACHE "/MTd" FORCE)
#set_property(TARGET ${NAME}_test PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CompilerFlags
        CMAKE_CXX_FLAGS
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
        CMAKE_C_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELWITHDEBINFO
        )
foreach(CompilerFlag ${CompilerFlags})
    string(REPLACE "/MT" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
    set(${CompilerFlag} "${${CompilerFlag}}" CACHE STRING "msvc compiler flags" FORCE)
    message("MSVC flags: ${CompilerFlag}:${${CompilerFlag}}")
endforeach()


target_link_libraries(${NAME}_test ${NAME}_lib ${LIBS})

# Link test obj files to GoogleTest library that also contains main() function.
target_link_libraries(${NAME}_test gtest_main)
target_link_libraries(${NAME}_test gmock)

# Add all tests created using GoogleTest to CTEST.
include(GoogleTest)
gtest_discover_tests(${NAME}_test)