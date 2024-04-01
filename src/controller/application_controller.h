#ifndef SRC_CONTROLLER_APPLICATION_CONTROLLER_H_
#define SRC_CONTROLLER_APPLICATION_CONTROLLER_H_

#include <model/i_render_model.h>
#include <model/utility/transform.h>
#include <view/i_render_view.h>
#include <view/render/renderer.h>

namespace s21 {
/**
 * i guess you should implement interface to maintain
 * view <-> controller interaction
 * **/
class ApplicationController {
 public:
  ApplicationController(IRenderModel* model, IRenderView* view);
  ~ApplicationController();

 private:
  // file loading event
  // load file into scene using IRenderModel::LoadFromObj
  // then create Drawable object via Renderer::copy, save ref to this object
  // apply object's transform via Drawable::updateTransform
  void OnLoad(std::string file, Renderer& ren);

  void OnDelete();

  // transforming event
  void OnTransformed(Transform& value, Renderer& ren);

  IRenderModel* model_;
  IRenderView* view_;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_APPLICATION_CONTROLLER_H_
