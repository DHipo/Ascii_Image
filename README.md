# Template - Proyecto C++ con MSYS2

Este es un template para proyectos en C++ con SDL2.

## Prerrequisitos

Antes de comenzar, asegúrate de tener instalados los siguientes componentes:

1. **MSYS2**: Puedes descargarlo desde [msys2.org](https://www.msys2.org/).

2. **Paquetes necesarios**: Los paquetes esenciales para la compilación de proyectos en C++ en MSYS2. 

## Instalación de MSYS2 y Paquetes Necesarios

1. **Instala MSYS2**: Sigue las instrucciones de instalación en [msys2.org](https://www.msys2.org/).

2. **Actualiza los paquetes de MSYS2**: Abre el shell de MSYS2 (MSYS2 MinGW 64-bit) y ejecuta los siguientes comandos:

    ```sh
    pacman -Syu
    ```

3. **Instala el toolchain de MinGW y las bibliotecas necesarias**:

    ```sh
    pacman -S mingw-w64-x86_64-toolchain
    pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_image
    ```

## Compilación del Proyecto

1. **Clona el repositorio del proyecto** (si aún no lo has hecho):

    ```sh
    git clone <URL_DEL_REPOSITORIO>
    cd <NOMBRE_DEL_REPOSITORIO>
    ```

2. **Limpia el directorio de compilación** (opcional pero recomendado antes de una compilación limpia):

    ```sh
    make clean
    ```

3. **Compila el proyecto**:

    ```sh
    make
    ```

## Ejecución del Proyecto

1. **Ejecuta el proyecto**:

    ```sh
    make IMAGE_NAME="name of image in the assets/img folder" run
    ```

## Estructura del Proyecto

```plaintext
.
├── bin
│   ├── out
│   │   └── (archivos objeto)
│   └── (archivo ejecutable)
├── include
│   ├── (archivos de cabecera)
│   └── (subdirectorios con archivos de cabecera)
├── src
│   └── (archivos fuente)
├── Makefile
└── README.md
