# music-visualizer
Proiect SMP Georgescu Mihnea-Stefan 331AB
## Descriere
Proiectul are rolul de a crea un mod de vizualizare a sunetului, cel mai des a muzicii, prin descompunere acestuia in frecvente si afisarea grafica a intensitatii acestora. In stadiul actual, sunetul provine de la un microfon, iar afisarea este facuta pe o matrice led.
## Componente
Ansamblul este format din:
### - Placa de dezvoltare compatibilă cu Arduino UNO
### - Matrice LED MAX7219
Matrice de 8x8 LED-uri, comandata de un chip MAX7219, ce are comanda seriala. Avantajul acestui modul este posibilitatea de a adresa fiecare output fara necesitatea de refresh a intregului display.
### - Modul detectare sunet cu microfon KY-037
Compus dintr-un microfon si un circuit de amplificare, ofera atat output digital cu prag reglabil, cat si analog. In acest caz, am folosit pinul analog pentru a citi informatii exacte legate de sunetul detectat.
### - Breadboad
### - Cabluri
## Montaj![Montaj](https://user-images.githubusercontent.com/80157650/168164323-becaa6c8-62ce-4130-9dcf-ce47cd06ccf3.jpeg)
## Functionare
#### 1. Citire microfon
Se citeste inputul analog provenit de la modulul de detectie sunet pentru 64 de inregistrari
#### 2. Procesare date
Asupra inregistrarilor este aplicat FFT pentru a obtine magnitudinile frecventelor din care este compus sunetul. Apoi, datele sunt constranse intre 0 si 8 pentru a putea fi afisate, tinand cont de o valoare minima ce poate fi afisata si de maximul inregistrat.
#### 3. Afisare pe matricea LED
Fiecare coloana reprezinta o raza diferita de frecvente. Pe coloana corespunzatoare, va fi aprins un numar de leduri egal cu valoarea calculata anterior.
## Biblioteci folosite
- LedControl - contine functii pentru adresarea facila a ledurilor din matrice
- arduinoFFT - o implementare a algoritmului FFT optimizata pentru functionarea pe placute Arduino
