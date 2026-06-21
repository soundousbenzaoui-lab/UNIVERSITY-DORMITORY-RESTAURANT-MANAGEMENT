#ifndef STAFFMEMBER_H
#define STAFFMEMBER_H

#include "Person.h"
#include <string>

// ============================================================
// Class: StaffMember  (ABSTRACT, inherits Person)
// ------------------------------------------------------------
// Purpose: common ground for every paid employee of the
// dormitory/restaurant system (as opposed to a Student, who is
// a resident, not an employee). Adds a salary attribute that
// only makes sense for staff, not for students.
//
// Still abstract: getRole()/describe() remain undefined here,
// so concrete duties (DormSupervisor, RestaurantStaff) must
// each provide their own meaningful implementation.
// ============================================================

class StaffMember : public Person
{
protected:
    double m_monthlySalary;

public:
    StaffMember(int id, const std::string& fullName, double monthlySalary);

    ~StaffMember() override = default;

    // --- Getter / setter specific to staff ---
    double getMonthlySalary() const;
    void   setMonthlySalary(double salary);

    // getRole() and describe() are still NOT implemented here —
    // they remain pure virtual (inherited from Person), forcing
    // every concrete staff type below to define its own.
};

#endif // STAFFMEMBER_H
