cmake_minimum_required (VERSION 3.8)


add_library (imgui
	"imgui.cpp" "imgui_demo.cpp" "imgui_draw.cpp" "imgui_impl_glfw.cpp" "imgui_impl_opengl3.cpp"
	"imgui_stdlib.cpp" "imgui_tables.cpp" "imgui_widgets.cpp"
	)

target_include_directories(imgui 
	PUBLIC ${PROJECT_SOURCE_DIR}/Graphics_starter_files/vendor/GLFW/include
)