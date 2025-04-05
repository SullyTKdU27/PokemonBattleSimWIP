#ifndef RECORD_LOG_H
#define RECORD_LOG_H

#include <string>

/**
 * @brief Class for tracking battle statistics
 */
class RecordLog {
public:
    int wins = 0;
    int losses = 0;
    int totalDamageDealt = 0;
    int totalDamageTaken = 0;
    int pokemonDefeated = 0;
    int pokemonLost = 0;
    int itemsUsed = 0;
    int criticalHits = 0;
    int statusEffectsCaused = 0;
    int totalExperienceGained = 0;
    int evolutionsTriggered = 0;
    
    /**
     * @brief Save record log to a file
     * @param filename The file to save to
     * @return True if successfully saved
     */
    bool saveToFile(const std::string& filename);
    
    /**
     * @brief Load record log from a file
     * @param filename The file to load from
     * @return True if successfully loaded
     */
    bool loadFromFile(const std::string& filename);
    
    /**
     * @brief Display record statistics
     */
    void displayStats() const;
};

#endif // RECORD_LOG_H