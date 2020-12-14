# Projekt TM2 - Sekwencer muzyczny

### Opis projektu:

Celem projektu jest wykonanie podstawowego sekwencera muzycznego. Za pomocą zewnętrznych przycisków na klawiaturze matrycowej wybieramy przypisane sample dźwiękowe, które będą odtwarzane za pomocą modułu głośnika. Dodatkowo parametry dźwiękowe sampli będą regulowane potencjometrami oraz sliderem.

### Analiza problemu:

Moduł wzmacniacza _WAVESHARE 3972_, oprócz głośnika który zostanie wykorzystany do odtwarzania sampli, posiada 2 potencjometry pozwalające na regulację napięcia w zakresie od 0 V do 3.3 V. Jeden z nich zostanie wykorzystany do regulacji głośności dźwięku emitowanego przez głośnik, natomiast drugi będzie służył do zwiększenia szybkości odtwarzania wybranych sampli.

Slider pojemnościowy znajdujący się na płytce rozwojowej _FRDM-KL05Z_ także zostanie wykorzystany w projekcie. Będzie on odpowiadał za zmianę częstotliwości odtwarzanego dźwięku poprzez przesunięcie palcem w lewo (niższa częstotliwość) lub w prawo (wyższa częstotliwość).

Klawiatura matrycowa użyta zostanie do wyboru sampli przypisanych programowo do przycisków.

### Plan realizacji:

Projekt zostanie wykonany na płytce rozwojowej _FRDM-KL05Z_, wyposażonej w mikroprocesor _Cortex M0+_. Inne użyte w projekcie komponenty to moduł wzmacniacza _WAVESHARE 3972_ z układem _LM386M_, głośnikiem i dwoma potencjometrami oraz klawiatura matrycowa.

W ramach projektu utworzone zostaną sample dźwiękowe w programie _Audacity_. Następnie za pomocą skryptu w języku _Pyton_ zostaną przekonwertowane tak, aby można było umieścić je w tablicach w programie. Napisana zostanie obługa potencjometrów umieszczonych na module wzmacniacza oraz odpowiednia funkcja obsługi slidera pozwalająca modyfikować częstotliwośćsampli dźwiękowych. 

#### Autorzy: Kumka Krzysztof, Potoczek Sławomir
