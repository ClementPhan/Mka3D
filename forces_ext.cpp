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
\authors Laurent Monasse
 *  \file forces_ext.cpp
 *  \brief Definition of the functions giving the external forces.
 */

#include "geometry.hpp"
#ifndef FORCES_EXT_CPP
#define FORCES_EXT_CPP

Vector_3 Forces_externes(const Point_3 &X, const Vector_3 &e, const double& t, const double& T)
{
  return Vector_3(0,0,0);
  /*if(X.x() <= 1.)
    return Vector_3(-90000000.,0,0); // * t / T; //Chargement lineaire jusqu'à valeure fixée
  else if(X.x() >= 19.)
  return Vector_3(0,0,0);*/
}

Vector_3 Moments_externes(const Point_3 &X, const Vector_3 &e)
{
  return Vector_3(0,0,0);
}


#endif
