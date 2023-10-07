#include "Keypad.h"
#include "TextLCD.h"
#include "iostream"
#include "mbed.h"
#include "string"
#include <cmath>
#include <cstdio>

using namespace std;

TextLCD  lcd(D2, D3, D4, D5, D6, D7, TextLCD::LCD16x2);

PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

void setRGBColor(float red, float green, float blue) {
  ledR = red;
  ledG = green;
  ledB = blue;
}

Keypad kpad(D12, D14, D15, PTB8, D8, D9, D10, D11);



string leerNum() {
  string caracterPresionado = "";
  string cadena = "";

  while (caracterPresionado != "*") {
    caracterPresionado = kpad.ReadKey();

    if (caracterPresionado != "") {

      cadena += caracterPresionado;
      cout << caracterPresionado << flush;
    }
  }

  cout << endl;

  return cadena;
}

void pend_inter() {
  float x1, x2, y1, y2;
  lcd.cls();
  lcd.printf("Teniendo en cuenta el p=(x,y)");
  wait_us(2000000);
  lcd.printf("Para el primer punto: ");
  wait_us(2000000);
  lcd.printf("Digite la coordenada en x");
  wait_us(2000000);
  x1 = stoi(leerNum());
  lcd.cls();
  lcd.printf("Digite la coordenada en y");
  wait_us(2000000);
  y1 = stoi(leerNum());
  lcd.printf("Para el segundo punto: ");
  wait_us(2000000);
  lcd.printf("Digite la coordenada en x");
  wait_us(2000000);
  x2 = stoi(leerNum());
  lcd.printf("Digite la coordenada en y");
  wait_us(2000000);
  y2 = stoi(leerNum());

  if (x1 == x2) {
   lcd.printf("recta vertical no tiene pendiente,");
   wait_us(2000000);
   lcd.printf("la division por 0 es indefinida");
   wait_us(2000000);
  } else {
    float m = y2 - y1 / (x2 - x1);
    lcd.printf("La pendiente es: %.2f",m);
    wait_us(2000000);
    float inter = -1 * x1 * m + y1;
    lcd.printf("El intercepto es: %.2f",inter);
    wait_us(2000000);
  }
}

float calcular_promedio(float arr[], int n) {
  float suma = 0;
  for (int i = 0; i < n; i++) {
    suma += arr[i];
  }
  return suma / n;
}

float calcular_desviacion_estandar(float arr[], int n, float promedio) {
  float suma_cuadrados = 0;
  for (int i = 0; i < n; i++) {
    suma_cuadrados += pow(arr[i] - promedio, 2);
  }
  return sqrt(suma_cuadrados / n);
}

void temperatura() {
  int n;
  lcd.cls();
  lcd.printf("Ingrese la cantidad de");
  wait_us(1000000);
  lcd.printf("temperaturas a digitar:");
  wait_us(1000000);
  n = stoi(leerNum());
  float temps[n];
  int i = 0;
  for (i = 0; i < n; i++) {
    int i1=i+1;
    wait_us(1000000);
    lcd.cls();
    lcd.printf("ingrese la temperatura: %.0d", i1);
    temps[i] = stoi(leerNum());
  }

  float promedio = calcular_promedio(temps, n);
  lcd.cls();
  lcd.printf("Promedio de temperaturas: %.2f", promedio);
  wait_us(2000000);
  float desviacionEst = calcular_desviacion_estandar(temps, n, promedio);
  lcd.cls();
  lcd.printf("Desviacion Estandar: %.2f", desviacionEst);
  wait_us(2000000);
}

void leds() {
  lcd.cls();
  lcd.printf("Digite el valor R:");
  wait_us(2000000);
  float red = stoi(leerNum());

  while (red > 255) {
    lcd.cls();
    lcd.printf("Digite un valor [0-255]:");
    wait_us(2000000);
    red = stoi(leerNum());
  }
  lcd.cls();
  lcd.printf("Digite el valor G:");
  wait_us(2000000);
  float green = stoi(leerNum());

  while (green > 255) {
    lcd.cls();
    lcd.printf("Digite un valor [0-255]:");
    wait_us(2000000);

    green = stoi(leerNum());
  }
  lcd.cls();
  lcd.printf("Digite valor de B");
  wait_us(2000000);

  float blue = stoi(leerNum());

  while (blue > 255) {
    lcd.cls();
    lcd.printf("Digite un valor [0-255]:");
    wait_us(2000000);

    blue = stoi(leerNum());
  }

  // Asignar valor de color a los leds
  float R = 1 - ((float)(red / 255.0f));
  float G = 1 - ((float)(green / 255.0f));
  float B = 1 - ((float)(blue / 255.0f));

  setRGBColor(R, G, B);
}

int opcion;
int main() {
  lcd.printf("Elija una opción y presione *");
  wait_us(2000000);
  lcd.cls();
  lcd.printf("1.Calcular pendiente e intercepto");
  wait_us(2000000);
  lcd.cls();
  lcd.printf("2. Calcular prommedio y");
  wait_us(2000000);
  lcd.cls();
  lcd.printf("   desviacion de temperaturas.");
  wait_us(2000000);
  lcd.cls();
  lcd.printf("3.LED RGB");
  wait_us(2000000);
  


  // Leer la elección del usuario desde el teclado de membrana
  while (opcion < 1 || opcion > 3) {
    lcd.cls();
    lcd.printf("Ingrese una opcion valida");
    wait_us(2000000);
    opcion = stoi(leerNum());
  }

  switch (opcion) {
  case 1:
    pend_inter();
    break;
  case 2:
    temperatura();
    break;
  case 3:
    leds();
    break;
  }
}
