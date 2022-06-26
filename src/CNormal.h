/**
 * @file CNormal.h
 * @brief Normal difficulty implementation
 * @author Aiattoi
 * @date 2021-05-09
 */

#pragma once

#include "CDifficulty.h"

class CNormal : public CDifficulty {
public:
    /**
     * @brief Constructor, initializes modes durations.
     */
    CNormal();

    virtual ~CNormal() = default;
    /**
     * @brief Constructor, initializes modes durations.
     *
     * @param[in] mScatter -durations of scatter mode
     * @param[in] mChase -durations of chase mode
     * @param[in] vulnerableTime -duration of vulnerable mode
     * @param[in] ghostRespawnTime -duration of ghost respawning
     */
    CNormal(std::array<size_t, 4> mScatter, std::array<size_t, 3> mChase,
            size_t vulnerableTime, size_t ghostRespawnTime,
            size_t gameSpeed, size_t ghostSpeed);

    /**
    * @brief Implementation of red ghost movement strategy.
    *
    * 3 movement modes:
    * -frightened: acts randomly on intersections
    * -scatter: tries to reach the upper right hand corner of the map
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
     * 3 movement modes:
     * -frightened: acts randomly on intersections
     * -scatter: tries to reach the upper left hand corner of the map
     * -chase: on intersections chooses direction, that is closest to the target tile
     *
     * target: 4 tiles before pacman position, if he maintains his current direction
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
     * 3 movement modes:
     * -frightened: acts randomly on intersections
     * -scatter: tries to reach the lower left hand corner of the map
     * -chase: on intersections chooses direction, that is closest to the target tile
     *
     * target: pacman position, if the distance is less than 8, then turns randomly on intersections
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
