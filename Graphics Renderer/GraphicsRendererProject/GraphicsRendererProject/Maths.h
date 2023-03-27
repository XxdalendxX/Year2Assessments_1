#pragma once

#include <math.h>
#include <vector>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"
#include "gtx/norm.hpp"

//vector_(x,y)
typedef glm::vec2 vec2;
//vector_(x,y,z)
typedef glm::vec3 vec3;
//vector_(x,y,z,w)
typedef glm::vec4 vec4;

//matrix_2x2
typedef glm::mat2 mat2;
//matrix_3x3
typedef glm::mat3 mat3;
//matrix_4x4
typedef glm::mat4 mat4;

//the ratio of the circumference of any circle to the diameter of that circle.
#define PI 3.14159265f