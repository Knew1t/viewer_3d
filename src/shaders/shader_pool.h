#ifndef SRC_SHADERS_SHADER_FACTORY_H_
#define SRC_SHADERS_SHADER_FACTORY_H_

#include <QOpenGLShader>
#include <map>
#include <string>

namespace s21 {
class ShaderPool final {
 public:
  ShaderPool();

  static ShaderPool& Instance() {
    static ShaderPool instance;
    return instance;
  };

  QOpenGLShader* defaultVertex() { return &default_vertex_; }

  QOpenGLShader* defaultFragment() { return &default_fragment_; }

  QOpenGLShader* get(std::string shader_name, QOpenGLShader::ShaderType type);

 private:
  QOpenGLShader default_vertex_;
  QOpenGLShader default_fragment_;

  std::map<std::string, QOpenGLShader> cache_;
};
}  // namespace s21
#endif  // SRC_SHADERS_SHADER_FACTORY_H_
