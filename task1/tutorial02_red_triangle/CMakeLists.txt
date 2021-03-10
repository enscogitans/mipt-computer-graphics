add_executable(tutorial02_red_triangle
        tutorial02.cpp
        ${TASK_1_SOURCE_DIR}/common/shader.cpp
        ${TASK_1_SOURCE_DIR}/common/shader.hpp)
target_link_libraries(tutorial02_red_triangle ${ALL_LIBS})
target_include_directories(tutorial02_red_triangle PRIVATE ${TASK_1_SOURCE_DIR})

set(DST ${TASK_1_INSTALL_DIR}/tutorial02_red_triangle)
install(TARGETS tutorial02_red_triangle DESTINATION ${DST})
install(FILES SimpleFragmentShader.fragmentshader SimpleVertexShader.vertexshader
        DESTINATION ${DST})
