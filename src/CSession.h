/**
 * @file CSession.h
 * @brief The Pacman game handler.
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <termios.h>

#include "CDifficulty.h"

#include "CMap.h"

#include "CMoving.h"
#include "CPacman.h"
#include "CGhost.h"
#include "CRedGhost.h"
#include "CPinkGhost.h"
#include "CBlueGhost.h"
#include "COrangeGhost.h"

class CSession {
public:
    /**
     * @brief Restore initial settings of termios
     * @author Whyrusleeping
     * source: https://gist.github.com/whyrusleeping/3983293
     * @param initial_settings
     */
    void RestoreKeyboardBlocking(struct termios *initial_settings) const;

    /**
     * @brief Set non blocking keyboard reading
     * @author Whyrusleeping
     * source: https://gist.github.com/whyrusleeping/3983293
     * @param initial_settings
     */
    void SetKeyboardNonBlock(struct termios *initial_settings) const;

    /**
     * @brief Read a char in a non blocking way
     * @author Jeremy Sonander
     * source: https://gist.github.com/whyrusleeping/3983293
     */
    char getcharAlt() const;

    /**
     * @brief Constructor, the whole game session takes place here.
     *
     * @param[in] diff -chosen difficulty
     * @param[in] map -chosen map
     */
    CSession(std::shared_ptr<CDifficulty> diff, CMap map);

    /**
     * @brief Destructor, reset of smart pointers.
     */
    ~CSession();

    /**
     * @brief Prints the game session.
     */
    void print() const;

    /**
     * @brief Handles pacman's lives and the game end.
     *
     * @param[in] kill -remove pacman's life
     * @return true -end of the game, false -otherwise
     */
    bool endGameManager(bool kill);

    /**
     * @brief Creates instances of the ghosts.
     */
    void createGhosts();

    /**
     * @brief Handles ghost spawning.
     *
     * Spawns ghosts at the game start according to the phase.
     * Respawns ghosts after capture.
     *
     * @param[in, out] phase -number of chase mode
     */
    void spawnGhosts(int &phase);

    /**
     * @brief Removes ghost from the map and sets his respawn time.
     *
     * @param[in, out] ghost
     */
    void removeGhost(const std::shared_ptr<CGhost> &ghost);

    /**
     * @brief Respawns ghosts and resets the game state.
     *
     * @param[in, out] phase
     * @param[in, out] timerUpdate
     * @param[in, out] vulnerableTime
     * @param[in, out] vulnerable
     */
    void respawnGhosts(int &phase, size_t &timerUpdate, size_t &vulnerableTime,
                       bool &vulnerable);

    /**
     * @brief Handles pacman's move, removes ghosts from the map, if captured by pacman.
     *
     * @param[in] dir -direction of pacman's move
     * @param[in, out] vulnerable -vulnerable/frightened mode signalization
     * @return true -pacman lost a life, false - no pacman's life lost
     */
    bool pacmanMove(const std::pair<int, int> &dir, bool &vulnerable);

    /**
     * @brief Converts player's input to pacman's move.
     *
     * @param[in, out] vulnerable -vulnerable/frightened mode signalization
     * @return true -pacman lost a life, false - no pacman's life lost
     */
    bool convert(bool &vulnerable, size_t gameSpeed);

    /**
     * @brief Handles moving of the ghosts, removes ghosts from the map, if captured by pacman.
     *
     * Moves the active ghosts according to their strategies.
     * On mode change ghosts reverse their direction.
     *
     * @param[in] phase -number of chase mode (max. number of active ghosts)
     * @param[in, out] vulnerable -vulnerable/frightened mode signalization
     * @param[in] modeChanged - mode change signalization
     * @return true -pacman lost a life, false - no pacman's life lost
     */
    bool ghostsMove(int phase, bool &vulnerable, bool modeChanged);

private:
    /**
     * @brief Handles timer update.
     *
     * @param[in, out] timerUpdate -timer update deciding is base on this value
     */
    void timeHandler(size_t &timerUpdate, size_t timerUpdateFrequency);

    std::shared_ptr<CDifficulty> m_diff; /**< chosen difficulty */
    CMap m_map; /**< chosen map */
    size_t m_timer;
    std::shared_ptr<CPacman> m_pacman;
    std::array<std::shared_ptr<CGhost>, 4> m_ghosts;
};
