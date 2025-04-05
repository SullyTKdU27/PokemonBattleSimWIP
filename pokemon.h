#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <map>
#include "move.h"
#include "types.h"
#include "status.h"
#include "item.h"

/**
 * @brief Class representing a Pokemon
 */
class Pokemon {
public:
    /**
     * @brief Constructor for Pokemon
     * @param n Name of the Pokemon
     * @param h Hit points (HP)
     * @param a Attack stat
     * @param d Defense stat
     * @param s Special attack stat
     * @param sd Special defense stat
     * @param spd Speed stat
     * @param t1 Primary type
     * @param t2 Secondary type (defaults to NONE)
     */
    Pokemon(const std::string& n, int h, int a, int d, int s, int sd, int spd, 
            PokemonType t1, PokemonType t2 = PokemonType::NONE);
    
    // Basic Pokemon properties
    std::string name;
    int hp;
    int maxHp;
    int attack;
    int defense;
    int specialAttack;
    int specialDefense;
    int speed;
    int level;
    int experience;
    int experienceToNextLevel;
    PokemonType primaryType;
    PokemonType secondaryType;
    StatusEffect status;
    std::vector<Move> moves;
    
    // Stat modifiers
    std::map<std::string, int> statModifiers;
    
    // Evolution information
    std::string evolutionForm;
    int evolutionLevel;
    
    /**
     * @brief Add a move to the Pokemon
     * @param move The move to add
     */
    void addMove(const Move& move);
    
    /**
     * @brief Check if the Pokemon is defeated
     * @return True if the Pokemon's HP is 0 or less
     */
    bool isDefeated() const;
    
    /**
     * @brief Reset the Pokemon's HP to maximum
     */
    void resetHp();
    
    /**
     * @brief Use an item on the Pokemon
     * @param item The item to use
     * @return String describing the effect of the item
     */
    std::string useItem(const Item& item);
    
    /**
     * @brief Apply a status effect to the Pokemon
     * @param newStatus The status to apply
     * @return String describing what happened
     */
    std::string applyStatus(StatusEffect newStatus);
    
    /**
     * @brief Add experience points to the Pokemon
     * @param exp The amount of experience to add
     * @return True if the Pokemon leveled up
     */
    bool addExperience(int exp);
    
    /**
     * @brief Check if the Pokemon can evolve
     * @return True if the Pokemon is ready to evolve
     */
    bool canEvolve() const;
    
    /**
     * @brief Evolve the Pokemon
     * @return String describing the evolution
     */
    std::string evolve();
    
    /**
     * @brief Get a colored display of the Pokemon's name with type
     * @return Formatted string with ANSI color codes
     */
    std::string getColoredDisplay() const;
    
private:
    /**
     * @brief Calculate experience needed for next level
     * @return Experience points needed
     */
    int calculateExpToNextLevel() const;
    
    /**
     * @brief Apply a stat modifier
     * @param stat The stat to modify
     * @param stages The number of stages to modify by
     */
    void applyStatModifier(const std::string& stat, int stages);
};

#endif // POKEMON_H