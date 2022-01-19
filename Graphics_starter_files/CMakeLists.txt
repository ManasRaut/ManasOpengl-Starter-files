# CMakeList.txt : CMake project for Graphics_starter_files, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
	"Main.cpp" "Camera.cpp" "Core.cpp" "Debug.cpp" "Gui.cpp" "Mesh.cpp"
	"Model.cpp" "SceneLoader.cpp" "Shader.cpp" "stb.cpp" "Window.cpp" "World.cpp")

# TODO: Add tests and install targets if needed.
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

add_subdirectory(vendor/GLFW)

target_include_directories(${PROJECT_NAME} 
	PUBLIC include 
	PUBLIC vendor/GLFW/include
	PUBLIC vendor/ImGUI
)

target_link_directories(${PROJECT_NAME}
	PRIVATE lib
	PUBLIC vendor/GLFW/src
)

target_link_libraries(${PROJECT_NAME} 
	glfw
)