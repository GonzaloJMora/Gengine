#include <iostream>
#include "Engine.h"

using namespace Gengine;

Gengine::Engine engine;

void callback();

int main( int argc, const char* argv[] ) {

	engine.Startup(callback);
    return 0;

}