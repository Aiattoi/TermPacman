/**
 * @file COrangeGhost.h
 * @brief Implementation of orange ghost - Clyde 
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include "CMoving.h"
#include "CGhost.h"

class COrangeGhost : public CGhost {
public:
    /**
     * @brief Constructor, initializes positions and looks.
     *
     * @param[in] spawn
     */
    COrangeGhost(std::pair<size_t, size_t> spawn);

    virtual ~COrangeGhost() = default;
    /**
    * @brief Gets direction ghost should take next.
    *
    * @param[in] diff -difficulty
    * @param[in] map
    * @param[in] pacmanPos -pacman position
    * @param[in] pacMove -pacman move
    * @return direction ghost should take next
    */
    std::pair<size_t, size_t> getDir(const CDifficulty &diff, const CMap &map,
                                     const std::pair<size_t, size_t> &pacmanPos,
                                     const std::pair<size_t, size_t> &pacMove) const override;

    /**
     * @brief Prints ghost's look to the output stream.
     *
     * @param[in, out] os -output stream
     */
    void draw(std::ostream &os) const override;
};
