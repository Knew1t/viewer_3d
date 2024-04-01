#include "scene.h"

namespace s21 {
Entity& Scene::Add(Entity&& target) {
  objects_.clear();
  return objects_.emplace_back(std::forward<Entity>(target));
}

void Scene::Clear() { objects_.clear(); }

Entity& Scene::Get(int32_t index) { return objects_.at(index); }
}  // namespace s21
