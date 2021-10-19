# Sistema de preservacion del agua
El sistema consiste en un dispositivo que contará con una válvula eléctrica, un pedal, una pantalla y un buzzer, todo controlado a través de un microcontrolador Arduino UNO. De esta manera, podemos hacer uso del pedal para iniciar el paso del agua sólo cuando es necesario, en lugar de desperdiciarla constantemente.
## Descarga
Para descargar este proyecto, se debe ejecutar el siguiente comando
```bash
git clone https://github.com/Juan-010/Sistema-de-preservacion-del-agua.git <directorio>
```
## Instalacion Arduino-CLI
Para compilar este proyecto, es necesario instalar arduino-cli. Siga las instrucciones en https://github.com/arduino/arduino-cli
### Configuración de librerías
Para que los sketches reconozcan las librerías de este proyecto, es necesario modificar la variable de entorno ARDUINO_DIRECTORIES_USER al valor del path del repositorio.
```bash
export ARDUINO_DIRECTORIES_USER=/path/to/repo/Sistema-de-preservacion-del-agua
```
