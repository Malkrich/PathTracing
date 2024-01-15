#include "Material.h"

namespace PathTracing
{
Material::Material() {
    color = glm::vec3(0,0,0);
}

Material::Material(glm::vec3 color_param):
    color(color_param)
{

}

}
