add_definitions(-DGLEW_STATIC)
set(ALL_LIBS glew32s glfw glm ${OPENGL_LIBRARY})

set(TASK_1_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TASK_1_INSTALL_DIR task1)

add_subdirectory(tutorial01_first_window)
add_subdirectory(tutorial02_red_triangle)
add_subdirectory(tutorial03_matrices)
add_subdirectory(tutorial04_colored_cube)
