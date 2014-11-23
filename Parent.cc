#include "Parent.h"

#include "MPRNG.h"

static MPRNG randGen;

void Parent::main() {
	//yield()
}

Parent::~Parent() {
	terminated = true;
}