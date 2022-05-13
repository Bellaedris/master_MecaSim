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
	for (int i = 0; i < _SystemeMasseRessort->GetNbParticule(); i++)
	{
		Particule *p = _SystemeMasseRessort->GetParticule(i);
		Vector sommeForces;
		for (int j = 0; j < p->GetNbVoisins(); j++)
		{
			Ressort *r = p->GetRessortList()[j];
			Point x(P[r->GetParticuleA()->GetId()]);
			Point y(P[r->GetParticuleB()->GetId()]);

			Vector dir = ((y - x) / length(y - x));

			Vector f = (-r->GetRaideur() * 
						(length(y - x) - r->GetLrepos())) * 
						dir;

			Vector a = -r->GetAmortissement() * dot((V[r->GetParticuleB()->GetId()] - V[r->GetParticuleA()->GetId()]), dir) * dir;
			sommeForces = sommeForces + f + a;
			
			//Force[r->GetParticuleB()->GetId()] = Force[r->GetParticuleB()->GetId()] - f; // appliquer l'opposé à l'autre coté du ressort?
		}
		Force[p->GetId()] = Force[p->GetId()] + sommeForces;
	}
	
	
	/// f = somme_i (ki * (l(i,j)-l_0(i,j)) * uij ) + (nuij * (vi - vj) * uij) + (m*g) + force_ext
	
	/// Rq : Les forces dues a la gravite et au vent sont ajoutees lors du calcul de l acceleration
    
		
}//void


/**
 * Gestion des collisions avec le sol.
 */
void ObjetSimuleMSS::Collision()
{
    /// Arret de la vitesse quand touche le plan
   
    
}// void

