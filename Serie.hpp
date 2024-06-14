#pragma once
#include "Led.hpp"
#include <list>

using namespace std;

int TRUE = 0;
int FALSE = 1;

class Serie {

  private: 
    list<Led> serie;
    string estado = "off";
    int ltr_actual = 0;
    int rtl_actual = 4;
    unsigned int tiempoEstadoFlash = 250;
    unsigned int tiempoEstadoNormal = 500;
    unsigned int tiempoActual = tiempoEstadoNormal;
    int serieEncendida = TRUE;
    int vecesFlasheadas = 0;

  public:
    Serie(list<Led> serie) {
      this->serie = serie;
    }

    void prenderSerie() {

      for(Led led : this->serie) {
        led.encender();
      }

      this->serieEncendida = TRUE;
    
    }

    void apagarSerie() {

      for(Led led : this->serie) {
        led.apagar();
      }

      this->serieEncendida = FALSE;

    }

    void prenderSoloUno(int numero) {

      this->apagarSerie();

      int contador = 0;

      for(Led led : this->serie) {

        if (contador == numero) {
          led.encender();
          return;
        }

        contador++;
      }

    }

    void actualizarEstado() {

      //Todo esto quedaria mejor en una clase pero ya nimodo

      if (this->estado.compare("ltr") == 0) {
        prenderSoloUno(ltr_actual);
        ltr_actual += 1;

        if (ltr_actual == this->serie.size()) {
          ltr_actual = 0;
        }

      } else if(this->estado.compare("rtl") == 0) {
        prenderSoloUno(rtl_actual);
        rtl_actual -= 1;

        if (rtl_actual == -1) {
          rtl_actual = this->serie.size() - 1;
        }

      } else if (this->estado.compare("flash") == 0) {

        if (this->serieEncendida == TRUE) {
          this->apagarSerie();
        } else {
          this->prenderSerie();
        }

        if (this->vecesFlasheadas == 5*2) {
          this->vecesFlasheadas = 0;
          this->cambiarEstado("off");
        }

        this->vecesFlasheadas += 1;

      }

    }

    void cambiarEstado(string estado) {

      if (this->estado.compare("off") == 0) {
        this->estado = estado;
        this->tiempoActual = this->tiempoEstadoNormal;
        Serial.println(estado.c_str());
      } else if (this->estado.compare("off") != 0 && estado.compare("off") != 0) {
        this->estado = "flash";
        Serial.print("Comando erroneo: ");
        Serial.println(estado.c_str());
        this->tiempoActual = this->tiempoEstadoFlash;
      } else if (estado.compare("off") == 0) {
        this->estado = "off";
        this->apagarSerie();
        this->ltr_actual = 0;
        this->rtl_actual = this->serie.size() - 1;
        this->tiempoActual = 1000;
      }
      
    }

    int obtenerTiempoEstado() {
      return this->tiempoActual;
    }

};