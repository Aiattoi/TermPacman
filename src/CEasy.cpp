/**
 * @file CEasy.cpp
 * @brief Easy difficulty implementation
 * @author Aiattoi
 * @date 2021-05-28
 */

#include "CEasy.h"


CEasy::CEasy()
//~5s without ghosts, ~20s red chase, ~15s red scatter, ~10s red+pink chase,
//~30s red+pink scatter, ~5s red+pink+blue chase, ~50s red+pink+blue scatter,
//then all ghosts chase
//vulnerable time ~20s, ghost respawn time ~10s, game speed move/~0.175 s, ghost speed move/~(4*0.175) s
        : CDifficulty({5, 15, 30, 50},
                      {20, 10, 5}, 20, 10, 2, 4) {}

std::pair<int, int>
CEasy::RedStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<int, int> &pacMove,
                   const std::pair<size_t, size_t> &myPos,
                   const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    std::pair<size_t, size_t> dir;
    int minDist = -1;
    dir = Strategy(map, pacmanPos, {map.getWidth(), 0}, myPos, myMove, possibleDirs, minDist, isFrightened);
    if (!isFrightened && !isScatter() && minDist != -1)
        return pacMove;
    return dir;
}

std::pair<int, int>
CEasy::PinkStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                    const std::pair<int, int> &pacMove,
                    const std::pair<size_t, size_t> &myPos,
                    const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    std::pair<size_t, size_t> dir;
    int minDist = -1;
    dir = Strategy(map, pacmanPos, {0, 0}, myPos, myMove, possibleDirs, minDist, isFrightened);
    if (!isFrightened && !isScatter() && minDist != -1)
        return pacMove;
    return dir;
}

std::pair<int, int>
CEasy::BlueStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                    const std::pair<int, int> &pacMove,
                    const std::pair<size_t, size_t> &myPos,
                    const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    std::pair<size_t, size_t> dir;
    int minDist = -1;
    dir = Strategy(map, pacmanPos, {map.getWidth(), map.getHeight()}, myPos, myMove, possibleDirs, minDist,
                   isFrightened);
    if (!isFrightened && !isScatter() && minDist != -1)
        return pacMove;
    return dir;
}

std::pair<int, int>
CEasy::OrangeStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                      const std::pair<int, int> &pacMove,
                      const std::pair<size_t, size_t> &myPos,
                      const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    std::pair<size_t, size_t> dir;
    int minDist = -1;
    dir = Strategy(map, pacmanPos, {0, map.getHeight()}, myPos, myMove, possibleDirs, minDist, isFrightened);
    if (!isFrightened && !isScatter() && minDist != -1)
        return pacMove;
    return dir;
}
