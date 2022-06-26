/**
* @file CMap.cpp
* @brief Pacman map implementation
* @author Aiattoi
* @date 2021-05-26
*/

#include "CMap.h"

bool CMap::load(std::istream &is) {
    bool pacmanFound = false, spawnFound = false, bonusFound = false;
    m_points = 0;
    size_t ghosts = 1, teleports = 0;
    size_t height = 0, width = 0;
    char nextChar;
    while (!(is.eof())) {
        is.get(nextChar);
        switch (nextChar) {
            default:
                return false;
            case ('\n'):
                if (height == 0)
                    m_width = width;
                if (width != m_width && !(is.eof()))
                    return false;
                width = 0;
                height++;
                break;
            case ('='):
                if (spawnFound)
                    return false;
                m_spawn = std::make_pair(width, height);
                spawnFound = true;
                insert(std::make_pair(width, height), nextChar);
                width++;
                break;
            case ('T'):
                if (++teleports > 2)
                    return false;
                if (teleports == 1)
                    teleport1 = std::make_pair(width, height);
                else if (teleports == 2)
                    teleport2 = std::make_pair(width, height);
                insert(std::make_pair(width, height), nextChar);
                width++;
                break;
            case ('C'):
                if (pacmanFound)
                    return false;
                m_spawns[0] = std::make_pair(width, height);
                pacmanFound = true;
                insert(std::make_pair(width, height), nextChar);
                width++;
                break;
            case ('A'):
                if (ghosts > 4)
                    return false;
                m_spawns[ghosts++] = std::make_pair(width, height);
                insert(std::make_pair(width, height), nextChar);
                width++;
                break;
            case ('B'):
                if (bonusFound)
                    return false;
                bonusFound = true;
            case ('.'):
                m_points++;
            case ('o'):
            case ('X'):
            case (' '):
                insert(std::make_pair(width, height), nextChar);
                width++;
                break;
        }
    }
    m_height = height - 1;
    if (!pacmanFound || !spawnFound || !bonusFound || ghosts != 5 || teleports != 2)
        return false;

    if (!checkTileNeighbours(m_spawn, 2, 2)
        || !checkTileNeighbours(teleport1, 1, 3)
        || !checkTileNeighbours(teleport2, 1, 3))
        return false;
    return true;
}

const std::array<std::pair<size_t, size_t>, 5> &CMap::getSpawns() const {
    return m_spawns;
}

void CMap::printMap() const {
    for (size_t height = 0; height < m_height; ++height) {
        for (size_t width = 0; width < m_width; ++width) {
            std::cout << m_map.at(std::make_pair(width, height));
        }
        std::cout << std::endl;
    }
}

size_t CMap::getHeight() const {
    return m_height;
}

size_t CMap::getWidth() const {
    return m_width;
}

const std::string &CMap::at(const std::pair<size_t, size_t> &tile) const {
    return m_map.at(tile);
}

void CMap::replace(const std::pair<size_t, size_t> &tile, std::string content) {
    m_map[tile] = std::move(content);
}

void CMap::removePoint() {
    m_points--;
}

size_t CMap::getPoints() const {
    return m_points;
}

std::pair<size_t, size_t> CMap::getSpawnPos() const {
    return m_spawn;
}

std::pair<size_t, size_t> CMap::getTeleportEnd(const std::pair<size_t, size_t> &from) const {
    return from == teleport1 ? teleport2 : teleport1;
}

size_t CMap::distance(const std::pair<size_t, size_t> &from,
                      const std::pair<size_t, size_t> &to) const {
    int x = from.first, y=from.second;
    x-=to.first; y-=to.second;
    return round(hypot(x,y));
}

void CMap::insert(const std::pair<size_t, size_t> &tile, char content) {
    std::string in;
    in.push_back(content);
    m_map.insert(std::make_pair(tile, in));
}

bool CMap::checkTileNeighbours(std::pair<size_t, size_t> &t, size_t resEmpty, size_t resWall) const {
    //up, down, right, left
    std::array<std::pair<int, int>, 4> dirs = {std::make_pair(0, -1),
                                               std::make_pair(0, 1),
                                               std::make_pair(1, 0),
                                               std::make_pair(-1, 0)};
    size_t empty = 0;
    size_t wall = 0;
    std::pair<size_t, size_t> update = t;
    for (const auto &dir:dirs) {
        std::string neighbour =
                at(std::make_pair(t.first + dir.first, t.second + dir.second));
        char neighbourContent =
                neighbour[0] != '\u001b' ? neighbour[0] : neighbour[5] != '1' ? neighbour[5] : neighbour[7];
        if (neighbourContent == ' ') {
            //update tile on the first empty tile
            if (update == t) {
                update.first += dir.first;
                update.second += dir.second;
            }
            empty++;
        }
        else if (neighbourContent == 'X')
            wall++;
    }
    if (empty != resEmpty || wall != resWall)
        return false;
    t=update;
    return true;
}
