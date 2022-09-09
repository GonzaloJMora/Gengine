#include <iostream>
#include "Engine.h"

using namespace Gengine;

Gengine::Engine engine;

void inputCallback();

int main( int argc, const char* argv[] ) {

	engine.Startup(inputCallback);
    return 0;

}
