add_executable(tutorial03_matrices
        tutorial03.cpp
        ${TASK_1_DIR}/common/shader.cpp
        ${TASK_1_DIR}/common/shader.hpp
        SimpleTransform.vertexshader
        SingleColor.fragmentshader)
target_link_libraries(tutorial03_matrices ${ALL_LIBS})
target_include_directories(tutorial03_matrices PRIVATE ${TASK_1_DIR})

configure_file(SimpleTransform.vertexshader
        ${CMAKE_CURRENT_BINARY_DIR}/SimpleTransform.vertexshader
        COPYONLY)
configure_file(SingleColor.fragmentshader
        ${CMAKE_CURRENT_BINARY_DIR}/SingleColor.fragmentshader
        COPYONLY)
