# Pac-Man

## Descriere
Proiectul implementează structura de bază a jocului Pac-Man, un joc clasic de tip arcade.

## Regulile jocului
- Jucătorul controlează pe Pac-Man, care trebuie să mănânce toate punctele din labirint.
- Există 4 fantome care încearcă să îl prindă.
- Dacă Pac-Man mănâncă o bilă specială, fantomele devin vulnerabile pentru scurt timp.
- Jocul se termină când Pac-Man pierde toate viețile sau când labirintul este golit de puncte.

- `W` - move Up,
- `A` - move Left,
- `D` - move Right,
- `S` - move Down,

## Structuri de date
- `Point` – coordonatele obiectelor (x, y).
- `Direction` – direcțiile posibile de mișcare.
- `Board` – harta jocului.
- `Pacman` – jucătorul.
- `Ghost` – inamicii.
- `GameEngine` – logica jocului.
- `Painter` – afișarea grafică.
