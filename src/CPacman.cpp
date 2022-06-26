/**
 * @file CPacman.cpp
 * @brief Pacman implementation.
 * @author Aiattoi
 * @date 2021-05-26
 */

#include "CPacman.h"

CPacman::CPacman(std::pair<size_t, size_t> spawn)
        : CMoving(std::move(spawn), "\u001b[33;1mC\u001b[0m"), m_score(0), m_lives(3) {}

int CPacman::nextStep(CMap &map, std::pair<int, int> dir, bool &vulnerable) {
    const int point = 10, bonus = 50, ghost = 200;
    if (dir.first == 0 && dir.second == 0)
        dir = m_prevMove;
    std::pair<size_t, size_t> nextPos = nextPosition(dir);
    std::string next = map.at(nextPos);
    char nextContent = next[0] != '\u001b' ? next[0] : next[5] != '1' ? next[5] : next[7];
    switch (nextContent) {
        case ' ':
            //empty space
            map.replace(m_position, " ");
            map.replace(nextPos, m_look);
            updatePosition(dir);
            break;
        case '.':
            //point
            addToScore(point);
            map.replace(m_position, " ");
            map.replace(nextPos, m_look);
            map.removePoint();
            updatePosition(dir);
            break;
        case 'T':
            //teleport
            map.replace(m_position, " ");
            map.replace(map.getTeleportEnd(m_position), m_look);
            m_position = map.getTeleportEnd(m_position);
            m_prevMove = dir;
            break;
        case 'o':
            //change of mode (to vulnerable)
            map.replace(m_position, " ");
            map.replace(nextPos, m_look);
            vulnerable = true;
            updatePosition(dir);
            break;
        case 'B':
            //bonus point
            addToScore(bonus);
            map.replace(m_position, " ");
            map.replace(nextPos, m_look);
            map.removePoint();
            updatePosition(dir);
            break;
        case 'A':
            //ghost
            map.replace(m_position, " ");
            m_prevMove = dir;
            return 1;
        case 'a':
            //vulnerable ghost
            addToScore(ghost);
            map.replace(m_position, " ");
            map.replace(nextPos, m_look);
            updatePosition(dir);
            return 2;
        default:
            m_prevMove = dir;
            return 0;
    }
    m_prevMove = dir;
    return 0;
}

void CPacman::draw(std::ostream &os) const {
    os << m_look;
}

void CPacman::addToScore(size_t inc) {
    m_score += inc;
}

void CPacman::removeLive() {
    m_lives--;
}

size_t CPacman::getScore() const {
    return m_score;
}

size_t CPacman::getLives() const {
    return m_lives;
}

