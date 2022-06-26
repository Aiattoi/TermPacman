/**
 * @file CApplication.h
 * @brief Wrapper of the Pacman game, loads map and difficulty.
 * @author Aiattoi
 * @date 2021-05-07
 */

#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "CSession.h"
#include "CDifficulty.h"
#include "CVeryEasy.h"
#include "CEasy.h"
#include "CNormal.h"
#include "CHard.h"
#include "CMap.h"

class CApplication {
public:
    /**
     * @brief Constructor, whole game takes place here.
     *
     * Loads map and difficulty, then runs the game.
     */
    CApplication();

    /**
     * @brief Default destructor.
     */
    ~CApplication() = default;

    /**
     * @brief Loads map from file.
     *
     * @param[in] file -location of the map to be loaded
     * @return true -on success, false -otherwise
     */
    bool loadCustomMap(const std::string &file);

    /**
     * @brief Handles loading of the game map.
     */
    void loadMap();

    /**
     * @brief Loads difficulty from file.
     *
     * @param[in] file -location of the difficulty to be loaded
     * @return true -on succes, false -otherwise
     */
    bool loadCustomDifficulty(const std::string &file);

    /**
     * @brief Handles loading of the game difficulty.
     */
    void loadDifficulty();

    /**
     * @brief Handles running of the game.
     */
    void runApplication();
private:
    bool m_repeat;
    std::shared_ptr<CDifficulty> m_diff;
    CMap m_map;
};

