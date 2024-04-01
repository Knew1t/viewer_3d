#ifndef SRC_VIEW_VERTEX_ROUND_H_
#define SRC_VIEW_VERTEX_ROUND_H_

#include "render_strategy.h"

namespace s21 {
class VertexRound final : public RenderStrategy {
 public:
  static VertexRound *Instance() {
    static VertexRound instance;
    return &instance;
  };

  void draw(Drawable &data) override;

 private:
  VertexRound();
};
}  // namespace s21

#endif  // SRC_VIEW_VERTEX_ROUND_H_
