include(FetchContent)

# OpenGL
find_package(OpenGL REQUIRED)


# The OpenGL Extension Wrangler Library
FetchContent_Declare(
        glew
        URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0-win32.zip)
FetchContent_MakeAvailable(glew)


# Graphics Library Framework
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.3)
FetchContent_MakeAvailable(glfw)


# OpenGL Mathematics
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)


# Open Asset Import Library
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v4.1.0)
FetchContent_MakeAvailable(assimp)


set(OPENGL_LIBRARY ${OPENGL_LIBRARY} PARENT_SCOPE)
set(EXTERNAL_INCLUDES
        ${glew_SOURCE_DIR}/include/
        ${assimp_SOURCE_DIR}/include/ ${assimp_BINARY_DIR}/include/
        PARENT_SCOPE)
set(EXTERNAL_LINKS
        ${glew_SOURCE_DIR}/lib/Release/x64
        ${assimp_BINARY_DIR}/code
        PARENT_SCOPE)
