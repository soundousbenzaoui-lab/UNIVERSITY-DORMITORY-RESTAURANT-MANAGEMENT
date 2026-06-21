#include "StaffRegistry.h"
#include <algorithm>
#include <iostream>

void StaffRegistry::addStaffMember(std::unique_ptr<Person> member)
{
    m_staff.push_back(std::move(member));
}

bool StaffRegistry::removeStaffMember(int id)
{
    auto it = std::find_if(m_staff.begin(), m_staff.end(),
        [id](const std::unique_ptr<Person>& p) { return p->getId() == id; });

    if (it == m_staff.end())
        return false;

    m_staff.erase(it);
    return true;
}

int StaffRegistry::getStaffCount() const
{
    return static_cast<int>(m_staff.size());
}

void StaffRegistry::displayAllStaff() const
{
    for (const auto& person : m_staff)
    {
        // person is a Person*, but describe() resolves at runtime
        // to DormSupervisor::describe() or RestaurantStaff::describe()
        // depending on the actual object — this line IS the
        // polymorphism, not the loop or the container.
        std::cout << person->describe() << std::endl;
    }
}

int StaffRegistry::countByRole(const std::string& role) const
{
    int count = 0;
    for (const auto& person : m_staff)
    {
        if (person->getRole() == role)
            ++count;
    }
    return count;
}
