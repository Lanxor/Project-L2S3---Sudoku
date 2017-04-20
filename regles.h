#ifndef HEADER_REGLES
#define HEADER_REGLES

/*
 * HEADER regles.c
 */

/*
 * R1 - Un seul candidats
 */
int candidatsSeul(T_sudoku* grille, int numCase);

/*
 * R2 - Elimination candidats ligne, colonne, region
 */
int eliminationCandidats(T_sudoku* grille, int numCase);
int eliminationCandidatsLigne(T_sudoku* grille, int numCase);
int eliminationCandidatsColonne(T_sudoku* grille, int numCase);
int eliminationCandidatsRegion(T_sudoku* grille, int numCase);

/*
 * R3 - Candidats uniques ligne, colonne, region
 */
int candidatsUniques(T_sudoku* grille, int numCase);
int candidatsUniquesLigne(T_sudoku grille, int numCase, int valCand);
int candidatsUniquesColonne(T_sudoku grille, int numCase, int valCand);
int candidatsUniquesRegion(T_sudoku grille, int numCase, int valCand);

/*
 * R4 - Considération interrégion
 */
int considerationInterregion(T_sudoku* grille, int numCase);
int rechCandDansRegAutreQueLigReg(T_sudoku grille, int numCase, int valCand);
int suppCandDansLigAutreQueLigReg(T_sudoku* grille, int numCase, int valCand);
int rechCandDansRegAutreQueColReg(T_sudoku grille, int numCase, int valCand);
int suppCandDansColAutreQueColReg(T_sudoku* grille, int numCase, int valCand);

#endif
