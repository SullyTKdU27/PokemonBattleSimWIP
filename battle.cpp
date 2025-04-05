#include "battle.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

Battle::Battle(Team& p, Team& e, float difficulty, const Environment& env)
    : playerTeam(p), enemyTeam(e), difficultyMultiplier(difficulty), environment(env) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);
}

bool Battle::start() {
    std::cout << "\n========== BATTLE START ==========" << std::endl;
    std::cout << "Environment: " << environment.getName() << std::endl;

    if (playerTeam.members.empty() || enemyTeam.members.empty()) {
        std::cout << "Error: One or both teams have no Pokemon!" << std::endl;
        return false;
    }

    auto playerIt = std::find_if(playerTeam.members.begin(), playerTeam.members.end(), 
                                  [](const Pokemon& p) { return !p.isDefeated(); });
    auto enemyIt = std::find_if(enemyTeam.members.begin(), enemyTeam.members.end(), 
                                 [](const Pokemon& p) { return !p.isDefeated(); });

    if (playerIt == playerTeam.members.end() || enemyIt == enemyTeam.members.end()) {
        std::cout << "Error: One or both teams have no active Pokemon!" << std::endl;
        return false;
    }

    Pokemon& playerPokemon = *playerIt;
    Pokemon& enemyPokemon = *enemyIt;

    std::cout << "Go, " << playerPokemon.name << "!" << std::endl;
    std::cout << "Enemy sent out " << enemyPokemon.name << "!" << std::endl;

    bool battleContinue = true;
    bool playerWon = false;

    while (battleContinue) {
        displayBattleStatus(playerPokemon, enemyPokemon);
        bool playerFirst = playerPokemon.speed >= enemyPokemon.speed;

        if (playerFirst) {
            battleContinue = playerTurn();
            if (!battleContinue) {
                playerWon = std::any_of(playerTeam.members.begin(), playerTeam.members.end(), 
                                         [](const Pokemon& p) { return !p.isDefeated(); });
                break;
            }
            battleContinue = enemyTurn();
        } else {
            battleContinue = enemyTurn();
            if (!battleContinue) {
                playerWon = std::any_of(playerTeam.members.begin(), playerTeam.members.end(), 
                                         [](const Pokemon& p) { return !p.isDefeated(); });
                break;
            }
            battleContinue = playerTurn();
        }
    }

    if (playerWon) {
        std::cout << "You won the battle!" << std::endl;
        int totalExp = 0;
        for (const auto& pokemon : enemyTeam.members) {
            totalExp += generateExperience(pokemon);
        }
        applyExperience(totalExp);
    } else {
        std::cout << "You lost the battle!" << std::endl;
    }

    std::cout << "========== BATTLE END ==========" << std::endl;
    return playerWon;
}