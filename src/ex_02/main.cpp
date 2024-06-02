#include "dibse.h"

int distance;
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
