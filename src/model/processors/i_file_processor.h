#ifndef SRC_MODEL_PROCESSORS_I_FILE_PROCESSOR_H_
#define SRC_MODEL_PROCESSORS_I_FILE_PROCESSOR_H_

#include "../entity.h"

namespace s21 {
class IFileProcessor {
 public:
  virtual ~IFileProcessor() = default;

  virtual Entity process(const std::string& file) = 0;
};
}  // namespace s21

#endif  // SRC_MODEL_PROCESSORS_I_FILE_PROCESSOR_H_
