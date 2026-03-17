// ========================================================================
//     🔸 A S 5 6 0 0  -  I 2 C  A N G L E   M U L T I P L E X E R 🔸
// ========================================================================
//  Archivo    : AS5600--I2C_angle_Multiplexer.ino
//  Autor      : Klaus Michalsky
//  Fecha      : Mar-2026
//
//  DESCRIPCION
//  -----------------------------------------------------------------------
//  - Lee el ángulo de 2 sensores AS5600 usando un multiplexor TCA9548A.
//  - Usa solo el bus I2C Wire.
//  - Canal 1 -> Motor1
//  - Canal 2 -> Motor2
//
//  HARDWARE
//  -----------------------------------------------------------------------
//  MCU     : RP2040-Zero
//  Sensor  : 2x AS5600
//  MUX     : TCA9548A
// ========================================================================

#include <Wire.h>

#define AS5600_ADDR 0x36
#define TCA_ADDR 0x70

//------------------------------------------------
// Seleccionar canal del TCA9548A
//------------------------------------------------
void tcaSelect(uint8_t channel)
{
    if (channel > 7)
        return;

    Wire.beginTransmission(TCA_ADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

//------------------------------------------------
// Leer ángulo AS5600
//------------------------------------------------
uint16_t readAS5600Angle()
{
    Wire.beginTransmission(AS5600_ADDR);
    Wire.write(0x0E);
    Wire.endTransmission(false);

    Wire.requestFrom(AS5600_ADDR, (uint8_t)2);

    if (Wire.available() < 2)
        return 0;

    uint8_t high = Wire.read();
    uint8_t low = Wire.read();

    return ((high & 0x0F) << 8) | low;
}

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Wire.setSDA(4);
    Wire.setSCL(5);
    Wire.begin();

    Serial.println("Sistema AS5600 con TCA9548A listo");
}

void loop()
{
    //------------------------------------------------
    // Motor 1 -> Canal 1
    //------------------------------------------------
    tcaSelect(1);
    uint16_t angle_mot1 = readAS5600Angle();
    float degrees_mot1 = (angle_mot1 * 360.0) / 4096.0;

    //------------------------------------------------
    // Motor 2 -> Canal 2
    //------------------------------------------------
    tcaSelect(2);
    uint16_t angle_mot2 = readAS5600Angle();
    float degrees_mot2 = (angle_mot2 * 360.0) / 4096.0;

    Serial.print("Ángulo Motor1: ");
    Serial.print(degrees_mot1);
    Serial.println("°");

    Serial.print("Ángulo Motor2: ");
    Serial.print(degrees_mot2);
    Serial.println("°");

    delay(200);
}