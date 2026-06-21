#include "Restaurant.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ============================================================
// Constructor
// ============================================================

Restaurant::Restaurant()
{
    // Menus start empty — items added via addXxxItem()
}

// ============================================================
// Getters
// ============================================================

const vector<string>& Restaurant::getBreakfastMenu() const
{
    return m_breakfastMenu;
}

const vector<string>& Restaurant::getLunchMenu() const
{
    return m_lunchMenu;
}

const vector<string>& Restaurant::getDinnerMenu() const
{
    return m_dinnerMenu;
}

// ============================================================
// Menu Management — add
// ============================================================

void Restaurant::addBreakfastItem(const string& p_item)
{
    if (p_item.empty())
        throw invalid_argument("Menu item cannot be empty.");
    m_breakfastMenu.push_back(p_item);
}

void Restaurant::addLunchItem(const string& p_item)
{
    if (p_item.empty())
        throw invalid_argument("Menu item cannot be empty.");
    m_lunchMenu.push_back(p_item);
}

void Restaurant::addDinnerItem(const string& p_item)
{
    if (p_item.empty())
        throw invalid_argument("Menu item cannot be empty.");
    m_dinnerMenu.push_back(p_item);
}

// ============================================================
// Menu Management — remove
// ============================================================

// Helper: remove first occurrence of value from a vector<string>
static bool removeFromMenu(vector<string>& menu, const string& item)
{
    auto it = find(menu.begin(), menu.end(), item);
    if (it == menu.end())
        return false;
    menu.erase(it);
    return true;
}

bool Restaurant::removeBreakfastItem(const string& p_item)
{
    return removeFromMenu(m_breakfastMenu, p_item);
}

bool Restaurant::removeLunchItem(const string& p_item)
{
    return removeFromMenu(m_lunchMenu, p_item);
}

bool Restaurant::removeDinnerItem(const string& p_item)
{
    return removeFromMenu(m_dinnerMenu, p_item);
}

void Restaurant::clearMenu()
{
    m_breakfastMenu.clear();
    m_lunchMenu.clear();
    m_dinnerMenu.clear();
}

// ============================================================
// Display
// ============================================================

static void printMenuSection(const string& title,
                              const vector<string>& items)
{
    cout << "\n" << title << ":\n";
    if (items.empty())
    {
        cout << "  (no items)\n";
        return;
    }
    for (const string& item : items)
        cout << "  - " << item << "\n";
}

void Restaurant::displayMenu() const
{
    cout << "===== RESTAURANT MENU =====\n";
    printMenuSection("Breakfast", m_breakfastMenu);
    printMenuSection("Lunch",     m_lunchMenu);
    printMenuSection("Dinner",    m_dinnerMenu);
}
