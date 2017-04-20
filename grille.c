/*
 * Fonction en rapport à la grille du sudoku
 * Affichage
 */

#include <stdio.h>
#include <assert.h>

#include "case.h"
#include "grille.h"

/*
 * Initialise la grille
 *
 */
void initGrille(T_sudoku* grille)
{
	T_case ca;
	initCase(&ca);
	int i = 0;
	while( i < 81 ) {
		grille->grille[i] = ca;
		++i;
	}
}

void afficherGrilleCandidats(T_sudoku grille) {
	int taille = 41;

	void affInterSimple(int t) {
		for(int i = 0; i < t; ++i)
			printf("-");
		printf("\n");
	}
	printf("     Grille Candidats\n");
	affInterSimple(taille);
	for(int lig = 0; lig < 9; ++lig) {
		if(lig%3 == 0)
			affInterSimple(taille);
		printf("|");
		for(int col = 0; col < 9; ++col) {
			T_case ca = grille.grille[ ligCol2Case(lig, col) ];
			if(col%3 == 0)
				printf("|");
			for(int ligCand = 1; ligCand <= 3; ++ligCand) {
				if( ca.val != 0 ) {
					if( ligCand == 1 )
						printf("#");
					else
						printf(" ");
				}
				else {
					int indiceValCand = rechIndice(ca.candidats, ca.n_candidats, ligCand);
					if( indiceValCand != ca.n_candidats)
						printf("%d", ligCand);
					else
						printf(" ");
				}
			}
			printf("|");
		}
		printf("|\n|");
		for(int col = 0; col < 9; ++col) {
			T_case ca = grille.grille[ ligCol2Case(lig,col) ];
			if(col%3 == 0)
				printf("|");
			for(int ligCand = 4; ligCand <= 6; ++ligCand) {
				if( ca.val != 0 ) {
					if( ligCand == 5 )
						printf("%d", ca.val);
					else
						printf(" ");
				}
				else {
					int indiceValCand = rechIndice(ca.candidats, ca.n_candidats, ligCand);
					if( indiceValCand != ca.n_candidats )
						printf("%d", ligCand);
					else
						printf(" ");
				}
			}
			printf("|");
		}
		printf("|\n|");
		for(int col = 0; col < 9; ++col) {
			T_case ca = grille.grille[ ligCol2Case(lig, col) ];
			if(col%3 == 0)
				printf("|");
			for(int ligCand = 7; ligCand <= 9; ++ligCand) {
				if( ca.val != 0 )
					printf(" ");
				else {
					int indiceValCand = rechIndice(ca.candidats, ca.n_candidats, ligCand);
					if( indiceValCand != ca.n_candidats )
						printf("%d", ligCand);
					else
						printf(" ");
				}
                        }
			printf("|");
                }
                printf("|\n");
		affInterSimple(taille);
	}
	affInterSimple(taille);
}


/*
 * Fonction d'affichage de la grille de Sudoku
 */
void afficherGrille(T_sudoku grille) {

    void afficherLigneDecor() {
        printf("     ");
        for( int k = 0; k < 41; ++k )
            printf("-");
        printf("\n");
    }

    afficherLigneDecor();
    afficherLigneDecor();
    for( int i = 0; i < 9; ++i ) {
        printf("     ");
        for( int j = 0; j < 9; ++j ) {
            if( j % 3 == 0 )
                printf("||");
            else
                printf("|");
            if( grille.grille[9*i+j].val != 0 )
                printf(" %d ",grille.grille[9*i+j].val);
            else
                printf("   ");
        }
        printf("||\n");
        if( i == 2 || i == 5 || i == 8 ) {
            afficherLigneDecor();
            afficherLigneDecor();
        }
        else
            afficherLigneDecor();
    }
    printf("\n");
}

/*
 * Saisi de valeur à l'utilisateur
 */
void saisiGrille(T_sudoku* grille) {
	int val;
	int i = 0;
	while( i < 81 ) {
		printf("Entrée une valeur pour la case [%d][%d] : ", case2Lig(i), case2Col(i));
		scanf("%d", &val);
		while( val <= 0 || val > 9 ) {
			printf("Erreur\n");
			scanf("%d", &val);
		}
		grille->grille[i].val = val;
		if(val != 0)
			grille->grille[i].n_candidats = 0;
		++i;
	}
}

/*
 * Affecte une grille sudoku avec un fichier
 * Return 1 :
 * Return 0 :
 */
int remplirGrilleF(T_sudoku* grille, char nomFichier[])
{
	int valeur;
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, "r+");
	if( fichier != NULL ) {
		rewind(fichier);
		for(int i = 0; i < 81; ++i) {
			fscanf(fichier, "%d", &valeur);
			grille->grille[i].val = valeur;
			fseek(fichier, 1, SEEK_CUR);
		}
		return 1;
	}
	return 0;
}

/*
 * Renvoie si le sudoku est plein ou non
 * Return 1 : n'est pas un Sudoku
 * Return 0 : est un Sudoku
 */
int estSudoku(T_sudoku grille) {
	int i = 0;
	while( i < 81 ) {
		assert( i < 81 );
		assert(grille.grille[i].val >= 0 && grille.grille[i].val <= 9);
		if(grille.grille[i].val == 0) {
			assert(grille.grille[i].val == 0);
			return 1;
		}
		++i;
	}
	assert( i >= 81 );
	return 0;
}



/*
 * Programme V1 - [1]
 * Correspondance entre une case du tableau
 * et les lignes, colonne, région
 */

// retourne la ligne du sudoku en fonction de la région
// renvoie la ligne de la case en haut à gauche de la région
int reg2Lig(int reg) {
	assert( reg >= 0 && reg < 9 );
	assert( (3 * (reg / 3)) >= 0 && (3 * (reg / 3)) < 9 );
	return 3 * (reg / 3);
}

// retourne la colonne du sudoku en fonction de la région
// renvoie la colonne de la case en haut à gauche de la région
int reg2Col(int reg) {
	assert( reg >= 0 && reg < 9 );
	assert( ( (3 * (reg % 3)) >= 0 ) && ( (3 * (reg % 3)) < 9 ) );
	return 3 * (reg % 3);
}

// retourne le numéro de région en fonction de la ligne et de la colonne
int ligCol2Reg(int lig, int col) {
	assert( lig >= 0 && lig < 9 );
	assert( col >= 0 && col < 9 );
	assert( (3 * (lig / 3) + (col / 3)) >= 0 && (3 * (lig / 3) + (col / 3)) < 9 );
	return 3 * (lig / 3) + (col / 3);
}

// retourne le numéro de la case en fonction de la ligne et de la colonne
int ligCol2Case(int lig, int col) {
	assert( lig >= 0 && lig < 9 );
	assert( col >= 0 && col < 9 );
	assert( (9 * lig + col) >= 0 && (9 * lig + col) < 81 );
	return 9 * lig + col;
}

// retourne la ligne du sudoku en fonction de la case
int case2Lig(int ca) {
	assert( ca >= 0 && ca < 81 );
	assert( (ca / 9) >= 0 && (ca / 9) < 9 );
	return ca / 9;
}

// retourne la colonne du sudoku en fonction de la case
int case2Col(int ca) {
	assert( ca >= 0 && ca < 81 );
	assert( (ca % 9) >= 0 && (ca % 9) < 9 );
	return ca % 9;
}
