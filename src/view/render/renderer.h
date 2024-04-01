#ifndef RENDERER_H
#define RENDERER_H

#include <QImage>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <list>
#include <vector>

#include "drawable.h"
#include "render_strategy.h"

namespace s21 {
class Renderer : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  enum class VertexType { kDisabled, kSquare, kRound };

  enum class EdgeType { kSolid, kThick, kDashed };

  enum class ProjectionType { kPerspective, kOrthographic };

  Renderer(QWidget* parent);
  virtual ~Renderer();

  // saves object data to renderer so it could draw it
  // returns reference to created Drawable object
  Drawable& copy(const std::vector<QVector3D>& vertices,
                 const std::vector<uint32_t>& indices,
                 const QMatrix4x4& transform, const QColor& color);
  Renderer& clear();
  Drawable* grabbed() noexcept;

  Renderer& backgroundColor(const QColor& color);
  Renderer& backgroundColor(float r, float g, float b);
  Renderer& setProjection(ProjectionType type);

  Renderer& edgeColor(const QColor& color);
  Renderer& edgeColor(float r, float g, float b);
  Renderer& edgeType(EdgeType type);
  Renderer& edgeThickness(float val);

  Renderer& vertexType(VertexType type);
  Renderer& vertexColor(const QColor& color);
  Renderer& vertexColor(float r, float g, float b);
  Renderer& vertexSize(float val);

  QImage getFrame();

 protected:
  void paintGL();
  void resizeGL(int width, int height);
  void initializeGL();

  Projection projection_supplier_;

  QOpenGLVertexArrayObject vao_;
  std::list<Drawable> object_data_;
  Drawable* grabbed_;

  RenderStrategy* vertex_drawer_;
  RenderStrategy* edge_drawer_;

  QMatrix4x4 camera_;

  QColor bg_color_;

  QColor vertex_color_;

  ProjectionType proj;
};
}  // namespace s21

#endif  // RENDERER_H
