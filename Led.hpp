#pragma once

class Led {

    public:
        Led(int pin) {
            this->pin = pin;
            this->modo = OUTPUT;

            pinMode(pin, OUTPUT);

        }

        void encender() {
            digitalWrite(this->pin, HIGH);
        }

        void apagar() {
            digitalWrite(this->pin, LOW);
        }

        void cambiarEstado() {
            if (this->modo == HIGH) {
                pinMode(this->pin, LOW);
            } else {
                pinMode(this->pin, HIGH);
            }
        }

    private:
        int pin;
        int modo;

};