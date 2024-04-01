#ifndef SRC_MODEL_PROECESSORS_PRIMITIVE_BUILDER_H_
#define SRC_MODEL_PROECESSORS_PRIMITIVE_BUILDER_H_

#include <map>

#include "../entity.h"

namespace s21 {
class PrimitiveBuilder {
 public:
  enum class Primitives { Cube, Pyramid, Prism };

  static Entity getPrimitive(Primitives type);

 private:
  static const std::map<Primitives, Entity> kPrimitivePool;
};
}  // namespace s21

#endif  // SRC_MODEL_PROECESSORS_PRIMITIVE_BUILDER_H_
