/************************************************************************************************
                                     Autor: Juliusz Pawlus
 Program 'drzewa' przy wywołaniu otrzymuje argument 'c' jeśli ma kompresować drzewo lub 'd',
 jesli ma dekompresować drzewo. Po inicjacji wczytuje kolejne węzły drzewa, które ma przetworzyć.
 Drzewo niepuste jest reprezentowane przez ciąg wierszy, z których pierwszy reprezentuje korzeń i
 zawiera jego wartość, a w kolejnych wierszach jest reprezentacja lewego poddrzewa. Po niej
 zapisywana jest reprezentacja prawego poddrzewa. W każdym wierszu występuje liczba naturalna,
 która jest wartością danego węzła. Puste drzewo jest reprezentowane przez wiersz z liczbą 0.
 Program wypisuje wedle życzenia, drzewo po skompresowaniu lub dekompresacji w tej samej formie,
 w której było wpisywane.
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 Tworzy typ list, dzięki którym zapisywane są wartości elementu listy.
 Trzyma też on również informację o adresie następnego elementu listy.
*/
typedef struct Tlista
{
    int w;
    struct Tlista *nast;
} Tlista;


/**
 Tworzy typ list, dzięki którym zapisywane są wartości elementu listy.
 Oprócz tego zapisany jest indeks w tablicy oraz, którym węzłem od startu jest ten element.
 Trzyma też on również informację o adresie następnego elementu listy.
*/
typedef struct Wlista
{
    int w;
    int indeks;
    int wezel;
    struct Wlista *nast;
} Wlista;


/**
 Szuka węzła o numerze 'droga' zaczynając od początku listy 'start'. Dodaje też na koniec listy
 odpowiednie poddrzewo.  Alokuje pamięć pod adresem 'nowy' za każdym razem, gdy tworzy nowy
 węzęł. Pamięc ta jest potem uwalniana.

 Dostaje wskaźnik 'akt' na adres końca listy.
 Dostaje wskaźnik 'start' na początek listy.
 Dostaje liczbę 'droga', która oznacza ilość niezerowych węzłów, które należy ominąć.
 Dostaje wskaźnik do liczby 'zera', która trzyma informację o ilości dotychczasowych zer.
 Dostaje wskaźnik do liczby 'wezly', która trzyma informację o ilości dotychczasowych wezłów.
*/
void szukaj_wezla(Tlista **akt, Tlista *start, int droga, int *zera, int *wezly)
{
    while (droga > 0 || start->w == 0) // Póki nie znaleźono odpowiedniego węzła.
    {
        if (start->w > 0) // Jeśli jest węzłem niezerowym.
        {
            droga--;
        }
        start = start->nast;
    }

    (*akt)->w = start->w; // Zmienia wartość aktualnego węzła na wartość znalezionego węzła.
    start = start->nast;
    Tlista *nowy; // Nowy element listy.
    int proporcja = 1; // Ilość węzłów w stosunku do 'NULL'.
    while (proporcja >= 0) // Dopóki 'NULL' nie jest więcej, niż węzłów.
    {
        nowy = malloc(sizeof(Tlista));
        (*akt)->nast = nowy;
        *akt = nowy;
        nowy->w = start->w;
        start = start->nast;
        if (nowy->w == 0) // Jeśli węzeł dopisywany jest 'NULL'.
        {
            (*zera)++;
            proporcja--;
        }
        else
        {
            (*wezly)++;
            proporcja++;
        }
    }
}


/**
 Sczytuje zdekompresowane drzewo wpisywane przez użytkownika programu.
 Tworzy zdekompresowane drzewo w postaci listy oraz wypisuje je.
 Alokuje pamięć pod adresem 'start' oraz pod adresem 'nowy',
 za każdym razem, gdy tworzy nowy węzęł. Pamięc ta jest potem uwalniana.
*/
void czytaj_dekompresje(void)
{
    int zera = 0; // Ilość 'NULL' w drzewie.
    int wezly = 0; // Ilość węzłów w drzewie.
    int *wzera = &zera; // Wskaźnik na ilość 'NULL'.
    int *wwezly = &wezly; // Wskaźnik na ilość węzłów.
    Tlista *start = malloc(sizeof(Tlista)); // Początek listy.
    Tlista *nowy; // Nowy element list.
    Tlista *szpieg = start; // Element podążający za nowym elementem.
    Tlista **adres; // Wskaźnik na ostatni element listy.
    while (zera - 1 < wezly) // Póki 'NULL' w drzewie jest niewięcej niż węzłów.
    {
        nowy = malloc(sizeof(Tlista));
        szpieg->nast = nowy;
        scanf("%d", &(nowy->w)); // Sczytuj wartość nowego elementu.
        if (nowy->w < 0) // Jeśli wartość elementu jest ujemna.
        {
            wezly++; // Zwiększa ilość węzłów.
            adres = &nowy; // Zapisuje wartość elementu ostatniego na liście.
            szukaj_wezla(adres, start->nast, abs(nowy->w) - 1, wzera, wwezly); // Dodaje poddrzewo.
            nowy = *adres; // Ustanawia nowy ostatni element.
        }
        else // Jeśli wartość nowego elementu jest większa lub równa zero.
        {
            if (nowy->w == 0) // Jeśli wartość nowego elementu jest równa zero.
            {
                zera++;
            }
            else
            {
                wezly++;
            }
        }
        szpieg = nowy;
    }
    nowy->nast = NULL;
    nowy = start;
    start = start->nast;
    free(nowy); // Usuwa atrapę.

    while (start != NULL) // Przechodzi całą listę.
    {
        printf("%d\n", start->w); // Wypisuje zdekompresowane drzewo.
        nowy = start;
        start = start->nast;
        free(nowy); // Uwalnia wypisane elementy.
    }
}


/**
 Sczytuje drzewo wpisywane przez użytkownika, zapisuje je w postaci tablicy.
 Znajduje lokalizacje pierwszego liścia oraz długość drzewa.
 Alokuje pamięć pod adresem'start' oraz pod adresem'nowy',
 za każdym razem, gdy tworzy nowy węzęł. Alokuje też pamięć pod adresem
 'treetab'. Pamięć ta jest potem uwalniana.

 Dostaje wskaźnik na adres tablicy 'treetab', gdzie zapisze drzewo.
 Dostaje wskaźnik na liczbę 'lisc', gdzie zapisuje indeks pierwszego liścia.
 Dostaje wskaźnik na liczbę 'dlugosc', gdzie zapisuje długość drzewa.
*/
void czytaj_drzewo(int **treetab, int *lisc, int *dlugosc)
{
    int zera = 0; // Ilość 'NULL' w drzewie.
    int wezly = 0; // Ilość węzłów w drzewie
    Tlista *start = malloc(sizeof(Tlista)); // Start listy.
    Tlista *nowy = start->nast; // Nowy element listy.
    Tlista *szpieg = start; // Element poprzedzający nowy element.
    while (zera - 1 < wezly) // Póki ilość 'NULL' jest niewiększa, niż ilość węzłów.
    {
        nowy = malloc(sizeof(Tlista));
        szpieg->nast = nowy;
        szpieg = nowy;
        scanf("%d", &(nowy->w)); // Sczytuje wartość nowego węzła.
        if (nowy->w == 0) // Jeśli nowa wartość to zero.
        {
            zera++;
        }
        else // Jeśli nowa wartość jest większa od zera.
        {
            wezly++;
        }
    }
    szpieg->nast = NULL; // Ustawia koniec listy.
    szpieg = start;
    start = start->nast;
    free(szpieg); // Uwalnia atrapę.
    szpieg = start;

    *dlugosc = zera + wezly; // Suma 'NULL' i węzłów to długość drzewa.
    bool pierwszy = true; // Póki nie znaleziono liścia.
    *treetab = malloc((long unsigned int)((int)sizeof(int) * (*dlugosc))); // Tworzy tablicę drzewa
    for (int i = 0; i < (*dlugosc); i++) // Przechodzi wszystkie węzły.
    {
        (*treetab)[i] = start->w; // Dopisuje wartość węzła do tablicy.
        if (pierwszy && (*treetab)[i] == 0 && i > 1 && (*treetab)[i - 1] == 0) // Jeśli liść.
        {
            pierwszy = false; // Znaleziono pierwszego liścia.
            *lisc = i; // Indeks pierwszego liścia.
        }
        szpieg = start;
        start = start->nast;
        free(szpieg); // Uwalnia aktualny element listy.
    }
}


/**
 Dostaje drzewo w postaci tablicy, kompresuje niektóre poddrzewa oraz wypisuje
 skompresowane drzewo.  Alokuje pamięć pod adresem'nowy', za każdym razem,
 gdy tworzy nowy węzęł. Pamięć ta jest potem uwalniana.

 Dostaje tablicę liczb 'drzewo', która reprezentuje drzewo.
 Dostaje liczbę 'dlugosc', która jest długością drzewa.
 Dostaje liczbę 'lisc', która jest wartością indeksu pierwszego liścia, o ile istnieje.
 Dostaje wskaźnik na tablicę, która trzyma dane o poddrzewach, które wystąpiły pierwszy raz.
*/
void kompresuj(int *drzewo, int dlugosc, int lisc, Wlista **indeksy)
{
    int indeks = 1; // Indeks aktualnego węzła.
    int numer_wezla = 1; // Numer rozpatrywanego węzła.
    int proporcja; // Ilość węzłów w stosunku do 'NULL'.
    int biegacz; // Trzyma informację o długości danego poddrzewa.
    Wlista *nowy; // Nowy element listy.
    printf("%d\n", drzewo[0]); // Wypisuje korzeń drzewa.
    while (indeks < lisc) // Póki indeks węzeła jest mniejszy od indeksu pierwszego liścia.
    {
        printf("%d\n", drzewo[indeks]); // Wypisuje węzeł drzewa.
        if (drzewo[indeks] != 0) // Jeśli węzeł nie jest 'NULL'.
        {
            proporcja = 0;
            biegacz = 0;
            while (proporcja >= 0) // Dopóki 'NULL' nie jest więcej, niż węzłów.
            {
                if (drzewo[indeks + biegacz] == 0) // Jeśli węzeł poddrzewa to 'NULL'.
                {
                    proporcja--;
                }
                else // Jeśli węzeł poddrzewa nie jest 'NULL'.
                {
                    proporcja++;
                }
                biegacz++;
            }
            numer_wezla++; // Indeks kolejnego węzła.
            nowy = malloc(sizeof(Wlista)); // Tworzy nowy element do tablicy 'indeksy'
            nowy->w = drzewo[indeks]; // Zapisuje wartość korzenia aktualnego poddrzewa.
            nowy->indeks = indeks; // Zapisuje indeks korzenia aktualnego poddrzewa.
            nowy->wezel = numer_wezla; // Zapisuje numer węzła aktualnego poddrzewa.
            nowy->nast = indeksy[biegacz /2 ]; // Zapisuje długość aktualnego poddrzewa.
            indeksy[biegacz / 2] = nowy; // Dodaje do 'indeksy' nowy element.
        }
        indeks++; // Kolejny węzeł.
    }

    bool printed_already; // Czy wypisany został element w tej iteracji pętli.
    while (indeks < dlugosc) // Póki nie dojedziemy do końca listy.
    {
        printed_already = false; // Nie wypisano jeszcze.
        if (drzewo[indeks] != 0) // Węzeł nie jest NULL.
        {
            numer_wezla++; // Kolejny wezel.
            proporcja = 0;
            biegacz = 0; // Zapisuje długość poddrzewa o korzeniu 'drzewo[indeks]'.
            while (proporcja >= 0)
            {
                if (drzewo[indeks + biegacz] == 0)
                {
                    proporcja--;
                }
                else
                {
                    proporcja++;
                }
                biegacz++;
            }
            Wlista *szukaj = indeksy[biegacz / 2]; // Sprawdza poddrzewa o długości 'biegacz'.
            bool znaleziony = false; // Czy znaleziono identyczne poddrzewo.

            // Póki nie sprawdzono wszystkich poddrzew lub nie znaleziono identycznego poddrzewa.
            while (szukaj != NULL && !znaleziony)
            {
                if (drzewo[indeks] == szukaj->w) // Jeśli korzenie mają tę samą wartość.
                {
                    int same = 0; // Odcinek, na którym poddrzewa są identyczne.
                    // Póki węzły są identyczne i długość poddrzewa nie wychodzi poza skalę.
                    while (same < biegacz && drzewo[indeks + same] ==
                        drzewo[szukaj->indeks + same])
                    {
                        same++; // Wydłuża identyczny odcinek.
                    }
                    if (same == biegacz) // Jeśli są identyczne całe drzewa.
                    {
                        znaleziony = true; // Znaleziono identyczne.
                    }
                }
                if (!znaleziony) // Jeśli nie znaleziono.
                {
                    szukaj = szukaj->nast; // Zmieniamy poddrzewo do porównywania.
                }
            }
            if (znaleziony) // Jeśli znaleziono identytczne poddrzewo.
            {
                printf("%d\n", -(szukaj->wezel)); // Wypisuje skompresowane poddrzewo.
                indeks += (biegacz - 1); // Przeskakuje na koniec skompresowanego poddrzewa.
                printed_already = true; // Wypisano poddrzewo skompresowane.
            }
            else // Jeśli nie było wcześniej identycznego poddrzewa.
            {
                // Dodajemy poddrzewo do zbioru świeżych poddrzew jak wyżej.
                nowy = malloc(sizeof(Wlista));
                nowy->w = drzewo[indeks];
                nowy->indeks = indeks;
                nowy->wezel = numer_wezla;
                nowy->nast = indeksy[biegacz / 2];
                indeksy[biegacz / 2] = nowy;
            }
        }
        if (!printed_already) // Jeśli nie wypisano skompresowanego poddrzewa.
        {
            printf("%d\n", drzewo[indeks]); // Wypisz węzeł.
        }
        indeks++; // Węzeł o kolejnym indeksie.
    }
}


/**
 Dostaje informację od użytkownika, czy kompresować drzewo, czy dekompresować drzewo.
 Czyta drzewo wpisywane przez użytkownika, transformuje je wedle wcześniej zadeklarowanego trybu,
 poczym wypisuje przetworzone drzewo. Alokuje pamięć pod adresami 'drzewo' oraz 'indeksy',
 którą potem uwalnia.

 Dostaje informację, o tym czy kompresować, czy dekompresować drzewo w postaci
 odpowiednio 'c' lub 'd' zapisaną w tablicy 'zapis' oraz wielkość tablicy 'zapis'
 zapisany jako 'tryb'.
*/
int main(int tryb, char *zapis[])
{
    char status = zapis[tryb - 1][0]; // Informacja, czy kompresować, czy nie.

    if (status == 'c') // Kompresuj.
    {
        int *drzewo; // Tablica, na której zapisane będzie drzewo.
        int **wdrzewo = &drzewo; // Wskaźnik na tablicę z drzewem.
        int dlugosc; // Długość drzewa.
        int *wdlugosc = &dlugosc; // Wskaźnik na długość drzewa.
        int lisc = 0; // Indeks pierwszego liścia.
        int *wlisc = &lisc; // Wskaźnik na indeks pierwszego liścia.
        czytaj_drzewo(wdrzewo, wlisc, wdlugosc); // Czyta wszystkie informacje o drzewie.

        // Tablica, która trzyma autentyczne poddrzewa i dzieli je według ich długości.
        Wlista **indeksy = malloc((long unsigned int)((int)sizeof(Wlista) * (dlugosc / 2)));
        for (int i = 0; i < dlugosc / 2; i++) // Zapełnia tablicę 'indeksy' wskaźnikami na 'NULL'.
        {
            indeksy[i] = NULL;
        }
        kompresuj(drzewo, dlugosc, lisc, indeksy); // Kompresuje i wypisuje drzewo.
        Wlista *kasownik; // Uwalnia elementy 'indeksy'.
        Wlista *pom; // Pomaga uwalniać elementy 'indeksy'.

        for (int i = 0; i < (dlugosc / 2); i++) // Sprawdza po kolei każdą długość poddrzew.
        {
            kasownik = indeksy[i]; // Początek listy z poddrzewami o danej długości.
            while (kasownik != NULL) // Przechodzi przez wszystkie poddrzewa o danej długości.
            {
                pom = kasownik;
                kasownik = kasownik->nast;
                free(pom); // Uwalnia poddrzewo.
            }
        }
        free(indeksy); // Uwalnia tablicę 'indeksy'
        free(drzewo); // Uwalnia tablicę, na której zapisano drzewo.
    }
    else // Dekompresuj.
    {
        czytaj_dekompresje(); // Dekompresuje drzewo i wypisuje je.
    }
    return 0;
}