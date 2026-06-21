#include "Room.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ============================================================
// Constructors
// ============================================================

Room::Room()
    : m_roomNumber(0), m_capacity(0)
{
}

Room::Room(int p_roomNumber, int p_capacity)
    : m_roomNumber(p_roomNumber), m_capacity(p_capacity)
{
    if (p_roomNumber < 0)
        throw invalid_argument("Room number cannot be negative.");
    if (p_capacity <= 0)
        throw invalid_argument("Room capacity must be > 0.");
}

// ============================================================
// Getters
// ============================================================

int Room::getRoomNumber() const
{
    return m_roomNumber;
}

int Room::getCapacity() const
{
    return m_capacity;
}

int Room::getCurrentOccupancy() const
{
    return static_cast<int>(m_students.size());
}

bool Room::isFull() const
{
    // Cast to the same signed type to avoid -Wsign-compare
    return getCurrentOccupancy() >= m_capacity;
}

const vector<Student>& Room::getStudents() const
{
    return m_students;
}

// ============================================================
// Setters
// ============================================================

void Room::setRoomNumber(int p_roomNumber)
{
    if (p_roomNumber < 0)
        throw invalid_argument("Room number cannot be negative.");
    m_roomNumber = p_roomNumber;
}

void Room::setCapacity(int p_capacity)
{
    if (p_capacity <= 0)
        throw invalid_argument("Room capacity must be > 0.");
    // Prevent reducing capacity below current occupancy
    if (p_capacity < getCurrentOccupancy())
        throw invalid_argument("New capacity cannot be less than current occupancy.");
    m_capacity = p_capacity;
}

// ============================================================
// Student management
// ============================================================

bool Room::hasStudent(int p_studentId) const
{
    for (const Student& s : m_students)
    {
        if (s.getId() == p_studentId)
            return true;
    }
    return false;
}

bool Room::addStudent(const Student& p_student)
{
    if (isFull())
        return false;

    // Prevent duplicate assignment
    if (hasStudent(p_student.getId()))
        return false;

    m_students.push_back(p_student);
    return true;
}

bool Room::removeStudent(int p_studentId)
{
    for (auto it = m_students.begin(); it != m_students.end(); ++it)
    {
        if (it->getId() == p_studentId)
        {
            m_students.erase(it);
            return true;
        }
    }
    return false;
}

// ============================================================
// Display
// ============================================================

void Room::display() const
{
    cout << "Room Number: " << m_roomNumber << "\n"
         << "Capacity:    " << m_capacity   << "\n"
         << "Occupancy:   " << getCurrentOccupancy()
         << "/" << m_capacity << "\n";

    if (m_students.empty())
    {
        cout << "(No students assigned)\n";
        return;
    }

    cout << "\nStudents:\n";
    for (const Student& s : m_students)
    {
        s.display();
        cout << "------------------------\n";
    }
}
