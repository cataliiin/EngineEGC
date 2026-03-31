#include <iostream>
#include "Engine/Engine.h"

int main(int argc, char **argv)
{
    Engine engine;
    engine.init(800, 600, "EngineEGC", true, Color4(0.0f, 0.0f, 0.0f, 1.0f));
    engine.run();
    return 0;
}