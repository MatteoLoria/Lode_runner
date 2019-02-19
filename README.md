# Lode_runner

This is a C++ LodeRunner clone for an OOP Exam @ [Università della Calabria](https://www.mat.unical.it/demacs)

To compile it:
1. Just clone the repository wherever you want on your computer
2. Move to your folder in a terminal
3. ``cd Source``
4. ``make``                                  (g++, Allegro and c++14 are required)
5. ``./LodeRunner``
6. Enjoy!

## Instructions

In the ``Options`` menu you can choose among 3 styles of tiles and 3 difficulties.
* If you set the difficulty on "Easy" once you die you won't lose your coins and every time you win a level you gain a life.
* On "Normal" you won't lose your coins.
* On "Hard" you lose all your coins every time you die.

#### In game

Move around with arrows ←↑↓→ and press X to dig at your right, Z for left.
To win the level just pick up every coin in the map and a new stair will appear.
If an enemy picks up a coin his hat will become red and you must dig a hole so he can fell in and drop the coin.
In every level there's a candy that gives you a bonus and makes enemies a lot slower than you. Music is affected too.
When your lifes reach 0 it's game over.




#### Debug purpose

If you want to go at next level without playing the current, press M. This is a debug purpose functionality and we are not sure that's bug-free.
