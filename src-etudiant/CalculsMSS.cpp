/*
 * CalculsMSS.cpp :
 * Copyright (C) 2016 Florence Zara, LIRIS
 *               florence.zara@liris.univ-lyon1.fr
 *               http://liris.cnrs.fr/florence.zara/
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/** \file CalculsMSS.cpp
Programme calculant pour chaque particule i d un MSS son etat au pas de temps suivant
 (methode d 'Euler semi-implicite) : principales fonctions de calculs.
\brief Fonctions de calculs de la methode semi-implicite sur un systeme masses-ressorts.
*/

#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>

#include "vec.h"
#include "ObjetSimule.h"
#include "ObjetSimuleMSS.h"
#include "Viewer.h"

using namespace std;

/**
 * Calcul des forces appliquees sur les particules du systeme masses-ressorts.
 */
void ObjetSimuleMSS::CalculForceSpring()
{
	std::vector<Ressort *> ressorts = _SystemeMasseRessort->GetRessortList();

	for (int i = 0; i < _SystemeMasseRessort->GetNbRessort(); i++)
	{
		Ressort *r = ressorts[i];

		int idX = r->GetParticuleA()->GetId();
		int idY = r->GetParticuleB()->GetId();

		Point x(P[idX]);
		Point y(P[idY]);

		Vector dir = ((y - x) / length(y - x));

		Vector f = -r->GetRaideur() *
				   (length(y - x) - r->GetLrepos()) *
				   dir;

		Vector a = -r->GetAmortissement() *
				   dot((V[idY] - V[idX]), dir) *
				   dir;

		Force[idX] = Force[idX] - f - a;
		Force[idY] = Force[idY] + f + a;
	}

	/// f = somme_i (ki * (l(i,j)-l_0(i,j)) * uij ) + (nuij * (vi - vj) * uij) + (m*g) + force_ext

	/// Rq : Les forces dues a la gravite et au vent sont ajoutees lors du calcul de l acceleration

} // void

/**
 * Gestion des collisions avec le sol.
 */
void ObjetSimuleMSS::Collision()
{
	Point origin(0,-10,0);
	/// Arret de la vitesse quand touche le plan
	for(int i = 0; i < _SystemeMasseRessort->GetNbParticule(); i++) {
		//transformer P en coordonnees monde
		if (P[i].y <= -10) {
			V[i] = Vector(0, 0, 0);
		} else if (distance(Point(P[i]), origin) <= 1) {
			V[i] = Vector(0, 0, 0);
		}
	}

} // void
