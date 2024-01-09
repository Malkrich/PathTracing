#include "Plane.h"

#include <cmath>

namespace PathTracing
{

Plane::Plane(glm::vec3 const& position_param,glm::vec3 const& normal_param)
    :position_data(position_param),normal_data(normal_param)
{

}

glm::vec3 const& Plane::position() const
{
    return position_data;
}
glm::vec3 const& Plane::normal() const
{
    return normal_data;
}

/*
bool Plane::intersect(ray const& ray_param,intersection_data& intersection) const
{



    // ********************************************************** //
    // ********************************************************** //
    //  TO DO:
    //    Calcul d'intersection entre un rayon et un plan
    //
    // Variables:
    //  - Position initiale du rayon: ray_param.p0()
    //  - Vecteur directeur unitaire du rayon: u
    //  - Position d'un point du plan: position_data
    //  - Normale unitaire au plan: n
    //
    // Aide de syntaxe:
    //  - Calcul du produit scalaire <a,b>: dot(a,b);
    //  - Mise a jour de la donnee d'intersection:
    //                intersection.set(p_inter,n_inter,t_inter);
    //
    // ********************************************************** //
    // ********************************************************** //

    //Le code suivant est arbitraire est doit etre modifie
    glm::vec3 xs = ray_param.p0();
    glm::vec3 const& u = ray_param.u();
    glm::vec3 const& np = normal_data;
    glm::vec3 xp = position_data;

    float const t=-1.0f *dot(xs-xp,np)/dot(u,np);

    if(t>0){
        glm::vec3 x_inter = xs+t*u;
        intersection.set(x_inter,np,t);
        return true;
    }
    else
        return false;


}*/

}
