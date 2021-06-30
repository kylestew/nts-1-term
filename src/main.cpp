#include <Arduino.h>
#include <nts-1.h>

NTS1 nts1;

char cmd_buffer[4];

nts1_value_event_handler value_event_handler(nts1_rx_value_t* value) {
    // TODO: send value on to MAX/MSP
}

void exec_command() {
    char cmd = cmd_buffer[0];
    switch (cmd) {
        case 'v':  // sys version
            nts1.reqSysVersion();
            break;

        case 'n':  // note on
            uint8_t note = cmd_buffer[1];
            uint8_t vel = cmd_buffer[2];
            nts1.noteOn(note, vel);
            break;

        case 'o':  // note off
            uint8_t note = cmd_buffer[1];
            nts1.noteOff(note);
            break;

        case 'p':  // param change
            uint8_t id = cmd_buffer[1];
            uint8_t subid = cmd_buffer[1];
            uint8_t value = cmd_buffer[1];
            nts1.paramChange(id, subid, value);
            break;

        case 'r':  // requestion info
            // param value
            // osc count
            // osc desc
            // osc edit param desc
            // filter count
            // filter descriptor
            // envelope count
            // envelope descriptor
            // mod count
            // mod descriptor
            // delay count
            // delay descriptor
            // reverb count
            // reverb descriptor
            // (ARP various bits)
            break;

        default:
            break;
    }

    cmd_buffer = {};
}

void setup() {
    Serial.begin(115200);
    nts1.init();
}

void loop() {
    nts1.idle();
    if (Serial.available()) {
        size_t num_read = Serial.readBytesUntil('\n', cmd_buffer, sizeof(cmd_buffer) - 1);
        if (num_read > 0) {
            exec_command();
        }
    }
}