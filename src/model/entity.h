#ifndef SRC_MODEL_ENTITY_H_
#define SRC_MODEL_ENTITY_H_

#include <QColor>
#include <QMatrix4x4>
#include <QVector3D>
#include <cstdint>
#include <vector>

#include "processors/transform_processor.h"
#include "utility/transform.h"

namespace s21 {
class Entity {
 public:
  // construct entity with given data
  Entity(const std::vector<QVector3D>& vertices,
         const std::vector<uint32_t>& order);
  // moving data would be better that copying
  Entity(std::vector<QVector3D>&& vertices, std::vector<uint32_t>&& order);

  virtual ~Entity() = default;

  QColor& color() { return color_; }
  const QColor& color() const { return color_; }

  Transform& transform() { return transform_; }
  const Transform& transform() const { return transform_; }

  const std::vector<QVector3D>& data() const { return vertices_; }
  const std::vector<uint32_t>& order() const { return vertex_order_; }

 private:
  Transform transform_;
  std::vector<QVector3D> vertices_;
  std::vector<uint32_t> vertex_order_;  // like face
  QColor color_;                        // for future use
};
}  // namespace s21

#endif  // SRC_MODEL_ENTITY_H_
