#include "status.h"
#include <random>
#include <unordered_map>
#include <sstream>

// Convert status effect to string
std::string statusToString(StatusEffect status) {
    static const std::unordered_map<StatusEffect, std::string> statusMap = {
        {StatusEffect::NONE, "None"},
        {StatusEffect::POISON, "Poisoned"},
        {StatusEffect::PARALYSIS, "Paralyzed"},
        {StatusEffect::BURN, "Burned"},
        {StatusEffect::SLEEP, "Asleep"},
        {StatusEffect::FROZEN, "Frozen"},
        {StatusEffect::CONFUSION, "Confused"}
    };
    
    return statusMap.at(status);
}

// Get ANSI color codes for console output based on status
std::string getStatusColor(StatusEffect status) {
    static const std::unordered_map<StatusEffect, std::string> colorMap = {
        {StatusEffect::NONE, "\033[0m"},        // Reset
        {StatusEffect::POISON, "\033[0;35m"},   // Purple
        {StatusEffect::PARALYSIS, "\033[1;33m"}, // Yellow
        {StatusEffect::BURN, "\033[1;31m"},     // Red
        {StatusEffect::SLEEP, "\033[0;30m"},    // Black
        {StatusEffect::FROZEN, "\033[1;36m"},   // Cyan
        {StatusEffect::CONFUSION, "\033[1;35m"} // Pink
    };
    
    auto it = colorMap.find(status);
    return (it != colorMap.end()) ? it->second : "\033[0m";
}

// Apply status effects
std::string applyStatusEffect(StatusEffect status, bool& canMove, int& currentHp, int maxHp) {
    std::stringstream result;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Default to being able to move
    canMove = true;
    
    switch (status) {
        case StatusEffect::POISON:
            // Poison deals 1/8 of max HP as damage
            {
                int damage = maxHp / 8;
                currentHp -= damage;
                result << "It's hurt by poison! (" << damage << " damage)";
            }
            break;
            
        case StatusEffect::PARALYSIS:
            // 25% chance of not being able to move
            {
                std::uniform_int_distribution<> dis(1, 100);
                if (dis(gen) <= 25) {
                    canMove = false;
                    result << "It's fully paralyzed!";
                }
            }
            break;
            
        case StatusEffect::BURN:
            // Burn deals 1/16 of max HP as damage
            {
                int damage = maxHp / 16;
                currentHp -= damage;
                result << "It's hurt by its burn! (" << damage << " damage)";
            }
            break;
            
        case StatusEffect::SLEEP:
            // Cannot move while asleep
            canMove = false;
            result << "It's fast asleep!";
            break;
            
        case StatusEffect::FROZEN:
            // Cannot move while frozen
            canMove = false;
            result << "It's frozen solid!";
            break;
            
        case StatusEffect::CONFUSION:
            // 33% chance of hitting itself
            {
                std::uniform_int_distribution<> dis(1, 100);
                if (dis(gen) <= 33) {
                    canMove = false;
                    int damage = maxHp / 8;
                    currentHp -= damage;
                    result << "It hurt itself in confusion! (" << damage << " damage)";
                } else {
                    result << "It's confused!";
                }
            }
            break;
            
        default:
            // No status effect
            break;
    }
    
    return result.str();
}

// Check for status recovery
bool checkStatusRecovery(StatusEffect status) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Different recovery rates for different statuses
    switch (status) {
        case StatusEffect::SLEEP:
            // 33% chance to wake up each turn
            {
                std::uniform_int_distribution<> dis(1, 100);
                return dis(gen) <= 33;
            }
            
        case StatusEffect::FROZEN:
            // 20% chance to thaw each turn
            {
                std::uniform_int_distribution<> dis(1, 100);
                return dis(gen) <= 20;
            }
            
        case StatusEffect::CONFUSION:
            // 25% chance to snap out of confusion each turn
            {
                std::uniform_int_distribution<> dis(1, 100);
                return dis(gen) <= 25;
            }
            
        default:
            // Other status effects don't auto-recover
            return false;
    }
}