#Take away game
This is a two player game called `take away`.
The AI "ULTRON" I have created is unbeatable unless the player 
plays perfectly for all turns.
The games consists of one or more piles.
Each pile contains stones or sticks or whatever you feel like calling the items in the pile.

A player may remove any number of stones from **a single pile**
when it is their turn.
The player who removes the last stone(s) wins.

## Basic Gameplay
Ask each player for their name.
The game initializes with a random number of piles and 
a random number of stones in each pile.
The first player starts.
When the game is over the program displays the name of the winning player
and prompt to play another game.

The game only allows legal moves:
- When it is a players turn they must remove at least 1 stone
- A player cannot remove more stones than are in a single pile
- A player may remove stones only from 1 pile per turn

After each player turn the game redraws the current state of
all remaining piles.
Does not display piles with 0 stones.

## command line arguments: 

   `-h` to display `h`elp text and exit.
   `-c` to play against the `c`omputer
   `-p` to set an exact number of `p`iles
   `-s` to set an exact number of `s`tones in each pile


### Show help

```
./take-away -h
Usage: ./take-away [-h] [-c] [-p # piles] [-s # stones] 

Options:
  -h   Show this text.
  -c   Make player two the computer.  Default = false.
  -p   Manually set the starting number of piles in the game.
  -s   Manually set the starting number of stones in each pile.

       Max values for piles and stones: 99
       Min values for piles and stones: 1
```

After the help text is displayed, the program should exit.

### Default behavior
Play a random two player game.

```plain
  ./take-away
  First player name: Alice
  Second player name: Bob
  Player 1: Alice
  Player 2: Bob
  Heap 1 [ 5]: *****
  Heap 2 [14]: **************
  Heap 3 [ 8]: ********

  Alice's turn
  Which heap? 1
  How many stones? 5
  Player 1: Alice
  Player 2: Bob
  Heap 1 [14]: **************
  Heap 2 [ 8]: ********

  Bob's turn
  Which heap? 2
  How many stones? 9
     There aren't that many stones in this heap.
  How many stones? 7
  Player 1: Alice
  Player 2: Bob
  Heap 1 [14]: **************
  Heap 2 [ 1]: *

  Alice's turn
  Which heap? 1
  How many stones? 13
  Player 1: Alice
  Player 2: Bob
  Heap 1 [ 1]: *
  Heap 2 [ 1]: *

  Bob's turn
  Which heap? 1
  How many stones? 1
  Player 1: Alice
  Player 2: Bob
  Heap 1 [ 1]: *

  Alice's turn
  How many stones? 1
  Alice wins!!
  Play another game? [Y/n] n

```


### Play against the computer

```plain
  ./take-away -c 
  Human player name: Darla

  Heap 0 [15]: ***************
  Heap 1 [13]: *************
  Heap 2 [ 7]: *******
  Heap 3 [12]: ************
  Heap 4 [11]: ***********
  Heap 5 [ 9]: *********
  Darla's turn
  Which heap? 1
  How many stones? 13

  Heap 0 [15]: ***************
  Heap 1 [ 7]: *******
  Heap 2 [12]: ************
  Heap 3 [11]: ***********
  Heap 4 [ 9]: *********
  Ultron's turn
  Ultron removed 6 stones from heap 0.

  Heap 0 [ 9]: *********
  Heap 1 [ 7]: *******
  Heap 2 [12]: ************
  Heap 3 [11]: ***********
  Heap 4 [ 9]: *********
  Darla's turn
  Which heap? 

  (rest of the game omitted)
```
