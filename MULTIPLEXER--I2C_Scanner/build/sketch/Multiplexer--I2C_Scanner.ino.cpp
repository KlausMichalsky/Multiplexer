#include <Arduino.h>
#line 1 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\AS5600--I2C_angle\\Multiplexer--I2C_Scanner\\Multiplexer--I2C_Scanner.ino"
#include <Wire.h>

#line 3 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\AS5600--I2C_angle\\Multiplexer--I2C_Scanner\\Multiplexer--I2C_Scanner.ino"
void setup();
#line 13 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\AS5600--I2C_angle\\Multiplexer--I2C_Scanner\\Multiplexer--I2C_Scanner.ino"
void loop();
#line 3 "C:\\Users\\Benutzer1\\Documents\\# Github repositories\\AS5600--I2C_angle\\Multiplexer--I2C_Scanner\\Multiplexer--I2C_Scanner.ino"
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
