/**
 * @file CMoving.h
 * @brief Abstract class above Pacman and ghosts.
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include <utility>

#include "CMap.h"

class CMoving {
public:
    /**
     * @brief Constructor, initializes positions and look.
     *
     * @param[in] spawn -spawn position
     * @param[in] look
     */
    CMoving(const std::pair<size_t, size_t> &spawn, std::string look);

    virtual  ~CMoving() = default;

    /**
     * @brief Moves object back to its spawning position.
     *
     * @param[in, out] map
     */
    virtual void respawn(CMap &map);

    /**
     * @brief Updates position according to the direction passed.
     *
     * @param[in] dir -direction
     */
    void updatePosition(std::pair<int, int> dir);

    /**
     * @brief Makes a step in a direction 'dir', implemented in child classes.
     */
    virtual int nextStep(CMap &map, std::pair<int, int> dir, bool &vulnerable) = 0;

    /**
     * @brief Getter of position changed by direction 'dir'.
     *
     * @param[in] dir -direction
     * @return position+dir
     */
    std::pair<size_t, size_t> nextPosition(const std::pair<int, int> &dir) const;

    /**
     * @brief Getter of position.
     *
     * @return position
     */
    std::pair<size_t, size_t> getPosition() const;

    /**
     * @brief Getter of previous move.
     *
     * @return previous move
     */
    const std::pair<size_t, size_t> &getPrevMove() const;

    /**
     * @brief Overloaded << operator, for object printing.
     *
     * @param[in, out] os -output stream
     * @param[in] mov -object to print
     * @return output stream with printed object
     */
    friend std::ostream &operator<<(std::ostream &os, const CMoving &mov);

    /**
     * @brief Prints the object to the output stream.
     *
     * @param[in, out] os -output stream
     */
    virtual void draw(std::ostream &os) const = 0;

protected:
    std::pair<size_t, size_t> m_spawnPosition;
    std::pair<size_t, size_t> m_position;
    std::string m_look;
    std::pair<size_t, size_t> m_prevMove;
};
