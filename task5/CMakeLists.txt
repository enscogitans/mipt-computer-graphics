add_definitions(-DGLEW_STATIC)

add_executable(task5
        main.cpp
        model/instancing_model.cpp model/instancing_model.hpp
        game/game.cpp game/game.hpp
        game/entity.cpp game/entity.hpp
        game/player.cpp game/player.hpp
        glfw_wrapper/session.cpp glfw_wrapper/session.hpp
        glfw_wrapper/window.cpp glfw_wrapper/window.hpp
        ${PROJECT_SOURCE_DIR}/common/shader.cpp ${PROJECT_SOURCE_DIR}/common/shader.hpp
        ${PROJECT_SOURCE_DIR}/common/bmp_loader.cpp ${PROJECT_SOURCE_DIR}/common/bmp_loader.hpp
        ${PROJECT_SOURCE_DIR}/common/dds_loader.cpp ${PROJECT_SOURCE_DIR}/common/dds_loader.hpp
        ${PROJECT_SOURCE_DIR}/common/text.cpp ${PROJECT_SOURCE_DIR}/common/text.hpp
        ${PROJECT_SOURCE_DIR}/common/misc.cpp ${PROJECT_SOURCE_DIR}/common/misc.hpp)
target_link_libraries(task5 assimp glew32s glfw glm ${OPENGL_LIBRARY})
target_include_directories(task5 PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/task5)

set(DST task5)
install(TARGETS task5 DESTINATION ${DST} COMPONENT hw2)
install(DIRECTORY resources DESTINATION ${DST} COMPONENT hw2)
