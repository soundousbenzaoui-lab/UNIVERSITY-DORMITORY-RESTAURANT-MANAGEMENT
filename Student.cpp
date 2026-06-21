#include "Student.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// ============================================================
// Constructors
// ============================================================

Student::Student()
    : m_id(0), m_fullName(""), m_academicYear(1)
{
}

// Parameter names use the p_ prefix so they never shadow members.
Student::Student(int p_id, const string& p_fullName, int p_academicYear)
    : m_id(p_id), m_fullName(p_fullName), m_academicYear(p_academicYear)
{
    // Basic validation at construction time
    if (m_id < 0)
        throw invalid_argument("Student ID cannot be negative.");
    if (m_fullName.empty())
        throw invalid_argument("Student full name cannot be empty.");
    if (m_academicYear < 1)
        throw invalid_argument("Academic year must be >= 1.");
}

// ============================================================
// Getters
// ============================================================

int Student::getId() const
{
    return m_id;
}

string Student::getFullName() const
{
    return m_fullName;
}

int Student::getAcademicYear() const
{
    return m_academicYear;
}

// ============================================================
// Setters
// ============================================================

void Student::setId(int p_id)
{
    if (p_id < 0)
        throw invalid_argument("Student ID cannot be negative.");
    m_id = p_id;
}

void Student::setFullName(const string& p_fullName)
{
    if (p_fullName.empty())
        throw invalid_argument("Student full name cannot be empty.");
    m_fullName = p_fullName;
}

void Student::setAcademicYear(int p_year)
{
    if (p_year < 1)
        throw invalid_argument("Academic year must be >= 1.");
    m_academicYear = p_year;
}

// ============================================================
// Display
// ============================================================

void Student::display() const
{
    cout << "ID: "            << m_id           << "\n"
         << "Full Name: "     << m_fullName     << "\n"
         << "Academic Year: " << m_academicYear << "\n";
}
