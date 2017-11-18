#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <utility>

namespace ai
{

class NodeDef;

enum class OpDef {
    plus,// operator+
    minus,// operator-
    multiply,// operator*
    divide,// operator/
    exponent,// exp() // e^x
    polynomial,// poly() // x^n 指数幂 在a^n中,a叫做底数,n叫做指数。a^n读作“a的n次方”或“a的n次幂“。
    none // no operators. leaf.
};

int numOpArgs(OpDef op);

}

namespace std
{

template <> struct hash<ai::NodeDef> {
    size_t operator()(const ai::NodeDef&) const;
};
}

namespace ai
{


class NodeDef
{

struct impl;

public:

    NodeDef(std::shared_ptr<impl>);

    NodeDef(double);
    NodeDef(OpDef, const std::vector<NodeDef>&);
    ~NodeDef();


    NodeDef(NodeDef&&) noexcept;
    NodeDef& operator=(NodeDef&&) noexcept;
    
    //浅拷贝
    NodeDef(const NodeDef&);
    NodeDef& operator=(const NodeDef&);

	//深拷贝
    NodeDef Clone();
    

    double GetValue() const;
    void SetValue(double);
    OpDef GetOp() const;
    void SetOp(OpDef);
    

    std::vector<NodeDef>& GetChildren() const;
    std::vector<NodeDef> GetParents() const;


    bool operator==(const NodeDef& rhs) const;
    friend struct std::hash<NodeDef>;

    template <typename... V>
    friend const NodeDef BuildGraph(OpDef, V&...);
private: 
    // PImpl idiom :
    std::shared_ptr<impl> pimpl;
};

struct NodeDef::impl
{
public:

    impl(double);
    impl(OpDef, const std::vector<NodeDef>&);
    double val;
    OpDef op; 
    std::vector<NodeDef> children;

    std::vector<std::weak_ptr<impl>> parents;
};


template <typename... V>
const NodeDef BuildGraph(OpDef op, V&... args){
    std::vector<std::shared_ptr<NodeDef::impl> > vimpl = { args.pimpl... };
    std::vector<NodeDef> v;
    for(const std::shared_ptr<NodeDef::impl>& _impl : vimpl){
        v.emplace_back(_impl); 
    }
    NodeDef res(op, v);
    for(const std::shared_ptr<NodeDef::impl>& _impl : vimpl){
        _impl->parents.push_back(res.pimpl);
    }
    return res;
}


inline const NodeDef operator+(NodeDef lhs, NodeDef rhs){
    return BuildGraph(OpDef::plus, lhs, rhs);
}

inline const NodeDef operator-(NodeDef lhs, NodeDef rhs){
    return BuildGraph(OpDef::minus, lhs, rhs);
}

inline const NodeDef operator*(NodeDef lhs, NodeDef rhs){
    return BuildGraph(OpDef::multiply, lhs, rhs);
}

inline const NodeDef operator/(NodeDef lhs, NodeDef rhs){
    return BuildGraph(OpDef::divide, lhs, rhs);
}

inline const NodeDef exp(NodeDef v){
    return BuildGraph(OpDef::exponent, v);
}

inline const NodeDef poly(NodeDef v, NodeDef power){
    NodeDef p(power);
    return BuildGraph(OpDef::polynomial, v, p);
}

}

