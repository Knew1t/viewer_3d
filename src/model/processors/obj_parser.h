#ifndef SRC_MODEL_PROCESSORS_OBJ_PARSER_H_
#define SRC_MODEL_PROCESSORS_OBJ_PARSER_H_

#include <QVector3D>
#include <cmath>
#include <fstream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "../entity.h"
#include "i_file_processor.h"

namespace s21 {
class ObjectParser : public IFileProcessor {
 public:
  ObjectParser(ObjectParser const& other) = delete;
  ObjectParser& operator=(ObjectParser const& other) = delete;
  ~ObjectParser() = default;

  static ObjectParser* GetInstance() {
    static ObjectParser single_instance;
    return &single_instance;
  }

  s21::Entity process(std::string const& file) {
    path_ = file;
    GeneralParser();
    s21::Entity instance(vertex_coordinates3D_, vertex_order_);
    return instance;
  }

 private:
  ObjectParser(){};

  void GeneralParser();
  void VerticesParser(std::string const& line);
  void EdgesParser(std::string const& line);
  std::map<std::string, int32_t> Count(std::ifstream& source) const;
  std::string path_;
  std::vector<QVector3D> vertex_coordinates3D_;
  std::vector<uint32_t> vertex_order_;
};
}  // namespace s21

#endif  // SRC_MODEL_PROCESSORS_OBJ_PARSER_H_
