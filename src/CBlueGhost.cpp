/**
 * @file CBlueGhost.cpp
 * @brief Implementation of blue ghost - Inky
 * @author Aiattoi
 * @date 2021-05-28
 */

#include "CBlueGhost.h"


CBlueGhost::CBlueGhost(std::pair<size_t, size_t> spawn)
        : CGhost(spawn, "\u001b[34mA\u001b[0m", "\u001b[34ma\u001b[0m") {}

std::pair<size_t, size_t>
CBlueGhost::getDir(const CDifficulty &diff, const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<size_t, size_t> &pacMove) const {
    return diff.BlueStrategy(map, pacmanPos, pacMove, m_position, m_prevMove, m_frightened);
}

void CBlueGhost::draw(std::ostream &os) const {
    os << m_look;
}
