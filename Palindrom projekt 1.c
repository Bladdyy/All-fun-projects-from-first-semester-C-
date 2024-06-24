/****************************************************************
	Autor: Juliusz Pawlus
	Następujący program symuluje grę w Connect Four 
	na niestandardowej planszy i na wybranej długości palindromu.
****************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 Liczba wierszy planszy
*/
#ifndef WIERSZE
#define WIERSZE 8
#endif

/**
 Liczba kolumn planszy
*/
#ifndef KOLUMNY
#define KOLUMNY 8
#endif

/**
 Długość palindromu niezbędna do wygranej
*/
#ifndef DLUGOSC
#define DLUGOSC 5
#endif


/*
 Dostaje tablicę wypełnioną znakami i rysuje na jej podstawie diagram planszy.
*/

void rysuj_plansze(char tab[][KOLUMNY])
{
    for (int wiersz = 0; wiersz < WIERSZE; wiersz++)
    {
        for (int kolumna = 0; kolumna < KOLUMNY; kolumna++)
        {
            printf(" ");
            putchar(tab[wiersz][kolumna]);
        }
        printf("\n");
    }
	for (int kolumna = 'a'; kolumna < KOLUMNY + 'a'; kolumna++)
    {
        printf(" ");
		putchar(kolumna);
    }
    printf("\n");
}


/*
 Dostaje tablicę wypełnioną znakami, informację o tym czyja tura, 
 wskaźnik do zmiennej kończącej grę oraz wskaźniki do koordynaty pierwszej oraz drugiej.
 Zapisuje na tablicy informację, gdzie został wykonany ruch oraz aktualizuje koordynaty tego ruchu.
 Sprawdza, czy gracze chcą przedwcześnie skończyć grę, jeśli tak, to wysyła informację o tym.
 */

void zagranie(char tab[][KOLUMNY], int kolejka, int *ender, int *koor1, int *koor2)
{
	int symbol = getchar();
	getchar(); // Sczytuje EOF
	int stop = 0;
	int obrot_petli = 1;
	if (symbol == '.')
	{
		*ender = 1;
	}
	else
	{
		while (stop == 0)
		{
			if (tab[WIERSZE - obrot_petli][symbol - 'a'] != '1' &&
			 tab[WIERSZE - obrot_petli][symbol - 'a'] != '2')
			{
				stop = 1;
				if (kolejka == 1)
				{	
					tab[WIERSZE - obrot_petli][symbol - 'a'] = '1';
				}
				else
				{
					tab[WIERSZE - obrot_petli][symbol - 'a'] = '2';
				}
				*koor1 = WIERSZE - obrot_petli;
				*koor2 = symbol - 'a';
			}
			
			obrot_petli++;
		}
	}
}


/*
 Dostaje tablicę wypełnioną znakami, wskaźnik do zmiennej kończącej grę,
 wskaźniki do koordynaty pierwszej oraz drugiej, informację o tym czyja jest tura
 oraz wskaźnik do zmiennej trzymającej informację o zwycięzcy.
 Sprawdza, czy którekolwiek z kryteriów wygranej jest spełnione. Jeśli tak jest,
 wysyła informację o zwycięzcy oraz o tym, że należy zakończyć grę.
*/

void zasady(char tab[][KOLUMNY], int *ender, int kor1, int kor2, int *ktowygral)
{
	int checker = 0; // Liczy segmenty palindromu
	int pass = 0; // Przepuszcza dalej, jeśli nie znaleziono dotychczas palindromu.
	if (WIERSZE - kor1 >= DLUGOSC) // Sprawdza palindrom w kolumnie
	{
		int dol = kor1 + DLUGOSC - 1; // Koordynata wiersza ostatniego elementu palindromu. 
		while (dol - checker > kor1 + checker 
		 && tab[dol - checker][kor2] == tab[kor1 + checker][kor2])
		{
			checker++;
		}
	
		if (checker == (DLUGOSC / 2))
		{
			*ender = 1;
			*ktowygral = tab[kor1][kor2];
			pass = 1;
		}
	}
	
	if (pass == 0) // Sprawdza palindrom w wierszu
	{
		int temp_kor2 = kor2; // Pierwsza koordynata palindromu od prawej po przejściu pętli.
		while (temp_kor2 < KOLUMNY && (tab[kor1][temp_kor2] == '1' || tab[kor1][temp_kor2] == '2'))
		{
			temp_kor2++;
		}
		temp_kor2--;  
		int blok = 0; // Przerywa wcześniej pętle, jeśli trzeba.
		while (blok == 0 && temp_kor2 >= DLUGOSC - 1)
		{
			checker = 0; // Liczy segmenty palindromu
			int illegal = 0; // Trzyma informacje czy palindromy nie równają się '-'
			int core2 = temp_kor2 - (DLUGOSC / 2);  // Koordynata środka palindromu 
			if (DLUGOSC % 2 == 0) // Sprawdza palindrom, jeśli ma być parzysty
			{
				while (checker < (DLUGOSC / 2) && illegal == 0 && 
				 tab[kor1][core2 - checker] == tab[kor1][core2 + checker + 1])
				{
					if (tab[kor1][core2 - checker] == '-' || tab[kor1][core2 + checker + 1] == '-')
					{
						illegal++;
					}
					else
					{
						checker++;
					}
				}
			}
			else // Sprawdza palindrom, jeśli ma być nieparzysty
			{
				if (tab[kor1][core2] != '-')
				{
					while (checker < (DLUGOSC / 2) && illegal == 0 && 
					 tab[kor1][core2 - checker - 1] == tab[kor1][core2 + checker + 1])
					{
						if (tab[kor1][core2 - checker - 1] == '-' || 
							tab[kor1][core2 + checker + 1] == '-')
						{
							illegal++;
						}
						else
						{
							checker++;
						}
					}
				}
			}
			temp_kor2--;
			if (checker == (DLUGOSC / 2)) // Sprawdza, czy ktoś wygrał.
			{
				*ender = 1;
				*ktowygral = tab[kor1][kor2];
				pass = 1;
				blok = 1;
			}
		}
	}
	
	if (pass == 0) // Sprawdza palindromy ukośne w prawo
	{
		int temp_kor1 = kor1;
		int temp_kor2 = kor2;
		int stop = 0;
		while (temp_kor1 >= 0 && temp_kor2 < KOLUMNY && stop == 0)
		{
			if (tab[temp_kor1][temp_kor2] == '1' || tab[temp_kor1][temp_kor2] == '2')
			{
				temp_kor2++;
				temp_kor1--;
			}
			else
			{
				stop = 1;
			}
		}
		temp_kor2--; 
		temp_kor1++;	
		int blok = 0; // Przerywa wcześniej pętle, jeśli trzeba.
		while (blok == 0 && temp_kor2 >= DLUGOSC - 1 && temp_kor1 <= WIERSZE - DLUGOSC)
		{
			checker = 0; // Liczy segmenty palindromu
			int illegal = 0; // Trzyma informacje czy palindromy nie równają się '-'
			int core1 = temp_kor1 + (DLUGOSC / 2); // Pierwsza koordynata środka palindromu
			int core2 = temp_kor2 - (DLUGOSC / 2); // Druga koordynata środka palindromu
			if (DLUGOSC % 2 == 0) // Sprawdza palindrom, jeśli ma być parzysty
			{
				while (checker < (DLUGOSC / 2) && illegal == 0 &&
					tab[core1 + checker][core2 - checker] == 
				    tab[core1 - checker - 1][core2 + checker + 1])
				{
					if (tab[core1 + checker][core2 - checker] == '-' || 
					    tab[core1 - checker - 1][core2 + checker + 1] == '-')
					{
						illegal++;
					}
					else
					{
						checker++;
					}
				}
			}
			else // Sprawdza palindrom, jeśli ma być nieparzysty
			{
				if (tab[core1][temp_kor2 - (DLUGOSC / 2)] != '-')
				{
					while (checker < (DLUGOSC / 2) && illegal == 0 &&
						tab[core1 + checker + 1][core2 - checker - 1] == 
						tab[core1 - checker - 1][core2 + checker + 1])
					{
						if (tab[core1 + checker + 1][core2 - checker - 1] == '-' ||
							tab[core1 - checker - 1][core2 + checker + 1] == '-')
						{
							illegal++;
						}
						else
						{
							checker++;
						}
					}
				}
			}
			temp_kor1++;
			temp_kor2--;
			if (checker == (DLUGOSC / 2)) // Sprawdza, czy ktoś wygrał.
			{
				*ender = 1;
				*ktowygral = tab[kor1][kor2];
				pass = 1;
				blok = 1;
			}
		}
	}
	
	if (pass == 0) // Sprawdza palindromy ukośne w lewo
	{
		int temp_kor1 = kor1;
		int temp_kor2 = kor2;
		int stop = 0;
		while (temp_kor1 >= 0 && temp_kor2 >= 0 && stop == 0)
		{
			if (tab[temp_kor1][temp_kor2] == '1' || tab[temp_kor1][temp_kor2] == '2')
			{
				temp_kor2--;
				temp_kor1--;
			}
			else
			{
				stop = 1;
			}
		}
		temp_kor2++; 
		temp_kor1++;	
		int blok = 0;
		while (blok == 0 && temp_kor2 <= KOLUMNY - DLUGOSC && temp_kor1 <= WIERSZE - DLUGOSC)
		{
			checker = 0; // Liczy segmenty palindromu
			int illegal = 0; // Trzyma informacje czy palindromy nie równają się '-'
			int core1 = temp_kor1 + (DLUGOSC / 2); // Pierwsza koordynata środka palindromu
			int core2 = temp_kor2 + (DLUGOSC / 2); // Druga koordynata środka palindromu
			if (DLUGOSC % 2 == 0) // Sprawdza palindrom, jeśli ma być parzysty
			{
				while (checker < (DLUGOSC / 2) && illegal == 0 &&
					tab[core1 - checker - 1][core2 - checker - 1] == 
					tab[core1 + checker][core2 + checker])
				{
					if (tab[core1 - checker - 1][core2 - checker - 1] == '-' ||
						tab[core1 + checker][core2 + checker] == '-')
					{
						illegal++;
					}
					else
					{
						checker++;
					}
				}
			}
			else // Sprawdza palindrom, jeśli ma być nieparzysty
			{
				if (tab[core1][core2] != '-')
				{
					while (checker < (DLUGOSC / 2) && illegal == 0 &&
						tab[core1 - checker - 1][core2 - checker - 1] == 
						tab[core1 + checker + 1][core2 + checker + 1])
					{
						if (tab[core1 - checker - 1][core2 - checker - 1] == '-' ||
							tab[core1 + checker + 1][core2 + checker + 1] == '-')
						{
							illegal++;
						}
						else
						{
							checker++;
						}

					}
				}
			}
			temp_kor1++;
			temp_kor2--;
			if (checker == (DLUGOSC / 2)) // Sprawdza, czy ktoś wygrał.
			{
				*ender = 1;
				*ktowygral = tab[kor1][kor2];
				pass = 1;
				blok = 1;
			}
		}
	}

}


/*
 Na wejściu czyta litery, a następnie przedstawia planszę zaktualizowaną o ruchy graczy
  oraz pokazuje, który gracz ma wykonać ruch.
 Powtarza te czynności dopóki, nie zostanie poproszona o zakończenie lub któryś z graczy
  wygra grę. W sytuacji wygranej, pokazuje kto wygrał.
*/

int main(void) 
{
	int tura;
	int newput1 = WIERSZE + 1; // Posiada informacje o pierwszej koordynacie miejsca w tablicy.
	int *wnewput1 = &newput1;
	int newput2 = KOLUMNY + 1; // Posiada informacje o drugiej koordynacie miejsca w tablicy.
	int *wnewput2 = &newput2;
	int end = 0;
	int *wend = &end;
	int winner = 0;
	int *wwinner = &winner;
	char plansza[WIERSZE][KOLUMNY];
    for (int wiersz = 0; wiersz < WIERSZE; wiersz++)
    {
        for (int kolumna = 0; kolumna < KOLUMNY; kolumna++)
        {
			plansza[wiersz][kolumna] = '-';
        }
    }
	int powtorzenie = 0;
	while (end == 0)
	{
		tura = (powtorzenie % 2) + 1;
		rysuj_plansze(plansza);
    	printf("%d:\n", (tura)); // Wypisuje, którego gracza jest tura.
		zagranie(plansza, tura, wend, wnewput1, wnewput2);
		zasady(plansza, wend, newput1, newput2, wwinner);
    	powtorzenie++;
	}
	if (winner == '1' || winner == '2') // Sprawdza, czy mamy zwycięzcę.
	{
		rysuj_plansze(plansza);
		printf("%c!\n", winner);
	}
    return 0;
}