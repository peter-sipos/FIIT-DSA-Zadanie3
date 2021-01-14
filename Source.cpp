#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define pocet_stavov 128
#define zachranene_vsetky 126
#define max_princezien 5
#define max_vrcholov 1280000
#define max_vzdialenost 2560000
#define dole(row) (row+1)
#define vpravo(column) (column+1)
#define hore(row) (row-1)
#define vlavo(column) (column-1)
#define neprechodne(policko) (policko == 'N' ? 0: 1)
#define zabity_drak 2
#define zapnuty_generator 1
#define drak_a_generator 3
#define gen_je_vypnuty(stav) (stav % 2 == 0 ? 1: 0)
#define pocet_typov_teleportov 10
#define max_teleportov 10
#define zach_jedna 6
#define zach_dve 14
#define zach_tri 30
#define zach_styri 62
#define zach_pat 126



typedef struct rodic {
	int stav, row, column;
};

typedef struct vrchol {
	int stav, row, column;
	int vzdialenost;
	struct rodic rodic;
};

typedef struct suradnica {
	int stav, row, column;
};

typedef struct princezna {
	int row, column;
	short cislo;
};

void zoskenuj_mapu(char **mapa, int rows, int columns, struct suradnica ****teleporty, int *pocet_princezien, struct princezna ***princezne) {
	int row, column, i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, ip;
	i0 = i1 = i2 = i3 = i4 = i5 = i6 = i7 = i8 = i9 = ip = 0;

	for (row = 0; row < rows; row++) {
		for (column = 0; column < columns; column++) {
			//printf("%c", mapa[row][column]);
			switch (mapa[row][column]) {
			case 'P':
				(*pocet_princezien)++;
				(*princezne)[ip]->cislo = 0; (*princezne)[ip]->row = row; (*princezne)[ip]->column = column;
				ip++;
				break;
			case '0':
				(*teleporty)[0][i0]->row = row; (*teleporty)[0][i0]->column = column; i0++; break;
			case '1':
				(*teleporty)[1][i1]->row = row; (*teleporty)[1][i1]->column = column; i1++; break;
			case '2':
				(*teleporty)[2][i2]->row = row; (*teleporty)[2][i2]->column = column; i2++;	break;
			case '3':
				(*teleporty)[3][i3]->row = row; (*teleporty)[3][i3]->column = column; i3++;	break;
			case '4':
				(*teleporty)[4][i4]->row = row; (*teleporty)[4][i4]->column = column; i4++;	break;
			case '5':
				(*teleporty)[5][i5]->row = row; (*teleporty)[5][i5]->column = column; i5++;	break;
			case '6':
				(*teleporty)[6][i6]->row = row; (*teleporty)[6][i6]->column = column; i6++;	break;
			case '7':
				(*teleporty)[7][i7]->row = row; (*teleporty)[7][i7]->column = column; i7++;	break;
			case '8':
				(*teleporty)[8][i8]->row = row; (*teleporty)[8][i8]->column = column; i8++;	break;
			case '9':
				(*teleporty)[9][i9]->row = row; (*teleporty)[9][i9]->column = column; i9++;	break;
			}
		}
		//printf("\n");
	}
}


void alokuj_polia(int rows, int columns,  struct suradnica ****teleporty, struct vrchol *****vrcholy, struct suradnica ***suradnice, struct princezna ***princezne) {
	int row, column, stav, vrchol, tele, i;

	//TODO POLE PRINCEZIEN NEPOTREBUJEM
	//(*princezne) = (char**)malloc(rows * sizeof(char*));
	(*teleporty) = (struct suradnica***)malloc(pocet_typov_teleportov * sizeof(struct suradnica*));
	//(*vzdialenosti) = (int***)malloc(pocet_stavov * sizeof(int**));
	(*vrcholy) = (struct vrchol****)malloc(pocet_stavov * sizeof(struct vrchol***));

	for (stav = 0; stav < pocet_stavov; stav++) {
	//	(*vzdialenosti)[stav] = (int**)malloc(rows * sizeof(int*));
		(*vrcholy)[stav] = (struct vrchol***)malloc(rows * sizeof(struct vrchol**));
		for (row = 0; row < rows; row++){
			//(*vzdialenosti)[stav][row] = (int*)malloc(columns * sizeof(int));
			(*vrcholy)[stav][row] = (struct vrchol**)malloc(columns * sizeof(struct vrchol*));
			for(column = 0; column<columns; column++)
				(*vrcholy)[stav][row][column] = (struct vrchol*)malloc(sizeof(struct vrchol));
		}
	}


	//? TELEPORTY BY STACILI AJ STRUKTURA LEN S ROW A COLUMN --> STAV JE NEPOTREBNY
	for (tele = 0; tele < pocet_typov_teleportov; tele++) {
		(*teleporty)[tele] = (struct suradnica**)malloc(max_teleportov * sizeof(struct suradnica*));
		for(i = 0; i<max_teleportov; i++)
			(*teleporty)[tele][i] = (struct suradnica*)malloc(sizeof(struct suradnica));
	}
	for (tele = 0; tele < pocet_typov_teleportov; tele++) {
		for (i = 0; i < max_teleportov; i++) {
			(*teleporty)[tele][i]->stav = -1;
			(*teleporty)[tele][i]->row = -1;
			(*teleporty)[tele][i]->column = -1;
		}
	}

	for (stav = 0; stav < pocet_stavov; stav++) {
		for (row = 0; row < rows; row++)
			for (column = 0; column < columns; column++) {
			//	(*vzdialenosti)[stav][row][column] = INT_MAX;
				(*vrcholy)[stav][row][column]->vzdialenost = INT_MAX;
			}
	}

	(*suradnice) = (struct suradnica**)malloc(max_vrcholov * sizeof(struct suradnica*));
	for (vrchol = 0; vrchol < max_vrcholov; vrchol++) {
		(*suradnice)[vrchol] = NULL;
	}


	(*princezne) = (struct princezna**)malloc(5 * sizeof(struct princezna*));
	for (i = 0; i < 5; i++) {
		(*princezne)[i] = (struct princezna*)malloc(sizeof(struct princezna));
	}


}

struct suradnica *nova_suradnica(int stav, int row, int column) {
	struct suradnica *nova = (struct suradnica*)malloc(sizeof(struct suradnica));
	nova->stav = stav;
	nova->row = row; 
	nova->column = column;
	return nova;
}

int oplati_sa_ist(int povodna_cena, int cena_prechodu, int aktualna_cena) {
	if (aktualna_cena + cena_prechodu < povodna_cena)
		return 1;
	else return 0;
}

// funckcia vrati 0 ak je niektora suradnice mimo hracej plochy, inak vrati 1
int mimo_plochy(struct suradnica *sur_skumaneho, int rows, int columns) {
	if (sur_skumaneho->row < 0 || sur_skumaneho->column < 0 || sur_skumaneho->row >= rows || sur_skumaneho->column >= columns)
		return 0;
	else return 1;
}

int je_zabity(int stav) {
	if (stav == zabity_drak || stav == drak_a_generator)
		return 1;
	else return 0;
}

int stoji_na_teleporte(char znak) {
	switch (znak) {
	case '0': return 1;
	case '1': return 1;
	case '2': return 1;
	case '3': return 1;
	case '4': return 1;
	case '5': return 1;
	case '6': return 1;
	case '7': return 1;
	case '8': return 1;
	case '9': return 1;
	default: return 0;
	}
}

int zisti_cenu_prechodu(char policko) {
	if (policko == 'H')
		return 2;
	else
		return 1;
}

void zmena_stavu(struct vrchol *****vrcholy, int stav, int row, int column, int povodny_stav, int *max_stav) {
	(*vrcholy)[stav][row][column]->vzdialenost = (*vrcholy)[povodny_stav][row][column]->vzdialenost;
	(*vrcholy)[stav][row][column]->rodic.stav = (*vrcholy)[povodny_stav][row][column]->rodic.stav;
	(*vrcholy)[stav][row][column]->rodic.row = (*vrcholy)[povodny_stav][row][column]->rodic.row;
	(*vrcholy)[stav][row][column]->rodic.column = (*vrcholy)[povodny_stav][row][column]->rodic.column;

	*max_stav = stav;
}

void uvolni_polia(int rows, int columns, struct suradnica ****teleporty, struct vrchol *****vrcholy, struct suradnica ***suradnice, struct princezna ***princezne, int pocet_suradnic) {
	int row, column, stav, vrchol, tele, i;

	// uvolnenie princezien
	for (i = 0; i < 5; i++) {
		free((*princezne)[i]);
	}
	free((*princezne));

	// uvolnenie suradnic
	//for (vrchol = 0; vrchol < pocet_suradnic; vrchol++) {
	//	if((*suradnice)[vrchol] != NULL)
	//		free((*suradnice)[vrchol]);
	//}
	free((*suradnice));

	// uvolnenie vrcholov
	for (stav = 0; stav < pocet_stavov; stav++) {
		for (row = 0; row < rows; row++)
			for (column = 0; column < columns; column++)
				free((*vrcholy)[stav][row][column]);
	}
	for (stav = 0; stav < pocet_stavov; stav++) {
		for (row = 0; row < rows; row++)
			free((*vrcholy)[stav][row]);
	}
	for (stav = 0; stav < pocet_stavov; stav++) {
		free((*vrcholy)[stav]);
	}
	free((*vrcholy));

	// uvolnenie teleportov
	for (tele = 0; tele < pocet_typov_teleportov; tele++) {
		for (i = 0; i<max_teleportov; i++)
			free((*teleporty)[tele][i]);
	}
	for (tele = 0; tele < pocet_typov_teleportov; tele++) {
		free((*teleporty)[tele]);
	}
	free((*teleporty));


}

int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty) {
	int row, column, stav, *cesta, pocet_princezien;
	int i, j, iter, cena_prechodu, pocet_zachranenych, cena_preskumavaneho, cena_aktualneho;
	char policko_preskumavaneho;
	struct vrchol ****vrcholy; 
	struct suradnica **suradnice, *sur_skumaneho, ***teleporty;
	struct princezna **princezne;
	int ip = 0;
	int max_stav = 0;

	pocet_princezien = 0;
	alokuj_polia(n, m, &teleporty,  &vrcholy, &suradnice, &princezne);
	zoskenuj_mapu(mapa, n, m, &teleporty, &pocet_princezien, &princezne);
	cesta = NULL;

	row = column = stav = 0;
	
	vrcholy[stav][row][column]->stav = stav; vrcholy[stav][row][column]->row = row;	vrcholy[stav][row][column]->column = column; 
	vrcholy[stav][row][column]->vzdialenost = zisti_cenu_prechodu(mapa[row][column]);
	vrcholy[stav][row][column]->rodic.stav = -1; vrcholy[stav][row][column]->rodic.row = -1; vrcholy[stav][row][column]->rodic.column = -1;   // nastav rodica prvej surednice na -1
	suradnice[0] = nova_suradnica(stav, row, column);				// pridaj prvu suradnicu do pola suradnic
	i = 0;
	j = 1;
	
																	
	struct vrchol *naj_zachranene;
	naj_zachranene = (struct vrchol*)malloc(sizeof(struct vrchol)); 
	naj_zachranene->vzdialenost = INT_MAX; 

	pocet_zachranenych = 1; 
	sur_skumaneho = (struct suradnica*)malloc(sizeof(struct suradnica));

	while (suradnice[i] != NULL /*|| stav < zachranene_vsetky*/) {
		// nastav suradnice (stav, row, column) na prvu (i-tu) suradnicu z pola 
		// vyskrtni suradnicu i zo zoznamu suradnic (free)
		// zvacsi i
		// opakuj pre dole, vpravo, hore a vlavo --> skus navstivit
		// ak nie si mimo hraciu plochu && nova vzdialenost na danej suradnici < ako povodna && nebude nepriechodne ('N' v hlavnej mape)
		//		--> zmen vzdialenost danej suradnice
		//		--> pridaj danu suradnicu do pola suradnic na poziciu j
		//		--> zvacsi j
		//		--> nastav rodica skumaneho vrchola na vychodzi vrchol

		// toto opakujem az kym neprejdem vsetky vrcholy

		stav = suradnice[i]->stav; row = suradnice[i]->row; column = suradnice[i]->column;
		free(suradnice[i]);
		i++;
		int povodny_stav = stav;


		if (stav > max_stav)
			max_stav = stav;


		// ZABITIE DRAKA A SPUSTENIE GENERATORA
		if (mapa[row][column] == 'D' && stav < zabity_drak) {
			stav += 2;
			zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);

		}

		// osetrenie generatora - zapnuty ak je stav neparne cislo
		if (mapa[row][column] == 'G' && gen_je_vypnuty(stav)==1) {
			stav += 1;
			zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);
		}

		// ak bude na mape menej ako 5 princezien, chod hned do stavu, kedy chyba uz len dany pocet princezien
		if (je_zabity(stav) && pocet_princezien != max_princezien) {
			switch (pocet_princezien) {
			case 1:	stav += 60; zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);
				break;
			case 2:	stav += 28; zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);
				break;
			case 3:	stav += 12; zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);
				break;
			case 4: stav += 4;  zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);
				break;
			default: printf("nieco nie je na poriadku\n"); break;
			}
		}

		// NAJDENIE PRINCEZNY
		for (ip = 0; ip < 5; ip++) {
			if (princezne[ip]->row == row && princezne[ip]->column == column && princezne[ip]->cislo == 0 && stav == max_stav) {
				if (mapa[row][column] == 'P' && stav > zabity_drak && stav < zachranene_vsetky) {
					princezne[ip]->cislo = 1;
					switch (stav) {
					case zabity_drak: pocet_zachranenych = 1; break;
					case drak_a_generator: pocet_zachranenych = 1; break;
					case zach_jedna: pocet_zachranenych = 2; break;
					case zach_jedna + 1: pocet_zachranenych = 2; break;
					case zach_dve: pocet_zachranenych = 3; break;
					case zach_dve + 1: pocet_zachranenych = 3; break;
					case zach_tri: pocet_zachranenych = 4; break;
					case zach_tri + 1: pocet_zachranenych = 4; break;
					case zach_styri: pocet_zachranenych = 5; break;
					case zach_styri + 1: pocet_zachranenych = 5; break;
					}
					pocet_zachranenych++;
					stav += (int)(pow(2, pocet_zachranenych));
					zmena_stavu(&vrcholy, stav, row, column, povodny_stav, &max_stav);
				}
			}
		}

		//AK SOM V NEJAKOM FINALNOM STAVE (stav >= 126) TAK pozri, ci jeho cena je mensia ako cena doterajsej najlepsej zachrany, ak ano, tak ju zmen na nu
		if (stav >= zachranene_vsetky && vrcholy[stav][row][column]->vzdialenost < naj_zachranene->vzdialenost) {
			naj_zachranene->vzdialenost = vrcholy[stav][row][column]->vzdialenost;
			naj_zachranene->stav = stav;
			naj_zachranene->row = row;
			naj_zachranene->column = column;

			naj_zachranene->rodic.stav = vrcholy[stav][row][column]->rodic.stav;
			naj_zachranene->rodic.row = vrcholy[stav][row][column]->rodic.row;
			naj_zachranene->rodic.column = vrcholy[stav][row][column]->rodic.column;
			continue;
		}


		//OSETRIT TELEPORTY (PRECHODY NIMI)
		int teleport;
		// ROB IBA AK STOJIS NA POLICKU S TELEPORTOM --> STATIE ZISTIT VO FUNKCII
		if (!gen_je_vypnuty(stav) && stoji_na_teleporte(mapa[row][column])) {
			switch (mapa[row][column]) {
			case '0': teleport = 0; break;
			case '1': teleport = 1; break;
			case '2': teleport = 2; break;
			case '3': teleport = 3; break;
			case '4': teleport = 4; break;
			case '5': teleport = 5; break;
			case '6': teleport = 6; break;
			case '7': teleport = 7; break;
			case '8': teleport = 8; break;
			case '9': teleport = 9; break;
			default: break;
			}
			//! AK STOJIM NA POLICKU S TELEPORTOM ---> OKREM KLASICKYCH SUSEDNYCH PREHLADAJ AJ VSETKY, NA KTORE SA VIES TELEPORTNUT 
			//	--> TYM ZMEN VZDZIALENOST NA ROVNAKU AKO MA AKTUALNE POLICKU (TO Z KT. SA TELEPOTUJEM)\
			//	--> ICH RODICA NASTAV ROVNAKO AK AJ OBYCAJNMYM SUSEDOM NA AKTUALNE POLICKO (TELEPORTACNE)
			//	--> ROVNAKO TAK ICH ZAPIS DO POLA SURADNIC
			int it = 0;
			while (teleporty[teleport][it]->row != -1) {
				sur_skumaneho->row = teleporty[teleport][it]->row; sur_skumaneho->column = teleporty[teleport][it]->column;
				cena_preskumavaneho = vrcholy[stav][sur_skumaneho->row][sur_skumaneho->column]->vzdialenost;				// prva suradnica je iba stav bo sa hybem len vramci jednej mapy
				cena_aktualneho = vrcholy[stav][row][column]->vzdialenost;
				cena_prechodu = 0;
				if (oplati_sa_ist(cena_preskumavaneho, cena_prechodu, cena_aktualneho)) {
					vrcholy[stav][sur_skumaneho->row][sur_skumaneho->column]->vzdialenost = cena_aktualneho;
					
					suradnice[j] = nova_suradnica(stav, sur_skumaneho->row, sur_skumaneho->column);
					j++;

					vrcholy[stav][sur_skumaneho->row][sur_skumaneho->column]->rodic.stav = stav;							// stav by mal byt rovnaky ako povodny stav --> stav sa totiz nemeni
					vrcholy[stav][sur_skumaneho->row][sur_skumaneho->column]->rodic.row = row;
					vrcholy[stav][sur_skumaneho->row][sur_skumaneho->column]->rodic.column = column;
				}

				it++;
			}
		}

		for (iter = 0; iter < 4; iter++) {
			sur_skumaneho->stav = stav; sur_skumaneho->row = row; sur_skumaneho->column = column;

			switch (iter) {
			case 0: sur_skumaneho->row = dole(row); break;
			case 1: sur_skumaneho->column = vpravo(column); break;
			case 2: sur_skumaneho->row = hore(row); break;
			case 3: sur_skumaneho->column = vlavo(column); break;
			default: printf("neco se porouchalo\n"); break;
			}

			cena_aktualneho = vrcholy[stav][row][column]->vzdialenost;
			if (mimo_plochy(sur_skumaneho, n, m)) {
				cena_prechodu = zisti_cenu_prechodu(mapa[sur_skumaneho->row][sur_skumaneho->column]);
				policko_preskumavaneho = mapa[sur_skumaneho->row][sur_skumaneho->column];
				cena_preskumavaneho = vrcholy[sur_skumaneho->stav][sur_skumaneho->row][sur_skumaneho->column]->vzdialenost;
			}

			// ak preskumavam novy bod
			if (mimo_plochy(sur_skumaneho, n, m) && oplati_sa_ist(cena_preskumavaneho, cena_prechodu, cena_aktualneho) && neprechodne(policko_preskumavaneho)) {
				vrcholy[sur_skumaneho->stav][sur_skumaneho->row][sur_skumaneho->column]->vzdialenost = cena_aktualneho + cena_prechodu;
				
				suradnice[j] = nova_suradnica(sur_skumaneho->stav, sur_skumaneho->row, sur_skumaneho->column);
				j++;

				vrcholy[sur_skumaneho->stav][sur_skumaneho->row][sur_skumaneho->column]->rodic.stav = stav;
				vrcholy[sur_skumaneho->stav][sur_skumaneho->row][sur_skumaneho->column]->rodic.row = row;
				vrcholy[sur_skumaneho->stav][sur_skumaneho->row][sur_skumaneho->column]->rodic.column = column;
			}
		}

	}

	//TODO SPATNE ZOSTROJENIE CESTY
	//! DLZKA CESTY (velkost pola) bude vzdialenost naj_zachranene ---> cestu TREBA ALOKOVAT
	// POSTUP:
		// vytvor novy temp_vrchol a nastavho na naj_zachranene
		// --> kym suradnice rodica temp_vrchola != -1
			// --> do cesty pridaj row a column temp_vrchola (kompresia dvoch suradnic do jednej)
				//! pridavaj to od konca pola po 0 --> potom nebudem musiet reverzovat to pole
			// --> temp_vrchol nastav na jeho parenta (teda vsetky jeho suradnice)
	struct vrchol *temp_vrchol;
	temp_vrchol = (struct vrchol*)malloc(sizeof(struct vrchol)); //? MUSIM TOTO TU ALOKOVAT???
	//temp_vrchol = naj_zachranene;
	temp_vrchol->stav = naj_zachranene->stav;
	temp_vrchol->row = naj_zachranene->row;
	temp_vrchol->column = naj_zachranene->column;
	temp_vrchol->vzdialenost = naj_zachranene->vzdialenost;
	temp_vrchol->rodic.stav = naj_zachranene->rodic.stav;
	temp_vrchol->rodic.row = naj_zachranene->rodic.row;
	temp_vrchol->rodic.column = naj_zachranene->rodic.column;
	while (temp_vrchol->rodic.stav != -1) {
		(*dlzka_cesty)++;
		temp_vrchol->stav = temp_vrchol->rodic.stav;
		temp_vrchol->row = temp_vrchol->rodic.row;
		temp_vrchol->column = temp_vrchol->rodic.column;

		temp_vrchol->rodic.stav = vrcholy[temp_vrchol->stav][temp_vrchol->row][temp_vrchol->column]->rodic.stav;
		temp_vrchol->rodic.row = vrcholy[temp_vrchol->stav][temp_vrchol->row][temp_vrchol->column]->rodic.row;
		temp_vrchol->rodic.column = vrcholy[temp_vrchol->stav][temp_vrchol->row][temp_vrchol->column]->rodic.column;
	}
	(*dlzka_cesty)++;


	cesta = (int*)malloc((*dlzka_cesty) * 2 * sizeof(int));

	iter = (*dlzka_cesty) * 2 - 1;

	temp_vrchol->stav = naj_zachranene->stav;
	temp_vrchol->row = naj_zachranene->row;
	temp_vrchol->column = naj_zachranene->column;
	temp_vrchol->vzdialenost = naj_zachranene->vzdialenost;
	temp_vrchol->rodic.stav = naj_zachranene->rodic.stav;
	temp_vrchol->rodic.row = naj_zachranene->rodic.row;
	temp_vrchol->rodic.column = naj_zachranene->rodic.column;
	while (temp_vrchol->rodic.stav != -1) {
		cesta[iter] = temp_vrchol->row;
		iter--;
		cesta[iter] = temp_vrchol->column;
		iter--;


		temp_vrchol->stav = temp_vrchol->rodic.stav;
		temp_vrchol->row = temp_vrchol->rodic.row;
		temp_vrchol->column = temp_vrchol->rodic.column;

		temp_vrchol->rodic.stav = vrcholy[temp_vrchol->stav][temp_vrchol->row][temp_vrchol->column]->rodic.stav;
		temp_vrchol->rodic.row = vrcholy[temp_vrchol->stav][temp_vrchol->row][temp_vrchol->column]->rodic.row;
		temp_vrchol->rodic.column = vrcholy[temp_vrchol->stav][temp_vrchol->row][temp_vrchol->column]->rodic.column;
	}

	cesta[iter] = temp_vrchol->row;
	iter--;
	cesta[iter] = temp_vrchol->column;
	iter--;

	uvolni_polia(n, m, &teleporty, &vrcholy, &suradnice, &princezne, j);
	free(sur_skumaneho); free(naj_zachranene); free(temp_vrchol);
	return cesta;
}

int main() {
	int i = 2, j = 3;
	i += pow(i, j);
	printf("%d\n", i);

	int dlzka_cesty = 0;
	int *cesta = NULL;

	char mapa1_static[5][5] = {
		'C','H','H','D','C',
		'H','C','C','H','H',
		'C','H','P','P','C',
		'P','H','H','H','C',
		'C','H','H','H','C' };
	char **mapa1;
	mapa1 = (char**)malloc(5 * sizeof(char*));
	for (i = 0; i < 5; i++) {
		mapa1[i] = (char*)malloc(5);
	}
	
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++)
			mapa1[i][j] = mapa1_static[i][j];
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++)
			printf("%c", mapa1[i][j]);
		printf("\n");
	}
	printf("\n\n");

	/*dlzka_cesty = 0;
	cesta = zachran_princezne(mapa1, 5, 5, 100, &dlzka_cesty);*/

	for (i = 0; i < dlzka_cesty*2; i++)
		printf("%d ", cesta[i]);

	char mapa2_static[7][7] = {
		'H','G','H','P','C','D','C',
		'C','0','C','C','H','P','P',
		'H','H','H','H','H','C','H',
		'H','H','H','H','H','H','C',
		'0','C','C','C','H','C','H',
		'0','C','H','C','H','1','C',
		'C','P','C','C','C','H','H' };
	char **mapa2;
	mapa2 = (char**)malloc(7 * sizeof(char*));
	for (i = 0; i < 7; i++) {
		mapa2[i] = (char*)malloc(7);
	}

	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++)
			mapa2[i][j] = mapa2_static[i][j];
	}
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++)
			printf("%c", mapa2[i][j]);
		printf("\n");
	}
	printf("\n\n");

	//dlzka_cesty = 0;
	//cesta = zachran_princezne(mapa2, 7, 7, 100, &dlzka_cesty);

	char mapa5_static[40][50] = {
		'C','H','H','C','C','C','H','C','H','H','C','H','H','C','H','C','C','C','C','H','C','C','H','C','H','H','H','H','C','H','H','C','H','H','C','H','C','C','H','H','H','H','C','H','H','C','H','H','H','H',
		'C','H','H','H','H','C','C','C','H','H','C','C','C','C','H','C','H','C','C','H','H','C','C','C','C','C','H','C','C','H','H','H','C','H','C','H','C','C','H','C','H','H','H','C','C','H','C','H','C','C',
		'H','C','C','C','C','H','C','H','C','C','C','C','H','C','H','C','H','C','C','C','H','C','H','H','C','H','C','C','C','H','C','C','C','H','C','C','H','H','H','C','C','C','C','H','C','C','C','H','H','C',
		'C','C','H','C','C','C','C','H','C','H','C','C','H','C','C','C','H','H','C','C','C','H','C','C','C','H','H','H','H','C','H','C','H','H','C','H','C','H','H','C','C','H','H','H','C','H','H','H','H','C',
		'H','C','C','C','C','C','C','C','H','H','H','C','C','H','H','C','C','C','C','C','H','H','C','H','H','H','C','C','C','C','C','C','H','C','C','C','C','C','H','C','H','C','H','H','H','C','C','H','H','C',
		'C','C','H','H','H','C','C','H','H','H','H','C','H','C','C','C','H','C','H','C','H','H','C','C','C','C','H','C','C','C','C','C','C','C','C','H','H','C','H','H','H','C','C','H','H','C','C','C','H','C',
		'C','C','C','C','H','H','H','H','C','C','C','C','C','C','C','C','H','H','C','C','C','C','H','C','H','C','C','C','H','H','C','H','C','H','H','C','C','H','C','H','H','H','C','H','H','H','C','C','H','C',
		'C','H','H','C','C','H','C','H','C','C','C','C','H','H','H','C','H','C','H','C','H','H','C','H','H','C','C','H','C','C','H','C','C','H','H','H','C','C','C','H','H','C','H','C','H','C','H','C','H','H',
		'H','H','G','H','C','H','H','C','C','H','H','H','C','C','H','H','H','H','H','H','C','H','H','C','H','H','C','H','C','C','C','H','C','C','H','H','H','H','C','H','H','H','C','C','H','H','H','H','H','C',
		'H','C','H','C','C','H','H','H','C','C','C','C','H','C','C','H','H','H','C','C','H','H','C','H','H','C','H','H','C','H','H','H','C','H','C','C','C','H','C','C','C','C','H','H','H','C','C','H','C','H',
		'C','H','H','H','H','C','H','C','C','H','H','H','H','H','H','H','C','C','H','H','C','H','H','C','C','H','H','H','C','C','H','H','H','C','C','C','H','C','H','C','H','H','H','C','H','C','C','H','H','H',
		'C','H','C','C','C','C','C','H','H','H','H','C','H','C','0','C','C','H','H','C','H','C','H','C','C','H','C','H','H','H','C','C','H','H','H','H','H','C','C','C','C','C','H','H','H','C','H','H','C','C',
		'H','H','C','H','H','H','C','H','H','H','H','H','H','C','C','H','H','C','C','C','H','C','C','C','C','C','C','C','H','H','C','H','C','C','H','H','C','C','H','H','H','H','C','C','C','C','C','H','C','H',
		'H','H','H','C','C','C','H','C','C','H','C','C','H','H','C','H','H','C','C','H','H','H','H','H','H','C','H','C','C','C','H','H','C','H','C','H','H','H','C','H','H','C','C','C','C','H','C','H','C','H',
		'H','C','H','C','C','H','H','C','C','C','H','H','C','C','C','C','C','0','C','P','H','C','H','H','H','H','C','C','C','H','C','H','C','H','H','H','C','H','H','C','H','C','H','H','C','H','H','C','H','C',
		'H','C','C','H','H','H','H','H','H','C','C','H','H','H','C','C','H','H','C','C','C','H','H','H','H','H','H','H','C','C','H','C','H','C','H','C','C','H','C','C','H','H','C','C','C','C','H','H','H','H',
		'C','C','C','0','C','H','C','C','H','H','C','H','C','C','H','H','C','H','C','C','C','C','C','H','H','C','H','H','C','C','H','C','C','H','C','C','C','C','H','H','C','H','H','H','H','H','C','H','H','H',
		'H','H','H','C','C','H','H','P','H','C','H','C','H','H','C','H','C','H','C','C','H','H','H','H','C','C','H','C','C','C','H','C','H','H','H','C','C','C','C','H','H','H','H','H','H','H','H','C','C','H',
		'H','H','H','H','C','H','H','H','C','H','H','C','C','C','H','C','C','H','H','C','H','C','C','C','C','C','H','C','C','H','C','C','H','C','H','H','H','C','C','H','H','C','H','H','C','H','C','H','H','C',
		'H','C','C','H','H','H','C','C','H','H','H','C','C','H','C','H','C','H','C','H','C','C','H','C','H','C','C','H','H','C','C','C','H','C','C','H','H','C','C','H','H','C','C','C','H','C','C','C','C','H',
		'C','C','C','H','H','H','C','H','C','C','H','P','H','C','H','H','C','H','H','H','C','C','C','C','H','H','H','H','0','C','H','H','H','H','C','H','H','C','H','H','C','C','C','H','C','H','C','C','H','C',
		'C','H','C','C','C','H','H','H','C','C','C','C','H','H','H','C','H','C','C','C','H','H','C','C','H','C','C','H','H','H','H','C','H','C','H','C','H','H','H','C','C','H','H','H','C','C','H','H','H','H',
		'H','H','C','C','C','H','C','H','C','H','H','H','H','C','H','C','C','H','C','H','C','C','C','H','C','H','H','C','C','H','H','H','H','C','H','H','H','H','C','C','C','H','H','C','H','H','H','C','C','H',
		'C','H','C','H','H','H','H','C','H','H','H','H','H','H','C','C','H','H','H','H','C','H','C','C','C','H','C','H','C','H','C','H','H','H','H','H','C','H','C','C','H','C','C','C','C','H','C','C','H','H',
		'C','H','C','H','C','H','C','H','C','C','C','C','C','H','H','H','C','H','H','H','C','H','C','H','C','H','C','H','C','C','C','H','C','C','C','H','H','C','H','H','H','C','H','C','H','H','C','C','H','H',
		'H','H','C','C','H','C','C','C','C','C','C','C','H','H','H','H','C','H','H','H','H','H','C','C','C','C','C','C','C','H','H','C','C','H','C','H','C','H','H','C','C','C','H','H','H','C','H','C','H','H',
		'H','C','C','H','H','C','0','C','C','H','H','H','C','C','H','C','H','C','C','H','C','H','C','H','C','H','C','C','C','H','C','H','C','C','H','H','C','H','H','H','H','H','H','H','H','H','C','C','H','C',
		'H','H','H','H','H','H','H','C','H','H','H','C','C','C','H','C','H','H','H','C','H','C','H','C','H','H','H','C','H','C','H','H','C','H','H','C','H','H','C','H','H','H','C','C','C','C','H','C','H','H',
		'H','C','C','H','H','H','C','C','H','H','C','C','C','C','C','C','C','C','C','H','C','C','H','C','H','C','H','H','C','H','H','H','H','H','H','H','H','H','H','C','H','C','C','C','H','H','C','H','C','C',
		'C','C','H','H','C','C','C','C','H','C','H','C','C','C','H','H','C','C','H','H','H','H','H','H','H','C','H','C','H','C','H','H','C','H','H','H','H','C','C','H','H','C','C','C','C','H','C','H','C','H',
		'C','H','C','H','H','C','C','C','C','H','C','C','C','C','H','C','H','H','C','C','C','C','H','C','C','H','C','H','H','C','C','H','H','H','C','C','H','H','C','H','C','C','H','H','C','C','C','H','H','C',
		'H','C','C','H','C','C','C','C','H','H','H','C','H','H','C','H','C','C','C','C','H','H','H','H','H','D','H','H','H','H','H','C','H','H','H','H','C','H','C','H','C','C','C','H','C','H','C','C','H','C',
		'H','1','H','C','H','H','H','H','C','C','C','H','C','C','H','H','0','H','H','H','H','H','C','H','H','H','H','C','H','C','C','H','C','C','C','C','H','H','H','C','H','C','C','C','H','C','H','H','H','C',
		'H','C','C','C','C','C','H','C','C','H','C','H','H','C','C','H','H','C','H','C','H','C','H','H','C','C','H','C','H','C','C','H','H','C','H','C','C','H','C','H','H','H','C','H','C','H','H','H','C','C',
		'C','H','C','H','H','C','H','C','C','C','C','H','C','H','H','C','H','H','H','H','C','H','H','C','H','C','C','C','H','H','H','C','C','H','H','C','H','C','C','H','H','C','H','H','H','H','H','H','H','H',
		'H','C','C','C','C','C','H','C','H','H','C','C','C','H','H','H','H','C','H','C','C','C','C','H','H','H','H','H','C','C','H','C','C','C','C','C','0','C','C','C','H','C','H','C','H','C','H','H','C','H',
		'C','H','H','C','H','C','H','H','C','C','C','H','C','H','C','H','H','C','C','C','H','H','C','H','H','H','1','C','H','H','H','H','C','H','C','H','C','C','C','C','H','1','H','H','C','P','H','H','C','H',
		'C','C','C','C','H','C','C','C','C','C','C','C','H','C','C','C','C','H','C','C','C','H','H','C','C','C','H','C','H','C','C','H','P','H','H','C','C','C','C','H','H','C','C','C','C','H','C','H','H','C',
		'H','H','H','C','C','C','C','C','H','C','C','H','C','H','C','H','H','C','H','C','C','C','H','H','H','C','C','H','C','H','C','H','H','H','H','C','H','C','H','H','H','H','H','C','H','C','C','H','H','C',
		'C','C','H','H','C','C','C','C','H','C','H','C','H','H','C','C','C','C','H','H','H','C','H','H','C','H','H','H','C','C','H','C','C','C','C','H','C','C','H','C','H','C','H','C','H','C','H','C','C','C', };
	char **mapa5;
	mapa5 = (char**)malloc(40 * sizeof(char*));
	for (i = 0; i < 40; i++) {
		mapa5[i] = (char*)malloc(50);
	}

	for (i = 0; i < 40; i++) {
		for (j = 0; j < 50; j++)
			mapa5[i][j] = mapa5_static[i][j];
	}
	for (i = 0; i < 40; i++) {
		for (j = 0; j < 50; j++)
			printf("%c", mapa5[i][j]);
		printf("\n");
	}
	printf("\n\n");

	dlzka_cesty = 0;
	cesta = zachran_princezne(mapa5, 40, 50, 100, &dlzka_cesty);
	for (i = 0; i < dlzka_cesty * 2; i++)
		printf("%d ", cesta[i]);

	getchar(); getchar();


	return 0;
}