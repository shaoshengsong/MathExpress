// MathExpress.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include "GraphDef.h"
int main()
{
	ai::NodeDef t1 = 12;
	ai::NodeDef t2 = t1 + ai::poly(2, 3);
	ai::NodeDef t3(10);
	ai::NodeDef t4 = t3 * 11 + t1* t2;

	ai::GraphDef g(t4);
	double d = g.eval();;
	std::cout << "result:" << d << std::endl;
	return 0;
}


