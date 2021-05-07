add_executable(tutorial03_matrices
        tutorial03.cpp
        ${TASK_1_SOURCE_DIR}/common/shader.cpp
        ${TASK_1_SOURCE_DIR}/common/shader.hpp)
target_link_libraries(tutorial03_matrices ${ALL_LIBS})
target_include_directories(tutorial03_matrices PRIVATE ${TASK_1_SOURCE_DIR})

set(DST ${TASK_1_INSTALL_DIR}/tutorial03_matrices)
install(TARGETS tutorial03_matrices DESTINATION ${DST} COMPONENT ${TASK_1_COMPONENT})
install(FILES SimpleTransform.vertexshader SingleColor.fragmentshader
        DESTINATION ${DST} COMPONENT ${TASK_1_COMPONENT})
