#include <iostream>
#include "Engine.h"

using namespace Gengine;

void callback();

int main( int argc, const char* argv[] ) {

    engine.Startup(callback);
    return 0;

}
