# Compilar sketches y subirlos a la placa
## Configuracion de placa y puerto
Primero se debe configurar el puerto y el FQBN (Fully Qualified Board Name) de la placa en el archivo arduino.mk.
Para encontrar estos datos, se debe conectar el Arduino y ejecutar el comando: 
```bash
arduino-cli board list
```
## Compilar el sketch
Para compilar el sketch, se debe ejecutar el comando:
```bash
make
```
## Subir el sketch a la placa
Para subir el sketch a la placa, se debe ejecutar el comando:
```bash
make upload
```
