#ifndef BATTLE_H
#define BATTLE_H

#include <random>
#include "team.h"
#include "environment.h"
#include "status.h"

/**
 * @brief Class for handling Pokemon battles
 */
class Battle {
public:
    /**
     * @brief Constructor for Battle
     * @param p Player's team
     * @param e Enemy team
     * @param difficulty Difficulty multiplier
     * @param env Battle environment
     */
    Battle(Team& p, Team& e, float difficulty, const Environment& env);
    
    /**
     * @brief Start the battle
     * @return True if the player won
     */
    bool start();

private:
    Team& playerTeam;
    Team& enemyTeam;
    std::mt19937 rng;
    float difficultyMultiplier;
    Environment environment;
    
    /**
     * @brief Handle the player's turn
     * @return True if the battle should continue
     */
    bool playerTurn();
    
    /**
     * @brief Handle the enemy's turn
     * @return True if the battle should continue
     */
    bool enemyTurn();
    
    /**
     * @brief Use a move
     * @param attacker The attacking Pokemon
     * @param defender The defending Pokemon
     * @param move The move to use
     * @return Damage dealt
     */
    int useMove(Pokemon& attacker, Pokemon& defender, const Move& move);
    
    /**
     * @brief Calculate damage for a move
     * @param attacker The attacking Pokemon
     * @param defender The defending Pokemon
     * @param move The move used
     * @return The calculated damage
     */
    int calculateDamage(const Pokemon& attacker, const Pokemon& defender, const Move& move);
    
    /**
     * @brief Display the battle menu
     * @param activePokemon The active Pokemon
     * @return The selected option
     */
    int displayBattleMenu(const Pokemon& activePokemon);
    
    /**
     * @brief Display the move selection menu
     * @param activePokemon The active Pokemon
     * @return The index of the selected move
     */
    int displayMoveMenu(const Pokemon& activePokemon);
    
    /**
     * @brief Display the item menu
     * @return The index of the selected item
     */
    int displayItemMenu();
    
    /**
     * @brief Display the Pokemon switch menu
     * @return The index of the Pokemon to switch to
     */
    int displaySwitchMenu();
    
    /**
     * @brief Display battle status
     * @param playerPokemon The player's active Pokemon
     * @param enemyPokemon The enemy's active Pokemon
     */
    void displayBattleStatus(const Pokemon& playerPokemon, const Pokemon& enemyPokemon);
    
    /**
     * @brief Check for status effects and apply them
     * @param pokemon The Pokemon to check status for
     * @return True if the Pokemon can move this turn
     */
    bool checkStatusEffects(Pokemon& pokemon);
    
    /**
     * @brief Check for status recovery
     * @param pokemon The Pokemon to check for recovery
     */
    void checkStatusRecovery(Pokemon& pokemon);
    
    /**
     * @brief Generate experience points for defeating a Pokemon
     * @param defeated The defeated Pokemon
     * @return The amount of experience earned
     */
    int generateExperience(const Pokemon& defeated);
    
    /**
     * @brief Apply experience to the player's team
     * @param exp The amount of experience to distribute
     */
    void applyExperience(int exp);
};

#endif // BATTLE_H