add_executable(tutorial02_red_triangle
        tutorial02.cpp
        ${TASK_1_DIR}/common/shader.cpp
        ${TASK_1_DIR}/common/shader.hpp
        SimpleFragmentShader.fragmentshader
        SimpleVertexShader.vertexshader)
target_link_libraries(tutorial02_red_triangle ${ALL_LIBS})
target_include_directories(tutorial02_red_triangle PRIVATE ${TASK_1_DIR})

configure_file(SimpleFragmentShader.fragmentshader
        ${CMAKE_CURRENT_BINARY_DIR}/SimpleFragmentShader.fragmentshader
        COPYONLY)
configure_file(SimpleVertexShader.vertexshader
        ${CMAKE_CURRENT_BINARY_DIR}/SimpleVertexShader.vertexshader
        COPYONLY)
