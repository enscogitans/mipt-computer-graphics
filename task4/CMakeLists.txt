add_definitions(-DGLEW_STATIC)

add_executable(task4
        main.cpp
        ${PROJECT_SOURCE_DIR}/common/shader.cpp
        ${PROJECT_SOURCE_DIR}/common/shader.hpp)
target_link_libraries(task4 glew32s glfw glm ${OPENGL_LIBRARY})
target_include_directories(task4 PRIVATE ${PROJECT_SOURCE_DIR})

set(DST task4)
install(TARGETS task4 DESTINATION ${DST})
install(FILES
        vertex.shader fragment.shader
        DESTINATION ${DST})
