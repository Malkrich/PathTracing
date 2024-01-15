#include "Lambertian.h"

namespace PathTracing
{

Lambertian::Lambertian() : Material()
{}

Lambertian::Lambertian(glm::vec3 color_param) : Material(color_param)
{}

}
