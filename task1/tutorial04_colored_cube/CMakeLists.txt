add_executable(tutorial04_colored_cube
        tutorial04.cpp
        ${TASK_1_DIR}/common/shader.cpp
        ${TASK_1_DIR}/common/shader.hpp
        TransformVertexShader.vertexshader
        ColorFragmentShader.fragmentshader)
target_link_libraries(tutorial04_colored_cube ${ALL_LIBS})
target_include_directories(tutorial04_colored_cube PRIVATE ${TASK_1_DIR})

configure_file(TransformVertexShader.vertexshader
        ${CMAKE_CURRENT_BINARY_DIR}/TransformVertexShader.vertexshader
        COPYONLY)
configure_file(ColorFragmentShader.fragmentshader
        ${CMAKE_CURRENT_BINARY_DIR}/ColorFragmentShader.fragmentshader
        COPYONLY)
