add_executable(tutorial04_colored_cube
        tutorial04.cpp
        ${TASK_1_SOURCE_DIR}/common/shader.cpp
        ${TASK_1_SOURCE_DIR}/common/shader.hpp)
target_link_libraries(tutorial04_colored_cube ${ALL_LIBS})
target_include_directories(tutorial04_colored_cube PRIVATE ${TASK_1_SOURCE_DIR})

set(DST ${TASK_1_INSTALL_DIR}/tutorial04_colored_cube)
install(TARGETS tutorial04_colored_cube DESTINATION ${DST})
install(FILES TransformVertexShader.vertexshader ColorFragmentShader.fragmentshader
        DESTINATION ${DST})
