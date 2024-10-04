# 4 big and fun projects from my first semester in C.

# First assignment

### Wprowadzenie
Palindrom to wariant gry znanej jako Connect Four .

Gra jest rozgrywana przez dwóch graczy, nazywanych Pierwszym i Drugim, na prostokątnej planszy, ustawionej pionowo, podzielonej na wiersze i kolumny. Każdy gracz ma swój rodzaj piona.

Na początku gry plansza jest pusta. Zaczyna gracz Pierwszy.

Gracze, na przemian, wykonują ruch, kładąc swój pion na polu planszy. Pion jest umieszczany w wybranej przez gracza kolumnie, w jej pierwszym wolnym polu, licząc od dołu planszy.

Gracz wygrywa, jeśli swoim ruchem zbudował z pionów na kolejnych polach tego samego wiersza, kolumny lub przekątnej palindrom określonej długości.

Gra jest parametryzowana trzema dodatnimi liczbami całkowitymi:

* WIERSZE to liczba wierszy planszy,
* KOLUMNY to liczba kolumn planszy,
* DLUGOSC to długość budowanego palindromu.

### Polecenie
Napisz program umożliwiający grę w Palindrom dwóm graczom.

Wartości parametrów gry WIERSZE, KOLUMNY i DLUGOSC są określone za pomocą stałych symbolicznych, które można zdefiniować opcją -D kompilatora.

W kodzie programu są podane wartości domyślne tych stałych:

* WIERSZE ma wartość 8,

* KOLUMNY ma wartość 8,

* DLUGOSC ma wartość 5.

Program, w pętli:

* pisze diagram aktualnego stanu planszy i wskazuje, który gracz ma wykonać ruch;

* czyta polecenie gracza;

* jeśli wczytał polecenie wykonania ruchu, wykonuje je;

* jeśli wczytał polecenie przerwania gry, kończy pracę.

Pętla kończy się, gdy:

* program dostanie polecenie przerwania gry, lub

* jeden z graczy wygra.

Jeśli jeden z graczy wygra, to program, na zakończenie pracy, pisze diagram końcowego stanu planszy i informuje, kto wygrał.

### Postać danych
Na wejściu programu są polecenia graczy. Każde polecenie zajmuje jeden wiersz. Wszystkie polecenia są poprawne. Po ostatnim poleceniu jest dowolny tekst, ignorowany przez program.

Jedynym znakiem w wierszu polecenia wykonania ruchu jest nazwa kolumny, w której gracz chce umieścić pion. Kolumny są nazywane kolejnymi małymi literami, od a.

Polecenie wykonania ruchu jest poprawne, jeśli we wskazanej kolumnie jest wolne pole.

Jedynym znakiem w wierszu polecenia przerwania gry jest kropka.

### Postać wyniku
Na wyjściu programu jest ciąg diagramów planszy. Po każdym diagramie jest wiersz z informacją, kto ma wykonać ruch lub kto wygrał.

Diagram opisuje pole planszy za pomocą znaku:

* - gdy pole jest puste;

* 1 gdy na polu jest pion gracza Pierwszego;

* 2 gdy na polu jest pion gracza Drugiego.

Przed każdym znakiem opisującym pole jest spacja.

Opisy pól są pogrupowane w wiersze, uporządkowe w kolejności od najwyższego do najniższego. Pola w wierszu są uporządkowane w kolejności wyznaczonej przez kolumny, zaczynając od kolumny a.

Po ostatnim wierszu pól diagramu jest wiersz z nazwami kolumn. Każda z nich jest poprzedzona spacją.

Informacja o tym, kto ma wykonać ruch, ma postać wiersza z nazwą gracza, 1 lub 2, po której jest dwukropek.

Informacja o tym, kto wygrał, ma postać wiersza z nazwą gracza, 1 lub 2, po której jest wykrzyknik.

W tekście wynikowym programu nie ma żadnych znaków, które nie zostały wymienione powyżej.

Każdy wypisywany wiersz, także ostatni, jest zakończony końcem wiersza \n.

# Second assignment

### Wprowadzenie
Prostokątna plansza do jednoosobowej gry SameGame dzieli się na pola, uporządkowane w wiersze i kolumny.

Każde pole albo jest puste, albo jest na nim klocek określonego rodzaju.

Gracz usuwa z planszy grupy sąsiadujących klocków tego samego rodzaju.

Usunięcie grupy klocków jest możliwe tylko, jeśli są w niej co najmniej dwa klocki.

Po usunięciu grupy plansza jest porządkowana:

* Klocki opadają na puste pola w wierszach poniżej.

* Kolumny, w których są jakieś klocki, są przesuwane w lewo, na miejsce kolumn pustych.

Gra jest parametryzowana trzema dodatnimi liczbami całkowitymi:

* WIERSZE to liczba wierszy planszy;

* KOLUMNY to liczba kolumn planszy;

* RODZAJE to liczba rodzajów klocków.

### Polecenie
Napisz program wykonujący jedno polecenie usunięcia klocków wydane przez grającego w SameGame.

Wartości parametrów gry WIERSZE, KOLUMNY i RODZAJE są określone za pomocą stałych symbolicznych, które można zdefiniować opcją -D kompilatora.

W kodzie programu są podane wartości domyślne tych stałych:

* WIERSZE ma wartość 10;

* KOLUMNY ma wartość 15;

* RODZAJE ma wartość 4.

Program jest wywoływany z dwoma argumentami - współrzędnymi pola wybranego przez gracza. Pierwszy argument to numer wiersza, liczony od 0. Drugi argument to numer kolumny, liczony od 0. Pole z wiersza 0 i kolumny 0 jest w lewym górnym rogu planszy.

Dane programu, czytane z wejścia, to aktualny stan planszy.

Wynik programu, pisany na wyjście, to stan planszy po wykonaniu polecenia gracza.

Stan planszy określa, dla każdego pola, czy jest na nim klocek, a jeśli tak, to jaki jest rodzaj tego klocka.

Zbiór G klocków na planszy nazywamy grupą, jeśli spełnione są trzy warunki:

* wszystkie klocki w zbiorze G są tego samego rodzaju;

* od każdego klocka w zbiorze G można przejść do każdego z pozostałych klocków w tym zbiorze, wykonując tylko kroki do bezpośrednich sąsiadów w wierszu lub w kolumnie i poruszając się przy tym wyłącznie po polach, na których są klocki ze zbioru G;

* zbioru G nie można rozszerzyć, nie łamiąc zasad 1 i 2.

Można zauważyć, że każdy klocek jednoznacznie określa grupę, do której należy.

Program:

* czyta stan planszy;

* sprawdza, czy na polu o współrzędnych określonych argumentami programu, jest klocek należący do grupy mającej co najmniej dwa elementy i jeśli tak, usuwa z planszy wszystkie klocki tej grupy;

* porządkuje planszę;

* pisze wynik.

Porządkując planszę, program:

* dopóki jest choć jeden klocek, bezpośrednio poniżej którego, w tej samej kolumnie, jest pole puste, przesuwa ten klocek o jedną pozycję w dół;

* dopóki jest choć jedna niepusta kolumna, bezpośrednio na lewo od której jest kolumna pusta, przesuwa wszystkie klocki tej niepustej kolumny o jedną pozycję w lewo.

Jeżeli pole o współrzędnych określonych argumentami programu jest puste lub jest na nim klocek, którego grupa jest jednoelementowa, to wynik programu jest taki sam jak dane.

### Postać danych
Liczba wierszy danych programu jest określona stałą WIERSZE. Każdy wiersz jest zakończony reprezentacją końca wiersza '\n'.

Liczba znaków w każdym wierszu jest określona stałą KOLUMNY.

Znak danych określa zawartość pola planszy:

* znak '.' wskazuje, że pole jest puste;

* cyfra dziesiętna, od '0' do '0' + RODZAJE - 1, reprezentuje rodzaj klocka.

Plansza opisana danymi jest uporządkowana. Nie ma na niej klocka, poniżej którego jest pole puste. Nie ma też niepustej kolumny, na lewo od której jest kolumna pusta.

### Postać wyniku
Format wyniku programu jest taki sam jak format danych.
