
cmake_minimum_required (VERSION 3.8)

add_executable (${PROJECT_NAME} 
	"Main.cpp" "Camera.cpp" "Core.cpp" "Debug.cpp" "Gui.cpp" "Mesh.cpp"
	"Model.cpp" "SceneLoader.cpp" "Shader.cpp" "Window.cpp" "World.cpp" 
	"vendor/glad/src/glad.c" "vendor/stb/src/stb.cpp" )

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/ImGUI)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/rs $<TARGET_FILE_DIR:${PROJECT_NAME}>/rs)

target_include_directories(${PROJECT_NAME} 
	PUBLIC include 
	PUBLIC vendor/GLFW/include
	PUBLIC vendor/ImGUI
	PUBLIC vendor/GLM/
	PUBLIC vendor
)

target_link_directories(${PROJECT_NAME}
	PRIVATE lib
	PUBLIC vendor/GLFW/src
)

target_link_libraries(${PROJECT_NAME} 
	glfw 
	imgui
	opengl32
	gdi32
)