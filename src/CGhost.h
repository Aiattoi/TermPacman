/**
 * @file CGhost.h
 * @brief Abstract class above ghosts
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include "CMoving.h"
#include "CDifficulty.h"

class CGhost : public CMoving {
public:
    /**
     * @brief Constructor, initializes positions and looks.
     *
     * @param[in] spawn
     * @param[in] look
     * @param[in] frightenedLook
     */
    CGhost(const std::pair<size_t, size_t> &spawn, std::string look, std::string frightenedLook);

    virtual ~CGhost() = default;

    /**
     * @brief Spawn ghost to game.
     *
     * @param[in, out] map
     */
    void activate(CMap &map);

    /**
     * @brief Return ghost back to spawn position.
     *
     * @param[in, out] map
     */
    void respawn(CMap &map) override;

    /**
     * @brief Return ghost back to spawn position.
     *
     * @param[in, out] map
     */
    void respawnNotEaten(CMap &map);

    /**
     * @brief Change frightened mode - on/off and change look accordingly.
     *
     * @param[in, out] map
     */
    void changeState(CMap &map);

    /**
     * @brief Gets direction ghost should take next, implemented in child classes.
     */
    virtual std::pair<size_t, size_t> getDir(const CDifficulty &diff, const CMap &map,
                                             const std::pair<size_t, size_t> &pacmanPos,
                                             const std::pair<size_t, size_t> &pacMove) const = 0;

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
     * @brief Getter of active state.
     *
     * @return true=ghost active, false=ghost waiting
     */
    bool isActive() const;

    /**
     * @brief Getter of frightened/vulnerable state.
     *
     * @return true=ghost frightened/vulnerable->can be captured,
     * false=not frightened/vulnerable->cannot be captured
     */
    bool isFrightened() const;

    /**
     * @brief Getter of previous content of the tile, where the ghost now stands.
     *
     * @return previous content of the tile, where the ghost now stands
     */
    char getPrevContent() const;

    /**
     * @brief Checks if it's time for ghost to reactivate.
     *
     * @param[in] timer
     * @return true=respawnTime->reactivate, false=notRespawnTime->wait
     */
    bool isRespawnTime(const size_t &timer) const;

    /**
     * @brief Setter of respawn time.
     *
     * @param[in] time -time when the ghost should be reactivated
     */
    void setRespawnTime(size_t time);

protected:
    bool m_active;
    bool m_frightened;
    std::string m_frightenedLook;
    std::string m_prevContent;
    size_t m_respawnTime;
    bool m_waiting;
};
