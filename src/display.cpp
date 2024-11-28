#include <Arduino.h>
#include <display.h>
#include <board_mapping.h>
#define boutonSelect A0
#define pot A2
HardwareSerial MySerial(1); // define a Serial for UART1
const int MySerialRX = 16;
const int MySerialTX = 17;

void init_ecran(void)
{
    MySerial.begin(9600, SERIAL_8N1, MySerialRX, MySerialTX);
}
int select(void)
{
    pinMode(boutonSelect, INPUT_PULLUP);
    if (digitalRead(boutonSelect))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int curseur(void)
{
    int potValue = analogRead(pot);
    Serial.println(potValue);
    if (potValue < 1023)
    {
        return 0; // Valeur entre 0 et 1022 (inclus)
    }
    else if (potValue >= 1023 && potValue < 2046)
    {
        return 1; // Valeur entre 1023 et 2045 (inclus)
    }
    else if (potValue >= 2046 && potValue < 3069)
    {
        return 2; // Valeur entre 2046 et 3068 (inclus)
    }
    else
    {
        return 3; // Valeur supérieure ou égale à 3069
    }
}
void clear_screen(void)
{
    MySerial.write(0xFE);
    MySerial.write(0x51);
}

int afficher_message_accueil(int curseurTest)
{
    if (curseurTest == 0 || curseurTest == 1)
    {
        MySerial.write(" [choix 1]");
        MySerial.write(0xFE);
        MySerial.write(0x45);
        MySerial.write(0x40);
        MySerial.write("choix 2");
        MySerial.write(0xFE);
        MySerial.write(0x45);
        MySerial.write(0x14);
        MySerial.write("choix 3");
        return 0;
    }

    else if (curseurTest == 2)
    {
        MySerial.write(" choix 1");
        MySerial.write(0xFE);
        MySerial.write(0x45);
        MySerial.write(0x40);
        MySerial.write("[choix 2]");
        MySerial.write(0xFE);
        MySerial.write(0x45);
        MySerial.write(0x14);
        MySerial.write("choix 3");
        return 0;
    }
    else 
    {
        MySerial.write(" choix 1");
        MySerial.write(0xFE);
        MySerial.write(0x45);
        MySerial.write(0x40);
        MySerial.write("choix 2");
        MySerial.write(0xFE);
        MySerial.write(0x45);
        MySerial.write(0x14);
        MySerial.write("[choix 3]");
        return 0;
    }
}