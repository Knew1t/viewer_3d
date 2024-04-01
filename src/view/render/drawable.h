#ifndef SRC_VIEW_DRAWABLE_H_
#define SRC_VIEW_DRAWABLE_H_

#include <QColor>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QVector3D>
#include <vector>

namespace s21 {
class Drawable {
 public:
  Drawable()
      : vbo_(QOpenGLBuffer::VertexBuffer), ebo_(QOpenGLBuffer::IndexBuffer) {}

  Drawable(const QMatrix4x4& transform, const QColor& color)
      : vbo_(QOpenGLBuffer::VertexBuffer),
        ebo_(QOpenGLBuffer::IndexBuffer),
        transform_(transform),
        color_(color) {}

  virtual ~Drawable() {
    vbo_.destroy();
    ebo_.destroy();
  };

  Drawable& create(const std::vector<QVector3D>& vertices,
                   const std::vector<uint32_t>& indices,
                   QOpenGLVertexArrayObject& vao);

  GLuint indexCount() { return e_size_; }
  GLuint vertexCount() { return v_size_; }

  void BindVBO() { vbo_.bind(); }
  void BindEBO() { ebo_.bind(); }
  void ReleaseVBO() { vbo_.release(); }
  void ReleaseEBO() { ebo_.release(); }

  // updates transform matrix
  // matrix should be obtained in controller via TransformProcessor
  QMatrix4x4& transform() { return transform_; }
  const QMatrix4x4& transform() const { return transform_; }
  QColor& color() { return color_; }
  const QColor& color() const { return color_; }

 private:
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
  uint32_t v_size_;
  uint32_t e_size_;
  QMatrix4x4 transform_;
  QColor color_;
};
}  // namespace s21

#endif  // SRC_VIEW_DRAWABLE_H_
