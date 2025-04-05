#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "types.h"
#include "status.h"

/**
 * @brief Class representing a Pokemon move
 */
class Move {
public:
    /**
     * @brief Constructor for Move
     * @param n Name of the move
     * @param p Power of the move (0 for status moves)
     * @param a Accuracy of the move (0-100)
     * @param t Type of the move
     */
    Move(const std::string& n, int p, int a, PokemonType t = PokemonType::NORMAL);
    
    /**
     * @brief Constructor for Move with status effect
     * @param n Name of the move
     * @param p Power of the move (0 for status moves)
     * @param a Accuracy of the move (0-100)
     * @param t Type of the move
     * @param s Status effect the move can cause
     * @param c Chance of causing status effect (0-100)
     */
    Move(const std::string& n, int p, int a, PokemonType t, StatusEffect s, int c);
    
    // Basic move properties
    std::string name;
    int power;
    int accuracy;
    PokemonType type;
    
    // Status effect properties
    StatusEffect statusEffect;
    int statusChance;
    
    /**
     * @brief Checks if the move has a status effect
     * @return True if the move can cause a status effect
     */
    bool hasStatusEffect() const;
    
    /**
     * @brief Checks if status effect should be applied
     * @return True if the status should be applied based on chance
     */
    bool shouldApplyStatus() const;
};

#endif // MOVE_H