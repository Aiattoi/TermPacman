# Colorful pacman in terminal

Do you want to play colorful pacman with custom maps and difficulties in your terminal? Now you can!

## How to run it

Just download this repository and start the game by typing `make run` in your terminal.

## Gameplay

![Gameplay](/gameplay.png?raw=true "Gameplay")

### Game initialization

Before game starts you choose a file with a game map(pre-made classic.txt), after successfull loading of the map you will choose difficulty. You can either choose one of available difficulties, or you can choose custom difficulty, which will then require a file, where durations of scatter and chase mode will be specified. Once the chosen difficulty loads itself the game starts.

Difficulties:
- Easy - ghosts will move very slowly in the same direction as the pacman, duration of the scatter mode is long
- Normal - ghosts will move the same as in the original pacman game
- Hard - ghosts will move right to the pacman, permanent chase mod, fast speed

- Custom difficulty - based on the Normal difficulty, parameters of the game have to be specified in a file (see the custom difficulties section)

### Game controls and objectives

You can control pacman with [w], [a], [s], [d] -used as: up, left, down, right. If you want to end the game early you can press [ESC] or [f]. Your goal is to collect all points in the map and don't get killed by ghosts, who will be chasing you according to the selected difficulty.
If you want to know more about game mechanics (such as the ghosts behaviour), you can find great description of the original game, by which is this game inspired, here: https://www.gamasutra.com/view/feature/132330/the_pacman_dossier.php

## Custom maps

If you want to make a custom map, be aware of these rules:
Rules for a map:
- must contain: 1 pacman, 1 spawn, 1 bonus, 2 teleports, 4 ghosts
- all rows must have the same width
- spawn must be next to 2 empty tiles and 2 walls
- teleports must be next to 1 empty tile and 3 walls

## Custom difficulties
If you want to make a custom difficulty, the file with it should look like this:
```
scatter: 0, 2, 2, 2
chase: 5, 20, 35
vulnerable: 10
ghostRespawn: 5
gameSpeed: 1
ghostSpeed: 2

```
where you change the numbers for your own difficulty specification. Note, that vulnerable and ghostRespawn time must be > 0, gameSpeed is from range 1-3, where 1 is the fastest and ghostSpeed is from range 1-5, where 1 is the fastest.

