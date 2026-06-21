#include "University.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ============================================================
// Constructors
// ============================================================

University::University()
    : m_name("")
{
}

University::University(const string& p_name)
    : m_name(p_name)
{
    if (p_name.empty())
        throw invalid_argument("University name cannot be empty.");
}

// ============================================================
// Getters
// ============================================================

string University::getName() const
{
    return m_name;
}

int University::getNumberOfDormitories() const
{
    return static_cast<int>(m_dormitories.size());
}

const vector<Dormitory>& University::getDormitories() const
{
    return m_dormitories;
}

// Const overload — safe read-only lookup
const Dormitory* University::findDormitory(const string& p_name) const
{
    for (const Dormitory& d : m_dormitories)
    {
        if (d.getName() == p_name)
            return &d;
    }
    return nullptr;
}

// Non-const overload — allows modification of the returned dormitory
Dormitory* University::findDormitory(const string& p_name)
{
    for (Dormitory& d : m_dormitories)
    {
        if (d.getName() == p_name)
            return &d;
    }
    return nullptr;
}

// ============================================================
// Setter
// ============================================================

void University::setName(const string& p_name)
{
    if (p_name.empty())
        throw invalid_argument("University name cannot be empty.");
    m_name = p_name;
}

// ============================================================
// Dormitory Management
// ============================================================

bool University::hasDormitory(const string& p_name) const
{
    return findDormitory(p_name) != nullptr;
}

void University::addDormitory(const Dormitory& p_dormitory)
{
    // Prevent duplicate dormitory names
    if (hasDormitory(p_dormitory.getName()))
        throw invalid_argument("A dormitory with this name already exists.");
    m_dormitories.push_back(p_dormitory);
}

bool University::removeDormitory(const string& p_name)
{
    for (size_t i = 0; i < m_dormitories.size(); ++i)
    {
        if (m_dormitories[i].getName() == p_name)
        {
            m_dormitories.erase(m_dormitories.begin() + static_cast<long>(i));
            return true;
        }
    }
    return false;
}

// ============================================================
// Display
// ============================================================

void University::displayDormitories() const
{
    if (m_dormitories.empty())
    {
        cout << "(No dormitories registered)\n";
        return;
    }

    for (const Dormitory& d : m_dormitories)
    {
        cout << "  - " << d.getName()
             << "  [capacity: " << d.getCapacity()
             << ", available rooms: " << d.getAvailableRooms() << "]\n";
    }
}

void University::displayUniversityInfo() const
{
    cout << "University Name:      " << m_name << "\n"
         << "Number of Dorms:      " << getNumberOfDormitories() << "\n";
}
