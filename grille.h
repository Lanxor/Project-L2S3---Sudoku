#ifndef HEADER_GRILLE
#define HEADER_GRILLE

/* FICHIER grille.C
 * HEADER grille.h
 */

/*
 * Structure de T_sudoku
 */
typedef struct {
	T_case grille[81];
} T_sudoku;

void initGrille(T_sudoku* grille);

void afficherGrilleCandidats(T_sudoku grille);
void afficherGrille(T_sudoku grille);

void saisiGrille(T_sudoku* grille);
int remplirGrilleF(T_sudoku* grille, char nomFichier[]);

int estSudoku(T_sudoku grille);

/*
 * Correspondance entre une case du tableau
 * et les lignes, colonne, région
 */
int reg2Lig(int reg);
int reg2Col(int reg);
int ligCol2Reg(int lig, int col);
int ligCol2Case(int lig, int col);
int case2Lig(int ca);
int case2Col(int ca);

#endif
