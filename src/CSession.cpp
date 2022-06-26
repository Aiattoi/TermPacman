/**
 * @file CSession.cpp
 * @brief The Pacman game handler.
 * @author Aiattoi
 * @date 2021-05-23
 */

#include "CSession.h"

#include <utility>

void CSession::RestoreKeyboardBlocking(struct termios *initial_settings) const {
    tcsetattr(0, TCSANOW, initial_settings);
}

void CSession::SetKeyboardNonBlock(struct termios *initial_settings) const {

    struct termios new_settings;
    tcgetattr(0, initial_settings);

    new_settings = *initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &new_settings);
}

char CSession::getcharAlt() const {
    char buff[2];
    int l = read(STDIN_FILENO, buff, 1);
    if (l > 0) return buff[0];
    return (EOF);
}

CSession::CSession(std::shared_ptr<CDifficulty> diff, CMap map)
        : m_diff(std::move(diff)), m_map(std::move(map)), m_timer(0),
          m_pacman(std::make_shared<CPacman>(m_map.getSpawns()[0])) {
    srandom(time(nullptr));
    m_pacman->respawn(m_map);
    createGhosts();
    int phase = -1; //number of chase mode (max. number of active ghosts)
    bool vulnerable = false; //vulnerable/frightened mode signalization
    bool killPacman = false;
    size_t timerUpdate = 0; //adjust m_timer++
    size_t gameSpeed = m_diff->getGameSpeed();
    size_t timerUpdateFrequency = round(1000.0/gameSpeed);
    size_t ghostSpeed = m_diff->getGhostSpeed();
    size_t vulnerableTime = 0; //timer for vulnerable/frightened mode
    bool prevMode = true; //previous mode signalization, true=!vulnerable, false=vulnerable
    bool modeChanged; //change of mode signalization
    bool isEnd = false; //end of game
    while (!isEnd) {
        print();
        modeChanged = false;
        timeHandler(timerUpdate, timerUpdateFrequency);
        //end vulnerable/frightened mode when time is up
        if (vulnerable && m_timer == vulnerableTime)
            vulnerable = false;

        spawnGhosts(phase);
        //check for change of mode
        if (prevMode != m_diff->isScatter()) {
            prevMode = m_diff->isScatter();
            modeChanged = true;
        }

        //pacman move
        killPacman = convert(vulnerable, gameSpeed);
        //check for vulnerable/frightened mode
        if (vulnerable != m_ghosts[0]->isFrightened()) {
            vulnerableTime = m_timer + m_diff->getVulnerableTime();
            for (auto &ghost:m_ghosts)
                ghost->changeState(m_map);
        }
        //ghosts move
        if (!killPacman && timerUpdate % ghostSpeed == 0)
            killPacman = ghostsMove(phase, vulnerable, modeChanged);

        if(killPacman)
            respawnGhosts(phase, timerUpdate, vulnerableTime, vulnerable);
        isEnd = endGameManager(killPacman);
        timerUpdate++;
    }
    system("clear");
}

CSession::~CSession() {
    m_diff.reset();
    m_pacman.reset();
    /*for (auto &m_ghost : m_ghosts)
        m_ghost.reset();*/
}

void CSession::print() const {
    system("clear");
    std::string gameName = "PACMAN";
    std::cout << std::endl;
    //get PACMAN to the middle
    for (size_t i = 0; i < m_map.getWidth() / 2 - gameName.size() / 2; ++i)
        std::cout << " ";
    std::cout << gameName << std::endl << std::endl;
    std::cout << " score: " << m_pacman->getScore() << std::endl;
    std::cout << " lives:";
    for (size_t i = 0; i < m_pacman->getLives(); ++i)
        std::cout << " " << *m_pacman;
    std::cout << std::endl;
    //for debug purposes
    //std::string scatter = m_diff->isScatter() ? "\u001b[32mScatter\u001b[0m" : "\u001b[31mChase\u001b[0m";
    //std::cout << scatter << std::endl;
    //std::cout << " collectibles left: " << m_map.getPoints() << std::endl;
    m_map.printMap();
}


bool CSession::endGameManager(int kill) {
    if (kill == 1) {
        if (m_pacman->getLives() == 1) {
            std::cout << std::endl << " GAME OVER " << std::endl;
            std::cout << " You've run out of your lives." << std::endl << std::endl;
            std::cout << " You've collected " << m_pacman->getScore() << " points." << std::endl << std::endl;
            return true;
        } else {
            m_pacman->removeLive();
            m_pacman->respawn(m_map);
        }
    } else if (m_map.getPoints() == 0) {
        std::cout << std::endl << " VICTORY " << std::endl;
        std::cout << " You've successfully cleared this level." << std::endl << std::endl;
        std::cout << " You've gained " << m_pacman->getScore() << " points." << std::endl << std::endl;
        return true;
    }
    return false;
}
void CSession::createGhosts() {
    size_t ghost = 0;
    m_ghosts[ghost] = std::make_shared<CRedGhost>(m_map.getSpawns()[ghost + 1]);
    m_ghosts[ghost]->respawn(m_map);
    ghost++;
    m_ghosts[ghost] = std::make_shared<CPinkGhost>(m_map.getSpawns()[ghost + 1]);
    m_ghosts[ghost]->respawn(m_map);
    ghost++;
    m_ghosts[ghost] = std::make_shared<CBlueGhost>(m_map.getSpawns()[ghost + 1]);
    m_ghosts[ghost]->respawn(m_map);
    ghost++;
    m_ghosts[ghost] = std::make_shared<COrangeGhost>(m_map.getSpawns()[ghost + 1]);
    m_ghosts[ghost]->respawn(m_map);
}

void CSession::spawnGhosts(int &phase) {
    //game start
    if (m_diff->getPhase(m_timer) > phase) {
        phase++;
        m_ghosts[phase]->activate(m_map);
    }
    //respawn
    for (auto &ghost:m_ghosts)
        if (ghost->isRespawnTime(m_timer))
            ghost->activate(m_map);
}

void CSession::removeGhost(const std::shared_ptr<CGhost> &ghost) {
    char prevContent = ghost->getPrevContent();
    if (prevContent == 'B' || prevContent == '.')
        m_map.removePoint();
    ghost->respawn(m_map);
    ghost->setRespawnTime(m_timer + m_diff->getGhostRespawnTime());
}

void CSession::respawnGhosts(int &phase, size_t &timerUpdate, size_t &vulnerableTime,
                             bool &vulnerable) {
    phase = -1;
    timerUpdate = 0;
    m_timer = 0;
    vulnerableTime = 0;
    vulnerable = false;
    for(const auto &ghost:m_ghosts)
        ghost->respawnNotEaten(m_map);
}

bool CSession::pacmanMove(const std::pair<int, int> &dir, bool &vulnerable) {
    int result = m_pacman->nextStep(m_map, dir, vulnerable);
    // ghost captured
    if (result == 2)
        for (size_t i = 0; i < m_ghosts.size(); ++i)
            if (m_ghosts[i]->getPosition() == m_pacman->getPosition())
                removeGhost(m_ghosts[i]);
    return result == 1;
}

bool CSession::convert(bool &vulnerable, size_t gameSpeed) {

    struct termios term_settings;
    char input;
    SetKeyboardNonBlock(&term_settings);
    usleep(gameSpeed*1000);
    input = getcharAlt();
    //Not restoring the keyboard settings causes the input from the terminal to not work right
    RestoreKeyboardBlocking(&term_settings);
    //for debug purposes
    //while(std::getc(stdin)!='\n');
    //int input = std::getc(stdin);

    //esc/f
    if (input == 27 || input == 'f')
        exit(0);

    //W/w -up
    if (input == 'W' || input == 'w') {
        return pacmanMove({0, -1}, vulnerable);
    }
        //S/s -down
    else if (input == 'S' || input == 's') {
        return pacmanMove({0, 1}, vulnerable);
    }
        //D/d -right
    else if (input == 'D' || input == 'd') {
        return pacmanMove({1, 0}, vulnerable);
    }
        //A/a -left
    else if (input == 'A' || input == 'a') {
        return pacmanMove({-1, 0}, vulnerable);
    }
    //no move, needed because of ghost capture, etc.
    return pacmanMove({0, 0}, vulnerable);
}

bool CSession::ghostsMove(int phase, bool &vulnerable, bool modeChanged) {
    const int ghostPoints = 200;
    int result = 0; // return val
    int tmpRes; //tmp
    // no ghosts spawned yet
    if (phase < 0)
        return false;
    for (int i = 0; i <= phase; ++i)
        if (m_ghosts[i]->isActive()) {
            // reverse dir on mode change
            if (modeChanged) {
                std::pair<int, int> invMyMove = m_ghosts[i]->getPrevMove();
                invMyMove.first = -invMyMove.first;
                invMyMove.second = -invMyMove.second;
                tmpRes = m_ghosts[i]->nextStep(m_map, invMyMove, vulnerable);
            }
                //apply strategy
            else
                tmpRes = m_ghosts[i]->nextStep(m_map,
                                               m_ghosts[i]->getDir(*m_diff, m_map, m_pacman->getPosition(),
                                                                   m_pacman->getPrevMove()),
                                               vulnerable);
            // pacman lost a life
            if (tmpRes == 1)
                result = 1;

                // ghost captured
            else if (tmpRes == 2) {
                removeGhost(m_ghosts[i]);
                m_pacman->addToScore(ghostPoints);
            }
        }
    return result == 1;
}

void CSession::timeHandler(size_t &timerUpdate, size_t timerUpdateFrequency) {
    if (timerUpdate == UINTMAX_MAX)
        timerUpdate = 0;
    if (m_timer == UINTMAX_MAX)
        m_timer = 0;
    if (timerUpdate % timerUpdateFrequency == 0)
        m_timer++;
}
