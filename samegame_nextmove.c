/**************************************************************************************************
                                Autor: Juliusz Pawlus
 Program samegame przy wywołaniu musi otrzymać dwie koordynaty w postaci liczb opisujących
 kolejno wiersz oraz kolumnę punktu na planszy, który wraz ze swoją grupą ma zostać usunięty.
 Koordynata wiersza musi być mniejsza od wartości makra 'WIERSZE', a koordynata kolumny musi
 być mniejsza od wartości makra 'KOLUMNY'. Oprócz tego po wywołaniu musi otrzymać linijki
 w ilości makra 'WIERSZE' oddzielone enterami. Linijki te są długości makra 'KOLUMNY' oraz
 są wypełnione znakami. Jeśli podany punkt będzie spełniał warunki bycia w grupie to program rysuje
 planszę po aktualizacji. W przeciwnym przypadku rysuje planszę wcześniej podaną. Wartości makr
 'WIERSZE', 'KOLUMNY' oraz 'RODZAJE' mogą być modyfikowane podczas wywoływania programu.
**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**
 Liczba wierszy planszy.
*/
#ifndef WIERSZE
#define WIERSZE 10
#endif

/**
 Liczba kolumn planszy.
*/
#ifndef KOLUMNY
#define KOLUMNY 15
#endif

/**
 Liczba rodzajów klocków.
*/
#ifndef RODZAJE
#define RODZAJE 4
#endif


/**
 Dostaje pustą tablicę 'temp_plansza', którą wypełnia wpisanymi znakami, co tworzy planszę do gry.
*/
void czytaj_plansze(int temp_plansza[][KOLUMNY])
{
    int temp_char; // Sczytuje znaki wpisywane do planszy.
    for (int wiersz = 0; wiersz < WIERSZE; wiersz++)
    {
        for (int kolumna = 0; kolumna < KOLUMNY; kolumna++)
        {
            temp_char = getchar();
            temp_plansza[wiersz][kolumna] = temp_char;
        }
        getchar(); // Sczytuje enter.
    }
}


/**
 Dostaje tablicę 'temp_plansza', która opisuje położenie klocków na planszy,
 wskaźnik 'przejscie' do zmiennej pozwalającej usunąć klocek startowy wraz z jego grupą
 oraz potem upordządkować planszę. Dostaje koordynaty pola 'kor1' i 'kor2,
 na którym jest początkowy klocek.  Sprawdza, czy klocek spełnia kryteria zadania
 i jeśli je spełnia, to zmienia wartość zmiennej zapisanej pod wskaźnikiem 'przejscie' na 1,
 co jest równoważne z tym, iż zmienna ta pozwala usunąć kolcek startowy wraz z jego grupą.
*/
void sprawdz_klocek(int kor1, int kor2, int *przejscie, int temp_plansza[][KOLUMNY])
{
    if (temp_plansza[kor1][kor2] != '.') // Sprawdza, czy pole nie jest puste.
    {
        if (kor1 > 0 && temp_plansza[kor1][kor2] == temp_plansza[kor1 - 1][kor2])
        {
            *przejscie = 1;
        }
        else if (kor2 > 0 && temp_plansza[kor1][kor2] == temp_plansza[kor1][kor2 - 1])
        {
            *przejscie = 1;
        }
        else if (kor2 + 1 < KOLUMNY && temp_plansza[kor1][kor2] == temp_plansza[kor1][kor2 + 1])
        {
            *przejscie = 1;
        }
        else if (kor1 + 1 < WIERSZE && temp_plansza[kor1][kor2] == temp_plansza[kor1 + 1][kor2])
        {
            *przejscie = 1;
        }
    }
}


/**
 Dostaje tablicę 'temp_plansza', która opisuje położenie klocków na planszy,
 tablicę 'zapis_kolumn', w której zapisuje, które kolumny zostały zmodyfikowane
 oraz koordynaty klocka 'kor1' oraz 'kor2', którego usuwa, po czym sprawdza,
 czy koło niego nie stały klocki z tej samej grupy. Jeśli tak,
 to powtarza dla nich tę samą procedurę.
*/
void usuwanie(int kor1, int kor2, int temp_plansza[][KOLUMNY], int zapis_kolumn[KOLUMNY])
{
    int temp_cel = temp_plansza[kor1][kor2]; // Zapisuje jakiego rodzaju był klocek docelowy.
    temp_plansza[kor1][kor2] = '.'; // Usuwa klocek z planszy.
    zapis_kolumn[kor2]++; // Zapisuje, że ta kolumna została zmodyfikowana.
    
    if (kor1 > 0 && temp_cel == temp_plansza[kor1 - 1][kor2]) // Jeśli jest taki sam klocek wyżej.
    {
        usuwanie(kor1 - 1, kor2, temp_plansza, zapis_kolumn);
    }
    if (kor2 > 0 && temp_cel == temp_plansza[kor1][kor2 - 1]) // Analogicznie po lewej.
    {
        usuwanie(kor1, kor2 - 1, temp_plansza, zapis_kolumn);
    }
    if (kor2 + 1 < KOLUMNY && temp_cel == temp_plansza[kor1][kor2 + 1]) // Analogicznie po prawej.
    {
        usuwanie(kor1, kor2 + 1, temp_plansza, zapis_kolumn);
    }
    if (kor1 + 1 < WIERSZE && temp_cel == temp_plansza[kor1 + 1][kor2]) // Analogicznie poniżej.
    {
        usuwanie(kor1 + 1, kor2, temp_plansza, zapis_kolumn);
    }
}


/**
 Dostaje tablicę 'temp_plansza', która opisuje położenie klocków na planszy
 oraz tablicę 'zapis_kolumn', która trzyma informację o kolumnach,
 które zostały zmodyfikowane. Sprawdza zmodyfikowane kolumny, pod względem lewitujących klocków,
 a jeśli takowe znajdzie, to znosi je na dół.
*/
void zrzucanie(int temp_plansza[][KOLUMNY], int zapis_kolumn[KOLUMNY])
{
    if (WIERSZE > 1) // Nie ma czego zrzucać jeśli jest jeden wiersz.
    {
        for(int kolumna = 0; kolumna < KOLUMNY; kolumna++) // Rozpatruje każdą kolumnę.
        {
            if (zapis_kolumn[kolumna] > 0) // Kolumna została zmodyfikowana podczas usuwania.
            {
                int wiersz_main = WIERSZE - 1; // koordynata wiersza, który trzeba będzie zamienić.
                int wiersz_temp = WIERSZE - 2; // koordynata wiersza oznaczająca lewitujące klocki.
                while (wiersz_temp >= 0 && wiersz_main >= 0)
                {
                    // Szuka pierwszego pustego wiersza w kolumnie zmodyfikowanej.
                    while (wiersz_main > 0 && temp_plansza[wiersz_main][kolumna]!= '.')
                    {
                        wiersz_main--;
                    }
                    if (wiersz_main <= wiersz_temp)
                    {
                        wiersz_temp = wiersz_main - 1;
                    }
					// Przenosi klocka lewitującego na najniższe wolne miejsce.
                    if (wiersz_temp >= 0 && temp_plansza[wiersz_main][kolumna] == '.' &&
                        temp_plansza[wiersz_temp][kolumna] != '.')
                    {
                        temp_plansza[wiersz_main][kolumna] = temp_plansza[wiersz_temp][kolumna];
                        temp_plansza[wiersz_temp][kolumna] = '.';
                        wiersz_main--;
                    }
                    wiersz_temp--;
                }
            }
        }
    }
}


/**
 Dostaje tablicę 'temp_plansza', która opisuje położenie klocków na planszy
 oraz koordynatę sprawdzanej kolumny 'kol'. Sprawdza, czy kolumna 'kol' jest pusta.
 Jeśli tak to przesuwa najbliżej położoną niepustą kolumnę w jej miejsce, jeśli istnieje takowa.
 Powtarza tę czynność, póki nie przesunie wszystkich kolumn najbliżej jak się da.
*/
void przerzut(int temp_plansza[][KOLUMNY], int kol)
{
    int block = 0; // Mówi o tym, czy wolno powtarzać poszukiwania niepustej kolumny.
    if (kol < KOLUMNY - 1 && temp_plansza[WIERSZE - 1][kol] == '.')
    {
        int temp_kol = kol + 1; // Koordynata najbliższej niepustej kolumny.
        while (temp_kol < KOLUMNY && temp_plansza[WIERSZE - 1][temp_kol] == '.')
        {
            temp_kol++;
        }
        if (temp_kol != KOLUMNY) // Jeśli znaleziono niepustą kolumnę
        {
            int wier = 0; // Koordynata sprawdzanego wiersza.
            // Zamienia zawartość kolumny pustej na zawartość znalezionej kolumny.
            while (wier < WIERSZE && temp_plansza[WIERSZE - 1 - wier][temp_kol] != '.')
            {
                temp_plansza[WIERSZE - 1 - wier][kol] = temp_plansza[WIERSZE - 1 - wier][temp_kol];
                temp_plansza[WIERSZE - 1 - wier][temp_kol] = '.';
                wier++;
            }
        }
        else
        {
            block = 1;
        }
    }
    // Przepuszcza do kolejnej kolumny.
    if (block == 0 && kol < KOLUMNY - 1)
    {
        przerzut(temp_plansza, kol + 1);
    }
}


/**
 Dostaje zaktualizowaną wersję tablicy 'temp_plansza',
 która opisuje położenie klocków na planszy oraz rysuje tę planszę.
*/
void rysuj_plansze(int temp_plansza[][KOLUMNY])
{
    for (int wiersz = 0; wiersz < WIERSZE; wiersz++)
    {
        for (int kolumna = 0; kolumna < KOLUMNY; kolumna++)
        {
            putchar(temp_plansza[wiersz][kolumna]);
        }
        printf("\n");
    }
}


/**
 Dostaje koordynaty klocka zapisane na *argv* oraz długość *argv* reprezentowaną przez *argc*
 Obie te wielkości uzupełniane są przez osobę wywołującą program.
 Koordynaty klock zapisane na *argv*, opisują miejsce na planszy klocka,
 który ma zostać usunięty. Przeprowadza proces spełniania warunków,
 a na koniec wywołuje rysowanie zaaktualizowanej planszy.
*/
int main(int argc, char *argv[])
{
    int koorw = atoi(argv[argc - 2]); // Koordynata wiersza klocka do usunięcia.
    int koork = atoi(argv[argc - 1]); // Koordynata kolumny klocka do usunięcia.
    int pass = 0; // Daje dostęp do wprowadzania zmian na planszy.
    int *wpass = &pass;
    int plansza[WIERSZE][KOLUMNY]; // Trzyma informacje o położeniu klocków na planszy
    int kontrola_lotow[KOLUMNY]; // Trzyma informacje o zmodyfikowanych kolumnach.
    for (int i = 0; i < KOLUMNY; i++) // Wypełnia tablicę 'kontrola_lotow' zerami.
    {
        kontrola_lotow[i] = 0;
    }
    
    czytaj_plansze(plansza);
    sprawdz_klocek(koorw, koork, wpass, plansza);
    if (pass == 1)
    {
        usuwanie(koorw, koork, plansza, kontrola_lotow);
        zrzucanie(plansza, kontrola_lotow);
        przerzut(plansza, 0);
    }
    rysuj_plansze(plansza);
    return 0;
}