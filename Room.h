#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include "Student.h"

// ============================================================
// Class: Room
// Responsibility: Manages a numbered room and its student list.
// Relationships:
//   - Contains a collection of Student objects (composition).
//   - Owned by Dormitory (composition).
// ============================================================

class Room
{
private:
    int                  m_roomNumber;  // Unique room identifier within a dormitory
    int                  m_capacity;   // Maximum number of students allowed
    std::vector<Student> m_students;   // Currently assigned students

public:
    // --- Constructors ---
    Room();                              // Default: room 0, capacity 0
    Room(int roomNumber, int capacity);  // Parameterised

    // --- Destructor ---
    ~Room() = default;

    // --- Getters ---
    int  getRoomNumber()       const;
    int  getCapacity()         const;
    int  getCurrentOccupancy() const;
    bool isFull()              const;

    // Read-only access to the student list
    const std::vector<Student>& getStudents() const;

    // --- Setters (validated) ---
    void setRoomNumber(int roomNumber);
    void setCapacity(int capacity);

    // --- Student management ---
    bool addStudent(const Student& student);    // Returns false if full or duplicate
    bool removeStudent(int studentId);          // Returns false if not found
    bool hasStudent(int studentId) const;       // Query without modification

    // --- Display ---
    void display() const;
};

#endif // ROOM_H
