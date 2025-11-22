#include "game-engine.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <random>
#include <chrono>
#include <thread>
#include <cmath>

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
    _ghostStarts = { Point{10, 9}, Point{9, 10}, Point{10, 10}, Point{11, 10} };
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
        if (x != 5 && x != 14) _map[4][x] = '#';
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

void GameEngine::DrawBoard() const {
    Point pacPos = _pacman.GetPosition();
    std::array<Point, 4> ghostPos;
    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        ghostPos[i] = _ghosts[i].GetPosition();
    }

    const std::array<char, 4> ghostChars = {'R', 'P', 'I', 'C'};

    for (int y = 0; y < _board->GetHeight(); y++) {
        for (int x = 0; x < _board->GetWidth(); x++) {
            Point p{x, y};
            if (p == pacPos) {
                std::cout << 'P';
                continue;
            }

            bool isGhost = false;
            for (std::size_t i = 0; i < ghostPos.size(); i++) {
                if (p == ghostPos[i]) {
                    std::cout << ghostChars[i];
                    isGhost = true;
                    break;
                }
            }
            if (isGhost) continue;

            std::cout << _map[y][x];
        }
        std::cout << "\n";
    }
    std::cout << "Scor: " << _pacman.GetScore() << "  Vieti: " << _pacman.GetLives() << "\n";
    std::cout << "WASD pentru miscare, Q pentru iesire:\n";
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
        if (!IsWall(c)) {
            result.push_back(c);
        }
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

    for (std::size_t i = 0; i < _ghosts.size(); i++) {
        Point gpos = _ghosts[i].GetPosition();
        Point target = pacPos;

        if (i == 0) {
         
            target = pacPos;
        } else if (i == 1) {
        
            target = pacPos;
            Direction d = _pacman.GetDirection();
            Point t = target;
            for (int k = 0; k < 3; k++) {
                if (d == Direction::Up)    t.y--;
                if (d == Direction::Down)  t.y++;
                if (d == Direction::Left)  t.x--;
                if (d == Direction::Right) t.x++;
                if (IsWall(t)) break;
                target = t;
            }
        } else if (i == 2) {
            Point blinkyPos = _ghosts[0].GetPosition();
            Point mid = pacPos;
            Direction d = _pacman.GetDirection();
            if (d == Direction::Up)    mid.y -= 2;
            if (d == Direction::Down)  mid.y += 2;
            if (d == Direction::Left)  mid.x -= 2;
            if (d == Direction::Right) mid.x += 2;
            Point v{mid.x - blinkyPos.x, mid.y - blinkyPos.y};
            target = Point{blinkyPos.x + 2 * v.x, blinkyPos.y + 2 * v.y};
            if (IsWall(target) || target.x < 0 || target.x >= _board->GetWidth()
                || target.y < 0 || target.y >= _board->GetHeight()) {
                target = pacPos;
            }
        } else if (i == 3) {
            int dist = Manhattan(gpos, pacPos);
            if (dist > 8) {
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
    bool running = true;

    while (running) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        DrawBoard();

        char c;
        std::cin >> c;

        if (c == 'q' || c == 'Q') break;

        if (c == 'w' || c == 'W') _pacman.Move(Direction::Up);
        else if (c == 's' || c == 'S') _pacman.Move(Direction::Down);
        else if (c == 'a' || c == 'A') _pacman.Move(Direction::Left);
        else if (c == 'd' || c == 'D') _pacman.Move(Direction::Right);

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

        MoveGhosts();

        Point pacPos = _pacman.GetPosition();
        bool collision = std::any_of(_ghosts.begin(), _ghosts.end(), [&](const Ghost& g) {
            return g.GetPosition() == pacPos;
        });

        if (collision) {
            _pacman.LoseLife();
            if (_pacman.GetLives() <= 0) {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                DrawBoard();
                std::cout << "Game over!\n";
                running = false;
            } else {
                ResetPositions();
            }
        } else if (!HasPellets()) {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            DrawBoard();
            std::cout << "Ai castigat!\n";
            running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}
