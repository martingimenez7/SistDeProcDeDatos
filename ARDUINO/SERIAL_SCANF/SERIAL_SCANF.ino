/******************************************************************
* Programa: Ejemplo de uso de la lectura por el Puerto Serie
*
* Objetivo:
*   Mostrar los aspectos básicos del funcionamiento del Puerto Serie
*
* Aspectos a destacar:
*   -Escritura por el puerto serie
*   -Lectura por el puerto serie
* 
*
* Versión: 0.1 del 5 de marzo de 2017
* Autor: Mauricio Dávila
* Revisión: -
*
* *******************************************************************/

#include "stdarg.h";

void serialPrintf(char *text, ...);


/** \brief  Se invoca una sola vez cuando el programa empieza. 
 *          Se utiliza para inicializar los modos de trabajo 
 *          de los pines, el puerto serie, etc... 
 * \param void
 * \return void
 */
void setup() {
  Serial.begin(9600); // Setea la velocidad del puerto Serie
}


/** \brief  Contiene el programa que se ejecutará cíclicamente
 *          
 * \param void
 * \return void
 */
void loop() 
{
  char rxBuffer[50];
  serialPrintf("Ingrese un texto y finalice con el caracter -\n");
  serialScanf(rxBuffer);
  serialPrintf("%s",rxBuffer);
}

/** \brief  Emula el funcionamiento del printf.
 * \param Recibe un texto seguido por argumentos variables
 * \return void
 */
void serialPrintf(char *text, ...)
{
  char aux[100];
  va_list ap;
  va_start(ap,text);
  vsprintf(aux,text,ap);
  va_end(ap);
  Serial.print(aux);
}

/** \brief  Emula el funcionamiento del scanf.
 * \param Recibe un array char donde guardar los bytes que recibe por el puerto
 * \return void
 */
void serialScanf(char *text)
{
  char byteRecibido = 0;
  int i=0;
  
  while(byteRecibido != '-')
  {
    if (Serial.available() > 0) 
    {
      byteRecibido = Serial.read();
      text[i] = byteRecibido;
      i++;
    }
  }
  text[i-1] = '\0';
}
