#ifndef SRC_VIEW_I_RENDER_VIEW_H_
#define SRC_VIEW_I_RENDER_VIEW_H_

#include <model/utility/transform.h>

#include <string>

#include "render/renderer.h"

namespace s21 {
class IRenderView {
 public:
  using LoadDelegate = std::function<void(std::string, Renderer&)>;
  using DeleteDelegate = std::function<void()>;
  using TransformDelegate = std::function<void(Transform&, Renderer&)>;
  virtual ~IRenderView() = default;

  virtual void SubscribeLoad(LoadDelegate) = 0;
  virtual void SubscribeDelete(DeleteDelegate) = 0;
  virtual void SubscribeTransform(TransformDelegate) = 0;
};
}  // namespace s21

#endif  // SRC_VIEW_I_RENDER_VIEW_H_
