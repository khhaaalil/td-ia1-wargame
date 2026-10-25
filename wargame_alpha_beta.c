

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NB_LIGNES 10
#define NB_COLONNES 10
#define INFINI 10000

/*#define DEBUG*/

typedef struct pion_s
{
	int couleur;
	int valeur;
}Pion;

Pion *plateauDeJeu;

// total number of nodes explored during the whole game
unsigned long compteurNoeuds = 0;

void f_affiche_plateau(Pion *plateau);
int f_convert_char2int(char c);
char f_convert_int2char(int i);



int f_convert_char2int(char c)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif
	if(c>='A' && c<='Z')
		return (int)(c-'A');
	if(c>='a' && c<='z')
		return (int)(c-'a');
	return -1;
}

char f_convert_int2char(int i)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	return (char)i+'A';
}

Pion *f_init_plateau()
{
	int i, j;
	Pion *plateau=NULL;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	plateau = (Pion *)malloc(NB_LIGNES*NB_COLONNES*sizeof(Pion));
	if(plateau == NULL)
	{
		printf("error: unable to allocate memory\n");
		exit(EXIT_FAILURE);
	}

	for(i=0; i<NB_LIGNES; i++)
	{
		for(j=0; j<NB_COLONNES; j++)
		{
			plateau[i*NB_COLONNES+j].couleur = 0;
			plateau[i*NB_COLONNES+j].valeur = 0;
		}
	}

	plateau[9*NB_COLONNES+5].couleur = 1;
	plateau[9*NB_COLONNES+5].valeur = 1;

	plateau[9*NB_COLONNES+6].couleur = 1;
	plateau[9*NB_COLONNES+6].valeur = 2;

	plateau[9*NB_COLONNES+7].couleur = 1;
	plateau[9*NB_COLONNES+7].valeur = 3;

	plateau[9*NB_COLONNES+8].couleur = 1;
	plateau[9*NB_COLONNES+8].valeur = 2;

	plateau[9*NB_COLONNES+9].couleur = 1;
	plateau[9*NB_COLONNES+9].valeur = 1;

	plateau[8*NB_COLONNES+0].couleur = 1;
	plateau[8*NB_COLONNES+0].valeur = 1;

	plateau[8*NB_COLONNES+1].couleur = 1;
	plateau[8*NB_COLONNES+1].valeur = 3;

	plateau[8*NB_COLONNES+2].couleur = 1;
	plateau[8*NB_COLONNES+2].valeur = 3;

	plateau[8*NB_COLONNES+3].couleur = 1;
	plateau[8*NB_COLONNES+3].valeur = 1;

	plateau[8*NB_COLONNES+6].couleur = 1;
	plateau[8*NB_COLONNES+6].valeur = 1;

	plateau[8*NB_COLONNES+7].couleur = 1;
	plateau[8*NB_COLONNES+7].valeur = 1;

	plateau[8*NB_COLONNES+8].couleur = 1;
	plateau[8*NB_COLONNES+8].valeur = 1;

	plateau[7*NB_COLONNES+1].couleur = 1;
	plateau[7*NB_COLONNES+1].valeur = 1;

	plateau[7*NB_COLONNES+2].couleur = 1;
	plateau[7*NB_COLONNES+2].valeur = 1;

	plateau[2*NB_COLONNES+7].couleur = -1;
	plateau[2*NB_COLONNES+7].valeur = 1;

	plateau[2*NB_COLONNES+8].couleur = -1;
	plateau[2*NB_COLONNES+8].valeur = 1;

	plateau[1*NB_COLONNES+1].couleur = -1;
	plateau[1*NB_COLONNES+1].valeur = 1;

	plateau[1*NB_COLONNES+2].couleur = -1;
	plateau[1*NB_COLONNES+2].valeur = 1;

	plateau[1*NB_COLONNES+3].couleur = -1;
	plateau[1*NB_COLONNES+3].valeur = 1;

	plateau[1*NB_COLONNES+6].couleur = -1;
	plateau[1*NB_COLONNES+6].valeur = 1;

	plateau[1*NB_COLONNES+7].couleur = -1;
	plateau[1*NB_COLONNES+7].valeur = 3;

	plateau[1*NB_COLONNES+8].couleur = -1;
	plateau[1*NB_COLONNES+8].valeur = 3;

	plateau[1*NB_COLONNES+9].couleur = -1;
	plateau[1*NB_COLONNES+9].valeur = 1;

	plateau[0*NB_COLONNES+0].couleur = -1;
	plateau[0*NB_COLONNES+0].valeur = 1;

	plateau[0*NB_COLONNES+1].couleur = -1;
	plateau[0*NB_COLONNES+1].valeur = 2;

	plateau[0*NB_COLONNES+2].couleur = -1;
	plateau[0*NB_COLONNES+2].valeur = 3;

	plateau[0*NB_COLONNES+3].couleur = -1;
	plateau[0*NB_COLONNES+3].valeur = 2;

	plateau[0*NB_COLONNES+4].couleur = -1;
	plateau[0*NB_COLONNES+4].valeur = 1;

#ifdef DEBUG
printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif

return plateau;
}

void f_affiche_plateau(Pion *plateau)
{
	int i,j,k;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	printf("\n    ");
	for(k=0; k<NB_COLONNES; k++)
		printf("%2c ",f_convert_int2char(k));
	printf("\n    ");
	for(k=0; k<NB_COLONNES; k++)
		printf("-- ");
	printf("\n");
	for(i=NB_LIGNES-1; i>=0; i--)
	{
		printf("%2d ", i);
		for(j=0; j<NB_COLONNES; j++)
		{
			printf("|");
			switch(plateau[i*NB_COLONNES+j].couleur)
			{
			case -1:
				printf("%do",plateau[i*NB_COLONNES+j].valeur);
				break;
			case 1:
				printf("%dx",plateau[i*NB_COLONNES+j].valeur);
				break;
			default:
				printf("  ");
			}
		}
		printf("|\n    ");
		for(k=0; k<NB_COLONNES; k++)
			printf("-- ");
		printf("\n");
	}
	printf("    ");

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}


int f_gagnant() // si retour, la partie est finie
{
	int i, j, somme1=0, somme2=0;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	//Quelqu'un est-il arrive sur la ligne de l'autre
	for(i=0; i<NB_COLONNES; i++)
	{
		if(plateauDeJeu[i].couleur == 1)
			return 1;
		if(plateauDeJeu[(NB_LIGNES-1)*NB_COLONNES+i].couleur == -1)
			return -1;
	}

	//taille des armees
	for(i=0; i<NB_LIGNES; i++)
	{
		for(j=0; j<NB_COLONNES; j++)
		{
			if(plateauDeJeu[i*NB_COLONNES+j].couleur == 1)
				somme1++;
			if(plateauDeJeu[i*NB_COLONNES+j].couleur == -1)
				somme2++;
		}
	}
	if(somme1==0)
		return -1;
	if(somme2==0)
		return 1;

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}


/**
 * Prend comme argument la ligne et la colonne de la case
 * 	pour laquelle la bataille a lieu
 * Renvoie le couleur du gagnant
 * */
int f_bataille(int l, int c)
{
	int i, j, mini, maxi, minj, maxj;
	int somme=0;

#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif
	mini = l-1<0?0:l-1;
	maxi = l+1>NB_LIGNES-1?NB_LIGNES-1:l+1;
	minj = c-1<0?0:c-1;
	maxj = c+1>NB_COLONNES-1?NB_COLONNES-1:c+1;

	for(i=mini; i<=maxi; i++)
	{
		for(j=minj; j<=maxj; j++)
		{
			somme += plateauDeJeu[i*NB_COLONNES+j].couleur*plateauDeJeu[i*NB_COLONNES+j].valeur;
		}
	}
	somme -= plateauDeJeu[l*NB_COLONNES+c].couleur*plateauDeJeu[l*NB_COLONNES+c].valeur;

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	if(somme < 0)
		return -1;
	if(somme > 0)
		return 1;

	return plateauDeJeu[l*NB_COLONNES+c].couleur;
}


/**
 * Prend la ligne et colonne de la case d'origine
 * 	et la ligne et colonne de la case de destination
 * Renvoie 1 en cas d'erreur
 * Renvoie 0 sinon
 * */
int f_test_mouvement(Pion *plateau, int l1, int c1, int l2, int c2, int couleur)
{
#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
	printf("de (%d,%d) vers (%d,%d)\n", l1, c1, l2, c2);
#endif
	/* Erreur, hors du plateau */
	if(l1 < 0 || l1 >= NB_LIGNES || l2 < 0 || l2 >= NB_LIGNES ||
			c1 < 0 || c1 >= NB_COLONNES || c2 < 0 || c2 >= NB_COLONNES)
		return 1;
	/* Erreur, il n'y a pas de pion a deplacer ou le pion n'appartient pas au joueur*/
	if(plateau[l1*NB_COLONNES+c1].valeur == 0 || plateau[l1*NB_COLONNES+c1].couleur != couleur)
		return 1;
	/* Erreur, tentative de tir fratricide */
	if(plateau[l2*NB_COLONNES+c2].couleur == plateau[l1*NB_COLONNES+c1].couleur)
		return 1;

	if(l1-l2 >1 || l2-l1 >1 || c1-c2 >1 || c2-c1 >1 || (l1==l2 && c1==c2))
		return 1;
#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}


/**
 * Prend la ligne et colonne de la case d'origine
 * 	et la ligne et colonne de la case de destination
 *  et effectue le trantement de l'operation demandée
 * Renvoie 1 en cas d'erreur
 * Renvoie 0 sinon
 * */
int f_bouge_piece(Pion *plateau, int l1, int c1, int l2, int c2, int couleur)
{
	int gagnant=0;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	if(f_test_mouvement(plateau, l1, c1, l2, c2, couleur) != 0)
		return 1;


	/* Cas ou il n'y a personne a l'arrivee */
	if(plateau[l2*NB_COLONNES+c2].valeur == 0)
	{
		plateau[l2*NB_COLONNES+c2].couleur = plateau[l1*NB_COLONNES+c1].couleur;
		plateau[l2*NB_COLONNES+c2].valeur = plateau[l1*NB_COLONNES+c1].valeur;
		plateau[l1*NB_COLONNES+c1].couleur = 0;
		plateau[l1*NB_COLONNES+c1].valeur = 0;
	}
	else
	{
		gagnant=f_bataille(l2, c2);
		/* victoire */
		if(gagnant == couleur)
		{
			plateau[l2*NB_COLONNES+c2].couleur = plateau[l1*NB_COLONNES+c1].couleur;
			plateau[l2*NB_COLONNES+c2].valeur = plateau[l1*NB_COLONNES+c1].valeur;
			plateau[l1*NB_COLONNES+c1].couleur = 0;
			plateau[l1*NB_COLONNES+c1].valeur = 0;
		}
		/* defaite */
		else if(gagnant != 0)
		{
			plateau[l1*NB_COLONNES+c1].couleur = 0;
			plateau[l1*NB_COLONNES+c1].valeur = 0;
		}
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
	return 0;
}

//Calcul du nombre de pions sur le plateau du joueur
int f_nbPions(Pion* jeu, int joueur)
{
	int nbPion=0;
	int i, j;
	for (i = 0; i < NB_COLONNES; ++i)
	{
		for (j = 0; j < NB_LIGNES; ++j)
		{
			if (jeu[i * NB_COLONNES + j].couleur == joueur)
			{
				++nbPion;
			}
		}
	}
	return nbPion;
}

//Calcul de la valeur de tous les pions du joueur
int f_valeur(Pion* jeu, int joueur)
{
	int i, j;
	int valeur=0;
	for (i = 0; i < NB_COLONNES; ++i)
	{
		for (j = 0; j < NB_LIGNES; ++j)
		{
			if (jeu[i * NB_COLONNES + j].couleur == joueur)
			{
				valeur += jeu[i * NB_COLONNES + j].valeur;
			}
		}
	}
	return valeur;
}

//fonction d'évaluation
int f_eval(Pion* jeu,int joueur) // compares power and progress of both armies
{
	// l, c : line, column ; 
	// avance : pawn's progress towards the opposite side
	int l, c, score, avance;

	// sum of squared progress for each army
	int avancement1 = 0, avancement2 = 0;

	// comparing both armies' power, with 10 points for each point of power
	score = 10 * (f_valeur(jeu, joueur) - f_valeur(jeu, -joueur)); // = 10* f_valeur(player1) - 10*f_valeur(player2)

	// checking every case of the board
	for(l=0; l<NB_LIGNES; l++)
	{
		for(c=0; c<NB_COLONNES; c++)
		{
			// player 1 'x' starts from the last line and tries to reach line 0
			if(jeu[l*NB_COLONNES+c].couleur == 1)
			{
				avance = NB_LIGNES-1-l;
				// using the square so that pawns closer to victory count more
				avancement1 += avance * avance;
			}
			// player -1 'o' moves in the opposite direction
			else if(jeu[l*NB_COLONNES+c].couleur == -1)
			{
				avance = l;
				avancement2 += avance * avance;
			}
		}
	}

	// keeping the IA's point of view : joueur changes the sign if the IA is -1
	score += joueur * (avancement1 - avancement2);
	// positive score is better for the IA, negative score is better for the opponent
	
	return score;
}

//copie du plateau
void f_copie_plateau(Pion* source, Pion* destination)
{
	int i, j;
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			destination[i * NB_COLONNES + j].couleur = source[i * NB_COLONNES + j].couleur;
			destination[i * NB_COLONNES + j].valeur = source[i * NB_COLONNES + j].valeur;
		}
	}
}

//mise a zero du plateau
Pion* f_raz_plateau()
{
	Pion* jeu = NULL;
	int i, j;
	jeu = (Pion *) malloc(NB_LIGNES * NB_COLONNES * sizeof (Pion));
	for (i = 0; i < NB_LIGNES; i++)
	{
		for (j = 0; j < NB_COLONNES; j++)
		{
			jeu[i * NB_COLONNES + j].couleur = 0;
			jeu[i * NB_COLONNES + j].valeur = 0;
		}
	}
	return jeu;
}

// finds the smallest score among the possible moves
// jeu = board, profondeur = depth, number of moves left to explore
// joueur = IA's color, stays the same during recursion
// alpha = best score guaranteed for the IA, beta = best upper limit from the opponent
int f_min(Pion *jeu, int profondeur, int joueur, int alpha, int beta)
{
	// this call represents one node explored by alpha-beta
	compteurNoeuds++;

	// prototype of f_max because it's defined later in this code
	int f_max(Pion *jeu, int profondeur, int joueur, int alpha, int beta);

	// l, c : line, column ; 
	// dl, dc : déplacement ligne, colonne ; movement in each direction (-1, 0 or 1)
	// starting high so that we can keep the smallest score
	int l, c, dl, dc, score, mini = INFINI;

	// winning color : 1 or -1, or 0 if there's no winner yet
	int gagnant;

	// board copy, so that we can do operations on the board without touching the original one
	Pion copie[NB_LIGNES * NB_COLONNES];

	// saving the global board's address so that we can restore it afterwards
	Pion *sauvegarde;

	// f_gagnant uses the global variable, so we make it read the simulated board
	// so we know the winning moves (if there's one)
	sauvegarde = plateauDeJeu;
	plateauDeJeu = jeu;
	gagnant = f_gagnant();
	plateauDeJeu = sauvegarde;

	// if the IA already won, we stop this branch with the highest score
	if(gagnant == joueur)
		return INFINI;

	// if the opponent won, we return the lowest score
	if(gagnant == -joueur)
		return -INFINI;

	// max depth achieved : evaluating this board from the IA's point of view
	if(profondeur <= 0)
		return f_eval(jeu, joueur);

	// opponent's turn : checking every case of the board
	for(l=0; l<NB_LIGNES; l++)
	{
		for(c=0; c<NB_COLONNES; c++)
		{
			// l*NB_COLONNES+c = index of pawn on the board
			// only exploring cases that contain an opponent's pawn
			if(jeu[l*NB_COLONNES+c].couleur == -joueur){

			// trying all directions, f_test_mouvement will reject (0,0)
			for(dl=-1; dl<=1; dl++)
			{
				for(dc=-1; dc<=1; dc++)
				{
					// if the movement is possible, we simulate the opponent's move on a copy
					if(f_test_mouvement(jeu, l, c, l+dl, c+dc, -joueur) == 0)
					{
						// starting from the same parent board for each move
						f_copie_plateau(jeu, copie);

						// f_bataille works with the global variable, that's why we had to make a checkpoint (*sauvegarde)
						sauvegarde = plateauDeJeu;
						plateauDeJeu = copie;
						f_bouge_piece(copie, l, c, l+dl, c+dc, -joueur);

						// restoring the global pointer, the simulated move stays in copie
						plateauDeJeu = sauvegarde;

						// IA's turn next, with one less move left to explore
						score = f_max(copie, profondeur-1, joueur, alpha, beta);

						// choosing the smallest score for the IA
						if(score < mini)
							mini = score;
						// the opponent can keep this score or find an even smaller one
						if(mini < beta)
							beta = mini;
						// this branch cannot improve the choice above, so we stop here
						// the global pointer was already restored before the recursive call
						if(alpha >= beta)
							return mini;
					}

				}
			}
		}

		}
	}
	// returning the smallest score
	return mini;
}

//Fonction max trouve le maximum des noeuds fils
// same as f_min, so i won't comment a lot sorry 
int f_max(Pion *jeu, int profondeur, int joueur, int alpha, int beta)
{
	// this call represents one node explored by alpha-beta
	compteurNoeuds++;

	int l, c, dl, dc, score, maxi = -INFINI;
	int gagnant;
	Pion copie[NB_LIGNES * NB_COLONNES];
	Pion *sauvegarde;

	sauvegarde = plateauDeJeu;
	plateauDeJeu = jeu;
	gagnant = f_gagnant();
	plateauDeJeu = sauvegarde;
	if(gagnant == joueur)
		return INFINI;
	if(gagnant == -joueur)
		return -INFINI;

	if(profondeur <= 0)
		return f_eval(jeu, joueur);

	for(l=0; l<NB_LIGNES; l++)
	{
		for(c=0; c<NB_COLONNES; c++)
		{
			if(jeu[l*NB_COLONNES+c].couleur == joueur)
			{
				for(dl=-1; dl<=1; dl++)
				{
					for(dc=-1; dc<=1; dc++)
					{
						if(f_test_mouvement(jeu, l, c, l+dl, c+dc, joueur) == 0)
						{
							f_copie_plateau(jeu, copie);
							sauvegarde = plateauDeJeu;
							plateauDeJeu = copie;
							f_bouge_piece(copie, l, c, l+dl, c+dc, joueur);
							plateauDeJeu = sauvegarde;
							score = f_min(copie, profondeur-1, joueur, alpha, beta);
							if(score > maxi)
								maxi = score;
							// the IA can keep this score or find an even greater one
							if(maxi > alpha)
								alpha = maxi;
							// returning stops all the loops for this node
							if(alpha >= beta)
								return maxi;
						}
					}
				}
			}
		}
	}
	return maxi;
}

/**
 * Calcule et joue le meilleur cout
 * */
void f_IA(int joueur)
{
	// l, c : starting case ; 
	//dl, dc : déplacement ligne, colonne; movement in each direction
	int l, c, dl, dc;
	
	// score : score of the move that we just did
	// gagnant = 0 if no winner yet, or the color of the winnre 
	int score, gagnant;

	//meilleur score : best score for the moment
	// trouve : 0 if no valid move yet, 1 else
	int meilleurScore = -INFINI, trouve = 0;
	// starting with the widest window, no move has been checked yet
	int alpha = -INFINI, beta = INFINI;

	// depth : CONSTANT
	int profondeur = 3;

	// saving the coordinates of the best move
	int meilleureLigneDepart = 0, meilleureColonneDepart = 0;
	int meilleureLigneArrivee = 0, meilleureColonneArrivee = 0;
	Pion copie[NB_LIGNES * NB_COLONNES];
	Pion *sauvegarde;

#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	// no move to play if the game is already over
	if(f_gagnant() != 0)
		return;

	// checking every pawn that belongs to the IA
	for(l=0; l<NB_LIGNES; l++)
	{
		for(c=0; c<NB_COLONNES; c++)
		{
			if(plateauDeJeu[l*NB_COLONNES+c].couleur == joueur)
			{
				for(dl=-1; dl<=1; dl++)
				{
					for(dc=-1; dc<=1; dc++)
					{
						if(f_test_mouvement(plateauDeJeu, l, c, l+dl, c+dc, joueur) == 0)
						{
							// trying this move on a fresh copy of the real board
							f_copie_plateau(plateauDeJeu, copie);
							sauvegarde = plateauDeJeu;
							plateauDeJeu = copie;

							f_bouge_piece(copie, l, c, l+dl, c+dc, joueur);
							gagnant = f_gagnant();
							plateauDeJeu = sauvegarde;

							// opponent's turn next, only 2 moves left to explore
							score = f_min(copie, profondeur-1, joueur, alpha, beta);

							// accepting the first move even if every score is -INFINI
							// an immediate win is preferred when scores are equal
							if(!trouve || score > meilleurScore || gagnant == joueur)
							{
								meilleurScore = score;
								meilleureLigneDepart = l;
								meilleureColonneDepart = c;
								meilleureLigneArrivee = l+dl;
								meilleureColonneArrivee = c+dc;
								trouve = 1;
							}
							// the next moves must improve on the best score already found
							if(meilleurScore > alpha)
								alpha = meilleurScore;
						}
					}
				}
			}
		}
	}

	// playing only the chosen move on the real board
	if(trouve)
	{
		f_bouge_piece(plateauDeJeu,
			meilleureLigneDepart, meilleureColonneDepart,
			meilleureLigneArrivee, meilleureColonneArrivee, joueur);
	}
	printf("total noeuds explores : %lu\n", compteurNoeuds);

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}


/**
 * Demande le choix du joueur humain et calcule le coup demande
 * */
void f_humain(int joueur)
{
	char c1, c2;
	char buffer[32];
	int l1, l2;


#ifdef DEBUG
	printf("dbg: entering %s %d\n", __FUNCTION__, __LINE__);
#endif

	printf("joueur ");
	switch(joueur)
	{
	case -1:
		printf("o ");
		break;
	case 1:
		printf("x ");
		break;
	default:
		printf("inconnu ");
	}
	printf("joue:\n");
	while(1)
	{
		fgets(buffer, 32, stdin);
		if(sscanf(buffer, "%c%i%c%i\n", &c1, &l1, &c2, &l2) == 4)
		{
			if(f_bouge_piece(plateauDeJeu, l1, f_convert_char2int(c1), l2, f_convert_char2int(c2), joueur) == 0)
				break;
		}
		fflush(stdin);
		printf("mauvais choix\n");
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif
}

int main(int argv, char *argc[])
{
	int fin = 0,mode=0 , ret, joueur = 1;
	printf("1 humain vs IA\n2 humain vs humain\n3 IA vs IA\n");
	scanf("%d",&mode);

	plateauDeJeu = f_init_plateau();
	while (!fin)
	{
		f_affiche_plateau(plateauDeJeu);
		if(mode==1)
		{
			if(joueur>0)
				f_humain(joueur);
			else
				f_IA(joueur);
		}
		else if(mode==2)
		{
			f_humain(joueur);
		}
		else
		{
			f_IA(joueur);
		}

		if ((ret = f_gagnant()) != 0)
		{
			switch (ret)
			{
			case 1:
				f_affiche_plateau(plateauDeJeu);
				printf("joueur x gagne!\n");
				fin = 1;
				break;
			case -1:
				f_affiche_plateau(plateauDeJeu);
				printf("joueur o gagne!\n");
				fin = 1;
				break;
			}
		}
		joueur = -joueur;
	}

#ifdef DEBUG
	printf("dbg: exiting %s %d\n", __FUNCTION__, __LINE__);
#endif

	return 0;
}

