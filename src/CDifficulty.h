/**
 * @file CDifficulty.h
 * @brief Abstract class above difficulties
 * @author Aiattoi
 * @date 2021-05-09
 */

#pragma once

#include <vector>
#include "CMap.h"

class CDifficulty {
public:
    /**
     * @brief Constructor, initializes modes durations.
     *
     * @param[in] mScatter -durations of scatter mode
     * @param[in] mChase -durations of chase mode
     */
    CDifficulty(const std::array<size_t, 4> &mScatter, const std::array<size_t, 3> &mChase,
                size_t vulnerableTime, size_t ghostRespawnTime,
                size_t gameSpeed, size_t ghostSpeed);

    virtual ~CDifficulty() = default;

    /**
     * @brief Getter of the current mode.
     *
     * @return true -scatter mode, false -chase mode
     */
    bool isScatter() const;

    /**
     * @brief Getter of the duration of the vulnerable mode.
     *
     * @return duration of the vulnerable mode
     */
    size_t getVulnerableTime() const;

    /**
     * @brief Getter of the duration of ghost respawning.
     *
     * @return duration of ghost respawning
     */
    size_t getGhostRespawnTime() const;

    /**
     * @brief Getter of the game speed.
     *
     * @return game speed in milliseconds
     */
    size_t getGameSpeed() const;

    /**
     * @brief Getter of the ghosts speed.
     *
     * @return ghost movement ratio
     */
    size_t getGhostSpeed() const;

    /**
     * @brief Getter of the game phase - number of the active chase mode.
     *
     * m_isScatter is also updated here.
     *
     * @param[in] timer
     * @return number of the active chase mode
     */
    int getPhase(size_t timer);

    /**
     * @brief getDirs for the red ghost, implemented in child classes.
     */
    virtual std::pair<int, int>
    RedStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                const std::pair<int, int> &pacMove,
                const std::pair<size_t, size_t> &myPos,
                const std::pair<int, int> &myMove, bool isFrightened) const = 0;

    /**
     * @brief getDirs for the pink ghost, implemented in child classes.
     */
    virtual std::pair<int, int>
    PinkStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                 const std::pair<int, int> &pacMove,
                 const std::pair<size_t, size_t> &myPos,
                 const std::pair<int, int> &myMove, bool isFrightened) const = 0;

    /**
     * @brief getDirs for the blue ghost, implemented in child classes.
     */
    virtual std::pair<int, int>
    BlueStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                 const std::pair<int, int> &pacMove,
                 const std::pair<size_t, size_t> &myPos,
                 const std::pair<int, int> &myMove, bool isFrightened) const = 0;

    /**
     * @brief getDirs for the orange ghost, implemented in child classes.
     */
    virtual std::pair<int, int>
    OrangeStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<int, int> &pacMove,
                   const std::pair<size_t, size_t> &myPos,
                   const std::pair<int, int> &myMove, bool isFrightened) const = 0;

protected:
    /**
     * @brief Common core for all ghost's individual strategies.
     *
     * Decides direction according to current game mode.
     *
     * @param[in] map
     * @param[in] target -target tile in chase mode
     * @param[in] scatterTarget -target tile in scatter mode
     * @param[in] myPos
     * @param[in] myMove
     * @param[out] possibleDirs
     * @param[out] minDist
     * @param[in] isFrightened
     * @return preferred direction to follow
     */
    std::pair<int, int>
    Strategy(const CMap &map, const std::pair<size_t, size_t> &target,
             const std::pair<size_t, size_t> &scatterTarget,
             const std::pair<size_t, size_t> &myPos,
             const std::pair<int, int> &myMove,
             std::vector<std::pair<int, int>> &possibleDirs, int &minDist,
             bool isFrightened) const;

private:
    /**
     * @brief Gets possible directions for a ghost to move and a preferred one.
     *
     * Checks the neighbouring tiles,
     * those, which can be stepped on are returned through possibleDirs.
     * When there is only one possible direction, method returns it.
     * In case there are more possible directions, method returns {0,0}.
     *
     * @param[in] map
     * @param[in] myPos -my position
     * @param[in] myMove -my last move
     * @param[out] possibleDirs
     * @return direction, that ghost should move in, {0,0} - when there are more than 1 possible direction
     */
    std::pair<int, int>
    getDirs(const CMap &map, const std::pair<size_t, size_t> &myPos,
            const std::pair<int, int> &myMove,
            std::vector<std::pair<int, int>> &possibleDirs) const;

    /**
     * @brief Gets the direction, that brings ghost closest to its target,
     * returns the distance too.
     *
     * @param[in] map
     * @param[in] possibleDirs
     * @param[in] myPos -my position
     * @param[in] target -target position
     * @param[out] minDist -minimal distance to target
     * @return direction, that brings ghost closest to its target
     */
    std::pair<int, int> moreDirs(const CMap &map, const std::vector<std::pair<int, int>> &possibleDirs,
                                 const std::pair<size_t, size_t> &myPos, const std::pair<size_t, size_t> &target,
                                 int &minDist) const;

    const std::array<std::pair<int, int>, 4> dirs = {std::make_pair(0, -1),
                                                     std::make_pair(-1, 0),
                                                     std::make_pair(0, 1),
                                                     std::make_pair(1, 0)};
    /**< up, left, down, right - prioritizing like the original pacman game */
    std::array<size_t, 4> m_scatter;
    std::array<size_t, 3> m_chase;
    bool m_isScatter;
    size_t m_vulnerableTime;
    size_t m_ghostRespawnTime;
    size_t m_gameSpeed;
    size_t m_ghostSpeed;
};
