# ## -----------------------------------------------------------------------
# ##
# ## If you want to learn CMake:
# ## https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/cmake/
# ##
# ## If you want to see how to add libraries to your project:
# ## https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/use-libraries/#how-to
# ##
# ## -----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.20)

# You can set the name of your project here
project(chess)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_CLANG_TIDY "clang-tidy"
)

# Choose your C++ version
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# Enable many good warnings.
# /WX and -Werror enable "warnings as errors": This means that your code won't compile if you have any warning.
# This forces you to take warnings into account, which is a good practice because warnings are here for a reason and can save you from a lot of bugs!
# If this is too strict for you, you can remove /WX and -Werror.
if(MSVC)
# target_compile_options(${PROJECT_NAME} PRIVATE /WX /W4)
else()
    # target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wimplicit-fallthrough)
endif()

# Set the folder where the executable is created
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Add all the source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Copy resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/src/shaders"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/src/shaders"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/src/DejaVuSans.ttf"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/src/DejaVuSans.ttf"
)


# Add quick-imgui library
add_subdirectory(lib/quick_imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE quick_imgui::quick_imgui)

# Add glimac library
add_subdirectory(glimac)
target_link_libraries(${PROJECT_NAME} PRIVATE glimac)
set_target_properties(glimac PROPERTIES CXX_CLANG_TIDY "")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unknown-pragmas")

# ---  Config des tests unitaires ---
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE LOGIC_SOURCES CONFIGURE_DEPENDS "src/Logic/*.cpp")

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")

add_executable(unit_tests 
    ${TEST_SOURCES}
    ${LOGIC_SOURCES}
)

target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(unit_tests PRIVATE src)
target_compile_features(unit_tests PRIVATE cxx_std_20)

include(Catch)
catch_discover_tests(unit_tests EXTRA_ARGS "-s")