/**
 * @file CMoving.cpp
 * @brief Abstract class above Pacman and ghosts.
 * @author Aiattoi
 * @date 2021-05-26
 */

#include "CMoving.h"

CMoving::CMoving(const std::pair<size_t, size_t> &spawn, std::string look)
        : m_spawnPosition(spawn),
          m_position(spawn),
          m_look(std::move(look)), m_prevMove({0, 0}) {}

void CMoving::respawn(CMap &map) {
    if (map.at(m_position) == m_look)
        map.replace(m_position, " ");
    map.replace(m_spawnPosition, m_look);
    m_position = m_spawnPosition;
    m_prevMove = {0, 0};
}

void CMoving::updatePosition(std::pair<int, int> dir) {
    m_position.first += dir.first;
    m_position.second += dir.second;
    m_prevMove = dir;
}

std::pair<size_t, size_t> CMoving::nextPosition(const std::pair<int, int> &dir) const {
    std::pair<size_t, size_t> pos = m_position;
    pos.first += dir.first;
    pos.second += dir.second;
    return pos;
}

std::pair<size_t, size_t> CMoving::getPosition() const {
    return m_position;
}

const std::pair<size_t, size_t> &CMoving::getPrevMove() const {
    return m_prevMove;
}

std::ostream &operator<<(std::ostream &os, const CMoving &mov) {
    mov.draw(os);
    return os;
}
