#ifndef SRC_MODEL_I_RENDER_MODEL_H_
#define SRC_MODEL_I_RENDER_MODEL_H_

#include <model/utility/transform.h>

#include <cstdint>

#include "entity.h"
namespace s21 {
class IRenderModel {
 public:
  // virtual ~IRenderModel() = default;

  // calls to parser to construct Entity from obj file
  virtual Entity& Add(Entity&& file) = 0;

  virtual void Clear() = 0;

  // updates current object's Transform
  // if transform component value is 0 this component is not updated
  // feel free to find some other ways of transform updating
  virtual Entity& Get(int32_t index) = 0;
};
}  // namespace s21

#endif  // SRC_MODEL_I_RENDER_MODEL_H_
