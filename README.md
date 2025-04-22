# Lab Work 5: Battleship Game Bot (Console Application)

This lab focuses on designing and implementing a console-based **battleship bot** that communicates via standard input and output streams. The bot supports two roles — `master` and `slave` — and follows the rules of the classic [Battleship game](https://en.wikipedia.org/wiki/Battleship_(game)) with extended flexibility.

---

## 🎯 Objective

Create a command-line program that:
- Implements both **master** and **slave** player roles
- Allows customizable game parameters (field size, number of ships)
- Interacts using a set of predefined **text commands**
- Supports **strategic gameplay** with interchangeable algorithms
- Separates game logic from input/output handling
- Can be tested automatically and used in bot-vs-bot tournaments

---

## 🕹️ Gameplay Overview

- The game starts when the `master` sets up the field and sends parameters to the `slave`.
- Both players place ships and take turns firing.
- Communication is **command-based** via stdin/stdout.
- The `slave` always fires first.

Field size and number of ships can be changed before the game starts. Ships must conform to standard sizes (1, 2, 3, and 4 cells).

---

## 📡 Supported Commands

| Command                         | Response         | Description                                              |
|---------------------------------|------------------|----------------------------------------------------------|
| `ping`                          | `pong`           | Test connectivity                                        |
| `exit`                          | `ok`             | Terminate the program                                    |
| `create [master|slave]`         | `ok`             | Create a game session in the specified role              |
| `start`                         | `ok`             | Start the game                                           |
| `stop`                          | `ok`             | Stop the current game                                    |
| `set width N`                  | `ok` / `failed`  | Set the field width (positive `uint64_t`)                |
| `get width`                    | `N`              | Get the current field width                              |
| `set height N`                 | `ok` / `failed`  | Set the field height (positive `uint64_t`)               |
| `get height`                   | `N`              | Get the current field height                             |
| `set count [1-4] N`            | `ok` / `failed`  | Set number of ships of a specific type                   |
| `get count [1-4]`              | `N`              | Get number of ships of a specific type                   |
| `set strategy [ordered|custom]`| `ok`             | Select the shooting strategy                             |
| `shot X Y`                     | `miss` / `hit` / `kill` | Fire at coordinates (X, Y)                          |
| `shot`                         | `X Y`            | Return the next shot coordinates                         |
| `set result [miss|hit|kill]`   | `ok`             | Inform the bot of the result of its last shot            |
| `finished`                     | `yes` / `no`     | Whether the game is over                                 |
| `win`                          | `yes` / `no`     | Whether this bot has won                                 |
| `lose`                         | `yes` / `no`     | Whether this bot has lost                                |
| `dump PATH`                    | `ok`             | Save field and ship layout to a file                     |
| `load PATH`                    | `ok`             | Load field and ship layout from a file                   |

---

## 🧾 Dump / Load File Format
WIDTH HEIGHT SIZE DIRECTION X Y ...


- `WIDTH`, `HEIGHT`: Field dimensions
- Each ship:
  - `SIZE`: Length of the ship (1–4)
  - `DIRECTION`: `h` (horizontal) or `v` (vertical)
  - `X`, `Y`: Top-left coordinates

### Example:
`10 10 1 v 0 0 2 h 3 4 4 h 1 8`

---

## 🧠 Strategies

Your bot must implement at least two strategies:

- **Ordered** — Fires from (0,0) row by row (used for testing)
- **Custom** — Your unique strategy (used by default)

You can implement more strategies and allow switching via command.

---

## 📌 Requirements

- Only one `master` and one `slave` per game
- Cannot start the game until field size and ship counts are valid
- Cannot change field or ship counts after the game starts
- Coordinates are 0-based, with (0,0) being the top-left
- `get shot` must be followed by `set result` before the next move
- Strategy can be changed mid-game
- `load` can override setup (before game start)

---

## 💡 Implementation Notes

- The program must run as either a `master` or `slave` per launch
- All interaction is through **stdin** and **stdout**
- Organize code using proper abstractions (input/output, game logic, strategies)
- Writing unit tests is encouraged
- Pay attention to architecture — it will be evaluated

---

## 🏆 Bonus: Tournament Mode

After the final deadline, a tournament will be held with bots competing within each group.

**Rules:**
- Each pair plays 2 games (roles swapped)
- Win both: 3 points; draw: 1; lose: 0
- Invalid commands, crashes, or rule violations = automatic loss
- `slave` fires first
- `master` must survive until game ends
- Top 5 players get bonus points (1st = +5, 5th = +1)

**Memory limit:** 64 MB

---


## 👨‍💻 Author

1st-year CS student @ ITMO University  
GitHub: [npapaHAHA](https://github.com/npapaHAHA)



