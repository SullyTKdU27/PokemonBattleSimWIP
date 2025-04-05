#include "pokemon.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>

// Constructor
Pokemon::Pokemon(const std::string& n, int h, int a, int d, int s, int sd, int spd,
                 PokemonType t1, PokemonType t2)
    : name(n), hp(h), maxHp(h), attack(a), defense(d), specialAttack(s), specialDefense(sd),
      speed(spd), level(5), experience(0), primaryType(t1), secondaryType(t2), status(StatusEffect::NONE),
      evolutionForm(""), evolutionLevel(0) {
    
    // Initialize stat modifiers
    statModifiers["attack"] = 0;
    statModifiers["defense"] = 0;
    statModifiers["specialAttack"] = 0;
    statModifiers["specialDefense"] = 0;
    statModifiers["speed"] = 0;
    statModifiers["accuracy"] = 0;
    statModifiers["evasion"] = 0;
    
    // Calculate experience needed for next level
    experienceToNextLevel = calculateExpToNextLevel();
}

// Add a move to the Pokemon
void Pokemon::addMove(const Move& move) {
    if (moves.size() < 4) {
        moves.push_back(move);
    } else {
        // Could add logic to replace a move
        std::cout << name << " already knows 4 moves!" << std::endl;
    }
}

// Check if the Pokemon is defeated
bool Pokemon::isDefeated() const {
    return hp <= 0;
}

// Reset the Pokemon's HP to maximum
void Pokemon::resetHp() {
    hp = maxHp;
}

// Use an item on the Pokemon
std::string Pokemon::useItem(const Item& item) {
    std::stringstream result;
    
    if (item.isHealingItem()) {
        int oldHp = hp;
        hp = std::min(maxHp, hp + item.healAmount);
        result << name << " recovered " << (hp - oldHp) << " HP!";
    } else if (item.isStatusHealItem()) {
        if (item.healStatus == StatusEffect::NONE || item.healStatus == status) {
            result << name << " was cured of " << statusToString(status) << "!";
            status = StatusEffect::NONE;
        } else {
            result << "It had no effect!";
        }
    } else if (item.isStatBoostItem()) {
        applyStatModifier(item.boostStat, item.boostAmount);
        result << name << "'s " << item.boostStat << " rose!";
    } else if (item.isReviveItem() && isDefeated()) {
        hp = maxHp / 2;
        result << name << " was revived!";
    } else {
        result << "The item had no effect!";
    }
    
    return result.str();
}

// Apply a status effect to the Pokemon
std::string Pokemon::applyStatus(StatusEffect newStatus) {
    // If already has a status, new one doesn't apply
    if (status != StatusEffect::NONE) {
        return name + " already has a status condition!";
    }
    
    status = newStatus;
    return name + " is now " + statusToString(status) + "!";
}

// Add experience points to the Pokemon
bool Pokemon::addExperience(int exp) {
    experience += exp;
    bool leveledUp = false;
    
    // Check for level up
    while (experience >= experienceToNextLevel) {
        // Level up
        level++;
        leveledUp = true;
        
        // Increase stats (simplified for this example)
        maxHp += 3 + (rand() % 3);
        attack += 1 + (rand() % 2);
        defense += 1 + (rand() % 2);
        specialAttack += 1 + (rand() % 2);
        specialDefense += 1 + (rand() % 2);
        speed += 1 + (rand() % 2);
        
        // Reduce experience by amount needed for this level
        experience -= experienceToNextLevel;
        
        // Calculate experience needed for next level
        experienceToNextLevel = calculateExpToNextLevel();
    }
    
    return leveledUp;
}

// Check if the Pokemon can evolve
bool Pokemon::canEvolve() const {
    return !evolutionForm.empty() && level >= evolutionLevel;
}

// Evolve the Pokemon
std::string Pokemon::evolve() {
    if (!canEvolve()) {
        return name + " cannot evolve yet!";
    }
    
    std::string oldName = name;
    name = evolutionForm;
    
    // Boost stats for evolution
    maxHp += 20;
    hp = maxHp;
    attack += 10;
    defense += 10;
    specialAttack += 10;
    specialDefense += 10;
    speed += 10;
    
    // Clear evolution info since it already evolved
    evolutionForm = "";
    evolutionLevel = 0;
    
    return oldName + " evolved into " + name + "!";
}

// Get a colored display of the Pokemon's name with type
std::string Pokemon::getColoredDisplay() const {
    std::stringstream ss;
    
    // Add colored name based on primary type
    ss << getTypeColor(primaryType) << name << "\033[0m";
    
    // Add type information
    ss << " [" << getTypeColor(primaryType) << typeToString(primaryType) << "\033[0m";
    
    // Add secondary type if it exists
    if (secondaryType != PokemonType::NONE) {
        ss << "/" << getTypeColor(secondaryType) << typeToString(secondaryType) << "\033[0m";
    }
    
    ss << "]";
    
    // Add status if present
    if (status != StatusEffect::NONE) {
        ss << " " << getStatusColor(status) << statusToString(status) << "\033[0m";
    }
    
    return ss.str();
}

// Calculate experience needed for next level
int Pokemon::calculateExpToNextLevel() const {
    // Simplified experience formula: level^3
    return level * level * level;
}

// Apply a stat modifier
void Pokemon::applyStatModifier(const std::string& stat, int stages) {
    // Ensure stat exists in the map
    if (statModifiers.find(stat) == statModifiers.end()) {
        return;
    }
    
    // Apply the modifier (clamped between -6 and +6)
    statModifiers[stat] = std::max(-6, std::min(6, statModifiers[stat] + stages));
}