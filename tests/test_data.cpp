#include <cassert>
#include "../point.hpp"
#include "../board.hpp"
#include "../pacman.hpp"
#include "../ghost.hpp"
#include "../direction.hpp"

int main() {
    Point p1(1, 2);
    Point p2(1, 2);
    Point p3(3, 4);

    assert(p1 == p2);
    assert(!(p1 == p3));

    Point p4;
    p4 = p3;
    assert(p4 == p3);

    Board b1(20, 15);
    Board b2(b1);
    assert(b1 == b2);
    assert(b1.GetWidth() == 20);
    assert(b1.GetHeight() == 15);

    Board b3;
    b3 = b1;
    assert(b3 == b1);

    Pacman pac1;
    int initialScore = pac1.GetScore();
    pac1.EatDot();
    assert(pac1.GetScore() == initialScore + 10);

    int initialLives = pac1.GetLives();
    pac1.LoseLife();
    assert(pac1.GetLives() == initialLives - 1);

    Point startPos(5, 5);
    Pacman pac2(startPos);
    assert(pac2.GetPosition() == startPos);

    pac2.SetPosition(Point(7, 8));
    assert(pac2.GetPosition() == Point(7, 8));

    Pacman pac3(pac2);
    assert(pac3 == pac2);

    Ghost g1;
    Ghost g2(Point(10, 10));
    assert(g2.GetPosition() == Point(10, 10));
    assert(!g2.IsVulnerable());

    g2.SetVulnerable(true);
    assert(g2.IsVulnerable());

    g2.SetDirection(Direction::Left);
    assert(g2.GetDirection() == Direction::Left);

    Ghost g3(g2);
    assert(g3 == g2);

    Ghost g4;
    g4 = g2;
    assert(g4 == g2);

    return 0;
}
