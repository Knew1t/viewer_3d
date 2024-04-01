#ifndef SRC_MODEL_SCENE_H_
#define SRC_MODEL_SCENE_H_

#include <vector>

#include "i_render_model.h"
#include "model/entity.h"

namespace s21 {
class Scene : public IRenderModel {
 public:
  virtual ~Scene() = default;

  // loads object from file
  // returns loaded object that is last in list
  Entity& Add(Entity&& target) override;

  void Clear() override;

  Entity& Get(int32_t index) override;

 private:
  std::vector<Entity> objects_;
};
}  // namespace s21

#endif  // SRC_VIEW_SCENE_H_
