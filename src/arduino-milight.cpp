#define DEBUG

#include <Arduino.h>
#include <RF24.h>

#ifdef DEBUG
    #include <printf.h>
#endif

#include "PL1167_nRF24.h"
#include "MiLightRadio.h"

#define CE_PIN 8
#define CSN_PIN 10
#define SYNC_BUTTON_PIN 2

// define message template (id, id, id, color, brightness, button, seq)
static uint8_t message_t[] = {0xB0, 0x2C, 0x8C, 0x00, 0xB9, 0, 0xDD};
// create nrf object
RF24 nrf24(CE_PIN, CSN_PIN);
// create pl1167 abstract object
PL1167_nRF24 prf(nrf24);
// create MiLight Object
MiLightRadio mlr(prf);
// create global sequence number
uint8_t seq_num = 0x00;



void setup() {
    Serial.begin(115200);
#ifdef DEBUG
    printf_begin();
#endif
    pinMode(SYNC_BUTTON_PIN, INPUT);
    delay(1000);
    Serial.println("# MiLight starting");
    // setup mlr (wireless settings)
    mlr.begin();


}

/**
 * Sends data via the MiLight Object.
 * Transmits mutliple times to improve chance of receiving.
 *
 * @param data uint8_t array of data to send
 * @param resend normally a packed is transmitted 3 times, for more important packages this number can be increased
 */
void send_raw(uint8_t data[7], uint8_t resend = 3) {
    data[6] = seq_num;
    seq_num++;
    mlr.write(data, 7);
    delay(1);
    for (int j = 0; j < resend; ++j) {
        mlr.resend();
        delay(5);
    }
    delay(10);

#ifdef DEBUG
    Serial.print("Sending: ");
    for (int i = 0; i < 7; i++) {
        printf("%02X ", data[i]);
    }
    Serial.print("\r\n");
#endif
}

/**
 * Converts RGB color to MiLight value
 *
 * MiLight works with 256 values where 26 is red
 */
uint8_t rgb2milight(uint8_t red, uint8_t green, uint8_t blue) {
    float rd = (float) red / 255;
    float gd = (float) green / 255;
    float bd = (float) blue / 255;
    float max = max(rd, max(gd, bd));
    float min = min(rd, min(gd, bd));
    float h = max;

    float d = max - min;
    if (max == min) {
        h = 0; // achromatic
    } else {
        if (max == rd) {
            h = (gd - bd) / d + (gd < bd ? 6 : 0);
        } else if (max == gd) {
            h = (bd - rd) / d + 2;
        } else if (max == bd) {
            h = (rd - gd) / d + 4;
        }
        h /= 6;
    }

    return (uint8_t) (int) ((h) * 256) + 26 % 256;
}

/**
 * Converts percentage to MiLight brightness
 *
 * MiLight works from 0x99 (dim) - 0x00/0xFF - 0xB9 (bright) with a step size of 0x08
 * This function translates 0-100 in this range
 */
uint8_t percentage2mibrightness(uint8_t percentage) {
    return (uint8_t) (145 - (int) (percentage / 3.58) * 8);
}

/**
 * Sends a set color message
 */
void setColor(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t message[7];
    memcpy(message, message_t, 7);
    message[5] = 0x0F;
    message[3] = rgb2milight(red, green, blue);
    send_raw(message);
}

/**
 * Sends a set brightness message
 *
 * @param percentage from 0 to 100
 */
void setBrightness(uint8_t percentage) {
    uint8_t message[7];
    memcpy(message, message_t, 7);
    message[5] = 0x0E;
    message[4] = percentage2mibrightness(percentage);
    send_raw(message);
}

/**
 * Syncs bulb to this device
 *
 * This is the same as long pressing a group button on the remote.
 *
 * @param group from 1 - 4
 */
void sendSync(uint8_t group) {
#ifdef DEBUG
    Serial.println("Sending sync signal for Group " + String(group));
#endif
    uint8_t message[7];
    memcpy(message, message_t, 7);
    // 0x03, 0x05, 0x07, 0x09
    message[5] = 3 + 2 * (group - 1);
    send_raw(message, 10);
    delay(50);
    // 0x13, 0x15, 0x17, 0x19
    message[5] = 19 + 2 * (group - 1);
    send_raw(message, 10);
}

void loop() {
    if (digitalRead(SYNC_BUTTON_PIN)) {

        sendSync(1);
    }

//    setColor(255, 0, 0);
//    setBrightness(100);
    delay(1000);
}
