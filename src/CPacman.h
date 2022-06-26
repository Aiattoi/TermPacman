/**
 * @file CPacman.h
 * @brief Pacman implementation.
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include "CMoving.h"
#include "CMap.h"

class CPacman : public CMoving {
public:
    /**
     * @brief Constructor, initializes positions and look.
     *
     * @param[in] spawn -spawn position
     */
    CPacman(std::pair<size_t, size_t> spawn);

    virtual ~CPacman() = default;
    /**
     * @brief Makes a step in a direction 'dir'.
     *
     * @param[in, out] map
     * @param[in] dir -direction to go
     * @param[in, out] vulnerable -vulnerable/frightened mode signalization
     * @return 1=pacman lost a life, 2=ghost captured, 0=no life lost
     */
    int nextStep(CMap &map, std::pair<int, int> dir, bool &vulnerable) override;

    /**
     * @brief Prints pacman's look to the output stream.
     *
     * @param[in, out] os -output stream
     */
    void draw(std::ostream &os) const override;

    /**
     * @brief Adds 'inc' points to pacman's score.
     *
     * @param inc -increment, number of point to add
     */
    void addToScore(size_t inc);

    /**
     * @brief Removes 1 pacman's life.
     */
    void removeLive();

    /**
     * @brief Getter of pacman's score.
     *
     * @return pacman's score
     */
    size_t getScore() const;

    /**
     * @brief Getter of pacman's remaining lives.
     *
     * @return count of pacman's remaining lives
     */
    size_t getLives() const;

private:
    size_t m_score;
    size_t m_lives;
};
