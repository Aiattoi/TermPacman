/**
 * @file CHard.cpp
 * @brief Hard difficulty implementation
 * @author Aiattoi
 * @date 2021-05-29
 */

#include "CHard.h"


CHard::CHard()
//no scatter
//spawn a ghost every ~5s
//vulnerable time ~10s, ghost respawn time ~5s, game speed move/~0.15 s, ghost speed move/~0.15 s
        : CDifficulty({0, 0, 0, 0},
                      {5, 5, 5}, 10, 5, 1, 1) {}

std::pair<int, int>
CHard::RedStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<int, int> &pacMove,
                   const std::pair<size_t, size_t> &myPos,
                   const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    return Strategy(map, pacmanPos, {map.getWidth(), 0}, myPos, myMove, possibleDirs, minDist, isFrightened);
}

std::pair<int, int>
CHard::PinkStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                    const std::pair<int, int> &pacMove,
                    const std::pair<size_t, size_t> &myPos,
                    const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    std::pair<int, int> target = pacmanPos;
    target.first += pacMove.first;
    target.second += pacMove.second;
    return Strategy(map, target, {0, 0}, myPos, myMove, possibleDirs, minDist, isFrightened);
}

std::pair<int, int>
CHard::BlueStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
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
CHard::OrangeStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                      const std::pair<int, int> &pacMove,
                      const std::pair<size_t, size_t> &myPos,
                      const std::pair<int, int> &myMove, bool isFrightened) const {
    std::vector<std::pair<int, int>> possibleDirs;
    int minDist = -1;
    std::pair<int, int> target = pacmanPos;
    target.first += 1;
    return Strategy(map, target, {0, map.getHeight()}, myPos, myMove, possibleDirs, minDist, isFrightened);
}
