#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include "pokemon.h"
#include "item.h"

/**
 * @brief Class representing a team of Pokemon
 */
class Team {
public:
    /**
     * @brief Default constructor
     */
    Team();
    
    std::vector<Pokemon> members;
    std::vector<Item> items;
    
    /**
     * @brief Add a Pokemon to the team
     * @param pokemon The Pokemon to add
     * @return True if the Pokemon was added successfully
     */
    bool addPokemon(const Pokemon& pokemon);
    
    /**
     * @brief Add an item to the team inventory
     * @param item The item to add
     */
    void addItem(const Item& item);
    
    /**
     * @brief Check if the team is defeated
     * @return True if all Pokemon in the team are defeated
     */
    bool isDefeated() const;
    
    /**
     * @brief Reset the team (heal all Pokemon)
     */
    void resetTeam();
    
    /**
     * @brief Get the first non-defeated Pokemon
     * @return Reference to the first available Pokemon
     * @throws std::runtime_error if no Pokemon are available
     */
    Pokemon& getFirstAlivePokemon();
    
    /**
     * @brief Use an item from inventory on a Pokemon
     * @param itemIndex The index of the item to use
     * @param pokemonIndex The index of the Pokemon to use the item on
     * @return String describing the effect
     */
    std::string useItem(int itemIndex, int pokemonIndex);
};

#endif // TEAM_H