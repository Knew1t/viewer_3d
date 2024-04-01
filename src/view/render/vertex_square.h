#ifndef SRC_VIEW_VERTEX_SQUARE_H_
#define SRC_VIEW_VERTEX_SQUARE_H_

#include "render_strategy.h"

namespace s21 {
class VertexSquare final : public RenderStrategy {
 public:
  static VertexSquare *Instance() {
    static VertexSquare instance;
    return &instance;
  };

  void draw(Drawable &data) override;

 private:
  VertexSquare();
};
}  // namespace s21

#endif  // SRC_VIEW_VERTEX_SQUARE_H_
