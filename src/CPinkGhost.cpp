/**
 * @file CPinkGhost.cpp
 * @brief Implementation of pin ghost - Pinky
 * @author Aiattoi
 * @date 2021-05-28
 */

#include "CPinkGhost.h"


CPinkGhost::CPinkGhost(std::pair<size_t, size_t> spawn)
        : CGhost(spawn, "\u001b[35mA\u001b[0m", "\u001b[35ma\u001b[0m") {}

std::pair<size_t, size_t>
CPinkGhost::getDir(const CDifficulty &diff, const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<size_t, size_t> &pacMove) const {
    return diff.PinkStrategy(map, pacmanPos, pacMove, m_position, m_prevMove, m_frightened);
}

void CPinkGhost::draw(std::ostream &os) const {
    os << m_look;
}
