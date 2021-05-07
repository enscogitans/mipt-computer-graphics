#include "game.hpp"

#include <set>

#include "dodecahedron.hpp"


namespace {

std::vector<glm::mat4> GetModelMatrices(const std::vector<game::Entity>& entities) {
    std::vector<glm::mat4> result(entities.size());
    std::transform(entities.begin(), entities.end(), result.begin(),
                   [](const game::Entity& e) { return e.GetModelMatrix(); });
    return result;
}

template <typename T>
std::vector<T> RemoveIndices(const std::vector<T>& src, const std::set<size_t>& indices) {
    std::vector<T> result;
    result.reserve(src.size() - indices.size());

    auto it = indices.begin();
    for (size_t i = 0; i < src.size(); ++i) {
        if (it != indices.end() && *it == i) {
            ++it;
            continue;
        }
        result.push_back(src[i]);
    }

    return result;
}

}  // namespace


namespace game {

Game::Game(const std::shared_ptr<gl::Session>& session)
        : session_(session)
        , window_(session->MakeWindow(kWindowWidth, kWindowHeight, kWindowTitle))
        , enemy_model_(dodecahedron::kTriangles, dodecahedron::kColors, kEnemyVertexShaderPath, kEnemyFragmentShaderPath, kEnemyRadius)
        , fireball_model_(kFireballModelPath, kFireballTexturePath, kFireballVertexShaderPath, kFireballFragmentShaderPath, kFireballRadius)
        , player_(kPlayerViewPoint, kPlayerViewDirection)
        , random_generator_(std::random_device()())
        , text_drawer_(kFontPath, kFontVertexShaderPath, kFontFragmentShaderPath)
{
    window_->SetContext(this);
    window_->SetCursorRawInputMode(true);
    RegisterControlCallbacks();
}

void Game::Run() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.5f, 0.9f, 1.0f, 0.0f);  // Light blue
    auto prev_time = static_cast<float>(glfwGetTime());
    float prev_generation_time = prev_time;
    while (!window_->ShouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen

        glm::mat4 vp = kProjection * player_.GetViewMatrix();
        enemy_model_.DrawInstances(vp, GetModelMatrices(enemy_entities_));
        fireball_model_.DrawInstances(vp, GetModelMatrices(fireball_entities_));

        auto time = static_cast<float>(glfwGetTime());
        UpdateEntities(time - prev_time);
        if (time - prev_generation_time > kEnemyGenerationTimeDelta) {
            GenerateEnemy();
            prev_generation_time = time;
        }
        prev_time = time;

        DrawHud();

        window_->SwapBuffers();
        session_->PollEvents();
    }
}

void Game::DrawHud() {
    text_drawer_.DrawText("Destroyed: " + std::to_string(enemies_destroyed_),
                          kHudPositionX, kHudPositionY, kFontSize,
                          kWindowWidth, kWindowHeight);
    text_drawer_.DrawText("Missed   : " + std::to_string(enemies_missed_),
                          kHudPositionX, kHudPositionY - kFontLeading, kFontSize,
                          kWindowWidth, kWindowHeight);
}

void Game::UpdateEntities(float time_delta) {
    std::set<size_t> enemies_to_delete;
    std::set<size_t> fireballs_to_delete;

    // Move objects
    for (size_t i = 0; i < enemy_entities_.size(); ++i) {
        enemy_entities_[i].UpdatePosition(time_delta);
        float dist = enemy_entities_[i].GetDistance(player_.GetPosition());
        if (dist == 0.0f) {
            ++enemies_missed_;
            enemies_to_delete.insert(i);
        } else if (dist > kWorldRadius) {
            enemies_to_delete.insert(i);
        }
    }
    for (size_t j = 0; j < fireball_entities_.size(); ++j) {
        fireball_entities_[j].UpdatePosition(time_delta);
        if (fireball_entities_[j].GetDistance(player_.GetPosition()) > kWorldRadius) {
            fireballs_to_delete.insert(j);
        }
    }

    // Collide objects
    for (size_t i = 0; i < enemy_entities_.size(); ++i) {
        for (size_t j = i + 1; j < enemy_entities_.size(); ++j) {
            if (Entity::IsOverlap(enemy_entities_[i], enemy_entities_[j])) {
                enemies_to_delete.insert(i);
                enemies_to_delete.insert(j);
            }
        }
    }
    for (size_t i = 0; i < fireball_entities_.size(); ++i) {
        for (size_t j = i + 1; j < fireball_entities_.size(); ++j) {
            if (Entity::IsOverlap(fireball_entities_[i], fireball_entities_[j])) {
                fireballs_to_delete.insert(i);
                fireballs_to_delete.insert(j);
            }
        }
    }

    size_t pred_enemies_to_delete_size = enemies_to_delete.size();
    for (size_t i = 0; i < enemy_entities_.size(); ++i) {
        for (size_t j = 0; j < fireball_entities_.size(); ++j) {
            if (Entity::IsOverlap(enemy_entities_[i], fireball_entities_[j])) {
                enemies_to_delete.insert(i);
                fireballs_to_delete.insert(j);
            }
        }
    }
    enemies_destroyed_ += enemies_to_delete.size() - pred_enemies_to_delete_size;

    // Delete objects
    enemy_entities_ = RemoveIndices(enemy_entities_, enemies_to_delete);
    fireball_entities_ = RemoveIndices(fireball_entities_, fireballs_to_delete);
}

/*
 * Generate enemy located in truncated pyramid and moving towards the player.
 * Parameters of this pyramid are taken from player's camera parameters
 */
void Game::GenerateEnemy() {
    static std::uniform_real_distribution<float> dist_gen(kEnemyGenerationMinDistance, kEnemyGenerationMaxDistance);
    static std::uniform_real_distribution<float> pos_gen(-1.0f, 1.0f);
    static auto angle_gen = [] (std::mt19937& rg) { return glm::pi<float>() * pos_gen(rg); };

    float z = dist_gen(random_generator_);
    float x = z * std::sin(kFov / 2) * pos_gen(random_generator_);
    float y = z * std::sin(kFov / 2) / kAspect * pos_gen(random_generator_);

    glm::vec3 enemy_pos{x, y, z};
    glm::vec3 enemy_speed_vec = kEnemySpeed * glm::normalize(player_.GetPosition() - enemy_pos);

    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle_gen(random_generator_), {1, 0, 0});
    rotation = glm::rotate(rotation, angle_gen(random_generator_), {0, 1, 0});

    enemy_entities_.emplace_back(kEnemyRadius, enemy_pos, rotation, enemy_speed_vec);
}

void Game::RegisterControlCallbacks() {
    window_->SetCursorPos(0, 0);
    window_->SetCursorPosCallback(Game::MousePosCallback);
    window_->SetMouseButtonCallback(Game::MouseButtonCallback);
    window_->SetKeyCallback(Game::KeyCallback);
}

void Game::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
        Game* self = gl::Window::GetContext<Game>(window);
        self->window_->SetShouldClose(true);
    }
}

void Game::MousePosCallback(GLFWwindow* window, double x, double y) {
    Game* self = gl::Window::GetContext<Game>(window);
    self->player_.MoveViewDirection(-static_cast<float>(x) * self->kMouseSensitivity,
                                    -static_cast<float>(y) * self->kMouseSensitivity);
    self->window_->SetCursorPos(0, 0);
}

void Game::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        Game* self = gl::Window::GetContext<Game>(window);
        std::optional<Entity> opt = self->player_.Shoot(
                game::Game::kFireballRadius,
                game::Game::kFireballSpeed,
                game::Game::kPlayerShootCooldown
        );
        if (opt) {
            self->fireball_entities_.push_back(*opt);
        }
    }
}

}  // namespace game
