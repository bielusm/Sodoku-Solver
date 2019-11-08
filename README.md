# Sodoku-Solver
The program solves simple Sodoku Puzzles using the process of elimation and the hidden singles technique found 
[here](http://hodoku.sourceforge.net/en/tech_singles.php#h1). 
This program is only able to solve simplier sodoku puzzles since there are [many](https://www.kristanix.com/sudokuepic/sudoku-solving-techniques.php) algorithms requried in solving sodoku puzzles.

## How to use
1. Compile and run in visual studio
2. Enter a sodoku board using 0s to indicate empty squares
For example: 

### Input: 
```
000000100
000067000
000000900
007300206
040506300
100002000
052090400
903000512
400700090
```

### Output
```
Puzzle solved:
725938164
391467825
864251937
587319246
249576381
136842759
652193478
973684512
418725693
Time elapsed: 3101900 nano seconds or: 3.1019 milli seconds
```
