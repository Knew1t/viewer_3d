#include "shader_pool.h"

namespace s21 {
ShaderPool::ShaderPool()
    : default_vertex_(QOpenGLShader::Vertex),
      default_fragment_(QOpenGLShader::Fragment) {
  default_vertex_.compileSourceFile(":/shaders/default_vertex.glsl");
  default_fragment_.compileSourceFile(":/shaders/default_fragment.glsl");
}

QOpenGLShader* ShaderPool::get(std::string shader_name,
                               QOpenGLShader::ShaderType type) {
  QOpenGLShader& shader = cache_.emplace(shader_name, type).first->second;
  if (!shader.isCompiled()) {
    shader.compileSourceFile(
        QString::fromStdString(":/shaders/" + shader_name + ".glsl"));
  }
  return &shader;
}
}  // namespace s21