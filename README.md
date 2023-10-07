# Parcial con LCD y KeyPad

### Por: Juan Esteban Castaño y Camilo Valencia
---

## LCD
se utiliza la libreria http://os.mbed.com/users/simon/code/TextLCD/#308d188a2d3a373e0f0757e2cc852a163d21101b para la comunicacion con el LCD. para esto se inicializa el objeto lcd asi:
```c++
#include "TextLCD.h"
TextLCD  lcd(D2, D3, D4, D5, D6, D7, TextLCD::LCD16x2);
```
Esto creara un objeto que se comunique con los diferentes puertos de la tarjeta y se especifica su tamaño.
### Metodos de lcd
cls() : Limpia todo lo que esta en la pantalla en el momento.

prinf() : imprime una cadena de caracteres en la pantalla, si sobre pasa los 16 cacarteres pasa a la segunda fila de la pantalla e imprime el resto.
```
lcd.cls();
lcd.printf("Hola profe");
```
## Metodo Principal
```c++
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
  
```
Se muestra en la pantalla lcd las instrucciones para el usuario y los diferentes casos de uso para el programa, para garantizar que solo se pueda digitar 1,2 o 3 se hace un ciclo while con las respectivas condiciones de parada.
se utiliza la funcion wait_us(2000000); para esperas 2 segundos entre mensaje impreso.

```c++
while (opcion < 1 || opcion > 3) {
    lcd.cls();
    lcd.printf("Ingrese una opcion valida");
    wait_us(2000000);
    opcion = stoi(leerNum());
  }
```
Mediante switch-case se llama a las diferentes funciones que cumple el programa.
```c++
switch(opcion) {
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
```

---
##Teclado Membrana

## Lectura de Tecla
Se importó la libreria http://os.mbed.com/users/grantphillips/code/Keypad/#4bbd88022a6f619b38925484d999e813d3a690be para el telcado de membrana, la libreria tiene un metodo ReadKey() que devulve un char con la tecla presionada. Se incluye la libreria y se inicializa. se eligio el PTB8 y no el D13 porque el D13 interactua con el led1, hacienod que no pueda funcionar la aplicacion de colores RGB.

```c++
#include "Keypad.h"
Keypad kpad(D12, D14, D15, PTB8, D8, D9, D10, D11);
```

### Para leer una cadena de caracteres
Se realiza una funcion la cual contiene la tecla que se oprime y una cadena de las teclas, en este caso se elijio el "*" para hacer las veces de enter, es decir, para que se sepa cuando para la cadena y asi devolver ésta.
```c++
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
```
### Pasar de String a Integer
Para esto se utilizo una funcion que hace parte de la libreria previamente importada <string>, teniendo en cuenta que la funcion leerNum() retorna una cadena de caracteres (String), entonces:
```c++
#include <string>
int numero = stoi(leerNum());
```

# Funciones del Programa
## Calcular Pendiente e Intercepto
Teniendo en cuenta la formula utilizada para encontrar la ecuacion de una recta que pasa por dos puntos:

m=y<sub>2</sub> - y<sub>1</sub>/(x<sub>2</sub> - x<sub>1</sub>)

y-y<sub>1</sub> = m ( x - x<sub>1</sub>)

ademas que toda recta esta dada por la forma y=mx + b, donde m es la pendiente y b (termino independiente) es el intercepto con el eje y, se hace x=0 y se despeja la y:
```c++
   int intercepto= -1*x1*m+y1;
```
Por ende la funcion para encontrar esto queda tal que asi:
```c++
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

```
*Se pide a el usuario digital las coordenadas tanto en x como en y de los dos puntos.
*Si las coordenadas en x coinciden, la recta es vertical y la division por 0 esta indefinida.
*se muestra por consola la pendiente previamente calculada y el intercepto.

## Temperaturas
### Promedio y desviacion estandar
Se realizó un metodo para calcular el promedio de los valores de un arreglo de n posiciones, este recorre cada posicion del arreglo y lo suma, despues se divide por la cantidad de elementos que contiene.
```c++
float calcular_promedio(float arr[], int n) {
  float suma = 0;
  for (int i = 0; i < n; i++) {
    suma += arr[i];
  }
  return suma / n;
}
```
Para la desviacion estandar se tiene en cuenta la sumatoria del cuadrado de el elemento en cuestion menos el promedio, despues se divide entre los n elementos y se saca raiz.
```c++
float calcular_desviacion_estandar(float arr[], int n, float promedio) {
  float suma_cuadrados = 0;
  for (int i = 0; i < n; i++) {
    suma_cuadrados += pow(arr[i] - promedio, 2);
  }
  return sqrt(suma_cuadrados / n);
}
```
### Funcion temperatura
```c++
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
```
Se le pide a el usuario el numero de temperaturas del conjunto y se almacena.
1. Se crea un arreglo con el numero introducido.
2. Mediante un ciclo for se le pide a el usuario las temperaturas una por una.
3. Teniendo el arreglo llenado, se llama a las funciones de calcular_promedio() y calcular_desviacion_estandar().
4. Se muestra por consola el resultado.


##Color RGB
Se le pide a el usuario el codigo RGB  restringiendo el input mediante ciclos while 8 de 0 a 255) y leyendo el input mediante la funcion ya utilizasa anteriormente leerNum()
```c++

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
```

*Los valores digitados por el usuario son guardados en una variable la cual se tiene que pasar a float en un intervalo de [0,1] indicando la intensidad de la luz en cada LED, siendo 0 estado alto y 1 estado bajo debido a la conexion con el sistema embebido.
*mediante la funcion setRGBColor() se le asigna a los LEDS inicalizados su respectiva intensidad.
```c++
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);

void setRGBColor(float red, float green, float blue) {
  ledR = red;
  ledG = green;
  ledB = blue;
}
```
