#include "move.h"
#include <random>

// Basic move constructor
Move::Move(const std::string& n, int p, int a, PokemonType t)
    : name(n), power(p), accuracy(a), type(t), statusEffect(StatusEffect::NONE), statusChance(0) {
}

// Move constructor with status effect
Move::Move(const std::string& n, int p, int a, PokemonType t, StatusEffect s, int c)
    : name(n), power(p), accuracy(a), type(t), statusEffect(s), statusChance(c) {
}

// Check if move has a status effect
bool Move::hasStatusEffect() const {
    return statusEffect != StatusEffect::NONE && statusChance > 0;
}

// Check if status effect should be applied
bool Move::shouldApplyStatus() const {
    if (!hasStatusEffect()) {
        return false;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    return dis(gen) <= statusChance;
}