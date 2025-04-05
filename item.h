#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "status.h"

/**
 * @brief Enum representing different item types
 */
enum class ItemType {
    POTION,
    STATUS_HEAL,
    STAT_BOOST,
    REVIVE
};

/**
 * @brief Class representing a usable item
 */
class Item {
public:
    /**
     * @brief Constructor for a healing item
     * @param n Name of the item
     * @param h Amount of HP to heal
     */
    Item(const std::string& n, int h);
    
    /**
     * @brief Constructor for a status healing item
     * @param n Name of the item
     * @param s StatusEffect the item can cure (NONE for all status effects)
     */
    Item(const std::string& n, StatusEffect s);
    
    /**
     * @brief Constructor for a stat-boosting item
     * @param n Name of the item
     * @param statName The name of the stat to boost
     * @param boost The amount to boost the stat by
     */
    Item(const std::string& n, const std::string& statName, int boost);
    
    std::string name;
    ItemType type;
    
    // Healing properties
    int healAmount;
    
    // Status healing properties
    StatusEffect healStatus;
    
    // Stat boost properties
    std::string boostStat;
    int boostAmount;
    
    /**
     * @brief Checks if the item is a healing item
     * @return True if the item is a healing item
     */
    bool isHealingItem() const;
    
    /**
     * @brief Checks if the item is a status-healing item
     * @return True if the item is a status-healing item
     */
    bool isStatusHealItem() const;
    
    /**
     * @brief Checks if the item is a stat-boosting item
     * @return True if the item is a stat-boosting item
     */
    bool isStatBoostItem() const;
    
    /**
     * @brief Checks if the item is a revive item
     * @return True if the item is a revive item
     */
    bool isReviveItem() const;
    
    /**
     * @brief Get a description of the item
     * @return String describing the item's effects
     */
    std::string getDescription() const;
};

#endif // ITEM_H