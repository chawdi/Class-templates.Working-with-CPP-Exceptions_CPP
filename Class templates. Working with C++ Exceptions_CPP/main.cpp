#include <iostream>

/**
 * In this laboratory work, it is necessary to solve two problems related to
  * organization of class templates. The first task is to convert to
  * template class of the numerical class that was developed by the student in
  * the first laboratory work on OOP. The second task is to develop a template
  * container. When solving the second problem, it is necessary to provide for the processing
  * exceptional situations.
  * Challenge #1
  * Design a class template for a dynamic one-dimensional array.
 */

#include <vector>

#include "vector.h"
#include "rational.h"
using std::cout;

void test_vector()
{
	int a[] = {9,8,7,6,5,4,3,2,1};
	cout << "v0 constructed from a pointer:\n	";
	lab::vector<int> v0(sizeof(a) / sizeof(int), a);
	v0.print();
	cout << "	v0, size = " << v0.size()
	     << ", capacity = " << v0.capacity() << "\n";

	cout << "v1 default constructed vector of 10 elements equal to 10:\n	";
	lab::vector<int> v1(10,10);
	v1.print();

	cout << "v2 constructed from v1:\n	";
	lab::vector<int> v2(v1);
	v2.print();

	cout << "v3 move constructed from v2:\n";
	lab::vector<int> v3(std::move(v2));
	cout << "	v2, size = " << v2.size() << ": "; v2.print();
	cout << "	v3, size = " << v3.size() << ": "; v3.print();

	cout << "v4 constructed from initializer list:\n	";
	lab::vector<int> v4{11,20,40,100,135, 341, 900, 1000, 9000, -1, -432};
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "v5 constructed from v4:\n	";
	lab::vector<int> v5{v4};
	v5.print();
	cout << "	v5, size = " << v5.size()
	     << ", capacity = " << v5.capacity() << "\n";

	cout << "v4: erase(3,3)\n	";
	v4.erase(3,3);
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "reserve 5 elements in v4:\n	";
	v4.reserve(5);
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "assign v1 to v4:\n	";
	v4.assign(v1);
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "push_back(1337) to v5:\n	";
	v5.push_back(1337);
	v5.print();
	cout << "	v5, size = " << v5.size()
	     << ", capacity = " << v5.capacity() << "\n";

	cout << "v4.insert(3, v5.data(), v5.size()):\n	";
	v4.insert(3, v5.data(), v5.size());
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "v4.insert(0, 0):\n	";
	v4.insert(0,0);
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "v4[1] = 432:\n	";
	v4[1] = 432;
	v4.print();
	cout << "	v4, size = " << v4.size()
	     << ", capacity = " << v4.capacity() << "\n";

	cout << "push_back() 1000 times to v5:\n	";
	for(int i = 0; i < 1000; i++)
		v5.push_back(i);
	v5.print();
	cout << "	v5, size = " << v5.size()
	     << ", capacity = " << v5.capacity() << "\n";

	int i = 80;
	while(i --> 0) cout << "=";
	cout << std::endl;

	cout << "exceptions:\n";

	try {
		cout << "try to create a vector from nullptr: ";
		lab::vector<int> v6(1, nullptr);
	} catch(std::exception const& e) {
		cout << e.what() << "\n";
	}

	try {
		cout << "try to access invalid element of v4: ";
		cout << v4[100];
	} catch(std::exception const& e) {
		cout << e.what() << "\n";
	}

	try {
		cout << "try to allocate 10GiB: ";
		lab::vector<int> v6(2684354560u); //try to allocate 10GiB (if int)
	} catch(std::exception const& e) {
		cout << e.what() << "\n"; // usually throws bad_alloc, but may actually take up 10GiB
	}
}

void test_rational()
{
	std::cout.setf(std::ios::boolalpha);
	std::cout <<  "operations:\n";

	lab::rational_t<char> n(94, -64);
	std::cout << n << "\n";
	std::cout << --n << "\n";
	std::cout << -n << "\n";
	std::cout << lab::rational_t<char>(3, 1) + lab::rational_t<char>(1, 1) << "\n";
	std::cout << lab::rational_t<char>(3, 2) - lab::rational_t<char>(8, 4) << "\n";
	std::cout << lab::rational_t<char>(1, 2) * lab::rational_t<char>(6, 1) << "\n";
	std::cout << lab::rational_t<char>(1, 2) / lab::rational_t<char>(6, 1) << "\n";

	std::cout <<  "\n\ncomparisons:\n";
	std::cout << (lab::rational_t<char>(1, 2) == lab::rational_t<char>(6, 1)) << "\n";
	std::cout << (lab::rational_t<char>(1, 2) == lab::rational_t<char>(2, 4)) << "\n";

	std::cout << (lab::rational_t<char>(1, 2) > lab::rational_t<char>(1, 4)) << "\n";
	std::cout << (lab::rational_t<char>(-1, -2) < lab::rational_t<char>(1, 98)) << "\n";

	std::cout << (lab::rational_t<char>(1, 3) >= lab::rational_t<char>(1, 98)) << "\n";
	std::cout << (lab::rational_t<char>(1, 3) <= lab::rational_t<char>(1, 3)) << "\n";

	std::cout << "\n\ninvalid rational:\n";
	try {
		lab::rational_t<char> invalid(1, 0);
	} catch (std::exception const& e) {
		std::cout << "error: " << e.what() << "\n";
	}



}

int main()
{
	test_vector();
	return 0;
}
