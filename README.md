# DBM
Prácticas y problemas de la asignatura de Diseño Basado en Microprocesadores.
## x86
 - Práctica 4 fallos problema 3
 - Práctica 5 fallos problema 3

## ARM
Contiene las prácticas de ARM de la asignatura.

## OEM_Base_Board_rev_C.pdf
Esquemas de la placa de desarrollo del laboratorio, útil para el proyecto de la asignatura.

## AVR_WIFI_TEST
Proyecto para el microcontrolador ATMEGA8515 para probar el módulo ESP8266. Puede ser fácilmente adaptado para cualquier otro ATMEGA cambiando la librería UART.

## Proyecto
Contiene el proyecto de la asignatura. Este proyecto consiste en el envío de las lecturas de los sensores LDR y de temperatura a un servidor NodeJS el cual se encargará de almacenar dicha información en un servidor de MongoDB. El envío se hace mediante el módulo ESP8266 ya probado en el proyecto AVR_WIFI_TEST. La librería usada en este proyecto para la comunicación con el módulo ESP8266 es la misma del proyecto AVR antes mencionado, solo que adaptada al microcontrolador LPC4088 y con algunas mejoras en cuanto al tratamiento de errores. Dichas mejoras del tratamiento de errores habría que perfeccionarlas.

## Node_Server
Aquí se almacena el servidor NodeJS usado en el proyecto. El servidor contiene 3 ficheros principales, siendo "index.js" el fichero a ejecutar para iniciar el servidor. El servidor se inicia con el comando "node index.js", desde el terminal de un ordenador que tenga dicho software instalado.
 - index.js: Este fichero es el principal, es el encargado de unir los módulos e iniciar el servidor. Aquí se configura el puerto a usar por el servidor.
 - routes/sensors.js: Este fichero contiene los "endpoints" del servidor, a los cuales se accede mediante la dirección IP del ordenador que ejecuta el servidor, dos puntos, el puerto del servidor, barra y el endpoint en cuestión.
 - routes/sensors-service.js:
