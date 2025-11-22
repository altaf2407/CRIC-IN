# 🏏 CRIC-IN – Virtual Cricket Game (C++)

CRIC-IN is a console-based virtual cricket simulation game developed using **C++**.  
It allows users to select teams, enter player details, perform toss, and play a ball-by-ball simulated cricket match with scoreboard updates and match summary.

---

## 🎯 Features

- Console-based interactive gameplay  
- Team creation with player name & role  
- Toss system to choose Bat / Bowl  
- Live ball-by-ball match simulation  
- Automatic score update & wickets tracking  
- Overs-based match simulation  
- Strike rotation & innings break  
- Final match summary with Winner declaration  
- Displays top scorer from each team  

---

## 🧠 Concepts Used

- Object-Oriented Programming  
  - Classes & Objects  
  - Encapsulation  
  - Constructors  
- Vectors & Dynamic Data Handling  
- Randomization (`rand()` for outcomes)  
- Modular Game Logic  
- Console I/O Handling

---

## 🔧 Technologies

| Component | Used |
|----------|------|
| Language | C++ |
| Paradigm | OOP |
| IDE (Any) | CodeBlocks / VS Code / Turbo C++ / Dev C++ |

---

## 🎮 Game Flow

1. Enter team names  
2. Enter number of players  
3. Input player name & role  
4. Select overs  
5. Toss decides who bats first  
6. First innings simulation  
7. Target appears  
8. Second innings begins  
9. Final Winner announcement  

---

## 🚀 How to Build & Run

### Using g++

```bash
g++ src/main.cpp src/Player.cpp src/Team.cpp -o CRIC-IN
./CRIC-IN
```

Or simply open the project in any C++ IDE and add `src/*.cpp` files to the project.

---

## 📂 Project Structure

```text
CRIC-IN/
├── include/
│   ├── Player.h
│   └── Team.h
├── src/
│   ├── main.cpp
│   ├── Player.cpp
│   └── Team.cpp
└── README.md
```

---

## ✍ Author

**Altaf Muzaffar**  
B.Tech CSE – Game & Software Developer (Beginner)  

---

## ⭐ Support

If you like this project, don’t forget to ⭐ this repository!  
Suggestions and contributions are always welcome.

---

_Made with ❤️ in C++_
