```markdown
CLI Minesweeper Implementation in C

A robust command-line implementation of the classic Minesweeper game. This project focuses on manual memory management, pointer arithmetic, and separation of concerns between game logic and user interface.

/* Architecture & Logic */

The core complexity of this application lies in the **Dual-Board System**. To ensure data integrity and prevent "spoilers" while maintaining game state, the program manages two distinct dynamic matrices simultaneously:

/* 1. The Logic Board (`int **pBoard`) */
**Hidden Layer:** This matrix is invisible to the user.
**Function:** Stores the actual state of the game (Mines, Numbers, Empty spaces).
**Values:** Uses integer constants (`1` for Mine, `0` for Empty) to perform proximity calculations efficiently.

/* 2. The View Board (`char **pShowBoard`) */
**Presentation Layer:** This is what is rendered to the terminal.
**Function:** Acts as a mask. Initially filled with 'blanks', it is updated only when the user explores (`E`) or marks (`M`) a coordinate.
**Logic:** It fetches data from `pBoard` only upon valid user moves, ensuring the hidden state remains secure until interaction occurs.

/* Technical Highlights */

* **Dynamic Memory Allocation:** Uses `malloc` and `free` to generate grids of user-defined sizes (up to 35x35) at runtime.
* **Double Pointers:** Extensive use of `int **` and `char **` to handle 2D array navigation.
* **Input Validation:** Strict coordinate checking to prevent segmentation faults or out-of-bound access.

/* How to Build and Run */

**Prerequisites:** GCC Compiler.

# Compile
gcc mine_sweeper.c -o minesweeper

# Run
./minesweeper
