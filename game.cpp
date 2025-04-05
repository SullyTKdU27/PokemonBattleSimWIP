#include "game.h"
#include "battle.h"
#include "data_loader.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

Game::Game() : difficulty(1.0f) {
    // Default initialization
    currentEnvironment = BattleEnvironment::NORMAL;
}

Game::~Game() {
    // Cleanup resources if needed
}

void Game::start() {
    try {
        initializeGame();
        displayStartScreen();
        playGame();
    } catch (const std::exception& e) {
        std::cerr << "Error in game: " << e.what() << std::endl;
    }
}

void Game::initializeGame() {
    // Load data from files
    loadPokemonData();
    loadItemData();
    initializeEnvironments();
}

void Game::displayStartScreen() {
    displayTitleArt();
    
    std::cout << "\nWelcome to Pokemon Battle Simulator!" << std::endl;
    std::cout << "1. Start New Game" << std::endl;
    std::cout << "2. View Record Log" << std::endl;
    std::cout << "3. Exit" << std::endl;
    
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    
    switch(choice) {
        case 1:
            selectDifficulty();
            selectTeam();
            selectEnvironment();
            break;
        case 2:
            displayRecordLog();
            displayStartScreen(); // Return to start screen after viewing log
            break;
        case 3:
            std::cout << "Thank you for playing!" << std::endl;
            exit(0);
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            displayStartScreen();
            break;
    }
}

void Game::playGame() {
    bool continueGame = true;
    
    while (continueGame) {
        // Generate enemy team for the battle
        generateEnemyTeam();
        
        // Create and start a battle
        Battle battle(playerTeam, enemyTeam, currentEnvironment, difficulty);
        BattleResult result = battle.start();
        
        // Record battle results
        recordLog.addEntry(result);
        
        // Ask if player wants to continue
        std::cout << "\nDo you want to continue playing?" << std::endl;
        std::cout << "1. Continue with current team" << std::endl;
        std::cout << "2. Change team" << std::endl;
        std::cout << "3. Change environment" << std::endl;
        std::cout << "4. Return to main menu" << std::endl;
        std::cout << "5. Exit" << std::endl;
        
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                // Continue with current team
                // Heal all Pokemon before next battle
                for (auto& pokemon : playerTeam.members) {
                    pokemon.heal();
                }
                break;
            case 2:
                changeTeam();
                break;
            case 3:
                selectEnvironment();
                break;
            case 4:
                displayStartScreen();
                break;
            case 5:
                std::cout << "Thank you for playing!" << std::endl;
                continueGame = false;
                break;
            default:
                std::cout << "Invalid choice. Continuing with current team." << std::endl;
                break;
        }
    }
}

void Game::changeTeam() {
    std::cout << "Current team:" << std::endl;
    for (size_t i = 0; i < playerTeam.members.size(); i++) {
        std::cout << (i+1) << ". " << playerTeam.members[i].name << " (Lv. " << playerTeam.members[i].level << ")" << std::endl;
    }
    
    std::cout << "\nDo you want to select a completely new team or modify current team?" << std::endl;
    std::cout << "1. Select new team" << std::endl;
    std::cout << "2. Modify current team" << std::endl;
    std::cout << "3. Cancel" << std::endl;
    
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    
    switch(choice) {
        case 1:
            selectTeam();
            break;
        case 2:
            // Modify team logic
            displayPokemonList();
            std::cout << "Select which Pokemon to replace (1-" << playerTeam.members.size() << "): ";
            int replaceIndex;
            std::cin >> replaceIndex;
            
            if (replaceIndex >= 1 && replaceIndex <= static_cast<int>(playerTeam.members.size())) {
                std::cout << "Select new Pokemon by number: ";
                int newPokemonIndex;
                std::cin >> newPokemonIndex;
                
                if (newPokemonIndex >= 1 && newPokemonIndex <= static_cast<int>(allPokemon.size())) {
                    playerTeam.members[replaceIndex - 1] = allPokemon[newPokemonIndex - 1];
                    std::cout << allPokemon[newPokemonIndex - 1].name << " added to your team!" << std::endl;
                } else {
                    std::cout << "Invalid Pokemon selection." << std::endl;
                }
            } else {
                std::cout << "Invalid team position." << std::endl;
            }
            break;
        case 3:
            // Cancel
            return;
        default:
            std::cout << "Invalid choice." << std::endl;
            break;
    }
}

void Game::displayRecordLog() {
    std::cout << "======== BATTLE RECORD LOG ========" << std::endl;
    recordLog.displayEntries();
    std::cout << "==================================" << std::endl;
    
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void Game::selectTeam() {
    playerTeam.members.clear();
    
    std::cout << "Select your team (max 6 Pokemon):" << std::endl;
    displayPokemonList();
    
    for (int i = 0; i < 6; i++) {
        std::cout << "Select Pokemon " << (i+1) << " (0 to finish): ";
        int choice;
        std::cin >> choice;
        
        if (choice == 0) {
            break;
        }
        
        if (choice >= 1 && choice <= static_cast<int>(allPokemon.size())) {
            playerTeam.members.push_back(allPokemon[choice - 1]);
            std::cout << allPokemon[choice - 1].name << " added to your team!" << std::endl;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
            i--; // Retry this position
        }
    }
    
    if (playerTeam.members.empty()) {
        std::cout << "You must select at least one Pokemon!" << std::endl;
        selectTeam();
    }
    
    std::cout << "Team selected! You have " << playerTeam.members.size() << " Pokemon." << std::endl;
}

void Game::generateEnemyTeam() {
    enemyTeam.members.clear();
    
    // Get random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    
    // Determine enemy team size (scaled to player team, but at least 1)
    int enemyTeamSize = std::max(1, static_cast<int>(playerTeam.members.size() * difficulty));
    enemyTeamSize = std::min(enemyTeamSize, 6); // Cap at 6 Pokemon
    
    // Create a uniform distribution for Pokemon selection
    std::uniform_int_distribution<int> distribution(0, allPokemon.size() - 1);
    
    // Select random Pokemon for enemy team
    for (int i = 0; i < enemyTeamSize; i++) {
        int index = distribution(generator);
        Pokemon enemyPokemon = allPokemon[index];
        
        // Scale level based on difficulty and player's Pokemon
        float avgPlayerLevel = 0;
        for (const auto& pokemon : playerTeam.members) {
            avgPlayerLevel += pokemon.level;
        }
        avgPlayerLevel /= playerTeam.members.size();
        
        int enemyLevel = static_cast<int>(avgPlayerLevel * difficulty);
        enemyLevel = std::max(1, std::min(enemyLevel, 100)); // Keep level between 1-100
        
        enemyPokemon.setLevel(enemyLevel);
        enemyTeam.members.push_back(enemyPokemon);
    }
    
    std::cout << "Enemy team generated with " << enemyTeam.members.size() << " Pokemon!" << std::endl;
}

void Game::displayPokemonList() {
    std::cout << "Available Pokemon:" << std::endl;
    for (size_t i = 0; i < allPokemon.size(); i++) {
        const auto& pokemon = allPokemon[i];
        std::cout << (i+1) << ". " << pokemon.name 
                  << " (Type: " << getPokemonTypeName(pokemon.type1);
        
        if (pokemon.type2 != PokemonType::NONE) {
            std::cout << "/" << getPokemonTypeName(pokemon.type2);
        }
        
        std::cout << ", Base stats: HP=" << pokemon.baseHP
                  << ", Atk=" << pokemon.baseAttack
                  << ", Def=" << pokemon.baseDefense
                  << ", Spd=" << pokemon.baseSpeed
                  << ")" << std::endl;
    }
}

void Game::selectDifficulty() {
    std::cout << "Select difficulty:" << std::endl;
    std::cout << "1. Easy" << std::endl;
    std::cout << "2. Normal" << std::endl;
    std::cout << "3. Hard" << std::endl;
    std::cout << "4. Very Hard" << std::endl;
    
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    
    switch(choice) {
        case 1:
            difficulty = 0.75f;
            std::cout << "Difficulty set to Easy." << std::endl;
            break;
        case 2:
            difficulty = 1.0f;
            std::cout << "Difficulty set to Normal." << std::endl;
            break;
        case 3:
            difficulty = 1.25f;
            std::cout << "Difficulty set to Hard." << std::endl;
            break;
        case 4:
            difficulty = 1.5f;
            std::cout << "Difficulty set to Very Hard." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Setting difficulty to Normal." << std::endl;
            difficulty = 1.0f;
            break;
    }
}

void Game::selectEnvironment() {
    std::cout << "Select battle environment:" << std::endl;
    
    for (size_t i = 0; i < allEnvironments.size(); i++) {
        std::cout << (i+1) << ". " << allEnvironments[i].getName() << " - " << allEnvironments[i].getDescription() << std::endl;
    }
    
    int choice;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    
    if (choice >= 1 && choice <= static_cast<int>(allEnvironments.size())) {
        // Set current environment based on user selection
        // This is a simplified version - you may need to adapt this to your Environment class structure
        switch (choice) {
            case 1:
                currentEnvironment = BattleEnvironment::NORMAL;
                break;
            case 2:
                currentEnvironment = BattleEnvironment::FIRE;
                break;
            case 3:
                currentEnvironment = BattleEnvironment::WATER;
                break;
            case 4:
                currentEnvironment = BattleEnvironment::GRASS;
                break;
            case 5:
                currentEnvironment = BattleEnvironment::ELECTRIC;
                break;
            default:
                currentEnvironment = BattleEnvironment::NORMAL;
                break;
        }
        
        std::cout << "Environment set to " << allEnvironments[choice - 1].getName() << std::endl;
    } else {
        std::cout << "Invalid choice. Setting environment to Normal." << std::endl;
        currentEnvironment = BattleEnvironment::NORMAL;
    }
}

void Game::displayTitleArt() {
    std::cout << R"(
  _____      _                           ______       _   _   _      
 |  __ \    | |                         |  ____|     | | | | | |     
 | |__) |__ | | _____ _ __ ___   ___  _ | |__   __ _| |_| |_| | ___ 
 |  ___/ _ \| |/ / _ \ '_ ` _ \ / _ \| ||  __| / _` | __| __| |/ _ \
 | |  | (_) |   <  __/ | | | | | (_) |  | |___| (_| | |_| |_| |  __/
 |_|   \___/|_|\_\___|_| |_| |_|\___/|  |______\__,_|\__|\__|_|\___|
                                      _/ |                           
                                     |__/                            
    )" << std::endl;
}

void Game::loadPokemonData() {
    try {
        // Use DataLoader to load Pokemon from CSV file
        DataLoader dataLoader;
        allPokemon = dataLoader.loadPokemon("pokemon.csv");
        
        if (allPokemon.empty()) {
            throw std::runtime_error("No Pokemon loaded from file!");
        }
        
        std::cout << "Loaded " << allPokemon.size() << " Pokemon from file." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading Pokemon data: " << e.what() << std::endl;
        std::cerr << "Creating default Pokemon set..." << std::endl;
        
        // Create some default Pokemon if file loading fails
        allPokemon = {
            Pokemon("Bulbasaur", 1, PokemonType::GRASS, PokemonType::POISON, 45, 49, 49, 45),
            Pokemon("Charmander", 4, PokemonType::FIRE, PokemonType::NONE, 39, 52, 43, 65),
            Pokemon("Squirtle", 7, PokemonType::WATER, PokemonType::NONE, 44, 48, 65, 43),
            Pokemon("Pikachu", 25, PokemonType::ELECTRIC, PokemonType::NONE, 35, 55, 40, 90)
        };
        
        // Add some moves to default Pokemon
        // This would depend on your Move class implementation
    }
}

void Game::loadItemData() {
    try {
        // Use DataLoader to load items from CSV file
        DataLoader dataLoader;
        allItems = dataLoader.loadItems("items.csv");
        
        if (allItems.empty()) {
            throw std::runtime_error("No items loaded from file!");
        }
        
        std::cout << "Loaded " << allItems.size() << " items from file." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error loading item data: " << e.what() << std::endl;
        std::cerr << "Creating default items..." << std::endl;
        
        // Create some default items if file loading fails
        allItems = {
            Item("Potion", ItemType::HEALING, 20),
            Item("Super Potion", ItemType::HEALING, 50),
            Item("Hyper Potion", ItemType::HEALING, 200),
            Item("Max Potion", ItemType::HEALING, 999),
            Item("Revive", ItemType::REVIVAL, 0)
        };
    }
}

void Game::initializeEnvironments() {
    // Create battle environments
    allEnvironments = {
        Environment("Normal", "Standard battle environment", BattleEnvironment::NORMAL),
        Environment("Fire", "Hot environment that boosts Fire-type moves", BattleEnvironment::FIRE),
        Environment("Water", "Aquatic environment that boosts Water-type moves", BattleEnvironment::WATER),
        Environment("Grass", "Grassy environment that boosts Grass-type moves", BattleEnvironment::GRASS),
        Environment("Electric", "Charged environment that boosts Electric-type moves", BattleEnvironment::ELECTRIC)
    };
}