#ifndef GAME_H
#define GAME_H

#include <vector>
#include "pokemon.h"
#include "team.h"
#include "record_log.h"
#include "environment.h"

/**
 * @brief Main game class
 */
class Game {
public:
    /**
     * @brief Constructor
     */
    Game();
    
    /**
     * @brief Destructor
     */
    ~Game();
    
    /**
     * @brief Start the game
     */
    void start();

private:
    std::vector<Pokemon> allPokemon;
    std::vector<Item> allItems;
    std::vector<Environment> allEnvironments;
    Team playerTeam;
    Team enemyTeam;
    float difficulty;
    RecordLog recordLog;
    BattleEnvironment currentEnvironment;
    
    /**
     * @brief Initialize game data
     */
    void initializeGame();
    
    /**
     * @brief Display the start screen
     */
    void displayStartScreen();
    
    /**
     * @brief Handle the main game loop
     */
    void playGame();
    
    /**
     * @brief Allow player to change their team
     */
    void changeTeam();
    
    /**
     * @brief Display record log
     */
    void displayRecordLog();
    
    /**
     * @brief Allow player to select their team
     */
    void selectTeam();
    
    /**
     * @brief Generate enemy team
     */
    void generateEnemyTeam();
    
    /**
     * @brief Display available Pokemon list
     */
    void displayPokemonList();
    
    /**
     * @brief Allow player to select difficulty
     */
    void selectDifficulty();
    
    /**
     * @brief Allow player to select battle environment
     */
    void selectEnvironment();
    
    /**
     * @brief ASCII art title screen
     */
    void displayTitleArt();
    
    /**
     * @brief Load Pokemon from file or create default
     */
    void loadPokemonData();
    
    /**
     * @brief Load items from file or create default
     */
    void loadItemData();
    
    /**
     * @brief Initialize battle environments
     */
    void initializeEnvironments();
};

#endif // GAME_H