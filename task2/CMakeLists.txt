add_definitions(-DGLEW_STATIC)

add_executable(task2
        main.cpp
        ${PROJECT_SOURCE_DIR}/common/shader.cpp
        ${PROJECT_SOURCE_DIR}/common/shader.hpp)
target_link_libraries(task2 glew32s glfw glm ${OPENGL_LIBRARY})
target_include_directories(task2 PRIVATE ${PROJECT_SOURCE_DIR})

set(DST task2)
install(TARGETS task2 DESTINATION ${DST})
install(FILES
        vertex.shader fragment_1.shader fragment_2.shader
        DESTINATION ${DST})
