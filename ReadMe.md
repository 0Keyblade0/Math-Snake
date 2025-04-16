# Math Snake 🐍➕ (Legacy C++ Project)

A math-based twist on the classic Snake game, developed in C++ using CLion. Players were intended to solve arithmetic challenges while controlling the snake — consuming the correct answer to grow, and avoiding incorrect ones to survive.

> ⚠️ **Note:** This project relies on external libraries that are no longer available, and will not build or run in its current state. It is preserved here for educational and reference purposes.

---

## 🧠 Concept

- A math problem appears on screen.
- The snake must consume the correct answer from options on the board.
- Wrong choices or wall/self-collisions result in game over.
- Designed with a modular architecture across controller, model, view, and test layers.

---

## 🛠 Project Structure

```
Math-Snake/
├── controller.cxx/hxx  # Handles game input and tick updates
├── food.cxx/hxx        # Spawns math problem answers as food
├── model.cxx/hxx       # Core game state and rules
├── view.cxx/hxx        # (Broken) Intended to handle UI rendering
├── snake.cxx/hxx       # Snake behavior and logic
├── main.cxx            # Entry point of the game
├── model_test.cxx      # Unit tests for game logic
├── CMakeLists.txt      # Build configuration
└── metadata.yml        # Metadata for project indexing
```

---

## 🧪 Tests

Includes a `model_test.cxx` file with test cases focused on game logic components.

To run tests (if working):

```bash
mkdir build
cd build
cmake ..
make
./ModelTest  # If `ModelTest` is defined as a test target
```

---

## 🚫 Why It Doesn't Run

- External dependencies used for rendering and input are no longer maintained or accessible.
- View and interaction logic depend on unknown or unavailable libraries.
- Code is retained as a reference for game architecture and modular C++ design.

---

## 📚 Educational Takeaways

- Demonstrates modular game architecture in C++
- Implements game mechanics, state transitions, and simple test-driven design
- Uses CMake as a modern C++ build tool

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

**Originally developed in CLion as a passion project combining math and gameplay.**
