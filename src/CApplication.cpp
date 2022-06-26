/**
 * @file CApplication.cpp
 * @brief Wrapper of the Pacman game, loads map and difficulty.
 * @author Aiattoi
 * @date 2021-05-09
 */

#include "CApplication.h"

CApplication::CApplication() {
    system("clear");
    loadMap();
    //loadDifficulty();
    m_repeat = true;
    while (m_repeat) {
        runApplication();
    }
}

bool CApplication::loadCustomMap(const std::string &file) {
    std::string path = "examples/" + file;
    std::ifstream ifs;
    ifs.open(path);
    if (!ifs.is_open())
        return false;
    if (m_map.load(ifs))
        return true;
    return false;
}

void CApplication::loadMap() {
    std::string mapFileName;
    bool isLoaded = false;
    std::cout << "			 PACMAN						  " << std::endl << std::endl;
    std::cout << " Insert name of the file with the map (with suffix, example: 'classic.txt')." << std::endl;
    while (!isLoaded) {
        std::cin >> mapFileName;
        isLoaded = loadCustomMap(mapFileName);
        if (!isLoaded)
            std::cout << "Failed loading map, please try again." << std::endl;
    }
    system("clear");
}

bool CApplication::loadCustomDifficulty(const std::string &file) {
    std::string path = "examples/" + file;
    std::ifstream ifs;
    ifs.open(path);
    if (!ifs.is_open())
        return false;
    std::array<size_t, 4> scatter;
    std::array<size_t, 3> chase;
    size_t vulnerableTime = 0;
    size_t ghostRespawnTime = 0;
    size_t gameSpeed = 0;
    size_t ghostSpeed = 0;
    bool isScatterLoaded = false, isChaseLoaded = false;
    std::string line;
    while (getline(ifs, line) && !(line.empty())) {
        std::stringstream ss(line);
        std::string id;
        std::string numStr;
        size_t num;
        if (getline(ss, id, ':')) {
            if (id == "scatter")
                for (size_t i = 0; i < scatter.size(); ++i)
                    if (getline(ss, numStr, ',')) {
                        std::stringstream numSs(numStr);
                        numSs >> num;
                        scatter[i] = num;
                        if (i == scatter.size() - 1)
                            isScatterLoaded = true;
                    }
            if (id == "chase")
                for (size_t i = 0; i < chase.size(); ++i)
                    if (getline(ss, numStr, ',')) {
                        std::stringstream numSs(numStr);
                        numSs >> num;
                        chase[i] = num;
                        if (i == chase.size() - 1)
                            isChaseLoaded = true;
                    }
            if (id == "vulnerable")
                ss >> vulnerableTime;
            if (id == "ghostRespawn")
                ss >> ghostRespawnTime;
            if (id == "gameSpeed") {
                ss >> gameSpeed;
                if (gameSpeed < 1 || gameSpeed > 3)
                    return false;
            }
            if (id == "ghostSpeed") {
                ss >> ghostSpeed;
                if (ghostSpeed < 1 || ghostSpeed > 5)
                    return false;
            }
        }
    }
    if (!isScatterLoaded || !isChaseLoaded || !vulnerableTime || !ghostRespawnTime
    || !gameSpeed || !ghostSpeed)
        return false;
    m_diff = std::make_shared<CNormal>(scatter, chase, vulnerableTime, ghostRespawnTime,
                                       gameSpeed, ghostSpeed);
    return true;
}

void CApplication::loadDifficulty() {
    std::string diffName;
    std::string diffFileName;
    bool isLoaded = false;
    std::cout << "			 PACMAN						  " << std::endl << std::endl;
    std::cout << " Select difficulty: " << std::endl;
    std::cout << "	VeryEasy" << std::endl;
    std::cout << "	Easy" << std::endl;
    std::cout << "	Normal" << std::endl;
    std::cout << "	Hard" << std::endl;
    std::cout << "	Custom" << std::endl;
    while (!isLoaded) {
        std::cin >> diffName;
        if (diffName == "VeryEasy") {
            m_diff = std::make_shared<CVeryEasy>();
            isLoaded = true;
        }
        if (diffName == "Easy") {
            m_diff = std::make_shared<CEasy>();
            isLoaded = true;
        }
        if (diffName == "Normal") {
            m_diff = std::make_shared<CNormal>();
            isLoaded = true;
        }
        if (diffName == "Hard") {
            m_diff = std::make_shared<CNormal>();
            isLoaded = true;
        }
        if (diffName == "Custom") {
            std::cout << " Insert name of the file with the difficulty (with suffix, example: 'myDiff.txt')."
                      << std::endl;
            std::cin >> diffFileName;
            isLoaded = loadCustomDifficulty(diffFileName);
        }
        if (!isLoaded)
            std::cout << "Failed loading difficulty, please try again." << std::endl;
    }
    system("clear");
}

void CApplication::runApplication() {
    CSession session = CSession(/*m_diff, */m_map);
    std::cout << "Do you wish to play again? [y/n]" << std::endl;
    char in;
    bool isLoaded = false;
    while (!isLoaded) {
        std::cin >> in;
        if (in == 'y') {
            isLoaded = true;
            m_repeat = true;
        } else if (in == 'n') {
            isLoaded = true;
            m_repeat = false;
        } else {
            std::cout << "Please enter 'y' as yes or 'n' as no." << std::endl;
        }
    }
    system("clear");
}

