#include "obj_parser.h"

void s21::ObjectParser::GeneralParser() {
  std::ifstream file;
  std::ifstream file_count;
  file_count.open(path_);
  std::map<std::string, int32_t> counts = Count(file_count);
  file_count.close();
  file.open(path_);
  if (file.is_open()) {
    vertex_coordinates3D_.reserve(counts["v"]);
    vertex_coordinates3D_.clear();
    vertex_order_.reserve(1000000);
    vertex_order_.clear();
    while (!file.fail()) {
      std::string line = "";
      std::getline(file, line);
      auto it = line.begin();
      if (*it == 'v' && *(++it) == ' ') {
        //++num_of_vertices_;
        VerticesParser(line);
      } else if (*it == 'f' && *(++it) == ' ') {
        //++num_of_faces_;
        EdgesParser(line);
      }
    }
    file.close();
    vertex_coordinates3D_.shrink_to_fit();
    vertex_order_.shrink_to_fit();
    // num_of_edges_ /= 2;
  } else {
    throw std::invalid_argument("Error: unable to open the file.");
  }
}

void s21::ObjectParser::VerticesParser(std::string const& line) {
  std::vector<float> xyz_temp;
  bool flag_number = false;
  int xyz_num = 0;
  float temp_num = 0;
  size_t pos = 2;
  while (pos < line.length()) {
    std::string temp_str = "";
    while ((line[pos] > 44 && line[pos] < 58) && line[pos] != 47) {
      if (!flag_number) flag_number = true;
      temp_str.push_back(line[pos]);
      ++pos;
    }
    if (flag_number) {
      try {
        temp_num = std::stod(temp_str);
      } catch (std::invalid_argument const& error) {
        temp_num = 0;
      }
      xyz_temp.push_back(temp_num);
      ++xyz_num;
    }
    if (xyz_num == 3) break;
    temp_num = 0;
    flag_number = false;
    ++pos;
  }
  while (xyz_num < 3) {
    xyz_temp.push_back(0);
    ++xyz_num;
  }
  float x_pos = xyz_temp[0];
  float y_pos = xyz_temp[1];
  float z_pos = xyz_temp[2];
  QVector3D xyz_vertex(x_pos, y_pos, z_pos);
  vertex_coordinates3D_.push_back(xyz_vertex);
}

void s21::ObjectParser::EdgesParser(std::string const& line) {
  int flag_num = 0;
  int order_check = 0;
  int first_num = 0;
  uint32_t temp_num = 0;
  size_t pos = 2;
  while (pos < line.length()) {
    char space_check = line[pos - 1];
    while (line[pos] > 47 && line[pos] < 58 && space_check == ' ') {
      flag_num = 1;
      temp_num = temp_num * 10 + (line[pos] - '0');
      ++pos;
    }
    if (flag_num) {
      ++order_check;
      //++num_of_edges_;
      --temp_num;
      vertex_order_.push_back(temp_num);
      if (order_check == 1) {
        first_num = temp_num;
      } else {
        //++num_of_edges_;
        vertex_order_.push_back(temp_num);
      }
      flag_num = 0;
      temp_num = 0;
    }
    ++pos;
  }
  //++num_of_edges_;
  vertex_order_.push_back(first_num);
}

std::map<std::string, int32_t> s21::ObjectParser::Count(
    std::ifstream& source) const {
  std::map<std::string, int32_t> counts;
  if (source.is_open()) {
    while (!source.fail()) {
      std::string thing;
      source >> thing;
      counts[thing]++;
    }
    source.seekg(0);
  } else {
    throw std::invalid_argument("Error: unable to open the file.");
  }
  return counts;
}
