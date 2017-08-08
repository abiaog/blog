#include <stdlib.h>
#include <iostream>
using namespace std;

class ZooAnimal
{
	public:
		ZooAnimal() {cout << "ZooAnimal constructor called!" << endl;}
		virtual ~ZooAnimal() {cout << "~ZooAnimal called!" << endl;}
};

class Bear : public ZooAnimal
{
	public:
		Bear() {cout << "Bear constructor called!" << endl;}
		virtual ~Bear() {cout << "~Bear called!" << endl;}
};

class Endangered
{
	public:
		Endangered() {cout << "Endangered constructor called!" << endl;}
		virtual ~Endangered() {cout << "~Endangered called!" << endl;}
};

class Panda : public Bear, public Endangered
// class Panda : public Endangered, public Bear 
{
	public:
		Panda() : Endangered()
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
	ZooAnimal *zooAnimal = &panda;

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
