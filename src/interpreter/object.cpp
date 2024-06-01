#include <iostream>

#include "object.h"

namespace Crimson {

NumObject::NumObject(double value)
    : m_value(value)
{
}

ObjectType NumObject::obj_type() { return m_obj_type; }

double NumObject::value() { return m_value; }

void NumObject::print_info() {
    std::cout << "Object: Number\t Value: " << m_value << "\n";
}


BoolObject::BoolObject(bool value)
    : m_value(value)
{
}

ObjectType BoolObject::obj_type() { return m_obj_type; }

bool BoolObject::value() { return m_value; }

void BoolObject::print_info() {
    std::cout << "Object: Boolean\t Value: " << m_value << "\n";
}

} // Crimson
