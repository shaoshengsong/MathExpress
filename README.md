# MathExpress

**Use DAG Save Mathematical Expression and  Calculate Value**

DAG(Directed acyclic graph)

Shao ShengSong



The all code is referenced
[How To Write Your Own Tensorflow in C++](https://oneraynyday.github.io/ml/2017/10/20/Tensorflow-C++/)


I changed the code to make it easier to understand for me


**Compile Environment:**

Visual Studio 2017


**Code Explanation**


propagate:  
This function used depth - first search calcuate value

BuildGraph:
Construction DAG

**Usage:**


```
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
```


**Execute**
- _rpropagate :110
- _rpropagate : 8
- _rpropagate : 20
- _rpropagate : 240
- _rpropagate : 350
- result : 350
