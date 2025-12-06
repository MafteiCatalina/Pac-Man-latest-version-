# Pac-Man

## 📌 Descrierea proiectului

Acest proiect implementează o versiune simplificată a jocului clasic **Pac-Man**, folosind limbajul **C++** și biblioteca grafică **raylib**.  
Jocul rulează într-o fereastră grafică și folosește o hartă internă reprezentată ca matrice de caractere, împreună cu clasele:

- `Point` – coordonatele obiectelor (x, y)
- `Direction` – direcțiile posibile de mișcare
- `Board` – harta jocului (dimensiuni)
- `Pacman` – jucătorul
- `Ghost` – inamicii
- `GameEngine` – logica jocului (inițializare, mișcare, coliziuni, randare)
- `Painter` / `AbstractPainter` – interfață și implementare de desen

## 🎮 Regulile jocului

- Jucătorul controlează pe **Pac-Man**, care trebuie să mănânce toate punctele din labirint.
- Mișcarea se face din taste:
  - `W` sau săgeata sus – UP
  - `A` sau săgeata stânga – LEFT
  - `S` sau săgeata jos – DOWN
  - `D` sau săgeata dreapta – RIGHT
- Pe hartă se află 4 fantome care urmăresc jucătorul, fiecare cu o logică de deplasare inspirată din jocul original.
- Dacă Pac-Man se ciocnește cu o fantomă:
  - pierde o viață;
  - dacă nu mai are vieți, jocul se termină (Game Over).
- Când toate punctele (pellets) sunt mâncate, jocul se încheie cu victorie.
- La final, scorul jucătorului este salvat în fișierul `save.json`.

## 🧩 Dependențe ale proiectului

### Limbaj și compilator

- **C++17**
- Compilator recomandat:
  - `g++` (MinGW pe Windows sau g++ pe Linux)
  - sau `clang++`

### Biblioteci externe

- [raylib](https://www.raylib.com/) – pentru fereastră grafică, desenarea formelor și gestionarea tastaturii.
  - În proiect, raylib este așteptat în directorul `external/raylib/` (include + lib).
- [nlohmann/json](https://github.com/nlohmann/json) – pentru salvarea scorului în format JSON.
  - În cod este inclus ca `external/json.hpp`.

### Mediu de dezvoltare

Proiectul a fost testat în:

- **Windows 10/11** cu MinGW și raylib compilat pentru Windows
- Editor recomandat: Visual Studio Code / CLion / VS + extensii pentru C++

## 🛠️ Modul de construire a aplicației

Proiectul folosește un fișier `Makefile`.

### Compilare aplicație

În directorul proiectului:

```bash
make
