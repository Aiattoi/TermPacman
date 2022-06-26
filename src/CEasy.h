/**
 * @file CEasy.h
 * @brief Easy difficulty implementation
 * @author Aiattoi
 * @date 2021-05-09
 */

#pragma once

#include "CDifficulty.h"

class CEasy : public CDifficulty {
public:
    /**
     * @brief Constructor, initializes modes durations.
     */
    CEasy();

    virtual ~CEasy() = default;
    /**
     * @brief Implementation of red ghost movement strategy.
     *
     * 3 movement modes:
     * -frightened: acts randomly on intersections
     * -scatter: tries to reach the upper right hand corner of the map
     * -chase: same move as pacman on intersections
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
     * 3 movement modes:
     * -frightened: acts randomly on intersections
     * -scatter: tries to reach the upper left hand corner of the map
     * -chase: same move as pacman on intersections
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
     * 3 movement modes:
     * -frightened: acts randomly on intersections
     * -scatter: tries to reach the lower right hand corner of the map
     * -chase: same move as pacman on intersections
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
     * 3 movement modes:
     * -frightened: acts randomly on intersections
     * -scatter: tries to reach the lower left hand corner of the map
     * -chase: same move as pacman on intersections
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
