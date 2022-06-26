/**
 * @file CPinkGhost.h
 * @brief Implementation of pin ghost - Pinky 
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include "CMoving.h"
#include "CGhost.h"

class CPinkGhost : public CGhost {
public:
    /**
     * @brief Constructor, initializes positions and looks.
     *
     * @param[in] spawn
     */
    CPinkGhost(std::pair<size_t, size_t> spawn);

    virtual ~CPinkGhost() = default;
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
