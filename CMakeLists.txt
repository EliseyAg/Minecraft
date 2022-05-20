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
	source/Renderer/ShaderProgram.hpp
	source/Renderer/IndexBuffer.hpp
	source/Renderer/VertexBuffer.hpp
	source/Renderer/VertexArray.hpp
)
set(PUBLIC_SOURCES
	source/Application.cpp
	source/Window.cpp
	source/Renderer/ShaderProgram.cpp
	source/Renderer/IndexBuffer.cpp
	source/Renderer/VertexBuffer.cpp
	source/Renderer/VertexArray.cpp
)
set(ALL_SOURCES
	${PUBLIC_INCLUDES}
	${PUBLIC_SOURCES}
)

add_library(${PROJECT_NAME} STATIC
	${ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ALL_SOURCES}
)

target_include_directories(${PROJECT_NAME} PUBLIC source)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../Minecraft/external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../Minecraft/external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)