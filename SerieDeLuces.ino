#include <NoDelay.h>

#include <iostream>
#include <list>

#include "Serie.hpp"
#include "Led.hpp"

using namespace std;

Led led1(2);
Led led2(4);
Led led3(5);
Led led4(18);

list<Led> leds{led1, led2, led3, led4};

Serie serieLed(leds);

string readSerial();

int led_ltr = 0;
int led_rtl = 4;

noDelay timer(serieLed.obtenerTiempoEstado());

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  string comando = readSerial();
  
  if (comando.compare("ltr") == 0) {
    serieLed.cambiarEstado("ltr");
    timer.setdelay(serieLed.obtenerTiempoEstado());
  } else if(comando.compare("rtl") == 0) {
    serieLed.cambiarEstado("rtl");
    timer.setdelay(serieLed.obtenerTiempoEstado());
  } else if (comando.compare("off") == 0) {
    serieLed.cambiarEstado("off");
  }

  if(timer.update()) {
    serieLed.actualizarEstado();
  }
  
}


string readSerial() {

  if (!Serial.available()) {
    return "";
  }

  string text;

  while( Serial.available() ) {

    text += char(Serial.read());

  }

  String helper(text.c_str());

  helper.trim();

  return helper.c_str();
}
