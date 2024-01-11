#include "SceneObject.h"

namespace PathTracing
{

SceneObject::SceneObject(Primitive* primitive_param,Material* material_param):
    primitive(primitive_param),material(material_param)
{}

}
