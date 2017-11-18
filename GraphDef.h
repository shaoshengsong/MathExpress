#pragma once

#include "NodeDef.h"
#include <queue>
#include <unordered_map>
#include <unordered_Set>

namespace ai
{
class GraphDef 
{
public:
    GraphDef(NodeDef);
    NodeDef GetRoot() const;
    double propagate();
private:
    NodeDef root;
public:
	double eval();//º∆À„÷µ
};

}
