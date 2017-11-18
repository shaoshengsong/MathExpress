#include "stdafx.h"
#include "GraphDef.h"
#include <cmath>
#include <exception>

namespace ai
{
double _eval(OpDef op, const std::vector<NodeDef>& operands)
{
    switch(op){
        case OpDef::plus:
            return operands[0].GetValue() + operands[1].GetValue();
        case OpDef::minus:
            return operands[0].GetValue() - operands[1].GetValue();
        case OpDef::multiply:
            return operands[0].GetValue() * operands[1].GetValue();
        case OpDef::divide:
            return operands[0].GetValue() / operands[1].GetValue();
        case OpDef::exponent:
            return std::exp(operands[0].GetValue());
        case OpDef::polynomial:
            return std::pow(operands[0].GetValue(), operands[1].GetValue());
        case OpDef::none:
            throw std::invalid_argument("_eval invalid argument");
    }; 

	return 0.0;
}


GraphDef::GraphDef(NodeDef _root) : root(_root){}

NodeDef GraphDef::GetRoot()const
{
    return root;
}

// depth-first search 递归式的深度优先搜索
void _rpropagate(NodeDef& v)
{
    if(v.GetChildren().empty())
        return;
    std::vector<NodeDef> children = v.GetChildren(); 
    for(NodeDef& _v : children){
        _rpropagate(_v);
    }
    v.SetValue(_eval(v.GetOp(), v.GetChildren()));
	std::cout <<"_rpropagate:" <<v.GetValue()<<std::endl;
}

double GraphDef::propagate()
{
    _rpropagate(root);
    return root.GetValue();
}



double GraphDef::eval()
{
	return propagate();
}

}
