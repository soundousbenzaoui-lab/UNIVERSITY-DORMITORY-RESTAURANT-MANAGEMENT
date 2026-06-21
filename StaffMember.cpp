#include "StaffMember.h"
#include <stdexcept>

StaffMember::StaffMember(int id, const std::string& fullName, double monthlySalary)
    : Person(id, fullName), m_monthlySalary(monthlySalary)
{
    if (monthlySalary < 0)
        throw std::invalid_argument("Monthly salary cannot be negative.");
}

double StaffMember::getMonthlySalary() const
{
    return m_monthlySalary;
}

void StaffMember::setMonthlySalary(double salary)
{
    if (salary < 0)
        throw std::invalid_argument("Monthly salary cannot be negative.");
    m_monthlySalary = salary;
}
