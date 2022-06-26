/**
 * @file CMap.h
 * @brief Pacman map implementation
 * @author Aiattoi
 * @date 2021-05-09
*/

#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <valarray>

class CMap {
public:

    /**
     * @brief Loads map from an input stream.
     *
     * Rules for a map:
     * -must contain: 1 pacman, 1 spawn, 1 bonus, 2 teleports, 4 ghosts
     * -all rows must have the same width
     * -spawn must be next to 2 empty tiles and 2 walls
     * -teleports must be next to 1 empty tile and 3 walls
     *
     * @param[in] is -input stream containing the map
     * @return true -map successfully loaded, false -the loaded map doesn't meet the rules
     */
    bool load(std::istream &is);

    /**
     * @brief Getter of spawning points of the ghosts and the pacman.
     *
     * @return spawning points of pacman and ghosts
     */
    const std::array<std::pair<size_t, size_t>, 5> &getSpawns() const;

    /**
     * @brief Prints contents of the map.
     */
    void printMap() const;

    /**
     * @brief Getter of map height.
     *
     * @return height of the map
     */
    size_t getHeight() const;

    /**
     * @brief Getter of map width.
     *
     * @return width of the map
     */
    size_t getWidth() const;

    /**
     * @brief Getter of content of a tile.
     *
     * @param[in] tile
     * @return content of the tile
     */
    const std::string &at(const std::pair<size_t, size_t> &tile) const;

    /**
     * @brief Setter of content of a tile.
     *
     * @param[in] tile
     * @param[in] content
     */
    void replace(const std::pair<size_t, size_t> &tile, std::string content);

    /**
     * @brief Decrease count of collectibles remaining in the map.
     */
    void removePoint();

    /**
     * @brief Getter of count of collectibles remaining in the map.
     *
     * @return count of collectibles remaining in the map
     */
    size_t getPoints() const;

    /**
     * @brief Getter of the spawn point.
     *
     * @return spawn point
     */
    std::pair<size_t, size_t> getSpawnPos() const;

    /**
     * @brief Getter of the other teleport position, than the one given.
     *
     * @param[in] from -first teleport position
     * @return position of the other teleport
     */
    std::pair<size_t, size_t> getTeleportEnd(const std::pair<size_t, size_t> &from) const;

    /**
     * @brief Counts the distance from 'from' to 'to'.
     *
     * @param[in] from -start position
     * @param[in] to -end position
     * @return distance from to
     */
    size_t distance(const std::pair<size_t, size_t> &from, const std::pair<size_t, size_t> &to) const;
private:
    /**
     * @brief Converts char into string and sets it on a tile.
     *
     * @param[in] tile -position to be set
     * @param[in] content -char to set
     */
    void insert(const std::pair<size_t, size_t> &tile, char content);

    /**
     * @brief Checks the neighbourhood of a tile and updates its position to a neighbouring empty tile.
     *
     * @param[in, out] t -tile to be checked
     * @param[in] resEmpty -count of neighbouring empty tiles
     * @param[in] resWall -count of neighbouring walls
     * @return true -when the counts are right, false -otherwise
     */
    bool checkTileNeighbours(std::pair<size_t, size_t> &t, size_t resEmpty, size_t resWall) const;

    size_t m_height; /**< height of the map */
    size_t m_width; /**< width of the map */
    size_t m_points; /**< number of remaining collectibles in the map */
    std::array<std::pair<size_t, size_t>, 5> m_spawns; /**< spawn points of pacman and ghosts */
    std::pair<size_t, size_t> m_spawn; /**< spawn, the place where all the ghosts set off from */
    std::pair<size_t, size_t> teleport1; /**< first teleport position */
    std::pair<size_t, size_t> teleport2; /**< second teleport position */
    std::map<std::pair<size_t, size_t>, std::string> m_map; /**< the very own map */
};
