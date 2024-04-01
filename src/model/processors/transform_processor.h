#ifndef SRC_MODEL_PROECESSORS_TRANSFORM_PROCESSOR_H_
#define SRC_MODEL_PROECESSORS_TRANSFORM_PROCESSOR_H_

#include <QMatrix4x4>

#include "../utility/transform.h"

namespace s21 {
class TransformProcessor {
 public:
  static QMatrix4x4 transform(Transform value);

 private:
  static void scale(QMatrix4x4& target, const QVector3D& value);
  static void rotate(QMatrix4x4& target, const QVector3D& value);
  static void translate(QMatrix4x4& target, const QVector3D& value);
};
}  // namespace s21

#endif  // SRC_MODEL_PROECESSORS_TRANSFORM_PROCESSOR_H_
