#include "primitive_builder.h"

namespace s21 {
const std::map<PrimitiveBuilder::Primitives, Entity>
    PrimitiveBuilder::kPrimitivePool{std::make_pair(
        PrimitiveBuilder::Primitives::Cube,
        Entity({QVector3D(1, 1, 1), QVector3D(1, -1, 1), QVector3D(-1, -1, 1),
                QVector3D(-1, 1, 1), QVector3D(1, 1, -1), QVector3D(1, -1, -1),
                QVector3D(-1, -1, -1), QVector3D(-1, 1, -1)},
               {0, 1, 1, 2, 2, 3, 3, 0, 0, 4, 1, 5,
                2, 6, 3, 7, 4, 5, 5, 6, 6, 7, 7, 4}))};

Entity PrimitiveBuilder::getPrimitive(PrimitiveBuilder::Primitives type) {
  if (kPrimitivePool.count(type)) {
    return kPrimitivePool.at(type);
  }
  return Entity({QVector3D(0, 0, 0)}, {0});
}

}  // namespace s21