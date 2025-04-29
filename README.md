# cub3D 🕹️ | 42 Amman

## 📖 Project Overview

**cub3D** is a 42 school project aiming to recreate a simple 3D game engine using **raycasting** principles, similar to early 90s shooters like **Wolfenstein 3D**.  
This project teaches fundamental graphics rendering, event handling, and 3D projection concepts, while adhering to strict C programming standards.

> 🎉 **Final Grade: 125/100 (with bonus)**

---

## 🎯 Goals

- Master window management, colors, textures, and event loops with **MiniLibX**.
- Apply mathematical concepts like trigonometry for raycasting.
- Strengthen C programming practices, memory management, and rigorous Norm compliance.
- Parse and validate structured configuration files.

---

## 🛠️ How to Run

### 1️⃣ Clone the repository  
```bash
git clone <your-repo-link>
cd cub3d
```

### 2️⃣ Build the project  
```bash
make
```

### 3️⃣ Run with a `.cub` map file  
```bash
./cub3D maps/good/your_map.cub
```

---

## 📄 Map File Format

A `.cub` file contains:

- Texture paths:
  ```
  NO ./textures/north_texture.png
  SO ./textures/south_texture.png
  ```
- Floor & ceiling colors:
  ```
  F 220,100,0
  C 225,30,0
  ```
- 2D map grid using:
  - `1` → Wall
  - `0` → Empty space
  - `N`, `S`, `E`, `W` → Player's starting position & orientation
  - `D` → Door (Bonus)

**Example**
```
11111
10001
10N01
11111
```

---

## ✨ Controls

| Key      | Action               |
|:---------|:--------------------|
| `W` `A` `S` `D` | Move player |
| `←` `→` | Rotate view |
| `ESC`   | Exit game |
| Close button | Exit cleanly |

---

## 🎁 Bonus Features

✅ Wall collisions  
✅ Minimap system  
✅ Animated textures  
✅ Mouse look support  

---

## 📂 Project Structure

```
cub3D/
├── inc/            # Header files
├── libft/          # Custom C library
├── MLX42/          # MiniLibX library
├── maps/           # .cub map files
├── src/            # Project source files
├── textures/       # Wall textures
├── obj/            # Compiled objects
├── Makefile
└── README.md
```

---

## 🖼️ Screenshots

![creepy map](creepy_map.png)  
![library map](library_map.png)


