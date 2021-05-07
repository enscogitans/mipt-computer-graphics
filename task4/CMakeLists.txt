add_definitions(-DGLEW_STATIC)

add_executable(task4
        main.cpp
        ${PROJECT_SOURCE_DIR}/common/shader.cpp ${PROJECT_SOURCE_DIR}/common/shader.hpp
        ${PROJECT_SOURCE_DIR}/common/misc.cpp ${PROJECT_SOURCE_DIR}/common/misc.hpp)
target_link_libraries(task4 glew32s glfw glm ${OPENGL_LIBRARY})
target_include_directories(task4 PRIVATE ${PROJECT_SOURCE_DIR})

set(DST task4)
set(CMP hw1)
install(TARGETS task4 DESTINATION ${DST} COMPONENT ${CMP})
install(FILES
        vertex.shader fragment.shader
        DESTINATION ${DST} COMPONENT ${CMP})
