#ifndef STATUS_H
#define STATUS_H

#include <string>

/**
 * @brief Enum representing different status effects
 */
enum class StatusEffect {
    NONE,
    POISON,
    PARALYSIS,
    BURN,
    SLEEP,
    FROZEN,
    CONFUSION
};

/**
 * @brief Converts StatusEffect enum to string
 * @param status The StatusEffect to convert
 * @return String representation of the status
 */
std::string statusToString(StatusEffect status);

/**
 * @brief Gets a color code for console output based on status effect
 * @param status The status effect
 * @return ANSI color code string
 */
std::string getStatusColor(StatusEffect status);

/**
 * @brief Applies status effect damage/restrictions
 * @param status The status effect to apply
 * @param canMove Reference to a boolean that determines if Pokemon can move
 * @param currentHp Reference to the Pokemon's current HP
 * @param maxHp The Pokemon's max HP (for percentage calculations)
 * @return String describing what happened due to status
 */
std::string applyStatusEffect(StatusEffect status, bool& canMove, int& currentHp, int maxHp);

/**
 * @brief Calculates chance of status recovery
 * @param status The status effect to check
 * @return True if the Pokemon recovers from status
 */
bool checkStatusRecovery(StatusEffect status);

#endif // STATUS_H