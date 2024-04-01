#include "vertex_square.h"

#include <shaders/shader_pool.h>

#include <iostream>

namespace s21 {
void VertexSquare::draw(Drawable &data) {
  shader_program_.bind();
  shader_program_.setUniformValue("u_model", data.transform());
  data.BindVBO();
  shader_program_.setAttributeBuffer(0, GL_FLOAT, 0, 3);
  shader_program_.enableAttributeArray(0);
  glDrawArrays(GL_POINTS, 0, data.vertexCount());
  data.ReleaseVBO();
  shader_program_.release();
};

VertexSquare::VertexSquare() {
  shader_program_.create();
  shader_program_.bind();
  shader_program_.addShader(ShaderPool::Instance().defaultVertex());
  shader_program_.addShader(ShaderPool::Instance().defaultFragment());
  shader_program_.link();

  shader_program_.setUniformValue("u_point_size", 1.0f);
  shader_program_.release();
};
}  // namespace s21
