#include "render_strategy.h"

#include <iostream>
namespace s21 {
RenderStrategy& RenderStrategy::setViewport(float width, float height) {
  shader_program_.bind();
  shader_program_.setUniformValue("u_viewport", QVector2D(width, height));
  shader_program_.release();
  return *this;
}

RenderStrategy& RenderStrategy::setProjectionMatrix(const QMatrix4x4& proj) {
  shader_program_.bind();
  shader_program_.setUniformValue("u_projection", proj);
  shader_program_.release();
  return *this;
}

RenderStrategy& RenderStrategy::setViewMatrix(const QMatrix4x4& view) {
  shader_program_.bind();
  shader_program_.setUniformValue("u_view", view);
  shader_program_.release();
  return *this;
}

RenderStrategy& RenderStrategy::setRenderColor(const QColor& value) {
  shader_program_.bind();
  shader_program_.setUniformValue("u_color", value);
  shader_program_.release();
  return *this;
}

RenderStrategy& RenderStrategy::set(const std::string& param_name,
                                    float value) {
  shader_program_.bind();
  shader_program_.setUniformValue(param_name.c_str(), value);
  shader_program_.release();
  return *this;
}
}  // namespace s21