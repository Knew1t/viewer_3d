#ifndef SRC_MODEL_UTILITY_TRANSFORM_H_
#define SRC_MODEL_UTILITY_TRANSFORM_H_

#include <QVector3D>

namespace s21 {
struct Transform {
  Transform() : scale(1, 1, 1) {}
  virtual ~Transform() = default;
  QVector3D position;
  QVector3D rotation;
  QVector3D scale;
};
}  // namespace s21

#endif  // SRC_MODEL_UTILITY_TRANSFORM_H_
