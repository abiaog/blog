#include <stdlib.h>
#include <iostream>
using namespace std;

class ZooAnimal
{
	public:
		ZooAnimal() {cout << "ZooAnimal constructor called!" << endl;}
		virtual ~ZooAnimal() {cout << "~ZooAnimal called!" << endl;}
};

class Bear : public virtual ZooAnimal
{
	public:
		Bear() {cout << "Bear constructor called!" << endl;}
		virtual ~Bear() {cout << "~Bear called!" << endl;}
};

class Raccoon : public virtual ZooAnimal
{
	public:
		Raccoon() {cout << "Raccoon constructor called!" << endl;}
		virtual ~Raccoon() {cout << "~Raccoon called!" << endl;}
};

class Endangered
{
	public:
		Endangered() {cout << "Endangered constructor called!" << endl;}
		virtual ~Endangered() {cout << "~Endangered called!" << endl;}
};

//class Panda : public Bear,
//	public Raccoon,
//	public Endangered
class Panda : public Endangered, // !!!
	public Bear,
	public Raccoon
{
	public:
		Panda()  
		{cout << "Panda constructor called!" << endl;}

		virtual ~Panda() {cout << "~Panda called!" << endl;}
};

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	Panda panda;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
