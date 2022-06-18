cmake_minimum_required()

set(PROJECT_NAME Minecraft)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
)

set(PUBLIC_INCLUDES
	external/stb_image/stb_image.h
	src/Application.hpp
	src/Window.hpp
	src/Cube.hpp
	src/Polygon2D.hpp
	src/Animated_Polygon2D.hpp
	src/Events/Event.hpp
	src/Events/Keys.hpp
	src/Events/Input.hpp
	src/Player/Camera.hpp
	src/Renderer/Texture2D.hpp
	src/Renderer/ShaderProgram.hpp
	src/Renderer/VertexBuffer.hpp
	src/Renderer/VertexBufferLayout.hpp
	src/Renderer/IndexBuffer.hpp
	src/Renderer/VertexArray.hpp
	src/Resources/ResourceManager.hpp
)
set(PUBLIC_SOURCES
	src/Application.cpp
	src/Window.cpp
	src/Cube.cpp
	src/Polygon2D.cpp
	src/Animated_Polygon2D.cpp
	src/Events/Input.cpp
	src/Player/Camera.cpp
	src/Renderer/Texture2D.cpp
	src/Renderer/ShaderProgram.cpp
	src/Renderer/VertexBuffer.cpp
	src/Renderer/VertexBufferLayout.cpp
	src/Renderer/IndexBuffer.cpp
	src/Renderer/VertexArray.cpp
	src/Resources/ResourceManager.cpp
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
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

add_subdirectory(../Minecraft/external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${PROJECT_NAME} PUBLIC glad)

add_subdirectory(../Minecraft/external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)