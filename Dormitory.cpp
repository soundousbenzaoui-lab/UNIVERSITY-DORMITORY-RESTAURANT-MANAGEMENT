#include "Dormitory.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ============================================================
// Constructors
// ============================================================

Dormitory::Dormitory()
    : m_name(""), m_capacity(0)
{
}

Dormitory::Dormitory(const string& p_name, int p_capacity)
    : m_name(p_name), m_capacity(p_capacity)
{
    if (p_name.empty())
        throw invalid_argument("Dormitory name cannot be empty.");
    if (p_capacity <= 0)
        throw invalid_argument("Dormitory capacity must be > 0.");
}

// ============================================================
// Getters
// ============================================================

string Dormitory::getName() const
{
    return m_name;
}

int Dormitory::getCapacity() const
{
    return m_capacity;
}

int Dormitory::getTotalRooms() const
{
    return static_cast<int>(m_rooms.size());
}

int Dormitory::getAvailableRooms() const
{
    int count = 0;
    for (const Room& room : m_rooms)
    {
        if (!room.isFull())
            ++count;
    }
    return count;
}

int Dormitory::getTotalOccupancy() const
{
    int total = 0;
    for (const Room& room : m_rooms)
        total += room.getCurrentOccupancy();
    return total;
}

const Restaurant& Dormitory::getRestaurant() const
{
    return m_restaurant;
}

Restaurant& Dormitory::getRestaurant()
{
    return m_restaurant;
}

const vector<Room>& Dormitory::getRooms() const
{
    return m_rooms;
}

// ============================================================
// Setters
// ============================================================

void Dormitory::setName(const string& p_name)
{
    if (p_name.empty())
        throw invalid_argument("Dormitory name cannot be empty.");
    m_name = p_name;
}

void Dormitory::setCapacity(int p_capacity)
{
    if (p_capacity <= 0)
        throw invalid_argument("Dormitory capacity must be > 0.");
    m_capacity = p_capacity;
}

// ============================================================
// Room Management
// ============================================================

bool Dormitory::hasRoom(int p_roomNumber) const
{
    for (const Room& room : m_rooms)
    {
        if (room.getRoomNumber() == p_roomNumber)
            return true;
    }
    return false;
}

Room* Dormitory::findRoom(int p_roomNumber)
{
    for (Room& room : m_rooms)
    {
        if (room.getRoomNumber() == p_roomNumber)
            return &room;
    }
    return nullptr;
}

void Dormitory::addRoom(const Room& p_room)
{
    // Prevent duplicate room numbers within the same dormitory
    if (hasRoom(p_room.getRoomNumber()))
        throw invalid_argument("A room with this number already exists in the dormitory.");
    m_rooms.push_back(p_room);
}

bool Dormitory::removeRoom(int p_roomNumber)
{
    for (size_t i = 0; i < m_rooms.size(); ++i)
    {
        if (m_rooms[i].getRoomNumber() == p_roomNumber)
        {
            m_rooms.erase(m_rooms.begin() + static_cast<long>(i));
            return true;
        }
    }
    return false;
}

// ============================================================
// Student Management
// ============================================================

bool Dormitory::hasStudent(int p_studentId) const
{
    for (const Room& room : m_rooms)
    {
        if (room.hasStudent(p_studentId))
            return true;
    }
    return false;
}

bool Dormitory::assignStudentToRoom(const Student& p_student, int p_roomNumber)
{
    // A student must not already live somewhere in this dormitory
    if (hasStudent(p_student.getId()))
        return false;

    Room* room = findRoom(p_roomNumber);
    if (room == nullptr)
        return false;

    return room->addStudent(p_student);
}

bool Dormitory::removeStudentFromRoom(int p_studentId, int p_roomNumber)
{
    Room* room = findRoom(p_roomNumber);
    if (room == nullptr)
        return false;

    return room->removeStudent(p_studentId);
}

// ============================================================
// Display
// ============================================================

void Dormitory::displayRooms() const
{
    if (m_rooms.empty())
    {
        cout << "(No rooms registered)\n";
        return;
    }

    for (const Room& room : m_rooms)
    {
        room.display();
        cout << "--------------------\n";
    }
}

void Dormitory::displayDormitoryInfo() const
{
    cout << "Dormitory Name:   " << m_name           << "\n"
         << "Capacity:         " << m_capacity        << "\n"
         << "Total Rooms:      " << getTotalRooms()   << "\n"
         << "Available Rooms:  " << getAvailableRooms()<< "\n"
         << "Total Occupancy:  " << getTotalOccupancy()<< "\n";
}
