#include <iostream>

#include "glfw_wrapper/session.hpp"
#include "game/game.hpp"


static constexpr std::pair<int, int> kOpenGlVersion{3, 3};  // OpenGL 3.3
static const int kMsaa = 4;

int main() {
    try {
        auto glfw_session = std::make_shared<gl::Session>(kOpenGlVersion.first, kOpenGlVersion.second, kMsaa);
        game::Game(glfw_session).Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }
}
