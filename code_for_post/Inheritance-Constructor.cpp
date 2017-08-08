#include <stdlib.h>
#include <string>
#include <memory>


struct Base1 {
	Base1() = default;
	Base1(const std::string&);
//	Base1(std::shared_ptr<int>);
};

struct Base2 {
	Base2() = default;
	Base2(const std::string&);
	Base2(int);
};

// error: D1 attempts to inherit D1::D1 (const string&) from both base classes
// struct D1: public Base1, public Base2 {
//     using Base1::Base1;  // inherit constructors from Base1
//         using Base2::Base2;  // inherit constructors from Base2
//         };
// }


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


