cmake_minimum_required()

set(PROJECT_NAME Minecraft)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	source/main.cpp
)

set(PUBLIC_INCLUDES
	source/Application.hpp
	source/Window.hpp
	source/Event.hpp
)
set(PUBLIC_SOURCES
	source/Application.cpp
	source/Window.cpp
)
add_library(${PROJECT_NAME} STATIC
	${PUBLIC_INCLUDES}
	${PUBLIC_SOURCES}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../Minecraft/external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../Minecraft/external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)