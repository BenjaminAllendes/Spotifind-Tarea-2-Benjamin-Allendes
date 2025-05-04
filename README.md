# Spotifind

Este sistema permite a los usuarios cargar canciones de un archivo csv, buscar las canciones cargadas por su genero, artista, o tempo (rapidez). 

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++, como **C/C++ Extension Pack de Microsoft**. Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

## Requisitos previos:

- Tener instalado Visual Studio Code.
- Instalar la extensión **C/C++** (Microsoft).
- Tener instalado un compilador de C (como gcc). Si estás en Windows, se recomienda instalar MinGW o utilizar el entorno WSL.

## Pasos para compilar y ejecutar:

1. Descarga y descomprime el archivo `.zip` en una carpeta de tu elección.
2. Abre el proyecto en Visual Studio Code
    -Inicia Visual Studio Code.
    -Selecciona `Archivo > Abrir carpeta...` y elige la carpeta donde descomprimiste el proyecto.
3. Compila el código
    - Abre el archivo principal (`spotifind.c`).
    - Abre la terminal integrada (`Terminal > Nueva terminal`).
    - En la terminal, compila el programa con el siguiente comando:
    ```
    gcc tdas/*.c spotifind.c -Wno-unused-result -o spotifind
    ```
4. Ejecuta el programa
    - Una vez compilado, puedes ejecutar la aplicación con:`
    ```
    ./spotifind
    ```
## Funcionalidades

### Funcionando correctamente:
- Cargar canciones de un archivo csv, guardar la informacion relevante de cada cancion y mostrar cada cancion guardada.
- Buscar canciones por genero y mostrar la informacion guardada de cada una.
- Buscar canciones por artista y mostrar la informacion guardada de cada una.
- Buscar canciones por tempo (lentas, moderadas y rapidas) y mostrar la informacion guardada de cada una.

### Problemas conocidos:
- Programa tiene problemas con algunos caracteres especiales como las tildes. 

### A mejorar:
- Compatibilidad con mas tipos de caracteres para evitar problemas con canciones que contengan estos.
- Implementar una interfaz mas amigable

## Ejemplo de uso
### Paso 1: Cargar canciones
En `sptofind.c` se ingresa la ruta de la ruta del arhcivo CSV dentro de la carpeta del programa  de donde se quiera cargar las canciones (por ejemplo `data/song_dataset_.csv`), se guardan la informacion de las canciones y se muestra cada cancion guardada.

```
60  FILE *archivo = fopen("RUTA DEL ARCHIVO", "r");
```

### Paso 2: Buscar por genero
Tras cargar las canciones, el usuario decide buscar todas las canciones de un artista que fueron cargadas.
```
Opcion seleccionada: 2) Asignar prioridad a ticket
ID del ticket: ticket-1
1) Prioridad Baja
2) Prioridad Media
3) Prioridad Alta
Ingrese su opcion: 3
Prioridad asignada correctamente!
```


### Paso 3: Ver la lista de tickets
El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.
```
Tickets en espera:
ID: ticket-1 prioridad = Alta <--
```
La lista muestra el ticket ingresado anteriormente, indicando que es el siguiente ticket en ser atendido

### Paso 4: Atender el siguiente ticket
El ticket con ID IIIIII es procesado y se revisa su solicitud de ayuda.
```
Opcion seleccionada: 4) Atender al siguiente ticket
Siguiente ticket: ID = ticket-1
Fecha y hora = Fri Apr 11 20:59:04 2025
Problema = Pagina web no carga.
Prioridad Alta
```
El sistema muestra la informacion guardada y lo elimina del sistema.

### Paso 5: Buscar ticket por ID
Otro ticket se registra y se ingresa para mostrar su informacion.
```
ID del ticket: otro-ticket

Informacion Del ticket 'otro-ticket':
Hora = Fri Apr 11 21:00:11 2025
Problema = No cargan las imagenes de la web.
Prioridad media
```
