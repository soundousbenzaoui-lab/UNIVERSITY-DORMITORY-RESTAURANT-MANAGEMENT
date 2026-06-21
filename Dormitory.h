#ifndef DORMITORY_H
#define DORMITORY_H

#include <vector>
#include <string>

#include "Student.h"
#include "Room.h"
#include "Restaurant.h"

// ============================================================
// Class: Dormitory
// Responsibility: Manages rooms, student assignments, and owns
//                 exactly one Restaurant (composition).
// Relationships:
//   - Composes a vector<Room>  (1 dormitory → many rooms).
//   - Composes one Restaurant  (1 dormitory → 1 restaurant).
//   - Owned by University      (University → many Dormitories).
// ============================================================

class Dormitory
{
private:
    std::string         m_name;       // Dormitory display name
    int                 m_capacity;   // Maximum total students
    std::vector<Room>   m_rooms;      // All rooms in this dormitory
    Restaurant          m_restaurant; // The single attached restaurant

public:
    // --- Constructors ---
    Dormitory();                                         // Default
    Dormitory(const std::string& name, int capacity);   // Parameterised

    // --- Destructor ---
    ~Dormitory() = default;

    // --- Getters ---
    std::string getName()           const;
    int         getCapacity()       const;
    int         getTotalRooms()     const;        // Total room count
    int         getAvailableRooms() const;        // Rooms with free beds
    int         getTotalOccupancy() const;        // Sum of all occupancies

    // Const and non-const access to the restaurant
    const Restaurant& getRestaurant() const;
    Restaurant&       getRestaurant();

    // Read-only access to the room list
    const std::vector<Room>& getRooms() const;

    // --- Setters (validated) ---
    void setName    (const std::string& name);
    void setCapacity(int capacity);

    // --- Room management ---
    void addRoom   (const Room& room);
    bool removeRoom(int roomNumber);          // Returns false if not found
    bool hasRoom   (int roomNumber) const;    // Query without side-effects
    Room* findRoom (int roomNumber);          // nullptr if not found

    // --- Student management ---
    // Assign student to a specific room; returns false on failure
    bool assignStudentToRoom  (const Student& student, int roomNumber);
    // Remove student from a specific room; returns false on failure
    bool removeStudentFromRoom(int studentId, int roomNumber);
    // Check whether a student is anywhere in this dormitory
    bool hasStudent(int studentId) const;

    // --- Display ---
    void displayRooms()         const;
    void displayDormitoryInfo() const;
};

#endif // DORMITORY_H
