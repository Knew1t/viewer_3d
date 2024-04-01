#ifndef SRC_VIEW_RENDER_STRATEGY_H_
#define SRC_VIEW_RENDER_STRATEGY_H_

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <list>

#include "../utility/projection.h"
#include "drawable.h"

namespace s21 {
class RenderStrategy : protected QOpenGLFunctions {
 public:
  RenderStrategy() { initializeOpenGLFunctions(); }
  virtual ~RenderStrategy() = default;

  virtual void draw(Drawable& data) = 0;

  virtual RenderStrategy& setViewport(float width, float height);

  virtual RenderStrategy& setProjectionMatrix(const QMatrix4x4& proj);

  virtual RenderStrategy& setViewMatrix(const QMatrix4x4& view);

  virtual RenderStrategy& setRenderColor(const QColor& value);

  virtual RenderStrategy& set(const std::string& param_name, float value);

 protected:
  QOpenGLShaderProgram shader_program_;
};
}  // namespace s21

#endif  // SRC_VIEW_RENDER_STRATEGY_H
