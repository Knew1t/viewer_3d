#ifndef SRC_VIEW_UTILITY_PROJECTION_H_
#define SRC_VIEW_UTILITY_PROJECTION_H_

#include <QMatrix4x4>

namespace s21 {
struct Projection final {
 public:
  float near_plane;
  float far_plane;
  float width;
  float height;

  const QMatrix4x4& Last() const { return last_; }

  const QMatrix4x4& Orthographic(QRect plane) {
    last_.setToIdentity();
    last_.ortho(plane.left(), plane.right(), plane.bottom() * height / width,
                plane.top() * height / width, near_plane, far_plane);
    return last_;
  };

  const QMatrix4x4& Perspective(float fov) {
    last_.setToIdentity();
    last_.perspective(fov, width / height, near_plane, far_plane);
    return last_;
  };

 private:
  QMatrix4x4 last_;
};
}  // namespace s21

#endif  // SRC_VIEW_UTILITY_PROJECTION_H_
