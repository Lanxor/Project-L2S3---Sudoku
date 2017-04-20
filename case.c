/* FICHIER CASE.C
 * HEADER CASE.C
 * 	Fonction en rapport aux case du sudoku
 */
#include <stdio.h>
#include <assert.h>
#include "case.h"

void afficherCandidatsCase(T_case ca) {
	if( ca.val == 0 ) {
		int i = 0;
		while( i < ca.n_candidats ) {
			printf("%d ", ca.candidats[i]);
			++i;
		}
	}
}

void initCase(T_case* ca)
{
	ca->val = 0;
	ca->n_candidats = 9;
	int i = 0;
	while( i < 9 ) {
		ca->candidats[i] = i + 1;
		++i;
	}

}

int rechIndice(int t[], int n, int val)
{
	int i = 0;
	/* (0 ≤ n ≤ 9) ∧ (0 < val ≤ 9) ∧ (0 ≤ i < 9) */
	assert( (n >= 0) && (n <= 9) && (val > 0) && (val <= 9) && (i >= 0) && (i < 9) );
	while( i < n ) {
		/* (0 ≤ n ≤ 9) ∧ (0 < val ≤ 9) ∧ (i < n) */
		assert( (n >= 0) && (n <= 9) && (val > 0) && (val <= 9) && (i < n) );
		if( t[i] == val) {
			/* (O ≤ i < n) ∧ (t[i] = val) */
			assert( (i >= 0) && (i < n) && (t[i] == val) );
			return i;
		}
		++i;
		/* (0 ≤ n ≤ 9) ∧ (0 < val ≤ 9) ∧ (i < n)*/
		assert( (n >= 0) && (n <= 9) && (val > 0) && (val <= 9) && (i < n+1) );
	}
	/* (0 ≤ n ≤ 9) ∧ (0 < val ≤ 9) ∧ (0 ≤ i < 9) ∧ (i ≥ n) */
	assert( (n >= 0) && (n <= 9) && (val > 0) && (val <= 9) && (i >= n) );
	return n;
}

void suppVal(int t[], int n, int indiceVal)
{
	/* (0 ≤ indiceVal < 9) ∧ (0 ≤ n ≤ 9) */
	assert( (indiceVal >= 0) && (indiceVal < 9) && (n >= 0) && (n <= 9) );
	if( indiceVal < n ) {
		int i = indiceVal;
		/* (0 ≤ indiceVal < 9) ∧ (0 ≤ n ≤ 9) ∧ (indiceVal < n) */
		assert( (indiceVal >= 0) && (indiceVal < 9) && (n >= 0) && (n <= 9) && (indiceVal < n) );
		while( i < n ) {
			/* (0 ≤ indiceVal < 9) ∧ (0 ≤ n ≤ 9) ∧ (indiceVal < n) ∧ (i < n) */
			assert( (indiceVal >= 0) && (indiceVal < 9) && (n >= 0) && (n <= 9) && (indiceVal < n) && (i < n) );
			t[i] = t[i+1];
			++i;
			/* (0 ≤ indiceVal < 9) ∧ (0 ≤ n ≤ 9) ∧ (indiceVal < n) ∧ (i < n) */
			assert( (indiceVal >= 0) && (indiceVal < 9) && (n >= 0) && (n <= 9) && (indiceVal < n) && (i < n+1) );
		}
		/* (0 ≤ indiceVal < 9) ∧ (0 ≤ n ≤ 9) ∧ (indiceVal < n) ∧ (i ≥ n) */
		assert( (indiceVal >= 0) && (indiceVal < 9) && (n >= 0) && (n <= 9) && (indiceVal < n) && (i >= n) );
	}
	/* (0 ≤ indiceVal < 9) ∧ (0 ≤ n ≤ 9) ∧ (indiceVal ≥ n) */
	assert( (indiceVal >= 0) && (indiceVal < 9) && (n >= 0) && (n <= 9));
}

int suppCandidats(T_case* ca, int val)
{
	int indiceVal;
	indiceVal = rechIndice(ca->candidats, ca->n_candidats, val);
	if( indiceVal != ca->n_candidats ) { // la valeur existe
		suppVal(ca->candidats, ca->n_candidats, indiceVal);
		ca->n_candidats--;
		return 1;
	}
	return 0;
}
