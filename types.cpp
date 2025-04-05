#include "types.h"
#include <unordered_map>

// Type to string mapping
std::string typeToString(PokemonType type) {
    static const std::unordered_map<PokemonType, std::string> typeMap = {
        {PokemonType::NORMAL, "Normal"},
        {PokemonType::FIRE, "Fire"},
        {PokemonType::WATER, "Water"},
        {PokemonType::GRASS, "Grass"},
        {PokemonType::ELECTRIC, "Electric"},
        {PokemonType::ICE, "Ice"},
        {PokemonType::FIGHTING, "Fighting"},
        {PokemonType::POISON, "Poison"},
        {PokemonType::GROUND, "Ground"},
        {PokemonType::FLYING, "Flying"},
        {PokemonType::PSYCHIC, "Psychic"},
        {PokemonType::BUG, "Bug"},
        {PokemonType::ROCK, "Rock"},
        {PokemonType::GHOST, "Ghost"},
        {PokemonType::DRAGON, "Dragon"},
        {PokemonType::DARK, "Dark"},
        {PokemonType::STEEL, "Steel"},
        {PokemonType::FAIRY, "Fairy"},
        {PokemonType::NONE, "None"}
    };
    
    return typeMap.at(type);
}

// String to type mapping
PokemonType stringToType(const std::string& typeStr) {
    static const std::unordered_map<std::string, PokemonType> stringMap = {
        {"Normal", PokemonType::NORMAL},
        {"Fire", PokemonType::FIRE},
        {"Water", PokemonType::WATER},
        {"Grass", PokemonType::GRASS},
        {"Electric", PokemonType::ELECTRIC},
        {"Ice", PokemonType::ICE},
        {"Fighting", PokemonType::FIGHTING},
        {"Poison", PokemonType::POISON},
        {"Ground", PokemonType::GROUND},
        {"Flying", PokemonType::FLYING},
        {"Psychic", PokemonType::PSYCHIC},
        {"Bug", PokemonType::BUG},
        {"Rock", PokemonType::ROCK},
        {"Ghost", PokemonType::GHOST},
        {"Dragon", PokemonType::DRAGON},
        {"Dark", PokemonType::DARK},
        {"Steel", PokemonType::STEEL},
        {"Fairy", PokemonType::FAIRY},
        {"None", PokemonType::NONE}
    };
    
    auto it = stringMap.find(typeStr);
    return (it != stringMap.end()) ? it->second : PokemonType::NONE;
}

// Type effectiveness chart implementation
float getTypeEffectiveness(PokemonType attackType, PokemonType defenderType) {
    // Simplified type effectiveness chart
    static const std::map<PokemonType, std::map<PokemonType, float>> effectivenessChart = {
        {PokemonType::NORMAL, {
            {PokemonType::ROCK, 0.5f},
            {PokemonType::GHOST, 0.0f},
            {PokemonType::STEEL, 0.5f}
        }},
        {PokemonType::FIRE, {
            {PokemonType::FIRE, 0.5f},
            {PokemonType::WATER, 0.5f},
            {PokemonType::GRASS, 2.0f},
            {PokemonType::ICE, 2.0f},
            {PokemonType::BUG, 2.0f},
            {PokemonType::ROCK, 0.5f},
            {PokemonType::DRAGON, 0.5f},
            {PokemonType::STEEL, 2.0f}
        }},
        {PokemonType::WATER, {
            {PokemonType::FIRE, 2.0f},
            {PokemonType::WATER, 0.5f},
            {PokemonType::GRASS, 0.5f},
            {PokemonType::GROUND, 2.0f},
            {PokemonType::ROCK, 2.0f},
            {PokemonType::DRAGON, 0.5f}
        }},
        {PokemonType::ELECTRIC, {
            {PokemonType::WATER, 2.0f},
            {PokemonType::ELECTRIC, 0.5f},
            {PokemonType::GRASS, 0.5f},
            {PokemonType::GROUND, 0.0f},
            {PokemonType::FLYING, 2.0f},
            {PokemonType::DRAGON, 0.5f}
        }},
        {PokemonType::GRASS, {
            {PokemonType::FIRE, 0.5f},
            {PokemonType::WATER, 2.0f},
            {PokemonType::GRASS, 0.5f},
            {PokemonType::POISON, 0.5f},
            {PokemonType::GROUND, 2.0f},
            {PokemonType::FLYING, 0.5f},
            {PokemonType::BUG, 0.5f},
            {PokemonType::ROCK, 2.0f},
            {PokemonType::DRAGON, 0.5f},
            {PokemonType::STEEL, 0.5f}
        }}
        // More types would be added here
    };
    
    // Default effectiveness is 1.0 (normal damage)
    float effectiveness = 1.0f;
    
    // Check if we have a specific effectiveness defined
    auto attackIter = effectivenessChart.find(attackType);
    if (attackIter != effectivenessChart.end()) {
        auto defenderIter = attackIter->second.find(defenderType);
        if (defenderIter != attackIter->second.end()) {
            effectiveness = defenderIter->second;
        }
    }
    
    return effectiveness;
}

// Get ANSI color codes for console output based on type
std::string getTypeColor(PokemonType type) {
    // ANSI color codes for console output
    static const std::unordered_map<PokemonType, std::string> colorMap = {
        {PokemonType::NORMAL, "\033[1;37m"},    // White
        {PokemonType::FIRE, "\033[1;31m"},      // Red
        {PokemonType::WATER, "\033[1;34m"},     // Blue
        {PokemonType::GRASS, "\033[1;32m"},     // Green
        {PokemonType::ELECTRIC, "\033[1;33m"},  // Yellow
        {PokemonType::ICE, "\033[1;36m"},       // Cyan
        {PokemonType::FIGHTING, "\033[0;31m"},  // Dark Red
        {PokemonType::POISON, "\033[0;35m"},    // Purple
        {PokemonType::GROUND, "\033[0;33m"},    // Brown
        {PokemonType::FLYING, "\033[1;35m"},    // Pink
        {PokemonType::PSYCHIC, "\033[1;35m"},   // Pink
        {PokemonType::BUG, "\033[0;32m"},       // Dark Green
        {PokemonType::ROCK, "\033[0;33m"},      // Brown
        {PokemonType::GHOST, "\033[0;35m"},     // Purple
        {PokemonType::DRAGON, "\033[0;34m"},    // Dark Blue
        {PokemonType::DARK, "\033[0;30m"},      // Black
        {PokemonType::STEEL, "\033[0;37m"},     // Gray
        {PokemonType::FAIRY, "\033[1;35m"},     // Pink
        {PokemonType::NONE, "\033[0m"}          // Reset
    };
    
    auto it = colorMap.find(type);
    return (it != colorMap.end()) ? it->second : "\033[0m";
}