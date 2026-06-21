#include "DormSupervisor.h"
#include <stdexcept>
#include <sstream>

DormSupervisor::DormSupervisor(int id, const std::string& fullName,
                                double monthlySalary,
                                const std::string& assignedDormitoryName)
    : StaffMember(id, fullName, monthlySalary),
      m_assignedDormitoryName(assignedDormitoryName)
{
    if (assignedDormitoryName.empty())
        throw std::invalid_argument("Assigned dormitory name cannot be empty.");
}

std::string DormSupervisor::getAssignedDormitoryName() const
{
    return m_assignedDormitoryName;
}

void DormSupervisor::setAssignedDormitoryName(const std::string& dormName)
{
    if (dormName.empty())
        throw std::invalid_argument("Assigned dormitory name cannot be empty.");
    m_assignedDormitoryName = dormName;
}

std::string DormSupervisor::getRole() const
{
    return "Dorm Supervisor";
}

std::string DormSupervisor::describe() const
{
    std::ostringstream oss;
    oss << getRole() << " " << m_fullName
        << " (ID " << m_id << ") supervises \""
        << m_assignedDormitoryName << "\", salary: "
        << m_monthlySalary << " DZD/month.";
    return oss.str();
}
