#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <vector>
#include <string>
#include "Dormitory.h"

// ============================================================
// Class: University
// Responsibility: Top-level aggregate; owns and manages a
//                 collection of Dormitory objects.
// Relationships:
//   - Composes a vector<Dormitory> (1 university → many dorms).
// ============================================================

class University
{
private:
    std::string             m_name;        // University display name
    std::vector<Dormitory>  m_dormitories; // All registered dormitories

public:
    // --- Constructors ---
    University();
    explicit University(const std::string& name); // explicit prevents implicit conversion

    // --- Destructor ---
    ~University() = default;

    // --- Getters ---
    std::string getName()                 const;
    int         getNumberOfDormitories()  const;

    // Find a dormitory by name; returns nullptr if not found
    const Dormitory* findDormitory(const std::string& name) const;
          Dormitory* findDormitory(const std::string& name);

    // Read-only access to the full list
    const std::vector<Dormitory>& getDormitories() const;

    // --- Setter ---
    void setName(const std::string& name);

    // --- Dormitory Management ---
    void addDormitory   (const Dormitory& dormitory);
    bool removeDormitory(const std::string& name);   // Returns false if not found
    bool hasDormitory   (const std::string& name) const;

    // --- Display ---
    void displayDormitories()   const;
    void displayUniversityInfo() const;
};

#endif // UNIVERSITY_H
