cmake_minimum_required()

set(PROJECT_NAME Minecraft)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} 
	src/main.cpp
)

set(PUBLIC_INCLUDES
	external/stb_image/stb_image.h

	src/Window/Window.hpp

	src/Game/Application.hpp
	src/Game/GameObjects/Cube.hpp
	src/Game/GameObjects/Block.hpp
	src/Game/GameObjects/Chunk.hpp
	src/Game/GameObjects/Button2D.hpp
	src/Game/GameStates/StartScreen.hpp
	src/Game/Renderer/ChunkRenderer.hpp

	src/Events/Event.hpp
	src/Events/Keys.hpp

	src/Player/Camera.hpp
	src/Player/Player.hpp
	src/Player/Ray.hpp

	src/Physics/PhysicsEngine.hpp

	src/RenderEngine/OpenGL/Polygon2D.hpp
	src/RenderEngine/OpenGL/Animated_Polygon2D.hpp
	src/RenderEngine/OpenGL/Texture2D.hpp
	src/RenderEngine/OpenGL/ShaderProgram.hpp
	src/RenderEngine/OpenGL/VertexBuffer.hpp
	src/RenderEngine/OpenGL/VertexBufferLayout.hpp
	src/RenderEngine/OpenGL/IndexBuffer.hpp
	src/RenderEngine/OpenGL/VertexArray.hpp
	src/RenderEngine/OpenGL/Renderer.hpp

	src/Resources/ResourceManager.hpp
)
set(PUBLIC_SOURCES
	src/Window/Window.cpp

	src/Game/Application.cpp
	src/Game/GameObjects/Cube.cpp
	src/Game/GameObjects/Block.cpp
	src/Game/GameObjects/Chunk.cpp
	src/Game/GameObjects/Button2D.cpp
	src/Game/GameStates/StartScreen.cpp
	src/Game/Renderer/ChunkRenderer.cpp

	src/Player/Camera.cpp
	src/Player/Player.cpp
	src/Player/Ray.cpp

	src/Physics/PhysicsEngine.cpp

	src/RenderEngine/OpenGL/Polygon2D.cpp
	src/RenderEngine/OpenGL/Animated_Polygon2D.cpp
	src/RenderEngine/OpenGL/Texture2D.cpp
	src/RenderEngine/OpenGL/ShaderProgram.cpp
	src/RenderEngine/OpenGL/VertexBuffer.cpp
	src/RenderEngine/OpenGL/VertexBufferLayout.cpp
	src/RenderEngine/OpenGL/IndexBuffer.cpp
	src/RenderEngine/OpenGL/VertexArray.cpp
	src/RenderEngine/OpenGL/Renderer.cpp

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

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/saved_worlds $<TARGET_FILE_DIR:${PROJECT_NAME}>/saved_worlds)