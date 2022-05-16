cmake_minimum_required()

set(PROJECT_NAME Minecraft)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	source/main.cpp
)

add_library(${PROJECT_NAME} STATIC
	source/Application.hpp
	source/Application.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)