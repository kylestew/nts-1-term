#include <Arduino.h>
#include <nts-1.h>

NTS1 nts1;

HardwareSerial uart(PA3, PA2);

char cmd_buffer[8];

/*
typedef struct {
  uint8_t  req_id;
  uint8_t  main_id;
  uint8_t  sub_id;
  uint8_t  padding;
  uint16_t value;
  uint8_t padding2[10];
} nts1_rx_value_t
*/

void value_event_handler(const nts1_rx_value_t* value) {
    uart.printf("%d ", value->req_id);
    uart.printf("%d ", value->main_id);
    uart.printf("%d ", value->sub_id);
    // uart.printf("%d ", value->padding);
    // uart.printf("%hu ", (unsigned int)value->value);
    uart.print("\n");
}

void exec_command(char cmd, char param_a, char param_b) {
    switch (cmd) {
        case 'v':  // sys version
            nts1.reqSysVersion();
            break;

        case 'n':  // note on
            nts1.noteOn(param_a, param_b);
            break;

        case 'o':  // note off
            nts1.noteOff(param_a);
            break;

        case 'p':  // param change
            // nts1.paramChange(cmd_buffer[1], cmd_buffer[2], cmd_buffer[3]);
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
}

void execute_serial() {
    if (uart.available()) {
        size_t num_read = uart.readBytesUntil('\r', cmd_buffer, sizeof(cmd_buffer) - 2);
        if (num_read > 0) {
            exec_command(cmd_buffer[0], cmd_buffer[1], cmd_buffer[2]);
        }
    }
}

void setup() {
    uart.begin(9600);
    nts1.init();
}

void loop() {
    nts1.idle();
    execute_serial();
}