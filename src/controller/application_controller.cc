#include "application_controller.h"

#include <model/processors/obj_parser.h>

#include <functional>

#include "model/processors/primitive_builder.h"
#include "model/utility/transform.h"

namespace s21 {
ApplicationController::ApplicationController(IRenderModel *model,
                                             IRenderView *view)
    : model_(model), view_(view) {
  view_->SubscribeLoad(std::bind(&ApplicationController::OnLoad, this,
                                 std::placeholders::_1, std::placeholders::_2));
  view_->SubscribeTransform(std::bind(&ApplicationController::OnTransformed,
                                      this, std::placeholders::_1,
                                      std::placeholders::_2));
  view_->SubscribeDelete(std::bind(&ApplicationController::OnDelete, this));
};
ApplicationController::~ApplicationController() {}

void ApplicationController::OnLoad(std::string file, Renderer &ren) {
  if (file != "cube") {
    Entity &loaded = model_->Add(ObjectParser::GetInstance()->process(file));
    ren.copy(loaded.data(), loaded.order(),
             TransformProcessor::transform(loaded.transform()), loaded.color());
  } else {
    Entity cube = model_->Add(
        PrimitiveBuilder::getPrimitive(PrimitiveBuilder::Primitives::Cube));
    ren.copy(cube.data(), cube.order(),
             TransformProcessor::transform(cube.transform()), cube.color());
  }
}

void ApplicationController::OnDelete() { model_->Clear(); }

// transforming event
void ApplicationController::OnTransformed(Transform &value, Renderer &ren) {
  Drawable *target = ren.grabbed();
  if (target) {
    target->transform() = TransformProcessor::transform(value);
  }
  model_->Get(0).transform() = value;
}
}  // namespace s21
