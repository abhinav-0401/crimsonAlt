#pragma once

namespace Crimson {

enum class ObjectType {
    Number,
    Boolean,
};

class Object {
public:
    virtual ObjectType obj_type() = 0;
    virtual void print_info() = 0;
};

class NumObject : public Object {
public:
    NumObject() = default;
    NumObject(double value);
    double value();
    ObjectType obj_type() override;
    void print_info() override;
private:
    double m_value;
    ObjectType m_obj_type;
};

class BoolObject : public Object {
public:
    BoolObject() = default;
    BoolObject(bool value);
    bool value();
    ObjectType obj_type() override;
    void print_info() override;
private:
    bool m_value;
    ObjectType m_obj_type;
};

} // Crimson
