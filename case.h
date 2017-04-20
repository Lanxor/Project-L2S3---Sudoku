#ifndef HEADER_CASE
#define HEADER_CASE

/*
 * HEADER de case.c
 */

/*
 * Structure de T_case
 */
typedef struct {
	int val;
	int n_candidats;
	int candidats[9];
} T_case;

void afficherCandidatsCase(T_case ca);
void initCase(T_case* ca);

// SOUS PROGRAMME
int rechIndice(int t[], int n, int val);
void suppVal(int t[], int n, int indiceVal);
int suppCandidats(T_case* ca, int val);

#endif
