# Snake Game

## Compilation and Execution

### Requirements
*   A C++ compiler with support for the C++20 standard.
*   CMake (version 3.3 or higher).

### Compilation - cmake (linux)
1.  In the root directory of the project, create a `build` folder:
    ```bash
    mkdir build
    ```
2.  Go to the newly created folder:
    ```bash
    cd build
    ```
3.  Run CMake to generate the build files:
    ```bash
    cmake ..
    ```
4.  Compile the project:
    ```bash
    cmake --build .
    ```


<img width="500" height="350" alt="image" src="https://github.com/user-attachments/assets/5cfb7d1b-14d0-483f-b4be-d7fd8f1af5cc" /> 
<img width="500" height="600" alt="image" src="https://github.com/user-attachments/assets/0af2ec3e-2205-41bc-85f3-095e8e91f967" />


*Game might not work correctly in windows terminals*

### Running the Game
After successful compilation, an executable file `snejks` will be created in the `build` folder.

*   To run the game with the main menu:
    ```bash
    ./snejks
    ```
*   To run the game directly (skipping the menu):
    ```bash
    ./snejks --play
    ```
*   To display help:
    ```bash
    ./snejks --help
    ```

## Command-line Arguments

The program supports the following command-line arguments:

*   `--help`, `-h`: Displays help with a description of the arguments and exits the program.
*   `--play`, `-p`: Starts the game immediately with default settings and skips the main menu. After the game ends, the program exits.

## Controls

The game is controlled using the keyboard:

| Key | Action |
|---|---|
| `W` | Move up (↑) |
| `A` | Move left (←) |
| `S` | Move down (↓) |
| `D` | Move right (→) |
| `T` | Immediately quit the game |

In the menu, number keys (`1`-`4`) are used to select options.


## 1. Game Logic

### Game Loop
The game uses multiple threads to ensure smooth gameplay. The main logic is divided into three separate threads:

1.  **Input Thread (`inputThread`):** Listens for user input (key presses) and updates the snake's direction or ends the game without blocking other threads.
2.  **Compute Thread (`computeThread`):** Responsible for all game logic – snake movement, collision detection, item collection, and score updates. The thread is put to sleep between loop steps, which determines the game speed.
3.  **Render Thread (`renderThread`):** Handles rendering the current game state to the terminal.

Synchronization between threads is managed using `std::mutex` and `std::condition_variable`. After each state update, the compute thread "wakes up" the render thread to display the changes. The mutex ensures that only one thread accesses shared data (game state, snake position, etc.) at a time, preventing synchronization issues.

### Snake Movement
The snake moves in steps in the direction determined by a movement vector (`x_vec`, `y_vec`). With each game state update, the head moves one step in the given direction. The snake's body (tail) is updated so that each tail segment moves to the previous position of the segment in front of it. When an item is collected, the snake's length increases by one segment.

### Collision Detection
At each step of the game logic, the following collisions are checked:
*   **Collision with the game board edges:** The snake's head coordinates are compared with the game board dimensions.
*   **Collision with walls:** Checks if the snake's head coordinates are the same as any wall's coordinates.
*   **Collision with its own body:** Determines if the snake's head coordinates are in the list of tail coordinates.

In case of any of these collisions, the game ends, and the score is displayed.

### Dynamic Difficulty
The game speed changes dynamically depending on the chosen difficulty and the player's current score.
*   **Speed:** As the score increases, the delay between game loop steps shortens, making the game faster. The rate of acceleration and the initial speed depend on the initially chosen difficulty.
*   **Number of walls:** The number of walls is calculated from the size of the game board and the chosen difficulty.

## 2. Classes and Methods

*   **`Game`**: The central class that controls the game itself.
    *   `startGame()`: Starts the game threads (input, compute, render).
    *   `stopGame()`- Ends the game threads and displays the game over screen.
    *   `inputLoop()`, `computeLoop()`, `renderLoop()`: Methods implementing the logic for individual game threads.
    *   `updateSnake()`: Updates the snake's position on the map.
    *   `checkCollisions()`: Checks for collisions between the snake and any object on the map or the map border.
    *   `inputHandle(char)`: Processes user input and changes the snake's direction.
    *   `calculateGameSpeed()`: Calculates the current game speed based on the score and difficulty.
    *   `renderGame()`: Renders the game board, snake, items, and score.
    *   `endScreen()`: Displays the final screen with the final game score.

*   **`GameMenu`**: A class for managing the main menu and game settings, responsible for the game's execution.
    *   `gameLoop()`: The main menu loop that displays the menu and responds to user choices.
    *   `showMenu()`, `showSettings()`, `showControls()`: Methods for displaying individual screens (main menu, settings, controls).
    *   `startGame()`: Creates a `Game` instance and starts the game with the currently set parameters.

*   **`Snake`**: Represents the snake.
    *   `Constructor` - allows you to set the default position of the snake, its length and the symbols that will be rendered for the head and body.
    *   `updateHead()`: Moves the snake's head in the current direction (determined by vectors).
    *   `updateTail()`: Updates the tail segments.
    *   `incrementSize()`: Increases the snake's length by one segment.
    *   `setDirection(string)`: Changes the snake's direction of movement.
    *   `getTailCoords()`: Returns a list of positions where the individual tail segments are located.

*   **`Item`**: The parent class for all objects on the game board. It stores their position (`x`, `y`) and graphical symbol.
    *   `respawnItem(width, height)`: Places the item at a random position within the game board.

*   **`CollectItem`**: A class for a collectible item by the snake, inherits from `Item`.

*   **`Walls`**: A class that manages the walls in the game field.
    *   `placeWalls(...)`: Randomly places walls on the game board, making sure that a wall does not appear in the immediate vicinity of the snake's head. The walls are represented as an array of `Item` objects.

*   **`FilePrinter`**: A helper static class.
*   `printFile(filePath, shouldAnimate)`: Prints the content of a file to the console. If the `shouldAnimate` parameter is true, it waits for a short while after each printed line (for an animation effect).



### Running Tests
The tests are compiled along with the game. They can be run from the `build` folder:
```bash
ctest
```
or directly:
```bash
./game-test-runner
```

## 3. Testing

The program is tested using unit tests with the Catch2 framework.

### Unit Tests
A set of tests (`game_tests/game_test.cpp`) covers key parts of the logic:
*   **`Snake constructor test`**: Verifies the correct setting of the snake's values in the constructor.
*   **`Snake move test`**: Tests the movement of the snake's head and the change of direction.
*   **`Snake tail move test`**: Checks if the tail correctly follows the head.
*   **`Item test spawn`**: Verifies that items appear at valid coordinates.
*   **`Game difficulty affects wall count`**: Tests whether the number of walls changes depending on the difficulty.
*   **`Game speed calculation`**: Verifies the correctness of the game speed calculation based on the score.
*   **`GameMenu settings management`**: Checks the default values of the settings in the menu.
*   **`GameMenu settings modification`**: Tests whether it is possible to change the game settings (dimensions, difficulty).

### Game Strategy

*   **Winning strategy:**
    - The game cannot be won, the goal is to survive as long as possible and collect as many items as possible.
*   **Losing**:
    - The player loses if they hit the edges of the map, their own tail, or the walls on the map.
