/**
 * @file CGhost.cpp
 * @brief Abstract class above ghosts
 * @author Aiattoi
 * @date 2021-05-28
 */

#include "CGhost.h"

#include <utility>

CGhost::CGhost(const std::pair<size_t, size_t> &spawn, std::string look, std::string frightenedLook)
        : CMoving(spawn, std::move(look)), m_active(false), m_frightened(false),
          m_frightenedLook(std::move(frightenedLook)),
          m_prevContent(" "), m_respawnTime(0), m_waiting(false) {}

void CGhost::activate(CMap &map) {
    map.replace(m_position, m_prevContent);
    m_frightened ? map.replace(map.getSpawnPos(), m_frightenedLook) : map.replace(map.getSpawnPos(), m_look);
    m_position = map.getSpawnPos();
    m_active = true;
    m_waiting = false;
}

void CGhost::respawn(CMap &map) {
    if (map.at(m_position) == m_look || map.at(m_position) == m_frightenedLook)
        map.replace(m_position, " ");
    map.replace(m_spawnPosition, m_look);
    m_position = m_spawnPosition;
    m_prevContent = " ";
    m_active = false;
    m_waiting = true;
    m_prevMove = {0, 0};
}

void CGhost::respawnNotEaten(CMap &map) {
    if (map.at(m_position) == m_look || map.at(m_position) == m_frightenedLook)
        map.replace(m_position, m_prevContent);
    map.replace(m_spawnPosition, m_look);
    m_position = m_spawnPosition;
    m_prevContent = " ";
    m_active = false;
    m_waiting = false;
    m_prevMove = {0, 0};
}

void CGhost::changeState(CMap &map) {
    m_frightened ? m_frightened = false : m_frightened = true;
    if (m_frightened && m_active)
        map.replace(m_position, m_frightenedLook);
    else
        map.replace(m_position, m_look);
}

int CGhost::nextStep(CMap &map, std::pair<int, int> dir, bool &vulnerable) {
    if (dir.first == 0 && dir.second == 0)
        return 0;
    std::pair<size_t, size_t> nextPos = nextPosition(dir);
    std::string next = map.at(nextPos);
    char nextContent = next[0] == '\\' ? next[10] : next[0];
    if (nextContent == 'C') {
        //pacman
        if (vulnerable)
            return 2;
        map.replace(m_position, m_prevContent);
        m_prevContent = " ";
        map.replace(nextPos, m_look);
        updatePosition(dir);
        return 1;
    }
    if (nextContent == 'T') {
        //teleport
        map.replace(m_position, m_prevContent);
        if (vulnerable)
            map.replace(map.getTeleportEnd(m_position), m_frightenedLook);
        else
            map.replace(map.getTeleportEnd(m_position), m_look);
        m_position = map.getTeleportEnd(m_position);
        m_prevMove = dir;
    } else if (nextContent == ' ' || nextContent == '.' || nextContent == 'o' || nextContent == 'B') {
        map.replace(m_position, m_prevContent);
        m_prevContent = nextContent;
        if (vulnerable)
            map.replace(nextPos, m_frightenedLook);
        else
            map.replace(nextPos, m_look);
        updatePosition(dir);
    }
    m_prevMove = dir;
    return 0;
}

bool CGhost::isActive() const {
    return m_active;
}

bool CGhost::isFrightened() const {
    return m_frightened;
}

char CGhost::getPrevContent() const {
    return m_prevContent[0] != '\u001b' ? m_prevContent[0]
                                        : m_prevContent[5] != '1' ? m_prevContent[5] : m_prevContent[7];;
}

bool CGhost::isRespawnTime(const size_t &timer) const {
    if (m_waiting)
        return timer == m_respawnTime;
    return false;
}

void CGhost::setRespawnTime(size_t time) {
    m_respawnTime = time;
}


