// ========================================================================
//     🔸  M U L T I P L E X E R  -  I 2 C   S C A N N E R 🔸
// ========================================================================
//  Archivo    : Multiplexer--I2C_Scanner.ino
//  Autor      : Klaus Michalsky
//  Fecha      : Mar-2026
//
//  DESCRIPCION
//  -----------------------------------------------------------------------
//  - Confirmemos la dirección del TCA9548A
//  - Si los pines A0 A1 A2 están puenteados puede ser:
//      0x71
//      0x72
//      0x73
//      ...
//      0x77
//  - Deberías ver algo como: Encontrado: 0x70
//  - Si no aparece, el problema es el cableado.
//
//  HARDWARE
//  -----------------------------------------------------------------------
//  MCU     : RP2040-Zero
//  MUX     : TCA9548A
//
//  ESTADO
//  -----------------------------------------------------------------------
//  ✅ Funcional
// ========================================================================

#include <Wire.h>

void setup()
{
    Serial.begin(115200);
    Wire.setSDA(4);
    Wire.setSCL(5);
    Wire.begin();

    Serial.println("I2C Scanner");
}

void loop()
{
    byte error, address;

    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("Encontrado: 0x");
            Serial.println(address, HEX);
        }
    }

    Serial.println("----");
    delay(3000);
}