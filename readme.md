# Minesweeper Implementation in C    
\
\
A command-line implementation of the classic Minesweeper game. This project focuses on manual memory management, pointer arithmetic, and the separation of game logic from the user interface.


## Architecture and Logic

The core complexity of this application lies in the Dual-Board System. To ensure data integrity and prevent information leakage while maintaining the game state, the program manages two distinct dynamic matrices simultaneously:

### 1. The Logic Board (int **pBoard)

This matrix constitutes the hidden layer, invisible to the user. It stores the actual state of the game using integer constants to represent mines and numerical values for proximity calculations. This separation ensures that the game state is calculated independently of the rendering.

### 2. The View Board (char **pShowBoard)

This matrix acts as the presentation layer or mask. It is the grid rendered to the terminal. Initially filled with blank characters, it is updated only when the user explores or marks a coordinate. It fetches data from the Logic Board only upon valid user moves.


## Technical Highlights

* **Dynamic Memory Allocation:** Utilizes malloc and free to generate grids of user-defined sizes (up to 35x35) at runtime, preventing stack overflow on large grids.

* **Double Pointers:** Extensive use of int ** and char ** to handle 2D array navigation and storage.

* **Input Validation:** Implementation of strict coordinate checking to prevent segmentation faults or out-of-bound array access.


## Build and Run

To compile and execute the program, a standard GCC compiler is required.

### Compilation

gcc mine_sweeper.c -o minesweeper

### Execution

./minesweeper


## Future Improvements

* Translation of in-game UI text from Spanish to English.

* Implementation of a recursive flood-fill algorithm to automatically reveal empty adjacent areas.

* Refactoring code into separate header files for better modularity.
