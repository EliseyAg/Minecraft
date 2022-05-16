cmake_minimum_required()

set(PROJECT_NAME Minecraft)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	source/main.cpp
)

set(PUBLIC_SOURCES
	source/Application.hpp
	source/Application.cpp
)

add_library(${PROJECT_NAME} STATIC
	${PUBLIC_SOURCES}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../Minecraft/external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)