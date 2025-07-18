# Usamos la imagen base oficial de Ubuntu 22.04, la misma que usa GitHub
FROM ubuntu:22.04

# Establecemos el frontend de apt para que no haga preguntas interactivas
ENV DEBIAN_FRONTEND=noninteractive

# LA SOLUCIÓN: La lista de dependencias completa y verificada
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    gobjc++ \
    libasound2-dev \
    libjack-jackd2-dev \
    libx11-dev \
    libxinerama-dev \
    libxrandr-dev \
    libxcursor-dev \
    libgl-dev \
    libfreetype6-dev \
    libfontconfig1-dev \
    libgtk-3-dev \
    git \
    cmake

# Establecemos el directorio de trabajo dentro del contenedor
WORKDIR /work
