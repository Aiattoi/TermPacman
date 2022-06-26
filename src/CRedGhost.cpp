/**
 * @file CRedGhost.cpp
 * @brief Implementation of red ghost - Blinky
 * @author Aiattoi
 * @date 2021-05-28
 */

#include "CRedGhost.h"


CRedGhost::CRedGhost(std::pair<size_t, size_t> spawn)
        : CGhost(spawn, "\u001b[31mA\u001b[0m", "\u001b[31ma\u001b[0m") {}

std::pair<size_t, size_t>
CRedGhost::getDir(const CDifficulty &diff, const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                  const std::pair<size_t, size_t> &pacMove) const {
    return diff.RedStrategy(map, pacmanPos, pacMove, m_position, m_prevMove, m_frightened);
}

void CRedGhost::draw(std::ostream &os) const {
    os << m_look;
}
