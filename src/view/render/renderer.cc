#include "renderer.h"

#include <QDebug>
#include <iostream>

#include "vertex_round.h"
#include "vertex_square.h"
#include "wireframe_edge.h"

// pizdec chto za alkash eto pisal (c) lacresha

namespace s21 {
Renderer::Renderer(QWidget* parent)
    : QOpenGLWidget(parent),
      grabbed_(nullptr),
      vertex_drawer_(nullptr),
      edge_drawer_(nullptr),
      bg_color_(100, 100, 100) {}

Renderer::~Renderer() {}

Drawable& Renderer::copy(const std::vector<QVector3D>& vertices,
                         const std::vector<uint32_t>& indices,
                         const QMatrix4x4& transform, const QColor& color) {
  object_data_.clear();
  Drawable& object = object_data_.emplace_back();
  object.create(vertices, indices, vao_);
  object.transform() = transform;
  object.color() = color;
  grabbed_ = &object;
  return object;
}

Renderer& Renderer::clear() {
  object_data_.clear();
  grabbed_ = nullptr;
  return *this;
}

Drawable* Renderer::grabbed() noexcept { return grabbed_; }

Renderer& Renderer::backgroundColor(const QColor& color) {
  bg_color_ = color;
  update();
  return *this;
}

Renderer& Renderer::backgroundColor(float r, float g, float b) {
  bg_color_.setRed(r);
  bg_color_.setGreen(g);
  bg_color_.setBlue(b);
  update();
  return *this;
}

Renderer& Renderer::setProjection(ProjectionType type) {
  proj = type;
  return *this;
}

QImage Renderer::getFrame() {
  QImage frame;
  int w = width();
  int h = height();
  resize(800, 600);
  paintGL();
  frame = grabFramebuffer();
  resize(w, h);
  return frame;
}

Renderer& Renderer::edgeType(EdgeType type) {
  if (type == EdgeType::kSolid) {
    edge_drawer_->set("u_count", 0);
  } else if (type == EdgeType::kDashed) {
    edge_drawer_->set("u_count", 10.5);
  }
  return *this;
}

Renderer& Renderer::edgeThickness(float val) {
  edge_drawer_->set("u_thickness", val);
  return *this;
}

Renderer& Renderer::edgeColor(const QColor& color) {
  edge_drawer_->setRenderColor(color);
  return *this;
}
Renderer& Renderer::edgeColor(float r, float g, float b) {
  edge_drawer_->setRenderColor(QColor(r, g, b));
  return *this;
}

Renderer& Renderer::vertexType(VertexType type) {
  if (type == VertexType::kDisabled) {
    vertex_drawer_ = nullptr;
  } else if (type == VertexType::kSquare) {
    vertex_drawer_ = VertexSquare::Instance();
    vertex_drawer_->setViewport(static_cast<float>(width()),
                                static_cast<float>(height()));
  } else if (type == VertexType::kRound) {
    vertex_drawer_ = VertexRound::Instance();
    vertex_drawer_->setViewport(static_cast<float>(width()),
                                static_cast<float>(height()));
  }
  return *this;
}

Renderer& Renderer::vertexSize(float val) {
  if (vertex_drawer_) {
    vertex_drawer_->set("u_point_size", val);
  }
  return *this;
}

Renderer& Renderer::vertexColor(const QColor& color) {
  vertex_color_ = color;
  return *this;
}

Renderer& Renderer::vertexColor(float r, float g, float b) {
  if (vertex_drawer_) {
    vertex_drawer_->setRenderColor(QColor(r, g, b));
  }
  return *this;
}

void Renderer::paintGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (proj == ProjectionType::kOrthographic) {
    edge_drawer_->setProjectionMatrix(
        projection_supplier_.Orthographic(QRect(-5, -5, 11, 11)));
  } else if (proj == ProjectionType::kPerspective) {
    edge_drawer_->setProjectionMatrix(projection_supplier_.Perspective(75));
  }

  if (vertex_drawer_) {
    if (proj == ProjectionType::kOrthographic) {
      vertex_drawer_->setProjectionMatrix(
          projection_supplier_.Orthographic(QRect(-5, -5, 11, 11)));
    } else if (proj == ProjectionType::kPerspective) {
      vertex_drawer_->setProjectionMatrix(projection_supplier_.Perspective(75));
    }
    vertex_drawer_->setViewMatrix(camera_);
    vertex_drawer_->setRenderColor(vertex_color_);
  }

  vao_.bind();
  for (Drawable& object : object_data_) {
    edge_drawer_->draw(object);
    if (vertex_drawer_) {
      vertex_drawer_->draw(object);
    }
  }
  vao_.release();
}

void Renderer::resizeGL(int width, int height) {
  projection_supplier_.width = width;
  projection_supplier_.height = height;
  edge_drawer_->setViewport(static_cast<float>(width),
                            static_cast<float>(height));
  if (vertex_drawer_) {
    vertex_drawer_->setViewport(static_cast<float>(width),
                                static_cast<float>(height));
  }
}

void Renderer::initializeGL() {
  initializeOpenGLFunctions();

  projection_supplier_.near_plane = 0.2f;
  projection_supplier_.far_plane = 200.0f;
  projection_supplier_.width = width();
  projection_supplier_.height = height();

  vao_.create();

  camera_.setToIdentity();
  camera_.translate(0.0f, 0.0f, -5.0f);

  edge_drawer_ = WireframeEdge::Instance();
  proj = ProjectionType::kPerspective;

  edge_drawer_->setViewMatrix(camera_);
  edge_drawer_->setRenderColor(QColorConstants::Black);
  edge_drawer_->set("u_count", 0);
  edge_drawer_->set("u_thickness", 1);
}
}  // namespace s21
