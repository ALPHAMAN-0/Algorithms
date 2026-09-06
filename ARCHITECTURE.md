---
tags: [architecture, Algorithms]
---

## Stack
- Language: C++ (`.cpp` files observed, `using namespace std;`).
- No build manifest present (no CMakeLists.txt, Makefile, package.json, etc.).
- Editor config only: `.vscode/` with `c_cpp_properties.json`, `tasks.json`, `launch.json`, `stdc++.h`, `custom.natvis`.
- Not an application/service — a collection of standalone algorithm/DSA practice source files.

## Directory map
| path | what lives there |
|---|---|
| `Problem Set 1/` | Standalone C++ solutions (`Problem 1.cpp`, `Problem 2.cpp`, `Problem 3.cpp`) plus `AIUB Lab Task Final.pdf` (assignment doc) |
| `SUM Algorithms/` | Standalone C++ sum-technique implementations (`prefix_Sum.cpp`, `Suffix_sum.cpp`, `Kadans.cpp`) |
| `.vscode/` | Editor/build config for VS Code (`c_cpp_properties.json`, `tasks.json`, `launch.json`, `stdc++.h`, `custom.natvis`, `settings.json`) |

## Diagram
```mermaid
flowchart TD
    Problem_Set_1["Problem_Set_1"]
    SUM_Algorithms["SUM_Algorithms"]
    VSCode_Config["VSCode_Config"]
```
No edges observed between these — each is an independent, self-contained set of files with no shared code or includes between them.

## Component index
- [[Problem_Set_1]]
- [[SUM_Algorithms]]
- [[VSCode_Config]]

## Entry points
- No single app entry point; each `.cpp` file is independently compiled and run (each contains its own `int main`... TODO: verify — `main` not confirmed read in full for every file).
- Dev: open/build individual file via VS Code tasks in `.vscode/tasks.json` (TODO: verify exact task command — not read in full).
- Prod: none — this is a practice/algorithms repo, not a deployed program.

## Conventions
- `using namespace std;` used in every `.cpp` file read.
- Files in `SUM Algorithms/` open with a large `/* ... */` block comment explaining the algorithm (technique name, complexity, visual example) before any code — seen in `Suffix_sum.cpp`, `prefix_Sum.cpp`, `Kadans.cpp`.
- `Problem Set 1/` files use plain global arrays and free functions (e.g. `Problem 2.cpp` implements a queue with a global `int queue[1000]`; `Problem 3.cpp` implements a stack with a global `int stack[1000]`) — no classes observed.
- Filenames mix spaces (`Problem 1.cpp`) and underscores (`Suffix_sum.cpp`) inconsistently.

## Where things go
- To add a new prefix/suffix/range-sum algorithm: add a new `.cpp` file under `SUM Algorithms/`, following the header-comment style seen in existing files there.
- To add a new problem-set solution: add a new `.cpp` file under `Problem Set 1/` (or a new `Problem Set N/` folder for a new set).
- To change VS Code build/debug behavior: edit files under `.vscode/` (`tasks.json`, `launch.json`, `c_cpp_properties.json`).
