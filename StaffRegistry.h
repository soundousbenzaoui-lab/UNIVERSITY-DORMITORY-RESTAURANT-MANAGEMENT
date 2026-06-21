#ifndef STAFFREGISTRY_H
#define STAFFREGISTRY_H

#include "Person.h"
#include <vector>
#include <memory>
#include <string>

// ============================================================
// Class: StaffRegistry
// ------------------------------------------------------------
// Holds ALL staff members (any subclass of Person/StaffMember)
// through base-class pointers. This is what makes polymorphism
// real instead of decorative: the registry does not know or
// care whether each entry is a DormSupervisor or a
// RestaurantStaff — it only calls the virtual interface
// (getRole/describe), and the correct override runs at runtime.
//
// Ownership: std::unique_ptr<Person> is used instead of raw
// pointers so the registry safely deletes every object (through
// Person's virtual destructor) when it is destroyed — no manual
// cleanup, no leaks, no slicing.
//
// IMPORTANT: this class is entirely independent from
// University/Dormitory/Room/Student. It does not replace or
// modify any existing relationship in the project; it is an
// additional, optional subsystem.
// ============================================================

class StaffRegistry
{
private:
    std::vector<std::unique_ptr<Person>> m_staff;

public:
    StaffRegistry() = default;
    ~StaffRegistry() = default;

    // Takes ownership of a heap-allocated Person (or subclass).
    void addStaffMember(std::unique_ptr<Person> member);

    bool removeStaffMember(int id);

    int  getStaffCount() const;

    // Prints describe() for every staff member, polymorphically.
    void displayAllStaff() const;

    // Returns role counts, demonstrating use of getRole() per object.
    int countByRole(const std::string& role) const;
};

#endif // STAFFREGISTRY_H
