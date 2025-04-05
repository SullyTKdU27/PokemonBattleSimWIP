#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include <vector>
#include <string>
#include "pokemon.h"
#include "move.h"
#include "item.h"

/**
 * @brief Class for loading Pokemon, moves, and items from data files
 */
class DataLoader {
public:
    /**
     * @brief Load Pokemon data from file
     * @param filename The file to load from
     * @return Vector of Pokemon objects
     */
    static std::vector<Pokemon> loadPokemon(const std::string& filename);
    
    /**
     * @brief Load move data from file
     * @param filename The file to load from
     * @return Vector of Move objects
     */
    static std::vector<Move> loadMoves(const std::string& filename);
    
    /**
     * @brief Load item data from file
     * @param filename The file to load from
     * @return Vector of Item objects
     */
    static std::vector<Item> loadItems(const std::string& filename);
    
    /**
     * @brief Save default data files if they don't exist
     */
    static void saveDefaultFiles();

private:
    /**
     * @brief Parse a line of Pokemon data
     * @param line The line to parse
     * @return Pokemon object
     */
    static Pokemon parsePokemonLine(const std::string& line);
    
    /**
     * @brief Parse a line of move data
     * @param line The line to parse
     * @return Move object
     */
    static Move parseMoveLine(const std::string& line);
    
    /**
     * @brief Parse a line of item data
     * @param line The line to parse
     * @return Item object
     */
    static Item parseItemLine(const std::string& line);
};

#endif // DATA_LOADER_H