
# Quotes
___
The task is to create a program that will display selected quotes.

The input of the program is a single integer. 
This number is in the range from 1 to 9 and determines the quote to be displayed.
The output of the program is the quote corresponding to the entered number.
Quotes corresponding to individual numbers are provided in the sample program runs below.
Note that there is a newline (\n) after the text of the quote.

If the input is invalid, the program must detect it and display an error message.
Display error messages on standard output (not on error output). Consider the following as errors:

* It is not possible to read a whole number from the input,
* The number read from the input is outside the interval 1 to 9.

Program's output is checked by a machine that requires an exact match 
between the output of  program and the reference output. Deviations in the output are considered errors. 
Missing or extra spaces/newlines are also considered errors. 
To quickly eliminate these problems, use the attached archive with a set of input and expected output data. 

Program was executed in a restricted testing environment.
Execution time is limited (the limit is visible in the log of the reference solution), and the available memory is also limited
(but this task should not have a problem with either limit).
The testing environment also prohibits the use of certain "dangerous functions" - functions for running programs,
working with the network, ... If these functions are used, the program will not run.

___
## Ukázka práce programu:
```
ml' nob:
1
Qapla'
noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.
```
```
ml' nob:
2
Qapla'
bortaS bIr jablu'DI' reH QaQqu' nay'.
```
```
ml' nob:
3
Qapla'
Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.
```
```
ml' nob:
4
Qapla'
bISeH'eghlaH'be'chugh latlh Dara'laH'be'.
```
```
ml' nob:
5
Qapla'
qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.
```
```
ml' nob:
6
Qapla'
Suvlu'taHvIS yapbe' HoS neH.
```
```
ml' nob:
007
Qapla'
Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.
```
```
ml' nob:
8
Qapla'
Heghlu'meH QaQ jajvam.
```
```
ml' nob:
00009
Qapla'
leghlaHchu'be'chugh mIn lo'laHbe' taj jej.
```
```
ml' nob:
10
luj
```
```
ml' nob:
0
luj
```
```
ml' nob:
abc
luj
```