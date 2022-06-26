/**
 * @file CHard.h
 * @brief Hard difficulty implementation
 * @author Aiattoi
 * @date 2021-05-09
 */

#pragma once

#include "CDifficulty.h"

class CHard : public CDifficulty {
public:
    /**
     * @brief Constructor, initializes modes durations.
     */
    CHard();

    virtual ~CHard() = default;
    /**
   * @brief Implementation of red ghost movement strategy.
   *
   * 2 movement modes:
   * -frightened: acts randomly on intersections
   * -chase: on intersections chooses direction, that is closest to the target tile
   *
   * target: pacman position
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
     * 2 movement modes:
     * -frightened: acts randomly on intersections
     * -chase: on intersections chooses direction, that is closest to the target tile
     *
     * target: 1 tile before pacman position, if he maintains his current direction
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
     * 2 movement modes:
     * -frightened: acts randomly on intersections
     * -chase: on intersections chooses direction, that is closest to the target tile
     *
     * target: tile, that is on the left from pacman position
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
     * 2 movement modes:
     * -frightened: acts randomly on intersections
     * -chase: on intersections chooses direction, that is closest to the target tile
     *
     * target: tile, that is on the right from pacman position
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
