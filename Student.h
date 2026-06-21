#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// ============================================================
// Class: Student
// Responsibility: Stores and exposes student identity data.
// Relationships: Contained (by value) inside Room.
// ============================================================

class Student
{
private:
    int         m_id;           // Unique student identifier
    std::string m_fullName;     // Full legal name
    int         m_academicYear; // Year of study (1-based)

public:
    // --- Constructors ---
    Student();                                                      // Default: zeroed state
    Student(int id, const std::string& fullName, int academicYear); // Parameterised

    // --- Destructor ---
    ~Student() = default; // No dynamic resources; compiler default is correct

    // --- Getters ---
    int         getId()           const;
    std::string getFullName()     const;
    int         getAcademicYear() const;

    // --- Setters (input-validated) ---
    void setId(int id);
    void setFullName(const std::string& fullName);
    void setAcademicYear(int year);

    // --- Display ---
    void display() const;
};

#endif // STUDENT_H
