#include "team.h"
#include <algorithm>
#include <stdexcept>

// Default constructor
Team::Team() {}

// Add a Pokemon to the team
bool Team::addPokemon(const Pokemon& pokemon) {
    if (members.size() < 6) {  // Pokemon teams can have up to 6 members
        members.push_back(pokemon);
        return true;
    }
    return false;
}

// Add an item to the team inventory
void Team::addItem(const Item& item) {
    items.push_back(item);
}

// Check if the team is defeated
bool Team::isDefeated() const {
    return std::all_of(members.begin(), members.end(), [](const Pokemon& p) { 
        return p.isDefeated(); 
    });
}

// Reset the team (heal all Pokemon)
void Team::resetTeam() {
    for (auto& pokemon : members) {
        pokemon.resetHp();
        pokemon.status = StatusEffect::NONE;
    }
}

// Get the first non-defeated Pokemon
Pokemon& Team::getFirstAlivePokemon() {
    for (auto& pokemon : members) {
        if (!pokemon.isDefeated()) {
            return pokemon;
        }
    }
    // This should never happen if we check for team defeat properly
    throw std::runtime_error("No alive Pokemon found!");
}

// Use an item from inventory on a Pokemon
std::string Team::useItem(int itemIndex, int pokemonIndex) {
    // Check if indices are valid
    if (itemIndex < 0 || itemIndex >= static_cast<int>(items.size())) {
        return "Invalid item index!";
    }
    
    if (pokemonIndex < 0 || pokemonIndex >= static_cast<int>(members.size())) {
        return "Invalid Pokemon index!";
    }
    
    // Use the item on the Pokemon
    std::string result = members[pokemonIndex].useItem(items[itemIndex]);
    
    // Remove the item from inventory
    items.erase(items.begin() + itemIndex);
    
    return result;
}