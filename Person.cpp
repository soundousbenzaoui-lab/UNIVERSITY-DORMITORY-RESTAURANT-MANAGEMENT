#include "Person.h"

Person::Person(int id, const std::string& fullName)
    : m_id(id), m_fullName(fullName)
{
}

int Person::getId() const
{
    return m_id;
}

std::string Person::getFullName() const
{
    return m_fullName;
}
