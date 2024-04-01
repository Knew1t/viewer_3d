#include "drawable.h"

namespace s21 {
Drawable& Drawable::create(const std::vector<QVector3D>& vertices,
                           const std::vector<uint32_t>& indices,
                           QOpenGLVertexArrayObject& vao) {
  vao.bind();

  vbo_.create();
  vbo_.bind();
  vbo_.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
  vbo_.allocate(vertices.data(), sizeof(*vertices.data()) * vertices.size());

  ebo_.create();
  ebo_.bind();
  ebo_.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
  ebo_.allocate(indices.data(), sizeof(GLuint) * indices.size());

  ebo_.release();
  vao.release();

  v_size_ = vertices.size();
  e_size_ = indices.size();
  return *this;
};
}  // namespace s21