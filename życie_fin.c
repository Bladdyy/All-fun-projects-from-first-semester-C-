/**************************************************************************************************
                                     Autor: Juliusz Pawlus
 Program 'życie' symuluje życie kolejnych generacji komórek. Po wywołaniu musi otrzymać spis
 pierwszej żywej generacji w postaci pasów tekstu, które zaczynają się od '/'. Po '/' wpisywany
 jest numer wiersza żyjących w nim komórek, a potem po oddzielnych spacjach numery reprezentujące
 kolumnę, w której żyje dana komórka. Numery kolumn powinny być wpisywane w porządku rosnącym.
 Po zakończeniu wpisywania żywych komórek należy w nowej linijce wpisać '/' i zatwierdzić 'enterem'
 Program przyjmuje polecenia użytkownika. By zobaczyć następną generację należy nacisnąć 'enter'.
 Można też zobaczyć dowolną kolejną generację, wystarczy wpisać jedną liczbę naturalną,
 która mówi o ile generacji chcemy przeskoczyć. By zobaczyć spis aktualnie żyjących komórek
 należy wpisać '0'. Przed każdym poleceniem wypisuje się okno o wymiarach makr WIERSZE i KOLUMNY
 obrazujące część planszy, na której żyją komórki. Można zmieniać widoczny obszar zmieniając
 koordynaty lewego górnego rogu okna poprzez wpisanie dwóch liczb całkowitych oddzielonych spacją.
 Koordynaty te domyślnie ustawione są na pozycję 1 1. By zakończyć pracę programu należy
 wpisać '.'. Każdą komendę należy potwierdzać 'enterem'. Wartości makr 'WIERSZE' ORAZ 'KOLUMNY'
 ustawione są domyślnie na 22 oraz 80 i mogą być modyfikowane podczas wywoływania programu.
**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 Liczba wierszy okna.
*/
#ifndef WIERSZE
#define WIERSZE 22
#endif

/**
 Liczba kolumn okna.
*/
#ifndef KOLUMNY
#define KOLUMNY 80
#endif


/**
 Tworzy typ list, dzięki którym zapisywane są wartości wiersza oraz kolumny danego elementu.
 Trzyma też on również informację o następnej komórce na liście.
*/
typedef struct Tlista
{
    int wiersz;
    int kolumna;
    struct Tlista *nast;
} Tlista;


/**
 Tworzy typ list, dzięki którym zapisywane są wartości wiersza oraz kolumny danego elementu.
 Trzyma on również informację o tym jaki wiersz jest kolejny (rosnąco)
 oraz o następnym elemencie, który jest w tym samym wierszu .
*/
typedef struct Wlista
{
    int wiersz;
    int kolumna;
    struct Wlista *nast_wiersz;
    struct Wlista *nast_kol;
} Wlista;


/**
 Czyta dane startowe w postaci liczb oraz '/' i oddaje listę z
 żywymi komórkami oraz maksymalne i minimalne wartości wierszy i kolumn.

 Dostaje wskaźnik do listy 'alive', która trzyma informacje o żywych komórkach.
 Dostaje też wskaźniki 'maxw', 'minw', 'maxk' oraz 'mink', które kolejno trzymają informacje o
 maskymalnym numerze wiersza, minimalnym numerze wiersza oraz maksymalnym numerze kolumny i
 minimalnym numerze kolumny.
 Dostaje też wskaźnik 'alldead', który mówi o tym, że wszystkie komórki nie żyją.
*/
void czytaj_dane_start(Tlista **alive, int *maxw, int *minw, int *maxk, int *mink, bool *alldead)
{
    bool stop = true; // Zatrzymuje pętlę, jeśli zostaną wczytane wszystkie dane początkowe.
    Tlista *element = malloc(sizeof(Tlista)); // Pierwszy element na liście żywych komórek.
    *alive = element; // Zapamiętuje gdzie zaczyna się lista żywych komórek.
    Tlista *nowy_el; // Trzyma informacje o nowo pojawiających się elementach.
    Tlista *pom = element; // Pomaga uwolnić element.
    bool pierwsza_iteracja_w = true; // Mówi, czy to pierwsza zmiana zmiennych wiersza.
    bool pierwsza_iteracja_k = true; // Mówi, czy to pierwsza zmiana zmiennych kolumny.
    int wiersz = 0; // Numer danego wiesza.
    while (stop)
    {
        getchar();
        int znak = getchar(); // Sczytuje znak po '/'.
        if (znak != 10) // Jeśli znak to nie 'enter'.
        {
            int uj = 1; // Trzyma informacje o tym, czy liczba jest parzysta, czy ujemna.
            if (znak == '-')
            {
                znak = getchar();
                uj = -1;
            }
            wiersz = 0;
            int liczby = znak; // Zapisuje kolejne cyfry wiersza.
            while (liczby != ' ')
            {
                if (liczby >= '0' && liczby <= '9')
                {
                    wiersz = wiersz * 10 + (liczby - '0');
                }
                liczby = getchar();
            }
            wiersz = uj * wiersz;
            if (pierwsza_iteracja_w) // Jeśli pierwszy raz przeczytał liczbę wiersza.
            {
                *minw = wiersz;
                pierwsza_iteracja_w = false;
            }
            liczby = getchar();
            int aktualna_kol = 0; // Trzyma informację o liczbie aktualnej kolumny.
            uj = 1;
            while (liczby != 10) // Dopóki znak nie jest enterem.
            {
                if (liczby == '-')
                {
                    liczby = getchar();
                    uj = -1;
                }
                if (liczby >= '0' && liczby <= '9')
                {
                    aktualna_kol = aktualna_kol * 10 + (liczby - '0');
                }
                else
                {
                aktualna_kol = aktualna_kol * uj;
                if (pierwsza_iteracja_k) // Jeśli pierwszy raz przeczytał liczbę wiersza.
                    {
                        *mink = aktualna_kol; // Trzyma informację o najmniejszej kolumnie.
                        *maxk = aktualna_kol; // Trzyma informację o największej kolumnie.
                        pierwsza_iteracja_k = false;
                    }
                    if (*mink > aktualna_kol)
                    {
                        *mink = aktualna_kol;
                    }
                    else if (*maxk < aktualna_kol)
                    {
                        *maxk = aktualna_kol;
                    }
                    element->wiersz = wiersz;
                    element->kolumna = aktualna_kol;
                    nowy_el = malloc(sizeof(Tlista)); // Tworzy nowy element ma liście komórek.
                    element->nast = nowy_el;
                    element = nowy_el;
                    aktualna_kol = 0;
                    uj = 1;
                }
                liczby = getchar(); // Sczytuje kolejne znaki.
            }
            /*
             Powtarzam ten fragment raz poza pętlą, by sprawdzić informacje na temat
             kolumny po której jest 'enter'.
            */
            aktualna_kol = aktualna_kol * uj;
            if (pierwsza_iteracja_k)
            {
                *mink = aktualna_kol;
                *maxk = aktualna_kol;
                pierwsza_iteracja_k = false;
            }
            if (*mink > aktualna_kol)
            {
                *mink = aktualna_kol;
            }
            else if (*maxk < aktualna_kol)
            {
                *maxk = aktualna_kol;
            }
            element->wiersz = wiersz;
            element->kolumna = aktualna_kol;
            nowy_el = malloc(sizeof(Tlista));
            pom = element;
            element->nast = nowy_el;
            element = nowy_el;
        }
        else
        {
            if (pierwsza_iteracja_w) // Nie ma ani jednej żywej komórki.
            {
                *alldead = true;
            }
            stop = false; // Jeśli po '/' jest enter to kończy sczytywać.
        }
    }
    if (*alldead == false) // Jeśli żyje choć jedna komórka.
    {
        *maxw = wiersz; // Zapisuje informację o największym wierszu jaki był.
        free(element); // Uwalnia pierwszy pusty element, który był atrapą.
    }
    pom->nast = NULL;
}


/**
 Czyta aktualne polecenie, poczym aktualizuje odpowiadające temu poleceniu wskaźniki.

 Dostaje wskaźnik 'powtorzenia', który zapisuje ilość generacji komórek do przetworzenia.
 Dostaje też wskaźnik 'koniec', który trzyma informacje o tym, czy zakończyć program.
 Dostaje wskaźniki 'wiersz_okna' i 'kolumna_okna' zapisują informacje o koordynatach okna.
 Dostaje wskaźnik 'pokaz_generacje' zapisuje informację o tym,
 czy podać spis aktualnie żywych komórek.
*/
void czytaj_polecenia(int *powtorzenia, bool *koniec, int *wiersz_okna, int *kolumna_okna,
    bool *pokaz_generacje)
{
    int znak = getchar(); // Sczytuje znak.
    if (znak == 10) // Jeśli enter.
    {
        *powtorzenia = 1; // Wysyła informację o przejściu jednej generacji.
    }
    else if (znak == '.')
    {
        *koniec = false; // Wysyła informację o zakończeniu programu.
    }
    else if (znak >= '0' && znak <='9')
    {
        int kolejny_znak = getchar(); // Czyta znaki.
        int akt_num = znak - '0'; // Trzyma informację o aktualnej liczbie.
        while (kolejny_znak >= '0' && kolejny_znak <= '9')
        {
            akt_num = akt_num * 10 + (kolejny_znak - '0');
            kolejny_znak = getchar();
        }
        if (kolejny_znak == ' ') // Jeśli jest druga liczba.
        {
            *wiersz_okna = akt_num; // Zapisuje koordynatę wiersza.
            akt_num = 0;
            kolejny_znak = getchar();
            int uj = 1; // Trzyma informację o tym, czy liczba jest parzysta, czy ujemna.
            if (kolejny_znak == '-')
            {
                uj = -1;
                kolejny_znak = getchar();
            }
            while (kolejny_znak >= '0' && kolejny_znak <= '9')
            {
                akt_num = akt_num * 10 + (kolejny_znak - '0');
                kolejny_znak = getchar();
            }
            akt_num = akt_num * uj;
            *kolumna_okna = akt_num; // Zapisuje koordynatę kolumny.
        }
        else // Jeśli jest jedna liczba.
        {
            if (akt_num == 0)
            {
                *pokaz_generacje = true;
            }
            else
            {
                *powtorzenia = akt_num;
            }
        }
    }
    else if (znak == '-') // Jeśli liczba zaczyna się od minusa.
    {
        int kolejny_znak = getchar(); // Sczytuje znaki.
        int akt_num = 0; // Trzyma informację o aktualnej liczbie.
        while (kolejny_znak >= '0' && kolejny_znak <= '9')
        {
            akt_num = akt_num * 10 + (kolejny_znak - '0');
            kolejny_znak = getchar();
        }
        *wiersz_okna = (-1) * akt_num; // Zapisuje koordynatę wiersza.
        akt_num = 0;
        kolejny_znak = getchar();
        int uj = 1; // Trzyma informację o tym, czy liczba jest parzysta, czy ujemna.
        if (kolejny_znak == '-')
        {
            uj = -1;
            kolejny_znak = getchar();
        }
        while (kolejny_znak >= '0' && kolejny_znak <= '9')
        {
            akt_num = akt_num * 10 + (kolejny_znak - '0');
            kolejny_znak = getchar();
        }
        akt_num = akt_num * uj;
        *kolumna_okna = akt_num; // Zapisuje koordynatę kolumny.
    }
}


/**
 Sprawdza ilu komórka ma żywych sąsiadów oraz, czy żyje i zwraca te informacje.

 Dostaje liczby 'cell_wiersz' oraz 'cell_kolumna', które określają koordynaty komórki,
 którą aktualnie sprawdzamy.
 Dostaje wskaźniki 'wiersze1', 'wiersze2', 'wiersze3', 'wiersze4',
 które wskazują cztery częsci planszy, na której zapisane są komórki.
 Dostaje liczby 'minw' oraz 'mink', czyli koordynaty punktu środkowego, czyli takiego,
 w którym plansza łączy się w całość.
 Dostaje wskaźnik 'sasiedzi', który zapisuje liczbę żywych sąsiadów danej komórki.
 Dostaje wskaźnik 'zywa', który trzyma informacje o tym, czy sprawdzana komórka żyje, czy nie.
*/
void ile_sasiadow(int cell_wiersz, int cell_kolumna, int **wiersze1, int **wiersze2,
    int **wiersze3, int **wiersze4, int minw, int mink, int *sasiedzi, int *zywa)
{
    if ((cell_wiersz) < minw) // Jeśli koordynata wiersza jest mniejsza, niż środek plansz.
    {
        if ((cell_kolumna) < mink) // Jeśli koordynata kolumny jest mniejsza, niż środek plansz.
        {
            // Komórka leży na planszy 4 i to czy jest żywa jest tam zapisane.
            *zywa = wiersze4[minw - cell_wiersz - 1][mink - cell_kolumna- 1];
        }
        else
        {
            // Komórka leży na planszy 3 i to czy jest żywa jest tam zapisane.
            *zywa = wiersze3[minw - cell_wiersz - 1][cell_kolumna - mink];
        }
    }
    else
    {
        if (cell_kolumna < mink) // Jeśli koordynata kolumny jest mniejsza, niż środek plansz.
        {
            // Komórka leży na planszy 2 i to czy jest żywa jest tam zapisane.
            *zywa = wiersze2[cell_wiersz - minw][mink - cell_kolumna - 1];
        }
        else
        {
            // Komórka leży na planszy 1 i to czy jest żywa jest tam zapisane.
            *zywa = wiersze1[cell_wiersz - minw][cell_kolumna - mink];
        }
    }
    int counter = 0; // Liczy żywych sąsiadów.

    // Sprawdza komórkę w lewym górnym rogu.
    if ((cell_wiersz - 1) < minw) // Koordynata komórki w lewym górnym jest mniejsza od minw.
    {
        if ((cell_kolumna - 1) < mink) // Koordynata komórki w lewym górnym jest mniejsza od mink.
        {
            if (wiersze4[minw - (cell_wiersz - 1) - 1][mink - (cell_kolumna - 1) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - (cell_wiersz - 1) - 1][(cell_kolumna - 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna - 1 < mink) // Koordynata komórki w lewym górnym jest mniejsza od mink.
        {
            if (wiersze2[(cell_wiersz - 1) - minw][mink - (cell_kolumna - 1) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[(cell_wiersz - 1) - minw][(cell_kolumna - 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę nad aktualną komórką.
    if ((cell_wiersz - 1) < minw) // Ten i pozostałe warunki analogicznie jak wyżej.
    {
        if ((cell_kolumna) < mink)
        {
            if (wiersze4[minw - (cell_wiersz - 1) - 1][mink - (cell_kolumna) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - (cell_wiersz - 1) - 1][(cell_kolumna) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna< mink)
        {
            if (wiersze2[(cell_wiersz - 1) - minw][mink - (cell_kolumna) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[(cell_wiersz - 1) - minw][(cell_kolumna) - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę w prawym górnym rogu.
    if ((cell_wiersz - 1) < minw)
    {
        if ((cell_kolumna + 1) < mink)
        {
            if (wiersze4[minw - (cell_wiersz - 1) - 1][mink - (cell_kolumna + 1) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - (cell_wiersz - 1) - 1][(cell_kolumna + 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna + 1 < mink)
        {
            if (wiersze2[(cell_wiersz - 1) - minw][mink - (cell_kolumna + 1) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[(cell_wiersz - 1) - minw][(cell_kolumna + 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę z lewej strony.
    if ((cell_wiersz) < minw)
    {
        if ((cell_kolumna - 1) < mink)
        {
            if (wiersze4[minw - cell_wiersz - 1][mink - (cell_kolumna - 1) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - cell_wiersz - 1][(cell_kolumna - 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna - 1 < mink)
        {
            if (wiersze2[cell_wiersz - minw][mink - (cell_kolumna - 1) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[cell_wiersz - minw][(cell_kolumna - 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę z prawej strony.
    if (cell_wiersz < minw)
    {
        if ((cell_kolumna + 1) < mink)
        {
            if (wiersze4[minw - cell_wiersz - 1][mink - (cell_kolumna + 1) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - cell_wiersz - 1][(cell_kolumna + 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna + 1 < mink)
        {
            if (wiersze2[cell_wiersz - minw][mink - (cell_kolumna + 1) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[cell_wiersz - minw][(cell_kolumna + 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę w lewym dolnym rogu.
    if ((cell_wiersz + 1) < minw)
    {
        if ((cell_kolumna - 1) < mink)
        {
            if (wiersze4[minw - (cell_wiersz + 1) - 1][mink - (cell_kolumna - 1) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - (cell_wiersz + 1) - 1][(cell_kolumna - 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna - 1 < mink)
        {
            if (wiersze2[(cell_wiersz + 1) - minw][mink - (cell_kolumna - 1) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[(cell_wiersz + 1) - minw][(cell_kolumna - 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę w poniżej.
    if ((cell_wiersz + 1) < minw)
    {
        if ((cell_kolumna) < mink)
        {
            if (wiersze4[minw - (cell_wiersz + 1) - 1][mink - cell_kolumna - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - (cell_wiersz + 1) - 1][cell_kolumna - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna < mink)
        {
            if (wiersze2[(cell_wiersz + 1) - minw][mink - cell_kolumna - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[(cell_wiersz + 1) - minw][cell_kolumna - mink]  == 1)
            {
                counter++;
            }
        }
    }

    // Sprawdza komórkę w prawym dolnym rogu.
    if ((cell_wiersz + 1) < minw)
    {
        if ((cell_kolumna + 1) < mink)
        {
            if (wiersze4[minw - (cell_wiersz + 1) - 1][mink - (cell_kolumna + 1) - 1] == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze3[minw - (cell_wiersz + 1) - 1][(cell_kolumna + 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    else
    {
        if (cell_kolumna + 1 < mink)
        {
            if (wiersze2[(cell_wiersz + 1) - minw][mink - (cell_kolumna + 1) - 1]  == 1)
            {
                counter++;
            }
        }
        else
        {
            if (wiersze1[(cell_wiersz + 1) - minw][(cell_kolumna + 1) - mink]  == 1)
            {
                counter++;
            }
        }
    }
    *sasiedzi = counter; // Zapisuje informację o ilości sąsiadów.
}


/**
 Sprawdza czy komórki z listy aktualnie żyjących komórek oraz ich sąsiedzi żyją w następnej
 generacji. Oddaje liste z nową generacją albo informuje, że wszystkie komórki są martwe.

 Dostaje wskaźnik do listy 'alive', która trzyma informacje o aktualnie żywych komórkach.
 Dostaje wskaźniki 'wiersze1', 'wiersze2', 'wiersze3', 'wiersze4', które wskazują
 cztery częsci planszy, na której zapisane są komórki.
 Dostaje liczby 'minw' oraz 'mink', czyli koordynaty punktu środkowego, czyli takiego,
 w którym plansza łączy się w całość.
 Dostaje wskaźniki 'newgen' oraz 'alldead', które kolejno trzymają informację,
 o komórkach z kolejnej generacji oraz o tym, czy zmarły wszystkie komórki.
*/
void next_gen(Tlista **alive, int **wiersze1, int **wiersze2, int **wiersze3, int **wiersze4,
    int mink, int minw, Tlista **new_gen, bool *alldead)
{
    Tlista *past_alive = *alive; // Pierwszy element żywych z listy żywych komórek.
    Tlista *cell = malloc(sizeof(Tlista)); // Pierwszy element listy komórek nowej generacji.
    Tlista *new_alive = cell; // Wskaźnik na pierwszy element z listy komórek nowej generacji.
    Tlista *pom = new_alive; // Wskaźnik pomagający tworzący nowe komórki.
    int sasiedzi = 0; // Ilość sąsiadów podanej komórki.
    int *wsasiedzi = &sasiedzi; // Wskaźnik na liczbę sąsiadów podanej komórki.
    int dead; // Trzyma informację o tym, czy komórka żyje, czy nie.
    int *wdead = &dead; // Wskaźnik na informację o tym, czy komórka żyje.
    *alldead = true;
    // Sprawdza czy każda komórka oraz jej sąsiedzi będą żyć w następnej generacji.
    while (past_alive != NULL)
    {
        // Sprawdza, czy aktualna komórka żyje.
        ile_sasiadow(past_alive->wiersz, past_alive->kolumna,
            wiersze1, wiersze2, wiersze3, wiersze4,	minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 2 || sasiedzi == 3) // Jeśli ma dwóch lub trzech sąsiadów, to będzie żyć.
        {
            pom = malloc(sizeof(Tlista)); // Tworzy nowy element na liście nowej generacji.
            pom->wiersz = past_alive->wiersz;
            pom->kolumna = past_alive->kolumna;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false; // Ktoś będzie żył w nowej generacji.
        }

        // Sprawdza, czy sąsiad w lewym dolnym rogu będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz + 1, past_alive->kolumna - 1,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0) // Jeśli ma 3 sąsiadów i jest martwa, to będzie żyć.
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz + 1;
            pom->kolumna = past_alive->kolumna - 1;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy sąsiad poniżej będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz + 1, past_alive->kolumna,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0) // Analogicznie jak wyżej.
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz + 1;
            pom->kolumna = past_alive->kolumna;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy sąsiad w prawym dolnym rogu będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz + 1, past_alive->kolumna + 1,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0)
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz + 1;
            pom->kolumna = past_alive->kolumna + 1;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy sąsiad po lewej będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz, past_alive->kolumna - 1,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0)
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz;
            pom->kolumna = past_alive->kolumna - 1;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy sąsiad po prawej będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz, past_alive->kolumna + 1,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0)
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz;
            pom->kolumna = past_alive->kolumna + 1;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy sąsiad w lewym dolnym górnym będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz - 1, past_alive->kolumna - 1,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0)
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz - 1;
            pom->kolumna = past_alive->kolumna - 1;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy powyżej będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz - 1, past_alive->kolumna,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0)
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz - 1;
            pom->kolumna = past_alive->kolumna;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }

        // Sprawdza, czy sąsiad w prawym górnym rogu będzie żyć w nowej generacji.
        ile_sasiadow(past_alive->wiersz - 1, past_alive->kolumna + 1,
            wiersze1, wiersze2, wiersze3, wiersze4, minw, mink, wsasiedzi, wdead);
        if (sasiedzi == 3 && dead == 0)
        {
            pom = malloc(sizeof(Tlista));
            pom->wiersz = past_alive->wiersz - 1;
            pom->kolumna = past_alive->kolumna + 1;
            pom->nast = NULL;
            cell->nast = pom;
            cell = pom;
            sasiedzi = 0;
            *alldead = false;
        }
        past_alive = past_alive->nast;
    }
    pom = new_alive; // Zapisuje wskaźnik na pierwszy element, który jest atrapą.
    new_alive = new_alive->nast;
    free(pom);
    *new_gen = new_alive; // Zapisuje nową generację na liście.
}


/**
 Czyści planszę z poprzednej generacji oraz uwalnia dane opisujące starą generację.
 Zapisuje na planszy nową generację oraz dopilnowuje, by w spisie nowej generacji nie było
 duplikatów. Kontroluje, czy została osiągnięta najmniejsza/największa wartość kolumny/wiersza
 w historii. Jeśli tak, zapisuje tę informację oraz poszerza odpowiednie plansze.

 Dostaje wskaźnik do listy 'alive', która trzyma informacje o aktualnie żywych komórkach.
 Dostaje wskaźniki 'wiersze1', 'wiersze2', 'wiersze3', 'wiersze4', które wskazują
 cztery częsci planszy, na której zapisane są komórki.
 Dostaje liczby 'minw' oraz 'mink', czyli koordynaty punktu środkowego, czyli takiego,
 w którym plansza łączy się w całość.
 Dostaje wskaźnik 'newgen' który trzyma listę z informacjami, o komórkach z nowej generacji.
 Dostaje wskaźniki 'temp_min_k', 'temp_min_w', 'temp_max_k' oraz 'temp_max_w', które kolejno
 trzymają informację o najmniejszej koordynacie, na której wystąpiła żywa komórka w kolumnie i
 wierszu oraz największej koodynacie, na której wystąpiła w kolumnie i wierszu.
*/
void update_plansze(Tlista **alive, int ***wiersze1, int ***wiersze2, int ***wiersze3,
    int ***wiersze4, int mink, int minw, Tlista *new_gen, int *temp_min_k, int *temp_min_w,
    int *temp_max_k, int *temp_max_w)
{
    Tlista *old_gen = *alive; // Początek listy z żywymi komórkami.
    Tlista *akt_gen = new_gen; // Początek listy z komórkami z nowej generacji.
    Tlista *pom; // Pomocniczy element list.
    bool chan_min_k = false; // Czy minimalny próg kolumny został zmieniony.
    bool chan_max_k = false; // Czy maksymalny próg kolumny został zmieniony.
    bool chan_min_w = false; // Czy minimalny próg wiersza został zmieniony.
    bool chan_max_w = false; // Czy maksymalny próg wiersza został zmieniony.
    while (old_gen != NULL) // Sprawdza wszystkie komórki poprzedniej generacji.
    {
        if ((old_gen->wiersz) < minw) // Jeśli koordynata wiersza jest mniejsza od minw.
        {
            if ((old_gen->kolumna) < mink) // Jeśli koordynata kolumny jest mniejsza od mink.
            {
                // Czyści komórkę z planszy czwartej.
                (*wiersze4)[minw - old_gen->wiersz - 1][mink - old_gen->kolumna - 1] = 0;
            }
            else
            {
                // Czyści komórkę z planszy trzeciej.
                (*wiersze3)[minw - old_gen->wiersz - 1][old_gen->kolumna - mink] = 0;
            }
        }
        else
        {
            if (old_gen->kolumna < mink) // Jeśli koordynata kolumny jest mniejsza od mink.
            {
                // Czyści komórkę z planszy drugiej.
                (*wiersze2)[old_gen->wiersz - minw][mink - old_gen->kolumna - 1] = 0;
            }
            else
            {
                // Czyści komórkę z planszy pierwszej.
                (*wiersze1)[old_gen->wiersz - minw][old_gen->kolumna - mink] = 0;
            }
        }
        pom = old_gen; // Aktualna komórka.
        old_gen = old_gen->nast;
        free(pom);
    }
    Tlista *poprz = NULL; // Wskaźnik na poprzednią komórkę.
    while (akt_gen != NULL)
    {
        if (akt_gen->wiersz - 2 < *temp_min_w) // Ma najmniejszą koordynatę wiersza w historii.
        {
            chan_min_w = true;
        }
        else if (akt_gen->wiersz + 2 > *temp_max_w) // Ma największą koordynatę wiersza w historii.
        {
            chan_max_w = true;
        }
        if (akt_gen->kolumna - 2 < *temp_min_k) // Ma najmniejszą koordynatę kolumny w historii.
        {
            chan_min_k = true;
        }
        else if (akt_gen->kolumna + 2 > *temp_max_k) // Ma największą koordynatę kolumny w historii
        {
            chan_max_k = true;
        }
        if ((akt_gen->wiersz) < minw) // Jeśli koordynata wiersza jest mniejsza od minw.
        {
            if ((akt_gen->kolumna) < mink) // Jeśli koordynata kolumny jest mniejsza od mink.
            {
                if ((*wiersze4)[minw - akt_gen->wiersz - 1][mink - akt_gen->kolumna - 1] == 1)
                {
                    poprz->nast = akt_gen->nast;
                    free(akt_gen); // Kasuje komórki, które są już zapisane w nowej generacji.
                    akt_gen = poprz;
                }
                else // Komórka wystąpiła pierwszy raz, więc zapisujemy ją na planszy.
                {
                    (*wiersze4)[minw - akt_gen->wiersz - 1][mink - akt_gen->kolumna - 1] = 1;
                }
            }
            else
            {
                if ((*wiersze3)[minw - akt_gen->wiersz - 1][akt_gen->kolumna - mink] == 1)
                {
                    poprz->nast = akt_gen->nast;
                    free(akt_gen); // Kasuje komórki, które są już zapisane w nowej generacji.
                    akt_gen = poprz;
                }
                else // Komórka wystąpiła pierwszy raz, więc zapisujemy ją na planszy.
                {
                    (*wiersze3)[minw - akt_gen->wiersz - 1][akt_gen->kolumna - mink] = 1;
                }
            }
        }
        else
        {
            if (akt_gen->kolumna < mink) // Jeśli koordynata kolumny jest mniejsza od mink.
            {
                if ((*wiersze2)[akt_gen->wiersz - minw][mink - akt_gen->kolumna - 1] == 1)
                {
                    poprz->nast = akt_gen->nast;
                    free(akt_gen); // Kasuje komórki, które są już zapisane w nowej generacji.
                    akt_gen = poprz;
                }
                else // Komórka wystąpiła pierwszy raz, więc zapisujemy ją na planszy.
                {
                    (*wiersze2)[akt_gen->wiersz - minw][mink - akt_gen->kolumna - 1] = 1;
                }
            }
            else
            {
                if ((*wiersze1)[akt_gen->wiersz - minw][akt_gen->kolumna - mink] == 1)
                {
                    poprz->nast = akt_gen->nast;
                    free(akt_gen); // Kasuje komórki, które są już zapisane w nowej generacji.
                    akt_gen = poprz;
                }
                else // Komórka wystąpiła pierwszy raz, więc zapisujemy ją na planszy.
                {
                    (*wiersze1)[akt_gen->wiersz - minw][akt_gen->kolumna - mink] = 1;
                }
            }
        }
        poprz = akt_gen;
        akt_gen = akt_gen->nast;
    }
    *alive = new_gen;
    if (chan_min_w) // Jeśli jakaś komórka przekroczyła próg najmniejszego wiersza w historii.
    {
        *temp_min_w = *temp_min_w - 1;
    }

    if (chan_max_w) // Jeśli jakaś komórka przekroczyła próg największego wiersza w historii.
    {
        *temp_max_w = *temp_max_w + 1;
    }

    if (chan_min_k) // Jeśli jakaś komórka przekroczyła próg najmniejszej kolumny w historii.
    {
        *temp_min_k = *temp_min_k - 1;
    }

    if (chan_max_k) // Jeśli jakaś komórka przekroczyła próg największej kolumny w historii.
    {
        *temp_max_k = *temp_max_k + 1;
    }

    // Poszerza planszę 3 oraz 4 o dodatkowy wiersz.
    if (chan_min_w) // Jeśli jakaś komórka przekroczyła próg najmniejszego wiersza w historii.
    {
        (*wiersze3) = realloc(*wiersze3,
            (long unsigned int)((int)(sizeof(int *)) * (minw - *temp_min_w)));
        (*wiersze4) = realloc(*wiersze4,
            (long unsigned int)((int)(sizeof(int *)) * (minw - *temp_min_w)));
        (*wiersze3)[minw - *temp_min_w - 1] =
            calloc((long unsigned int)(*temp_max_k - mink + 1), sizeof(int));
        (*wiersze4)[minw - *temp_min_w - 1] =
            calloc((long unsigned int)(mink - *temp_min_k), sizeof(int));
    }

    // Poszerza planszę 1 oraz 2 o dodatkowy wiersz.
    if (chan_max_w) // Jeśli jakaś komórka przekroczyła próg największego wiersza w historii.
    {
        (*wiersze1) = realloc(*wiersze1,
            (long unsigned int)((int)(sizeof(int *)) * (*temp_max_w - minw + 1)));
        (*wiersze2) = realloc(*wiersze2,
            (long unsigned int)((int)(sizeof(int *)) * (*temp_max_w - minw + 1)));
        (*wiersze1)[*temp_max_w - minw] =
            calloc((long unsigned int)(*temp_max_k - mink + 1), sizeof(int));
        (*wiersze2)[*temp_max_w - minw] =
            calloc((long unsigned int)(mink - *temp_min_k), sizeof(int));
    }

    // Poszerza planszę 2 oraz 4 o dodatkową kolumnę.
    if (chan_min_k) // Jeśli jakaś komórka przekroczyła próg najmniejszej kolumny w historii.
    {
        for (int i = 0; i < (*temp_max_w - minw + 1); i++)
        {
            (*wiersze2)[i] = realloc((*wiersze2)[i],
                (long unsigned int)((int)(sizeof(int)) * (mink - *temp_min_k)));
            (*wiersze2)[i][mink - *temp_min_k - 1] = 0;
        }
        for (int i = 0; i < (minw - *temp_min_w); i++)
        {
            (*wiersze4)[i] = realloc((*wiersze4)[i],
                (long unsigned int)((int)(sizeof(int)) * (mink - *temp_min_k)));
            (*wiersze4)[i][mink - *temp_min_k - 1] = 0;
        }
    }

    // Poszerza planszę 1 oraz 3 o dodatkową kolumnę.
    if (chan_max_k) // Jeśli jakaś komórka przekroczyła próg największej kolumny w historii.
    {
        for (int i = 0; i < (*temp_max_w - minw + 1); i++)
        {
            (*wiersze1)[i] = realloc((*wiersze1)[i],
                (long unsigned int)((int)(sizeof(int)) * (*temp_max_k - mink + 1)));
            (*wiersze1)[i][*temp_max_k - mink] = 0;;
        }
        for (int i = 0; i < (minw - *temp_min_w); i++)
        {
            (*wiersze3)[i] = realloc((*wiersze3)[i],
                (long unsigned int)((int)(sizeof(int)) * (*temp_max_k - mink + 1)));
            (*wiersze3)[i][*temp_max_k - mink] = 0;
        }
    }
}


/**
 Rysuje planszę na podstawie poniższych danych.

 Dostaje liczby 'kor_wier' oraz 'kor_kol', które opisują koordynaty lewego górnego rogu okna.
 Dostaje wskaźniki 'wiersze1', 'wiersze2', 'wiersze3', 'wiersze4', które wskazują
 cztery częsci planszy, na której zapisane są komórki.
 Dostaje liczby 'minw' oraz 'mink', czyli koordynaty punktu środkowego,
 czyli takiego, w którym plansza łączy się w całość.
 Dostaje wskaźniki 'temp_min_k', 'temp_min_w', 'temp_max_k' oraz 'temp_max_w', które kolejno
 trzymają informację o najmniejszej koordynacie, na której wystąpiła żywa komórka w kolumnie i
 wierszu oraz największej koodynacie, na której wystąpiła w kolumnie i wierszu.
*/
void rysuj_plansze(int kor_wier, int kor_kol, int **wiersze1, int **wiersze2, int **wiersze3,
    int **wiersze4, int min_const_kol, int min_const_wier, int temp_min_k, int temp_min_w,
    int temp_max_k, int temp_max_w)
{
    for (int i = kor_wier; i < WIERSZE + kor_wier; i++)
    {
        if (i >= temp_min_w && i < min_const_wier) // Jeśli wiersz 'i' jest w zakresie.
        {
            for (int x = kor_kol; x < KOLUMNY + kor_kol; x++)
            {
                if (x >= temp_min_k && x < min_const_kol) // Jeśli kolumna 'x' jest w zakresie.
                {
                    // Jeśli na danym miejscu na planszy 4 jest żywa komórka.
                    if (wiersze4[min_const_wier - i - 1][min_const_kol - x - 1] == 1)
                    {
                        printf("0");
                    }
                    else
                    {
                        printf(".");
                    }
                }
                else if (x >= min_const_kol && x <= temp_max_k) // Jeśli kolumna x jest w zakresie.
                {
                    // Jeśli na danym miejscu na planszy 3 jest żywa komórka.
                    if (wiersze3[min_const_wier - i - 1][x - min_const_kol] == 1)
                    {
                        printf("0");
                    }
                    else
                    {
                        printf(".");
                    }
                }
                else // Jeśli kolumna 'x' jest poza zakresem planszy.
                {
                    printf(".");
                }
            }
        }
        else if (i >= min_const_wier && i <= temp_max_w) // Jeśli wiersz 'i' jest w zakresie.
        {
            for (int x = kor_kol; x < KOLUMNY + kor_kol; x++)
            {
                if (x >= temp_min_k && x < min_const_kol) // Jeśli kolumna 'x' jest w zakresie.
                {
                    // Jeśli na danym miejscu na planszy 2 jest żywa komórka.
                    if (wiersze2[i - min_const_wier][min_const_kol - x - 1] == 1)
                    {
                        printf("0");
                    }
                    else
                    {
                        printf(".");
                    }
                }
                else if (x >= min_const_kol && x <= temp_max_k) // Jeśli kolumna x jest w zakresie.
                {
                    // Jeśli na danym miejscu na planszy 1 jest żywa komórka.
                    if (wiersze1[i - min_const_wier][x - min_const_kol] == 1)
                    {
                        printf("0");
                    }
                    else
                    {
                        printf(".");
                    }
                }
                else // Jeśli kolumna 'x' jest poza zakresem planszy.
                {
                    printf(".");
                }
            }
        }
        else // Jeśli wiersz 'i' jest poza zakresem planszy.
        {
            for (int x = 0; x < KOLUMNY; x++)
            {
                printf(".");
            }
        }
        printf("\n");
    }
    for (int x = 0; x < KOLUMNY; x++) // Rysuje ramkę.
    {
        printf("=");
    }
    printf("\n");
}


/**
 Ustawia elementy w dobrej kolejności, poczym wypisuje wszystkie aktualnie żyjące komórki.

 Dostaje wskaźnik 'akt_gen', który wskazuje początek listy, z aktualnie żyjącą generacją.
*/
void gdzie_zywe(Tlista *akt_gen)
{
    Tlista *czytnik = akt_gen->nast; // Drugi element listy.
    Wlista *pom = malloc(sizeof(Wlista)); // Pierwszy element uporządkowanej listy.
    Wlista *atrapa = malloc(sizeof(Wlista)); // Atrapa wskazująca pierwszą listę.
    atrapa->nast_wiersz = pom;
    Wlista *poprz; // Element poprzedzający aktualny element.
    pom->wiersz = akt_gen->wiersz;
    pom->kolumna = akt_gen->kolumna;
    pom->nast_kol = NULL;
    pom->nast_wiersz = NULL;
    while (czytnik != NULL) // Przejeżdża przez każdy element listy;
    {
        poprz = atrapa;
        pom = atrapa->nast_wiersz;
        while (pom != NULL && pom->wiersz < czytnik->wiersz) // Dopóki 'pom' ma mniejszy wiersz.
        {
            pom = pom->nast_wiersz;
            poprz = poprz->nast_wiersz;
        }
        if (pom == NULL)
        {
            pom = malloc(sizeof(Wlista)); // Nowy element listy z największym numerem wiersza.
            pom->wiersz = czytnik->wiersz;
            pom->kolumna = czytnik->kolumna;
            pom->nast_kol = NULL;
            pom->nast_wiersz = NULL;
            poprz->nast_wiersz = pom;
        }
        else if (pom->wiersz == czytnik->wiersz) // Jeśli numer wiersza jest równy
        {
            if (pom->kolumna > czytnik->kolumna) // Jeśli kolumna jest mniejsza.
            {
                poprz->nast_wiersz = malloc(sizeof(Wlista)); // Podmienia najmniejszy element.
                poprz->nast_wiersz->wiersz = czytnik->wiersz;
                poprz->nast_wiersz->kolumna = czytnik->kolumna;
                poprz->nast_wiersz->nast_wiersz = pom->nast_wiersz;
                poprz->nast_wiersz->nast_kol = pom;
                pom->nast_wiersz = NULL;
            }
            else
            {
                poprz = pom;
                pom = pom->nast_kol;
                while (pom != NULL && pom->kolumna < czytnik->kolumna) // Aktualna kolumna mniejsza
                {
                    poprz = poprz->nast_kol;
                    pom = pom->nast_kol;
                }
                poprz->nast_kol = malloc(sizeof(Wlista)); // Dodaje element w poszczególne miejsce.
                poprz->nast_kol->wiersz = czytnik->wiersz;
                poprz->nast_kol->kolumna = czytnik->kolumna;
                if (pom == NULL)
                {
                    poprz->nast_kol->nast_kol = NULL;
                }
                else
                {
                    poprz->nast_kol->nast_kol = pom;
                }
            }
        }
        else // Jeśli istnieje większy wiersz, a równy nie.
        {
            poprz->nast_wiersz = malloc(sizeof(Wlista)); // Dodaje element z nowym wierszem.
            poprz->nast_wiersz->wiersz = czytnik->wiersz;
            poprz->nast_wiersz->kolumna = czytnik->kolumna;
            poprz->nast_wiersz->nast_wiersz = pom;
            poprz->nast_wiersz->nast_kol = NULL;
        }
        czytnik = czytnik->nast;
    }
    pom = atrapa;
    atrapa = atrapa->nast_wiersz;
    free(pom); // Uwalnia wskaźnik na pierwszy element uporządkowanej listy.
    while (atrapa != NULL)
    {
        pom = atrapa->nast_kol;
        printf("/%d", atrapa->wiersz); // Pisze wiersz elementów zaraz wypisywanych.
        printf(" %d", atrapa->kolumna); // Pisze numer pierwszej kolumny.
        while (pom != NULL)
        {
            printf(" %d", pom->kolumna); // Pisze numery kolejnych kolumn.
            poprz = pom;
            pom = pom->nast_kol;
            free(poprz); // Uwalnia element z danymi aktualnej komórki.
        }
        pom = atrapa;
        atrapa = atrapa->nast_wiersz;
        free(pom); // Uwalnia najmniejszy element w wierszu.
        printf("\n");
    }
    printf("/\n");
}


/**
 Przyjmuje dane początkowe i tworzy planszę. Przyjmuje i wykonuje polecenia.
*/
int main(void)
{
    int korw = 1; // Bazowa koordynata wiersza okna.
    int kork = 1; // Bazowa koordynata kolumny okna.
    int *wkorw = &korw; // Wskaźnik na bazową koordynatę wiersza okna.
    int *wkork = &kork; // Wskaźnik na bazową koordynatę kolumny okna.
    int pokolenia = 0; // Ilość kolejnych pokoleń do policzenia.
    int *wpokolenia = &pokolenia; // Wskaźnik na ilość kolejnych pokoleń do policzenia.
    int max_const_wier = 0; // Wartość największego wiersza komórek pierwszej genereacji.
    int *wmax_const_wier = &max_const_wier; // Wskaźnik na wartość największego wiersza.
    int min_const_wier = 0; // Wartość najmniejszego wiersza komórek pierwszej genereacji.
    int *wmin_const_wier = &min_const_wier; // Wskaźnik na wartość najmniejszejego wiersza.
    int max_const_kol = 0; // Wartość największej kolumny komórek pierwszej genereacji.
    int *wmax_const_kol = &max_const_kol; // Wskaźnik na wartość największej kolumny.
    int min_const_kol = 0; // Wartość najmniejszej kolumny komórek pierwszej genereacji.
    int *wmin_const_kol = &min_const_kol; // Wskaźnik na wartość najmniejszej kolumny.
    bool stop = true; // Mówi o tym, czy główna pętla może się powtórzyć.
    bool *wstop = &stop; // Wskaźnik na 'stop'.
    bool show = false; // Mówi o tym, czy pokazać rozpiskę aktualnej generacji.
    bool *wshow = &show; // Wskaźnik na 'show'
    bool alldead = false; // Mówi o tym, czy wszystkie komórki umarły.
    bool *walldead = &alldead; // Wskaźnik na 'alldead'.
    Tlista *alive; // Początek listy aktualnie żywej generacji.
    Tlista **walive = &alive; // Wskaźnik na początek listy aktualnie żywej generacji.
    Tlista *new_gen; // Początek listy przyszłej generacji.
    Tlista **wnew_gen = &new_gen; // Wskaźnik na początek listy przyszłej generacji.

    czytaj_dane_start(walive, wmax_const_wier, wmin_const_wier, wmax_const_kol, wmin_const_kol,
    walldead);
    int temp_min_k = min_const_kol - 2; // Wartość najmniejszej kolumny przyjętej w historii.
    int *wtemp_min_k = &temp_min_k; // Wskaźnik na 'temp_min_k'.
    int temp_max_k = max_const_kol + 2; // Wartość największej kolumny przyjętej w historii.
    int *wtemp_max_k = &temp_max_k; // Wskaźnik na 'temp_max_k'.
    int temp_min_w = min_const_wier - 2; // Wartość najmniejszego wiersza przyjętejego w historii.
    int *wtemp_min_w = &temp_min_w; // Wskaźnik na 'temp_min_w'.
    int temp_max_w = max_const_wier + 2; // Wartość największego wiersza przyjętejego w historii.
    int *wtemp_max_w = &temp_max_w;  // Wskaźnik na 'temp_max_w'.

    // Wskaźnik na wiersze planszy numer 1.
    int **wiersze1 = malloc((long unsigned int)((int)(sizeof(int *)) *
        (temp_max_w - min_const_wier + 1)));
    // Wskaźnik na wiersze planszy numer 2.
    int **wiersze2 = malloc((long unsigned int)((int)(sizeof(int *)) *
        (temp_max_w - min_const_wier + 1)));
    // Wskaźnik na wiersze planszy numer 3.
    int **wiersze3 = malloc((long unsigned int)((int)(sizeof(int *)) *
        (min_const_wier - temp_min_w)));
    // Wskaźnik na wiersze planszy numer 4.
    int **wiersze4 = malloc((long unsigned int)((int)(sizeof(int *)) *
        (min_const_wier - temp_min_w)));
    int ***wiersze1_ptr = &wiersze1; // Wskaźnik na 'wiersze1'.
    int ***wiersze2_ptr = &wiersze2; // Wskaźnik na 'wiersze2'.
    int ***wiersze3_ptr = &wiersze3; // Wskaźnik na 'wiersze3'.
    int ***wiersze4_ptr = &wiersze4; // Wskaźnik na 'wiersze4'.
    // Tworzy kolumny dla każdego wiersza na planszy 1 oraz 2.
    for (int i = 0; i < (temp_max_w - min_const_wier + 1); i++)
    {
        wiersze1[i] = calloc((long unsigned int)(temp_max_k - min_const_kol + 1), sizeof(int));
        wiersze2[i] = calloc((long unsigned int)(min_const_kol - temp_min_k), sizeof(int));
    }
    // Tworzy kolumny dla każdego wiersza na planszy 3 oraz 4.
    for (int i = 0; i < min_const_wier - temp_min_w; i++)
    {
        wiersze3[i] = calloc((long unsigned int)(temp_max_k - min_const_kol + 1), sizeof(int));
        wiersze4[i] = calloc((long unsigned int)(min_const_kol - temp_min_k), sizeof(int));
    }

    Tlista *czytnik = alive; // Wskaźnik na początek listy komórek pierwszej generacji.
    if (!alldead) // Jeśli cokolwiek żyje.
    {
        // Zapisuje na planszy pierwszej, gdzie leżą żywe komórki pierwszej generacji.
        while (czytnik != NULL)
        {
            wiersze1[czytnik->wiersz - min_const_wier][czytnik->kolumna - min_const_kol] = 1;
            czytnik = czytnik->nast;
        }
    }

    while (stop) // Póki nie zostało zarządzone zakończenie procesu.
    {
        if (!alldead) // Póki żyje choć jedna komórka
        {
            rysuj_plansze(korw, kork, wiersze1, wiersze2, wiersze3, wiersze4,
                min_const_kol, min_const_wier, temp_min_k, temp_min_w, temp_max_k, temp_max_w);
            czytaj_polecenia(wpokolenia, wstop, wkorw, wkork, wshow);
            if (show) // Jeśli zostało nakazane wypisanie aktualnie żywych komórek.
            {
                gdzie_zywe(alive);
            }
            else
            {
                for (int i = 0; i < pokolenia; i++) // Oblicza następne generacje.
                {
                    next_gen(walive, wiersze1, wiersze2, wiersze3, wiersze4,
                        min_const_kol, min_const_wier, wnew_gen, walldead);
                    if (!alldead)
                    {
                        update_plansze(walive, wiersze1_ptr, wiersze2_ptr, wiersze3_ptr,
                            wiersze4_ptr, min_const_kol, min_const_wier, new_gen, wtemp_min_k,
                            wtemp_min_w, wtemp_max_k, wtemp_max_w);
                    }
                }
            }
            pokolenia = 0;
            show = false;
        }
        else // Jeśli nie ma żywych komórek.
        {
            // Rysuje pustą planszę.
            for (int i = 0; i < WIERSZE; i++)
            {
                for (int x = 0; x < KOLUMNY; x++)
                {
                    printf(".");
                }
                printf("\n");
            }
            for (int x = 0; x < KOLUMNY; x++)
            {
                printf("=");
            }
            printf("\n");
            czytaj_polecenia(wpokolenia, wstop, wkorw, wkork, wshow);
            if (show) // Jeśli zostało nakazane wypisanie aktualnie żywych komórek.
            {
                printf("/\n");
            }
            show = false;
        }
    }

    while (alive != NULL) // Uwalnia wszytkie elementy listy z aktualną generacją.
    {
        czytnik = alive;
        alive = alive->nast;
        free(czytnik);
    }
    // Uwalnia wszystkie kolumny plansz 1 i 2.
    for (int i = 0; i < (temp_max_w - min_const_wier + 1); i++)
    {
        free(wiersze1[i]);
        free(wiersze2[i]);
    }
    free(wiersze1); // Uwalnia wiersze planszy 1.
    free(wiersze2); // Uwalnia wiersze planszy 2.
    // Uwalnia wszystkie kolumny plansz 3 i 4.
    for (int i = 0; i < (min_const_wier - temp_min_w); i++)
    {
        free(wiersze3[i]);
        free(wiersze4[i]);
    }
    free(wiersze3); // Uwalnia wiersze planszy 3.
    free(wiersze4); // Uwalnia wiersze planszy 4.
    return 0;
}