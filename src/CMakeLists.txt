find_package(glfw3 REQUIRED)

add_library(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}
  PRIVATE
    platform/platform_window.h
    platform/glfw_platform_window_impl.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PUBLIC
        glfw
)

