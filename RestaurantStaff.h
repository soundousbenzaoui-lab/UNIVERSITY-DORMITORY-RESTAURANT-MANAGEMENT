#ifndef RESTAURANTSTAFF_H
#define RESTAURANTSTAFF_H

#include "StaffMember.h"
#include <string>

// ============================================================
// Class: RestaurantStaff  (CONCRETE, inherits StaffMember)
// ------------------------------------------------------------
// A staff member who works in a dormitory's restaurant. Adds a
// shift label ("Morning", "Evening", ...) — meaningless for a
// DormSupervisor, which is exactly why it lives here and not in
// the shared StaffMember base.
// ============================================================

class RestaurantStaff : public StaffMember
{
private:
    std::string m_shift;

public:
    RestaurantStaff(int id, const std::string& fullName,
                      double monthlySalary,
                      const std::string& shift);

    ~RestaurantStaff() override = default;

    std::string getShift() const;
    void        setShift(const std::string& shift);

    // --- Overrides: same two functions, completely different behavior ---
    std::string getRole()  const override;
    std::string describe() const override;
};

#endif // RESTAURANTSTAFF_H
