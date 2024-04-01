#ifndef SRC_VIEW_LINE_STRATEGY_H_
#define SRC_VIEW_LINE_STRATEGY_H_

#include "render_strategy.h"

namespace s21 {
class WireframeEdge final : public RenderStrategy {
 public:
  static WireframeEdge *Instance() {
    static WireframeEdge instance;
    return &instance;
  };

  void draw(Drawable &data) override;

 private:
  WireframeEdge();
};
}  // namespace s21
#endif  // SRC_VIEW_LINE_STRATEGY_H_
