FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
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

WORKDIR /work
