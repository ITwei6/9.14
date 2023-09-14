#include <iostream>
using namespace std;
#include "mymap.h"
#include "myset.h"
#include "RBTree.h"


int main()
{

	tao::map<int, int> m;
	m.insert(make_pair(2, 2));
	m.insert(make_pair(1, 1));
	m.insert(make_pair(3, 3));
	m.insert(make_pair(4, 4));


	tao::set<int> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
}