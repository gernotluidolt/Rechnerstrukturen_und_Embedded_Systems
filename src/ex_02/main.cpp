#include "dibse.h"

DibsE dibse;

void setup()
{
    Serial.begin (115200);
    dibse.setup();
}

void loop()
{
    dibse.loop();
}
