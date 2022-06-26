/**
 * @file CVeryEasy.h
 * @brief Very Easy difficulty implementation
 * @author Aiattoi
 * @date 2021-06-06
 */

#pragma once

#include "CDifficulty.h"

class CVeryEasy : public CDifficulty {
public:
    /**
     * @brief Constructor, initializes modes durations.
     */
    CVeryEasy();

    virtual ~CVeryEasy() = default;
    /**
     * @brief Implementation of red ghost movement strategy.
     *
     * Always move the same as pacman.
     *
     * @param[in] map
     * @param[in] pacmanPos -pacman position
     * @param[in] pacMove -pacman move
     * @param[in] myPos -my position
     * @param[in] myMove -my previous move
     * @param[in] isFrightened -vulnerable/frightened mode indicator
     * @return direction, which should ghost follow
     */
    std::pair<int, int>
    RedStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                const std::pair<int, int> &pacMove,
                const std::pair<size_t, size_t> &myPos,
                const std::pair<int, int> &myMove, bool isFrightened) const override;

    /**
     * @brief Implementation of pink ghost movement strategy.
     *
     * Use pacman move on intersections.
     *
     * @param[in] map
     * @param[in] pacmanPos -pacman position
     * @param[in] pacMove -pacman move
     * @param[in] myPos -my position
     * @param[in] myMove -my previous move
     * @param[in] isFrightened -vulnerable/frightened mode indicator
     * @return direction, which should ghost follow
     */
    std::pair<int, int>
    PinkStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                 const std::pair<int, int> &pacMove,
                 const std::pair<size_t, size_t> &myPos,
                 const std::pair<int, int> &myMove, bool isFrightened) const override;

    /**
     * @brief Implementation of blue ghost movement strategy.
     *
     * Move around spawn bunker.
     *
     * @param[in] map
     * @param[in] pacmanPos -pacman position
     * @param[in] pacMove -pacman move
     * @param[in] myPos -my position
     * @param[in] myMove -my previous move
     * @param[in] isFrightened -vulnerable/frightened mode indicator
     * @return direction, which should ghost follow
     */
    std::pair<int, int>
    BlueStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                 const std::pair<int, int> &pacMove,
                 const std::pair<size_t, size_t> &myPos,
                 const std::pair<int, int> &myMove, bool isFrightened) const override;

    /**
     * @brief Implementation of orange ghost movement strategy.
     *
     * Capture pacman.
     *
     * @param[in] map
     * @param[in] pacmanPos -pacman position
     * @param[in] pacMove -pacman move
     * @param[in] myPos -my position
     * @param[in] myMove -my previous move
     * @param[in] isFrightened -vulnerable/frightened mode indicator
     * @return direction, which should ghost follow
     */
    std::pair<int, int>
    OrangeStrategy(const CMap &map, const std::pair<size_t, size_t> &pacmanPos,
                   const std::pair<int, int> &pacMove,
                   const std::pair<size_t, size_t> &myPos,
                   const std::pair<int, int> &myMove, bool isFrightened) const override;
};
