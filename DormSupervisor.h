#ifndef DORMSUPERVISOR_H
#define DORMSUPERVISOR_H

#include "StaffMember.h"
#include <string>

// ============================================================
// Class: DormSupervisor  (CONCRETE, inherits StaffMember)
// ------------------------------------------------------------
// A staff member responsible for one specific dormitory
// building. Adds the dormitory name they supervise — a piece
// of data that has no meaning for a generic StaffMember or for
// restaurant staff.
// ============================================================

class DormSupervisor : public StaffMember
{
private:
    std::string m_assignedDormitoryName;

public:
    DormSupervisor(int id, const std::string& fullName,
                    double monthlySalary,
                    const std::string& assignedDormitoryName);

    ~DormSupervisor() override = default;

    std::string getAssignedDormitoryName() const;
    void        setAssignedDormitoryName(const std::string& dormName);

    // --- Overrides: function overriding in action ---
    std::string getRole()   const override;
    std::string describe()  const override;
};

#endif // DORMSUPERVISOR_H
