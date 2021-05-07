add_definitions(-DGLEW_STATIC)

add_executable(task3
        main.cpp
        ${PROJECT_SOURCE_DIR}/common/shader.cpp ${PROJECT_SOURCE_DIR}/common/shader.hpp
        ${PROJECT_SOURCE_DIR}/common/misc.cpp ${PROJECT_SOURCE_DIR}/common/misc.hpp)
target_link_libraries(task3 glew32s glfw glm ${OPENGL_LIBRARY})
target_include_directories(task3 PRIVATE ${PROJECT_SOURCE_DIR})

set(DST task3)
set(CMP hw1)
install(TARGETS task3 DESTINATION ${DST} COMPONENT ${CMP})
install(FILES
        vertex.shader fragment_1.shader fragment_2.shader
        DESTINATION ${DST} COMPONENT ${CMP})
