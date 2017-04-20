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
