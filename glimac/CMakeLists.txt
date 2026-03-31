cmake_minimum_required(VERSION 3.10)

add_library(glimac)

file(GLOB_RECURSE GLIMAC_SOURCES CONFIGURE_DEPENDS src/*)
if (MSVC)
target_compile_options(glimac PRIVATE /W3)
else()
target_compile_options(glimac PRIVATE -std=c++17)
endif()
target_sources(glimac PRIVATE ${GLIMAC_SOURCES})
target_include_directories(glimac PUBLIC ../glimac)

# ---Add GLFW---
# add_subdirectory(third-party/glfw) # Provided by quick_imgui
target_link_libraries(glimac PUBLIC glfw)
# ---Add glad---
# add_library(glad third-party/glad/src/glad.c) # Provided by quick_imgui
# target_include_directories(glad PUBLIC third-party/glad/include) # Provided by quick_imgui
target_link_libraries(glimac PUBLIC glad)
# ---Add glm---
add_subdirectory(third-party/glm)
target_link_libraries(glimac PUBLIC glm)