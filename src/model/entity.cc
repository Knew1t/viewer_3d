#include "entity.h"

// construct entity with given data
s21::Entity::Entity(const std::vector<QVector3D>& vertices,
                    const std::vector<uint32_t>& order)
    : vertices_(vertices), vertex_order_(order), color_(0, 0, 0, 1) {}

// moving data would be better that copying
s21::Entity::Entity(std::vector<QVector3D>&& vertices,
                    std::vector<uint32_t>&& order)
    : vertices_(vertices), vertex_order_(order), color_(0, 0, 0, 1) {}
