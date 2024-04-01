#include "wireframe_edge.h"

#include <shaders/shader_pool.h>

#include <iostream>

namespace s21 {
void WireframeEdge::draw(Drawable &data) {
  shader_program_.bind();
  shader_program_.setUniformValue("u_model", data.transform());
  data.BindVBO();
  shader_program_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
  shader_program_.enableAttributeArray(0);
  data.BindEBO();
  glDrawElements(GL_LINES, data.indexCount(), GL_UNSIGNED_INT, 0);
  data.ReleaseEBO();
  shader_program_.release();
};

WireframeEdge::WireframeEdge() {
  shader_program_.create();
  shader_program_.bind();
  shader_program_.addShader(ShaderPool::Instance().defaultVertex());
  shader_program_.addShader(
      ShaderPool::Instance().get("line_geometry", QOpenGLShader::Geometry));
  shader_program_.addShader(
      ShaderPool::Instance().get("line_fragment", QOpenGLShader::Fragment));
  shader_program_.link();
  std::cout << shader_program_.isLinked() << std::endl;

  shader_program_.setUniformValue("u_point_size", 1.0f);
  shader_program_.release();
};
}  // namespace s21
