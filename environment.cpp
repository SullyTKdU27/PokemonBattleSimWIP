#include "environment.h"
#include <unordered_map>
#include <sstream>

// Constructor
Environment::Environment(BattleEnvironment type) : envType(type), boostMultiplier(1.5f) {
    // Set the boosted type based on environment
    switch (envType) {
        case BattleEnvironment::GRASS_FIELD:
            boostedType = PokemonType::GRASS;
            break;
        case BattleEnvironment::WATER_SURFACE:
            boostedType = PokemonType::WATER;
            break;
        case BattleEnvironment::CAVE:
            boostedType = PokemonType::ROCK;
            break;
        case BattleEnvironment::VOLCANO:
            boostedType = PokemonType::FIRE;
            break;
        case BattleEnvironment::ELECTRIC_TERRAIN:
            boostedType = PokemonType::ELECTRIC;
            break;
        case BattleEnvironment::PSYCHIC_TERRAIN:
            boostedType = PokemonType::PSYCHIC;
            break;
        default:
            boostedType = PokemonType::NONE;
            boostMultiplier = 1.0f;
            break;
    }
}

// Get the name of the environment
std::string Environment::getName() const {
    static const std::unordered_map<BattleEnvironment, std::string> names = {
        {BattleEnvironment::NORMAL, "Normal Field"},
        {BattleEnvironment::GRASS_FIELD, "Grassy Field"},
        {BattleEnvironment::WATER_SURFACE, "Water Surface"},
        {BattleEnvironment::CAVE, "Cave"},
        {BattleEnvironment::VOLCANO, "Volcano"},
        {BattleEnvironment::ELECTRIC_TERRAIN, "Electric Terrain"},
        {BattleEnvironment::PSYCHIC_TERRAIN, "Psychic Terrain"}
    };
    
    auto it = names.find(envType);
    return (it != names.end()) ? it->second : "Unknown";
}

// Get the type boost for this environment
PokemonType Environment::getBoostedType() const {
    return boostedType;
}

// Get the boost multiplier for the environment
float Environment::getBoostMultiplier() const {
    return boostMultiplier;
}

// Get a description of the environment
std::string Environment::getDescription() const {
    std::stringstream ss;
    
    ss << "Battle environment: " << getName();
    
    if (boostedType != PokemonType::NONE) {
        ss << " - " << typeToString(boostedType) << " moves are " 
           << (boostMultiplier * 100 - 100) << "% stronger!";
    }
    
    return ss.str();
}