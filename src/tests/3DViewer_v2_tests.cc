// g++ -Wall -Werror -Wextra -Wpedantic 3DViewer_v2_tests.cc
// ../model/obj_parser.cc -lgtest -lgtest_main -pthread

#include <gtest/gtest.h>

#include "../model/processors/obj_parser.h"

TEST(Viewer_2, Test_1) {
  std::string path = "./pyramid.obj";
  int expected_num_of_vertices = 5;
  int expected_num_of_edges = 18;
  s21::ObjectParser *prsr = s21::ObjectParser::GetInstance();
  s21::Entity obj = prsr->process(path);
  EXPECT_EQ(obj.data().size(), expected_num_of_vertices);
  EXPECT_EQ(obj.order().size() / 2, expected_num_of_edges);
}

TEST(Viewer_2, Test_2) {
  std::string path = "./cube.obj";
  int expected_num_of_vertices = 8;
  int expected_num_of_edges = 36;
  s21::ObjectParser *prsr = s21::ObjectParser::GetInstance();
  s21::Entity obj = prsr->process(path);
  EXPECT_EQ(obj.data().size(), expected_num_of_vertices);
  EXPECT_EQ(obj.order().size() / 2, expected_num_of_edges);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
