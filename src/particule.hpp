//Copyright 2017 Laurent Monasse

/*
  This file is part of Mka3D.
  
  Mka3D is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  Mka3D is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with Mka3D.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
\authors Laurent Monasse and Adela Puscas
 *  \file solide.hpp
 *  \brief D&eacute;finition des classes d&eacute;crivant le solide.
 */

#ifndef PARTICULE_HPP
#define PARTICULE_HPP

#include "geometry.hpp"
#include "face.hpp"
#include <map>

class Particule
{

 public:
   
  Particule();//:faces(std::vector<Face>(1)){}
  Particule(const int& Id); // Permet de créer une particule à partir de son numéro et de la donnée de ses vertex
  Particule(const double &x_min, const double &y_min, const double &z_min, 
			const double &x_max, const double &y_max,const double &z_max);
  
  Particule(const Point_3 &c, const double &x_min, const double &y_min, const double &z_min, 
			const double &x_max, const double &y_max,const double &z_max, 
			const std::vector<Face> & F);
  ~Particule();
  Particule & operator=(const Particule &P); // opérateur = surcharge pour l'affectation
  //void Affiche();  //fonction auxilaire utile pour les tests
  //void CompVolumeIntegrals(double &T1, double &Tx, double &Ty, double &Tz, double &Txx, double &Tyy, double &Tzz, double &Txy, double &Tyz, double &Tzx);
  //void Inertie(const double &rho);
  void solve_position(const double &dt, const bool &flag_2d, const double& t, const double& T);
  void solve_vitesse(const double &dt, const bool &flag_2d, const double& Amort, const double& t, const double& T);

  Vector_3 vitesse_parois(const Point_3& X_f);  
  Vector_3 vitesse_parois_prev(const Point_3& X_f);  
bool cube; //!< = true si la particule est un cube, false sinon
Bbox bbox;

  std::vector<Face> faces; //!< liste de faces de la particule

  std::vector<Point_3> vertices;//!< liste des sommets de la particule

  Triangles triangles; //!< Triangulation des faces de la particule au temps t

  Triangles triangles_prev; //!< Triangulation des faces de la particule au temps t-dt

  std::vector<Vector_3> normales; //!< normales ext&eacute;rieures aux \a Particule.triangles

  std::vector<Vector_3> normales_prev; //!< normales ext&eacute;rieures aux \a Particule.triangles_prev
    
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  std::vector<bool> vide; //!< =true si \a Particule.triangles en contact avec le fluide
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  std::vector<bool> fluide; //!< =true si \a Particule.triangles en contact avec le fluide
    
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  std::vector<bool> fluide_prev; //!< =true si \a Particule.triangles_prev en contact avec le fluide
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  std::vector< std::vector<Point_3> > Points_interface; //!< Liste de points d'intersections de \a Particule.triangles avec la grille fluide au temps t 
    
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  std::vector< std::vector<Point_3> > Points_interface_prev; //!< Liste de points d'intersections de \a Particule.triangles_prev avec la grille fluide au temps t-dt 
  /*! 
    std::vector< std::vector<Triangle_3> > Triangles_interface; //!< Triangulation des \a Particule.triangles au temps t
    
    /*! 
    * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
    */
  std::vector< std::vector< std::vector<int> > > Position_Triangles_interface; //!< index de la cellule o&ugrave; se trouve \a Triangles_interface au temps t
    
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  std::vector< std::vector<Triangle_3> > Triangles_interface_prev; //!< Triangulation des \a Particule.triangles_prev au temps t  
    
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
     */
  std::vector< std::vector<std::vector<int> > > Position_Triangles_interface_prev; //!< index de la cellule o&ugrave; se trouve \a Triangles_interface au temps t-dt

  int fixe; //!< =true si la particule est fix&eacute;e, false sinon
  double m; //!< Masse de la particule
  double V; //!< Volume de la particule
  double epsilon; //!< D&eacute;formation volumique globale de la particule
  double I[3]; //!< Moments d'inertie de la particule
  double rotref[3][3]; //!<Matrice de rotation \f$ Q_0 \f$ telle que la matrice d'inertie \f$ R \f$ s'&eacute;crit :\f$ R = Q_0 R_0 Q_0^{-1}\f$, avec \f$R_0=diag(I_1,I_2,I_3)\f$.
  Point_3 x0; //!<Position du centre de la particule &agrave; t=0
  Vector_3 Dx; //!<D&eacute;placement du centre de la particule en t
  //Vector_3 Dx_plas; //Déplacements plastiques...
  Vector_3 Dxprev; //!<D&eacute;placement du centre de la particule en t-dt
  Vector_3 Fi; //!<Forces int&eacute;rieures du solide
  //Vector_3 Fi_plas; //Forces plastiques dans particule
    /*! 
     * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
     */
  Vector_3 Ff; //!<Forces fluides exerc&eacute;es sur le solide entre t et t+dt/2
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  Vector_3 Ffprev; //!< Forces fluides exerc&eacute;es sur le solide entre t-dt/2 et t
  Vector_3 Mi; //!< Moments int&eacute;rieurs du solide
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  Vector_3 Mf; //!< Moments fluides exerc&eacute;s sur le solide entre t et t+dt/2
  /*! 
   * \warning  <b> Param&egrave;tre  sp&eacute;cifique  au  couplage! </b>
   */
  Vector_3 Mfprev; //!< Moments fluides exerc&eacute;s sur le solide entre t-dt/2 et t
  Vector_3 u; //!< Vitesse de la particule au temps t
  //Vector_3 u_plas; //Vitesse palstique
  Vector_3 u_half; //!< Vitesse de la particule au temps t-dt/2
  Vector_3 omega; //!< Vecteur rotation au temps t
  Vector_3 omega_half;//!< Vecteur rotation au temps t-dt/2
  Vector_3 e; //!<Vecteur de rotation de la particule au temps t
  Vector_3 eref;
  Vector_3 eprev; //!<Vecteur de rotation de la particule au temps t-dt
  Aff_transformation_3 mvt_t; //!<Transformation affine de la particule au temps t
  Aff_transformation_3 mvt_tprev; //!<Transformation affine de la particule au temps t-dt

  //Variables pour plasticité et nouvelle formulation Mka !
  Matrix discrete_gradient; //Gradient reconstruit par particule
  Matrix contrainte; //Contrainte par particule
  double def_plas_cumulee; //Déformation plastique cumulée du lien
  Matrix epsilon_p; //Déformation plastique rémanante
  double seuil_elas;

  int id; //Numéro de la particule dans la map de Solide
}; 

#endif
