#include "RestaurantStaff.h"
#include <stdexcept>
#include <sstream>

RestaurantStaff::RestaurantStaff(int id, const std::string& fullName,
                                  double monthlySalary,
                                  const std::string& shift)
    : StaffMember(id, fullName, monthlySalary), m_shift(shift)
{
    if (shift.empty())
        throw std::invalid_argument("Shift cannot be empty.");
}

std::string RestaurantStaff::getShift() const
{
    return m_shift;
}

void RestaurantStaff::setShift(const std::string& shift)
{
    if (shift.empty())
        throw std::invalid_argument("Shift cannot be empty.");
    m_shift = shift;
}

std::string RestaurantStaff::getRole() const
{
    return "Restaurant Staff";
}

std::string RestaurantStaff::describe() const
{
    std::ostringstream oss;
    oss << getRole() << " " << m_fullName
        << " (ID " << m_id << ") works the "
        << m_shift << " shift, salary: "
        << m_monthlySalary << " DZD/month.";
    return oss.str();
}
