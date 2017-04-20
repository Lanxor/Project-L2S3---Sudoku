#include <stdio.h>
#include <assert.h>
#include "case.h"
#include "grille.h"
#include "regles.h"

/*
 * R1 - candidatsSeul
 * Return 0 : Aucun candidats seul
 * Return 1 : Candidats seul affecter à la case
 */
int candidatsSeul(T_sudoku* grille, int numCase)
{
        if(grille->grille[numCase].val == 0 && grille->grille[numCase].n_candidats == 1) {
                grille->grille[numCase].val = grille->grille[numCase].candidats[0];
                grille->grille[numCase].n_candidats = 0;
                return 1;
        }
        return 0;
}

/*
 * R2 - Elimination candidats
 * Return 0 : Aucun elimination de candidats
 * Return nb > 0 : Il y a eu "nb" elimination de candidats pour la case
 */
int eliminationCandidats(T_sudoku* grille, int numCase)
{
	int nb = 0;
	if ( eliminationCandidatsLigne(grille, numCase) )
		++nb;
	if ( eliminationCandidatsColonne(grille, numCase) )
		++nb;
	if ( eliminationCandidatsRegion(grille, numCase) )
		++nb;
	return nb;
}

/*
 * R2 - ligne
 *
 */
int eliminationCandidatsLigne(T_sudoku* grille, int numCase)
{
	int nb = 0;
	int col = 0;
	while(col < 9) {
		int valCase = grille->grille[ ligCol2Case(case2Lig(numCase), col) ].val;
		if( valCase != 0 ) {
			if( suppCandidats(&grille->grille[numCase], valCase) ) {
				++nb;
			}
		}
		++col;
	}
	return nb;
}

/*
 * R2 - Colonne
 *
 */
int eliminationCandidatsColonne(T_sudoku* grille, int numCase)
{
	int nb = 0;
	int lig = 0;
	while( lig < 9 ) {
		int valCase = grille->grille[ ligCol2Case(lig, case2Col(numCase)) ].val;
		if( valCase != 0 ) {
			if( suppCandidats(&grille->grille[numCase], valCase) ) {
				++nb;
			}
		}
		++lig;
	}
	return nb;
}

/*
 * R2 - Region
 *
 */
int eliminationCandidatsRegion(T_sudoku* grille, int numCase)
{
	int nb = 0;
	int region = ligCol2Reg(case2Lig(numCase), case2Col(numCase));
	int lig = reg2Lig(region);
	while( lig < reg2Lig(region) + 3 ) {
		int col = reg2Col(region);
		while( col < reg2Col(region) + 3 ) {
			int valCase = grille->grille[ ligCol2Case(lig, col) ].val;
			if( valCase != 0 ) {
				if( suppCandidats(&grille->grille[numCase], valCase) ) {
					++nb;
				}
			}
			++col;
		}
		++lig;
	}
	return nb;
}

/*
 * R3 - Candidats uniques
 * Fonction Général pour la découverte de candidats unique
 */

int candidatsUniques(T_sudoku* grille, int numCase) {
	int indiceValCand, nb;
	// on récupère la case numCase
	T_case ca = grille->grille[numCase];
	// seulement si la case est nulle
	if(ca.val == 0) {
		// on teste pour tout les candidats de la case
		indiceValCand = 0;
		while( indiceValCand < ca.n_candidats ) {
			if( candidatsUniquesLigne(*grille, numCase, ca.candidats[indiceValCand]) ) {
				grille->grille[numCase].val = ca.candidats[indiceValCand];
				grille->grille[numCase].n_candidats = 0;
				return 1;
			}
			else if( candidatsUniquesColonne(*grille, numCase, ca.candidats[indiceValCand]) ) {
				grille->grille[numCase].val = ca.candidats[indiceValCand];
				grille->grille[numCase].n_candidats = 0;
				return 1;
			}
			else if( candidatsUniquesRegion(*grille, numCase, ca.candidats[indiceValCand]) ) {
				grille->grille[numCase].val = ca.candidats[indiceValCand];
				grille->grille[numCase].n_candidats = 0;
				return 1;
			}
			++indiceValCand;
		}
	}
	return 0;
}

/*
 * R3 - Candidats unique ligne
 * On recherche s'il n'y a pas d'autre occurence dans la ligne
 * Return 0 : n'est pas unique sur la ligne
 * Return 1 : est unique sur la ligne
 */
int candidatsUniquesLigne(T_sudoku grille, int numCase, int valCand) {
	int indiceValCand;
	T_case ca;
	// on parcoure toutes les cases de la ligne
	int col = 0;
	while( col < 9 ) {
		// on récupère la case courante
		ca = grille.grille[ ligCol2Case(case2Lig(numCase),col) ];
		// on teste seulement toutes les cases nulle et qui ne sont pas numCase (celle que l'on veut tester
		if( ca.val == 0 && col != case2Col(numCase) ) {
			// on cherche l'indice de la valeur valCand dans la liste de candidats de la case ca
			indiceValCand = rechIndice(ca.candidats, ca.n_candidats, valCand);
			// si l'indice est dans la liste de candidats alors on retourne 0
			if( indiceValCand != ca.n_candidats ) {
				return 0;
			}
		}
		++col;
	}
	return 1;
}

/*
 * R3 - Candidats unique colonne
 * On recherche s'il n'y a pas d'autre occurence dans la colonne
 * Return 0 : n'est pas unique sur la colonne
 * Return 1 : est unique sur la ligne
 */
int candidatsUniquesColonne(T_sudoku grille, int numCase, int valCand) {
	int indiceValCand;
	T_case ca;
	// on parcoure toutes les cases de la colonne
	int lig = 0;
	while( lig < 9 ) {
		// on récupère la case courante
		ca = grille.grille[ ligCol2Case(lig, case2Col(numCase)) ];
		// on teste seulement toutes les cases nulle et qui ne sont pas numCase
		if( ca.val == 0 && lig != case2Lig(numCase) ) {
			// on reherche l'indice de la valeur valCand dans la liste de candidat de la case ca
			indiceValCand = rechIndice(ca.candidats, ca.n_candidats, valCand);
			// si l'indice est dans la liste de candidats alors on retourne 0
			if( indiceValCand != ca.n_candidats ) {
				return 0;
			}
		}
	++lig;
	}
	return 1;
}

/*
 * R3 - Candidats uniques region
 * On recherche s'il n'y a pas d'autre occurence dans la region
 * Retrun 0 : n'est pas unique dans la région
 * Return 1 : est unique dans la region
 */
int candidatsUniquesRegion(T_sudoku grille, int numCase, int valCand) {
	int indiceValCand, region, lig, col;
	T_case ca;
	// on parcoure toutes les cases de la région
	region = ligCol2Reg(case2Lig(numCase), case2Col(numCase));
	lig = reg2Lig(region);
	while( lig < reg2Lig(region) + 3 ) {
		col = reg2Col(region);
		while( col < reg2Col(region) + 3 ) {
			// on récupère la case courante
			ca = grille.grille[ ligCol2Case(lig, col) ];
			// on teste seulement toutes les cases null et qui ne sont pas numCase
			if( ca.val == 0 && ligCol2Case(lig,col) != numCase) {
				// on recherche l'indice de la valeur valCand dans la liste de candidats de la case ca
				indiceValCand = rechIndice(ca.candidats, ca.n_candidats, valCand);
				// si l'indice est dans la liste de candidats alors on retourne 0
				if( indiceValCand != ca.n_candidats ) {
					return 0;
				}

			}
			++col;
		}
		++lig;
	}
	return 1;
}

/*
 * R4 - Considération interrégion
 */
int considerationInterregion(T_sudoku* grille, int numCase)
{
	T_case caNumCase = grille->grille[numCase];
	int region = ligCol2Reg( case2Lig(numCase), case2Col(numCase) );
	if( caNumCase.val == 0 ) {
		// on parcoure tout les candidats de la case
		int indiceValCand = 0;
		while( indiceValCand < caNumCase.n_candidats ) {
			if(  rechCandDansRegAutreQueLigReg(*grille, numCase, caNumCase.candidats[indiceValCand]) ) {
				 suppCandDansLigAutreQueLigReg(grille, numCase, caNumCase.candidats[indiceValCand]);
			}
			if(  rechCandDansRegAutreQueColReg(*grille, numCase, caNumCase.candidats[indiceValCand]) ) {
				  suppCandDansColAutreQueColReg(grille, numCase, caNumCase.candidats[indiceValCand]);
			}
			++indiceValCand;
		}
	}
	return 0;
}

int  rechCandDansRegAutreQueLigReg(T_sudoku grille, int numCase, int valCand)
{
	int region = ligCol2Reg( case2Lig(numCase), case2Col(numCase) );
	// parcoure de toutes les cases de la région
	int lig = reg2Lig(region);
	while(lig < reg2Lig(region)+3 ) {
		int col = reg2Col(region);
		while(col < reg2Col(region)+3 ) {
			// on récupère la case courantes de la région
			T_case ca = grille.grille[ ligCol2Case(lig,col) ];
			// on selection seulement si il n'y a pas de valeur
			// et si les cases ne corresponden pas a la ligne de numCase
			if( ca.val == 0 && lig != case2Lig(numCase) ) {
				// on recherche dans les candidats de la case si il y a valCand
				if( rechIndice(ca.candidats, ca.n_candidats, valCand) != ca.n_candidats ) {
					return 0;
				}
			}
			++col;
		}
		++lig;
	}
	return 1;
}

int  suppCandDansLigAutreQueLigReg(T_sudoku* grille, int numCase, int valCand) {
	int region = ligCol2Reg( case2Lig(numCase), case2Col(numCase) );
	int lig = case2Lig(numCase);
	int col = 0;
	while( col < 9 ) {
		if( ligCol2Reg(lig,col) != region) {
			T_case ca = grille->grille[ ligCol2Case(lig,col) ];
			int indiceValCand = rechIndice(ca.candidats, ca.n_candidats, valCand);
			if( indiceValCand != ca.n_candidats ) {
				suppCandidats(&grille->grille[ ligCol2Case(lig,col) ], valCand);
			}
		}
		++col;
	}
	return 1;
}

int rechCandDansRegAutreQueColReg(T_sudoku grille, int numCase, int valCand)
{
	int region = ligCol2Reg( case2Lig(numCase), case2Col(numCase) );
	// parcoure de toutes les cases de la région
	int lig = reg2Lig(region);
	while(lig < reg2Lig(region)+3 ) {
		int col = reg2Col(region);
		while(col < reg2Col(region)+3 ) {
			// on récupère la case courantes de la région
			T_case ca = grille.grille[ ligCol2Case(lig,col) ];
			// on selection seulement si il n'y a pas de valeur
			// et si les cases ne corresponden pas a la ligne de numCase
			if( ca.val == 0 && col != case2Col(numCase) ) {
				// on recherche dans les candidats de la case si il y a valCand
				if( rechIndice(ca.candidats, ca.n_candidats, valCand) != ca.n_candidats ) {
					return 0;
				}
			}
			++col;
		}
		++lig;
	}
	return 1;
}

int  suppCandDansColAutreQueColReg(T_sudoku* grille, int numCase, int valCand) {
	int region = ligCol2Reg( case2Lig(numCase), case2Col(numCase) );
	int col = case2Col(numCase);
	int lig = 0;
	while( lig < 9 ) {
		if( ligCol2Reg(lig,col) != region) {
			T_case ca = grille->grille[ ligCol2Case(lig,col) ];
			int indiceValCand = rechIndice(ca.candidats, ca.n_candidats, valCand);
			if( indiceValCand != ca.n_candidats ) {
				suppCandidats(&grille->grille[ ligCol2Case(lig,col) ], valCand);
			}
		}
		++lig;
	}
	return 1;
}
