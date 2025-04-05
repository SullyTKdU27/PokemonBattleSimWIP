#include "data_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Pokemon> DataLoader::loadPokemon(const std::string& filename) {
    std::vector<Pokemon> pokemonList;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        pokemonList.push_back(parsePokemonLine(line));
    }
    return pokemonList;
}

std::vector<Move> DataLoader::loadMoves(const std::string& filename) {
    std::vector<Move> moveList;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        moveList.push_back(parseMoveLine(line));
    }
    return moveList;
}

std::vector<Item> DataLoader::loadItems(const std::string& filename) {
    std::vector<Item> itemList;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        itemList.push_back(parseItemLine(line));
    }
    return itemList;
}

void DataLoader::saveDefaultFiles() {
    // Implementation for saving default files if they don't exist
}

Pokemon DataLoader::parsePokemonLine(const std::string& line) {
    // Implementation for parsing a Pokemon line
}

Move DataLoader::parseMoveLine(const std::string& line) {
    // Implementation for parsing a Move line
}

Item DataLoader::parseItemLine(const std::string& line) {
    // Implementation for parsing an Item line
}