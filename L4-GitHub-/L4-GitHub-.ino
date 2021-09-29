//********************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrnónica Digital 2
// José David Méndez 19380
// Laboratorio
//********************************************************************************

//**********************************************************************************************************************
// Librerías
//**********************************************************************************************************************
#include <Arduino.h>
#include <LiquidCrystal.h> // Librería que contiene la cofiguración completa de la pantalla LCD
//**********************************************************************************************************************
// Defincion de Pines
//**********************************************************************************************************************
#define d4 18
#define d5 5
#define d6 17
#define d7 16
#define en 19
#define rs 21
#define btn1 12
#define btn2 32
#define pot1 34
#define pot2 35
//**********************************************************************************************************************
// Prototipo de Funciones
//**********************************************************************************************************************
void voltaje1(void); // Función para la impresión del voltaje del potenciometro 1
void voltaje2(void); // Función para la impresión del voltaje del potenciometro 2
void UPC(void);      // Función para la impresión del contador en la LCD
//**********************************************************************************************************************
// Variables Globales
//**********************************************************************************************************************
LiquidCrystal LCD(rs, en, d4, d5, d6, d7); // Variables definidas en la librería
uint8_t decenas, unidades, decimal;
uint8_t decenas1, unidades1, decimal1;
uint8_t centenas, decenas2, unidades2;
int adcRaw;
int contador = 0;
int estadobtn1 = 0;
int estadobtn2 = 0;
float voltaje;
float voltajeB;
//**********************************************************************************************************************
// ISR: Interrupciones
//**********************************************************************************************************************
void IRAM_ATTR ISRbtn1()
{ // Interrupción del boton de incrementar el contador
  estadobtn1 = 1;
  if (contador > 255)
  { // Condición que establece que el contador no se mayor al numero de condiciones que se tiene.
    contador = 0;
  }
}
void IRAM_ATTR ISRbtn2()
{ // Interrupción del boton de decrementar el contador
  estadobtn2 = 1;
  if (contador < 0)
  { // Condición que establece que el contador no tenga valores negativos.
    contador = 0;
  }
}
//**********************************************************************************************************************
// Configuracion
//**********************************************************************************************************************
void setup()
{
  // Velocidad a la que trabaja la comunicación serial
  Serial.begin(115200);

  // Se establece que los botones son entradas
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);

  // Se establece que la LCD utilizada es de 16x2
  LCD.begin(16, 2);

  // Se establece la relación entre los botones y sus respectivas interrupciones
  attachInterrupt(btn1, ISRbtn1, HIGH);
  attachInterrupt(btn2, ISRbtn2, HIGH);
}
//**********************************************************************************************************************
// LOOP
//**********************************************************************************************************************
//**********************************************************************************************************************
// Fuinciones
//**********************************************************************************************************************
