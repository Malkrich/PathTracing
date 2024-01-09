#include "Rectangle.h"

#include <cmath>

namespace PathTracing
{

Rectangle::Rectangle(glm::vec3 const& p0,glm::vec3 const& p1,glm::vec3 const& normal_param)
    :p0_data(p0),p1_data(p1),normal_data(normal_param)
{

}

glm::vec3 const& Rectangle::p0() const
{
    return p0_data;
}

glm::vec3 const& Rectangle::p1() const
{
    return p1_data;
}


glm::vec3 const& Rectangle::normal() const
{
    return normal_data;
}

/*
bool Rectangle::intersect(ray const& ray_param,intersection_data& intersection) const
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
