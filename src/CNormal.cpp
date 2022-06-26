/**
 * @file CNormal.cpp
 * @brief Normal difficulty implementation
 * @author Aiattoi
 * @date 2021-05-29
 */

#include "CNormal.h"

CNormal::CNormal()
//mode duration as an original game
//~7s without ghosts, ~20s red chase, ~7s red scatter, ~20s red+pink chase,
//~5s red+pink scatter, ~20s red+pink+blue chase, ~5s red+pink+blue scatter,
//then all ghosts chase
//vulnerable time ~15s, ghost respawn time ~10s, game speed move/~0.175 s, ghost speed move/~(2*0.175) s
        : CDifficulty({7, 7, 5, 5},
                      {20, 20, 20}, 15, 10, 2, 2) {}

CNormal::CNormal(std::array<size_t, 4> mScatter, std::array<size_t, 3> mChase,
                 size_t vulnerableTime, size_t ghostRespawnTime,
                 size_t gameSpeed, size_t ghostSpeed)
        : CDifficulty(mScatter, mChase, vulnerableTime, ghostRespawnTime, gameSpeed, ghostSpeed) {}

std::pair<int, int>
CNormal::RedStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                     const std::pair<int, int> &pacMove,
                     const std::pair<size_t, size_t> &myPos,
                     const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    return Strategy(map, pacmanPos, {map.getWidth(), 0}, myPos, myMove, possibleDirs, minDist, isFrightened);
}

std::pair<int, int>
CNormal::PinkStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                      const std::pair<int, int> &pacMove,
                      const std::pair<size_t, size_t> &myPos,
                      const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    std::pair<int, int> target = pacmanPos;
    target.first += 4 * pacMove.first;
    target.second += 4 * pacMove.second;
    return Strategy(map, target, {0, 0}, myPos, myMove, possibleDirs, minDist, isFrightened);
}

std::pair<int, int>
CNormal::BlueStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                      const std::pair<int, int> &pacMove,
                      const std::pair<size_t, size_t> &myPos,
                      const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    std::pair<int, int> target = pacmanPos;
    target.first += -1;
    return Strategy(map, target, {map.getWidth(), map.getHeight()}, myPos, myMove, possibleDirs, minDist, isFrightened);
}

std::pair<int, int>
CNormal::OrangeStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                        const std::pair<int, int> &pacMove,
                        const std::pair<size_t, size_t> &myPos,
                        const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    std::pair<size_t, size_t> dir;
    int minDist = -1;
    dir = Strategy(map, pacmanPos, {0, map.getHeight()}, myPos, myMove, possibleDirs, minDist, isFrightened);
    if (minDist > 8)
        return dir;
    if (dir.first == 0 && dir.second == 0)
        dir = possibleDirs[random() % possibleDirs.size()];
    return dir;
}
