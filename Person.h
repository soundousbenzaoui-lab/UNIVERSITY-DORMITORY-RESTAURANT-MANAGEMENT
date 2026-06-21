#ifndef PERSON_H
#define PERSON_H

#include <string>

// ============================================================
// Class: Person  (ABSTRACT BASE CLASS)
// ------------------------------------------------------------
// Purpose: common identity contract shared by every human role
// in the university system. This class is NOT used by the
// existing Student/Room/Dormitory/University classes — it is
// the root of a NEW, separate hierarchy (StaffMember) added to
// demonstrate real inheritance + polymorphism without touching
// or risking the already-working composition design.
//
// Why abstract: a bare "Person" with no role is not a concept
// the system needs to instantiate. Forcing getRole()/describe()
// to be pure virtual means every concrete subclass MUST define
// its own behavior — this is what makes the polymorphism real
// rather than decorative.
// ============================================================

class Person
{
protected:
    int         m_id;
    std::string m_fullName;

public:
    Person(int id, const std::string& fullName);

    // Virtual destructor is mandatory: Person will be deleted
    // through base-class pointers (see StaffRegistry), and
    // without this, derived destructors would never run.
    virtual ~Person() = default;

    // --- Getters (shared, non-virtual: identical for all roles) ---
    int         getId()       const;
    std::string getFullName() const;

    // --- Pure virtual contract: every subclass MUST implement ---
    // Returns a short role label, e.g. "Student", "Dorm Supervisor".
    virtual std::string getRole() const = 0;

    // Returns a one-line human-readable description.
    // This is the method that demonstrates polymorphism: calling
    // describe() through a Person* invokes the correct override
    // at runtime, without the caller knowing the concrete type.
    virtual std::string describe() const = 0;
};

#endif // PERSON_H
