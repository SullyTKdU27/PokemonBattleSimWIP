#include "item.h"
#include <sstream>

// Constructor for healing item
Item::Item(const std::string& n, int h)
    : name(n), type(ItemType::POTION), healAmount(h), healStatus(StatusEffect::NONE),
      boostStat(""), boostAmount(0) {
}

// Constructor for status healing item
Item::Item(const std::string& n, StatusEffect s)
    : name(n), type(ItemType::STATUS_HEAL), healAmount(0), healStatus(s),
      boostStat(""), boostAmount(0) {
}

// Constructor for stat boost item
Item::Item(const std::string& n, const std::string& statName, int boost)
    : name(n), type(ItemType::STAT_BOOST), healAmount(0), healStatus(StatusEffect::NONE),
      boostStat(statName), boostAmount(boost) {
}

// Check if item is a healing item
bool Item::isHealingItem() const {
    return type == ItemType::POTION;
}

// Check if item is a status-healing item
bool Item::isStatusHealItem() const {
    return type == ItemType::STATUS_HEAL;
}

// Check if item is a stat-boosting item
bool Item::isStatBoostItem() const {
    return type == ItemType::STAT_BOOST;
}

// Check if item is a revive item
bool Item::isReviveItem() const {
    return type == ItemType::REVIVE;
}

// Get item description
std::string Item::getDescription() const {
    std::stringstream ss;
    
    switch (type) {
        case ItemType::POTION:
            ss << "Heals " << healAmount << " HP";
            break;
            
        case ItemType::STATUS_HEAL:
            if (healStatus == StatusEffect::NONE) {
                ss << "Heals all status conditions";
            } else {
                ss << "Heals " << statusToString(healStatus);
            }
            break;
            
        case ItemType::STAT_BOOST:
            ss << "Raises " << boostStat << " by " << boostAmount;
            break;
            
        case ItemType::REVIVE:
            ss << "Revives a fainted Pokemon with half HP";
            break;
    }
    
    return ss.str();
}