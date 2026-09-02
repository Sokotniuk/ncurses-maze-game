<div align="center">

# Maze Game (Labyrinth)

**2D ASCII maze game built with ncurses in C**

<p>
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" />
  <img src="https://img.shields.io/badge/ncurses-333333?style=for-the-badge" />
</p>

</div>

---

## About

A terminal-based 2D maze game rendered entirely in ASCII using the **ncurses** library. The player navigates a character through a maze, avoiding walls, and has to reach the exit before time runs out. Built as a university project for the *Intelligent Systems* program at **TUKE** — the assignment required at least 3 of: color support, non-blocking keyboard input, multiple levels, timer-based logic, command-line arguments, and file handling. This project implements color support, non-blocking input, multiple levels, and a timer.

## Features

- **Main menu** — "Play Game" / "Exit", navigated with arrow keys
- **Level select menu** — choose between 3 levels or go back to the main menu
- **3 difficulty levels** — increasing maze size and complexity (Easy, Hard, Ultra Hard)
- **Timer** — 120 seconds per level; running out of time ends the run
- **HUD** — current level, step counter, warning counter, and remaining time, all shown live during play
- **Colored, rainbow-styled titles** — gradient-colored ASCII logo and menu titles using ncurses color pairs
- **Non-blocking input** — the game loop keeps rendering and tracking the timer while waiting for a keypress
- **Collision handling** — walking into a wall or the map border is blocked and increases the warning counter
- **Win / lose screens** — a message is shown when the player reaches the exit or runs out of time

## Controls

**In-game:**
- `W` `A` `S` `D` — move up / left / down / right
- `Q` — quit the current level immediately

**In menus:**
- `Arrow Up` / `Arrow Down` — navigate items
- `Enter` — confirm selection
- `Esc` — go back / exit

## Levels

| Level | Difficulty | Notes |
|---|---|---|
| 1 | Easy | Smaller map, simpler wall layout |
| 2 | Hard | Larger map, more walls and turns |
| 3 | Ultra Hard | Largest and most complex maze |

The player always starts in the top-left corner and must reach the exit (`E`), marked near the bottom-right of the map. Each level's walls are hand-designed to always leave a path through to the exit.

## Tech Stack

- **Language:** C (C99)
- **Graphics/Input:** ncurses
- **Build system:** Make (GCC)

## Project Structure

```
.
├── program.c          # Entry point: main menu, level-select menu, main()
├── game.c              # Game engine: map generation, rendering, player movement, game loop
├── game.h               # Public game API (init/end ncurses, run_game)
├── Makefile               # Build configuration
└── documentation1.pdf       # Original assignment documentation (Slovak)
```

## Building & Running

Requires `gcc` and the `ncurses` development library installed (on Debian/Ubuntu: `sudo apt install libncurses5-dev`).

```bash
make        # builds the "game" executable
make run    # builds (if needed) and runs the game
make clean  # removes build artifacts
```

## Notes

- The maze layout for each level is defined directly in code (`create_level1/2/3` in `game.c`) rather than loaded from a file.
- Color rendering degrades gracefully — the game checks `has_colors()` and falls back to bold text if the terminal doesn't support color.
- This was a coursework project (assignment PS6) for the *Intelligent Systems* program at TUKE, FEI, KKUI department.
