#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <string>

// ============================================================
// Class: Restaurant
// Responsibility: Manages daily meal menus for a dormitory.
// Relationships:
//   - Owned by Dormitory (composition, 1-to-1).
// ============================================================

class Restaurant
{
private:
    std::vector<std::string> m_breakfastMenu; // Breakfast items
    std::vector<std::string> m_lunchMenu;     // Lunch items
    std::vector<std::string> m_dinnerMenu;    // Dinner items

public:
    // --- Constructors / Destructor ---
    Restaurant();
    ~Restaurant() = default;

    // --- Getters ---
    const std::vector<std::string>& getBreakfastMenu() const;
    const std::vector<std::string>& getLunchMenu()     const;
    const std::vector<std::string>& getDinnerMenu()    const;

    // --- Menu Management ---
    void addBreakfastItem(const std::string& item);
    void addLunchItem    (const std::string& item);
    void addDinnerItem   (const std::string& item);

    bool removeBreakfastItem(const std::string& item); // Returns false if not found
    bool removeLunchItem    (const std::string& item);
    bool removeDinnerItem   (const std::string& item);

    void clearMenu(); // Clears all three menus

    // --- Display ---
    void displayMenu() const;
};

#endif // RESTAURANT_H
