/**
 * @file CVeryEasy.cpp
 * @brief Very Easy difficulty implementation
 * @author Aiattoi
 * @date 2021-06-06
 */

#include "CVeryEasy.h"


CVeryEasy::CVeryEasy()
//~5s without ghosts, ~20s red chase, ~15s red scatter, ~10s red+pink chase,
//~30s red+pink scatter, ~5s red+pink+blue chase, ~50s red+pink+blue scatter,
//then all ghosts chase
//vulnerable time ~20s, ghost respawn time ~10s, game speed move/~0.2 s, ghost speed move/~(5*0.2) s
        : CDifficulty({0, 0, 0, 0},
                      {5, 5, 5}, 5, 10, 3, 5) {}

std::pair<int, int>
CVeryEasy::RedStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<int, int> &pacMove,
                   const std::pair<size_t, size_t> &myPos,
                   const std::pair<int, int> &myMove, bool isFrightened) const {
        return pacMove;
}

std::pair<int, int>
CVeryEasy::PinkStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
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
CVeryEasy::BlueStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                    const std::pair<int, int> &pacMove,
                    const std::pair<size_t, size_t> &myPos,
                    const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    std::pair<size_t, size_t> target = {map.getWidth()/2, map.getHeight()/2};
    return Strategy(map, target, target, myPos, myMove, possibleDirs, minDist,
                   isFrightened);
}

std::pair<int, int>
CVeryEasy::OrangeStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                      const std::pair<int, int> &pacMove,
                      const std::pair<size_t, size_t> &myPos,
                      const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    std::pair<size_t, size_t> dir;
    int minDist = -1;
    return Strategy(map, pacmanPos, pacmanPos, myPos, myMove, possibleDirs, minDist, isFrightened);
}

