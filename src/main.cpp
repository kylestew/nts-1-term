#include <Arduino.h>
#include <nts-1.h>

NTS1 nts1;

void setup() {
    // TODO: setup serial pass thru for NTS-1 commands?
    // do I need to mirror all functionality 1 to 1 or can I simplify?

    nts1.init();
}

void loop() { nts1.idle(); }