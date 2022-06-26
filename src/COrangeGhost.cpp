/**
 * @file COrangeGhost.cpp
 * @brief Implementation of orange ghost - Clyde
 * @author Aiattoi
 * @date 2021-05-28
 */


#include "COrangeGhost.h"

COrangeGhost::COrangeGhost(std::pair<size_t, size_t> spawn)
        : CGhost(spawn, "\u001b[33mA\u001b[0m", "\u001b[33ma\u001b[0m") {}

std::pair<size_t, size_t>
COrangeGhost::getDir(const CDifficulty &diff, const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                     const std::pair<size_t, size_t> &pacMove) const {
    return diff.OrangeStrategy(map, pacmanPos, pacMove, m_position, m_prevMove, m_frightened);
}

void COrangeGhost::draw(std::ostream &os) const {
    os << m_look;
}

