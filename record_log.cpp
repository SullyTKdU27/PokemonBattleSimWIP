#include "record_log.h"
#include <iostream>
#include <fstream>

bool RecordLog::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << wins << "\n" << losses << "\n" << totalDamageDealt << "\n"
         << totalDamageTaken << "\n" << pokemonDefeated << "\n"
         << pokemonLost << "\n" << itemsUsed << "\n"
         << criticalHits << "\n" << statusEffectsCaused << "\n"
         << totalExperienceGained << "\n" << evolutionsTriggered << "\n";
    file.close();
    return true;
}

bool RecordLog::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file >> wins >> losses >> totalDamageDealt >> totalDamageTaken
         >> pokemonDefeated >> pokemonLost >> itemsUsed
         >> criticalHits >> statusEffectsCaused >> totalExperienceGained
         >> evolutionsTriggered;
    file.close();
    return true;
}

void RecordLog::displayStats() const {
    std::cout << "Wins: " << wins << "\nLosses: " << losses
              << "\nTotal Damage Dealt: " << totalDamageDealt
              << "\nTotal Damage Taken: " << totalDamageTaken
              << "\nPokemon Defeated: " << pokemonDefeated
              << "\nPokemon Lost: " << pokemonLost
              << "\nItems Used: " << itemsUsed
              << "\nCritical Hits: " << criticalHits
              << "\nStatus Effects Caused: " << statusEffectsCaused
              << "\nTotal Experience Gained: " << totalExperienceGained
              << "\nEvolutions Triggered: " << evolutionsTriggered << std::endl;
}