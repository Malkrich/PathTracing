#include "Lambertian.h"

namespace PathTracing
{

Lambertian::Lambertian()
    : Material()
{}

Lambertian::Lambertian(const glm::vec3& color)
    : Material(color)
{}

}
