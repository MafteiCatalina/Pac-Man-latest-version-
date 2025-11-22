#include "game-engine.hpp"
#include "raylib.h"
#include "external/json.hpp"

#include <algorithm>
#include <array>
#include <queue>
#include <random>
#include <chrono>
#include <cmath>
#include <fstream>

using json = nlohmann::json;

static int Manhattan(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

static std::mt19937& Rng() {
    static std::mt19937 rng(std::random_device{}());
    return rng;
}

GameEngine::GameEngine() {
    _board = std::make_unique<Board>(20, 20);
    _pacmanStart = {1, 1};
    _ghostStarts = {
        Point{10, 10},
        Point{11, 10},
        Point{12, 10},
        Point{13, 10}
    };
}

void GameEngine::Init() {
    int w = _board->GetWidth();
    int h = _board->GetHeight();

    _map.assign(h, std::string(w, '.'));

    for (int x = 0; x < w; x++) {
        _map[0][x] = '#';
        _map[h - 1][x] = '#';
    }
    for (int y = 0; y < h; y++) {
        _map[y][0] = '#';
        _map[y][w - 1] = '#';
    }

    for (int x = 2; x < w - 2; x++) {
        if (x != 5 && x != 14) _map[4][x]  = '#';
        if (x != 10)          _map[10][x] = '#';
        if (x != 6 && x !=16) _map[15][x] = '#';
    }

    for (int y = 2; y < h - 2; y++) {
        if (y != 5 && y != 12) _map[y][3]  = '#';
        if (y != 7 && y != 14) _map[y][8]  = '#';
        if (y != 6 && y != 11) _map[y][13] = '#';
        if (y != 9 && y != 16) _map[y][17] = '#';
    }

    _pacman = Pacman(_pacmanStart);
    _map[_pacmanStart.y][_pacmanStart.x] = '.';

    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        _ghosts[i] = Ghost(_ghostStarts[i]);
        _map[_ghostStarts[i].y][_ghostStarts[i].x] = ' ';
    }
}

bool GameEngine::IsWall(const Point& p) const {
    int w = _board->GetWidth();
    int h = _board->GetHeight();
    if (p.x < 0 || p.x >= w || p.y < 0 || p.y >= h) return true;
    return _map[p.y][p.x] == '#';
}

bool GameEngine::HasPellets() const {
    return std::any_of(_map.begin(), _map.end(), [](const std::string& row) {
        return row.find('.') != std::string::npos;
    });
}

std::vector<Point> GameEngine::GetNeighbors(const Point& p) const {
    std::vector<Point> result;
    std::array<Point, 4> candidates = {
        Point{p.x, p.y - 1},
        Point{p.x, p.y + 1},
        Point{p.x - 1, p.y},
        Point{p.x + 1, p.y}
    };
    for (const auto& c : candidates) {
        if (!IsWall(c)) result.push_back(c);
    }
    return result;
}

static Point BFSNextStep(const std::vector<std::string>& map,
                         const Board& board,
                         const Point& start,
                         const Point& target)
{
    int w = board.GetWidth();
    int h = board.GetHeight();

    auto isWall = [&](const Point& p) {
        if (p.x < 0 || p.x >= w || p.y < 0 || p.y >= h) return true;
        return map[p.y][p.x] == '#';
    };

    if (start == target) return start;

    std::queue<Point> q;
    std::vector<std::vector<bool>> used(h, std::vector<bool>(w, false));
    std::vector<std::vector<Point>> parent(h, std::vector<Point>(w, Point(-1, -1)));

    q.push(start);
    used[start.y][start.x] = true;

    bool found = false;

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur == target) {
            found = true;
            break;
        }

        std::array<Point, 4> cand = {
            Point{cur.x, cur.y - 1},
            Point{cur.x, cur.y + 1},
            Point{cur.x - 1, cur.y},
            Point{cur.x + 1, cur.y}
        };

        for (auto& nx : cand) {
            if (!isWall(nx) && !used[nx.y][nx.x]) {
                used[nx.y][nx.x] = true;
                parent[nx.y][nx.x] = cur;
                q.push(nx);
            }
        }
    }

    if (!found) {
        std::array<Point, 4> cand = {
            Point{start.x, start.y - 1},
            Point{start.x, start.y + 1},
            Point{start.x - 1, start.y},
            Point{start.x + 1, start.y}
        };
        std::vector<Point> valid;
        for (auto& c : cand) {
            if (!isWall(c)) valid.push_back(c);
        }
        if (valid.empty()) return start;
        return *std::min_element(valid.begin(), valid.end(),
            [&](const Point& a, const Point& b) {
                return Manhattan(a, target) < Manhattan(b, target);
            });
    }

    Point cur = target;
    Point prev = target;
    while (!(cur == start)) {
        prev = cur;
        cur = parent[cur.y][cur.x];
    }
    return prev;
}

void GameEngine::MoveGhosts() {
    Point pacPos = _pacman.GetPosition();

    Point blinkyPos = _ghosts[0].GetPosition();

    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        Point gpos = _ghosts[i].GetPosition();
        Point target = pacPos;

        if (i == 0) {
            target = pacPos;
        } else if (i == 1) {
            target = pacPos;
            Direction d = _pacman.GetDirection();
            Point t = target;
            for (int k = 0; k < 4; k++) {
                if (d == Direction::Up)    t.y--;
                if (d == Direction::Down)  t.y++;
                if (d == Direction::Left)  t.x--;
                if (d == Direction::Right) t.x++;
                if (IsWall(t)) break;
                target = t;
            }
        } else if (i == 2) {
            Point mid;
            mid.x = (pacPos.x + blinkyPos.x) / 2;
            mid.y = (pacPos.y + blinkyPos.y) / 2;
            target = mid;
        } else if (i == 3) {
            int dist = Manhattan(gpos, pacPos);
            if (dist > 6) {
                target = pacPos;
            } else {
                target = Point{1, _board->GetHeight() - 2};
            }
        }

        Point next = BFSNextStep(_map, *_board, gpos, target);
        _ghosts[i].SetPosition(next);
    }
}

void GameEngine::ResetPositions() {
    _pacman.SetPosition(_pacmanStart);
    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        _ghosts[i].SetPosition(_ghostStarts[i]);
    }
}

void GameEngine::Run() {
    int cellSize = 32;
    int w = _board->GetWidth();
    int h = _board->GetHeight();
    int screenW = w * cellSize;
    int screenH = h * cellSize;

    InitWindow(screenW, screenH, "Pac-Man Raylib");
    SetTargetFPS(60);

    bool running = true;
    int ghostStepCounter = 0;
    int ghostStepDelay = 25;

    while (running && !WindowShouldClose()) {
        bool movedThisFrame = false;

        if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
            _pacman.Move(Direction::Up);
            movedThisFrame = true;
        }
        if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
            _pacman.Move(Direction::Down);
            movedThisFrame = true;
        }
        if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
            _pacman.Move(Direction::Left);
            movedThisFrame = true;
        }
        if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
            _pacman.Move(Direction::Right);
            movedThisFrame = true;
        }

        if (movedThisFrame) {
            Point pos = _pacman.GetPosition();
            Direction d = _pacman.GetDirection();

            Point next = pos;
            if (d == Direction::Up)    next.y--;
            if (d == Direction::Down)  next.y++;
            if (d == Direction::Left)  next.x--;
            if (d == Direction::Right) next.x++;

            if (!IsWall(next)) {
                if (_map[next.y][next.x] == '.') {
                    _pacman.EatDot();
                    _map[next.y][next.x] = ' ';
                }
                _pacman.SetPosition(next);
            }
        }

        ghostStepCounter++;
        if (ghostStepCounter >= ghostStepDelay) {
            MoveGhosts();
            ghostStepCounter = 0;
        }

        Point pacPos = _pacman.GetPosition();
        bool collision = std::any_of(_ghosts.begin(), _ghosts.end(), [&](const Ghost& g) {
            return g.GetPosition() == pacPos;
        });

        if (collision) {
            _pacman.LoseLife();
            if (_pacman.GetLives() <= 0) {
                running = false;
            } else {
                ResetPositions();
            }
        } else if (!HasPellets()) {
            running = false;
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                char c = _map[y][x];
                int px = x * cellSize;
                int py = y * cellSize;

                if (c == '#') {
                    DrawRectangle(px, py, cellSize, cellSize, BLUE);
                } else if (c == '.') {
                    float cx = px + cellSize / 2.0f;
                    float cy = py + cellSize / 2.0f;
                    DrawCircle(cx, cy, cellSize * 0.15f, YELLOW);
                }
            }
        }

        Point pac = _pacman.GetPosition();
        float pacX = pac.x * cellSize + cellSize / 2.0f;
        float pacY = pac.y * cellSize + cellSize / 2.0f;
        DrawCircle(pacX, pacY, cellSize * 0.4f, YELLOW);

        std::array<Color, 4> ghostColors = { RED, PINK, SKYBLUE, ORANGE };

        for (std::size_t i = 0; i < _ghosts.size(); i++) {
            Point gp = _ghosts[i].GetPosition();
            float gx = gp.x * cellSize + cellSize / 2.0f;
            float gy = gp.y * cellSize + cellSize / 2.0f;
            float r = cellSize * 0.4f;

            Vector2 top   = { gx,      gy - r };
            Vector2 left  = { gx - r,  gy + r };
            Vector2 right = { gx + r,  gy + r };

            DrawTriangle(top, left, right, ghostColors[i]);
        }

        DrawText(TextFormat("Scor: %d  Vieti: %d",
                            _pacman.GetScore(),
                            _pacman.GetLives()),
                 10, 10, 20, BLACK);

        EndDrawing();
    }

    json data;
    data["score"] = _pacman.GetScore();
    std::ofstream file("save.json");
    file << data;

    CloseWindow();
}
