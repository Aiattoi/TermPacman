/**
 * @file CDifficulty.cpp
 * @brief Abstract class above difficulties
 * @author Aiattoi
 * @date 2021-05-28
 */

#include "CDifficulty.h"


CDifficulty::CDifficulty(const std::array<size_t, 4> &mScatter, const std::array<size_t, 3> &mChase,
                         size_t vulnerableTime, size_t ghostRespawnTime,
                         size_t gameSpeed, size_t ghostSpeed)
        : m_scatter(mScatter), m_chase(mChase), m_isScatter(true),
        m_vulnerableTime(vulnerableTime), m_ghostRespawnTime(ghostRespawnTime),
        m_gameSpeed(gameSpeed), m_ghostSpeed(ghostSpeed){}

bool CDifficulty::isScatter() const {
    return m_isScatter;
}

size_t CDifficulty::getVulnerableTime() const {
    return m_vulnerableTime;
}

size_t CDifficulty::getGhostRespawnTime() const {
    return m_ghostRespawnTime;
}

size_t CDifficulty::getGameSpeed() const {
    if(m_gameSpeed==1)
        return 150;
    if(m_gameSpeed==2)
        return 175;
    if(m_gameSpeed==3)
        return 200;
}

size_t CDifficulty::getGhostSpeed() const {
    return m_ghostSpeed;
}

int CDifficulty::getPhase(size_t timer) {
    long unsigned int time = m_scatter[0];
    int phase = -1;
    while (phase < (int) m_chase.size() - 1) {
        if (timer <= time) {
            m_isScatter = true;
            return phase;
        }
        ++phase;
        time += m_chase[phase];
        if (timer <= time) {
            m_isScatter = false;
            return phase;
        }
        time += m_scatter[phase + 1];
    }
    if (timer <= time) {
        m_isScatter = true;
        return phase;
    }
    //from now on only chase
    m_isScatter = false;
    return 3;
}

std::pair<int, int>
CDifficulty::Strategy(const CMap &map, const std::pair<size_t, size_t> &target,
                      const std::pair<size_t, size_t> &scatterTarget,
                      const std::pair<size_t, size_t> &myPos,
                      const std::pair<int, int> &myMove,
                      std::vector<std::pair<int, int>> &possibleDirs, int &minDist,
                      bool isFrightened) const {
    std::pair<int, int> dir = getDirs(map, myPos, myMove, possibleDirs);
    if (isFrightened) {
        if (dir.first == 0 && dir.second == 0)
            dir = possibleDirs[random() % possibleDirs.size()];
        return dir;
    }

    if (isScatter()) {
        if (dir.first == 0 && dir.second == 0)
            dir = moreDirs(map, possibleDirs, myPos, scatterTarget, minDist);
        return dir;
    }

    if (dir.first == 0 && dir.second == 0)
        dir = moreDirs(map, possibleDirs, myPos, target, minDist);
    return dir;
}

std::pair<int, int>
CDifficulty::getDirs(const CMap &map, const std::pair<size_t, size_t> &myPos,
                     const std::pair<int, int> &myMove,
                     std::vector<std::pair<int, int>> &possibleDirs) const {

    std::pair<int, int> invMyMove = {-myMove.first, -myMove.second};
    //get possible dirs
    for (const auto &dir:dirs) {
        std::string neighbour =
                map.at(std::make_pair(myPos.first + dir.first, myPos.second + dir.second));
        char neighbourContent =
                neighbour[0] != '\u001b' ? neighbour[0] : neighbour[5] != '1' ? neighbour[5] : neighbour[7];
        if (neighbourContent == 'C' && dir != invMyMove)
            return dir;
        if (neighbourContent == ' ' || neighbourContent == '.' || neighbourContent == 'o'
        || neighbourContent == 'B' || neighbourContent == 'T')
            if (dir != invMyMove)
                possibleDirs.push_back(dir);
    }
    //nowhere to go, except to return
    if (possibleDirs.empty())
        return invMyMove;
    //only one dir
    if (possibleDirs.size() == 1)
        return possibleDirs[0];
    //more dirs
    return {0,0};
}

std::pair<int, int> CDifficulty::moreDirs(const CMap &map, const std::vector<std::pair<int, int>> &possibleDirs,
                                          const std::pair<size_t, size_t> &myPos,
                                          const std::pair<size_t, size_t> &target,
                                          int &minDist) const {
    int dist;
    std::pair<int, int> mov;
    for (const auto &dir:possibleDirs) {
        dist = map.distance({myPos.first + dir.first, myPos.second + dir.second}, target);
        if (minDist == -1 || dist < minDist) {
            minDist = dist;
            mov = dir;
        }
    }
    return mov;
}
