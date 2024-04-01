#include "transform_processor.h"

namespace s21 {
QMatrix4x4 TransformProcessor::transform(Transform value) {
  QMatrix4x4 result;
  translate(result, value.position);
  rotate(result, value.rotation);
  scale(result, value.scale);
  return result;
}

void TransformProcessor::scale(QMatrix4x4& target, const QVector3D& value) {
  target.scale(value);
}
void TransformProcessor::rotate(QMatrix4x4& target, const QVector3D& value) {
  target.rotate(QQuaternion::fromEulerAngles(value));
}

void TransformProcessor::translate(QMatrix4x4& target, const QVector3D& value) {
  target.translate(value);
}
}  // namespace s21
