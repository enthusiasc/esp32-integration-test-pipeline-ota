FROM ubuntu:latest

# install dependencies
ARG DEBIAN_FRONTEND=noninteractive
RUN apt update -qq && apt install -y -qq python3-dev python3-pip httpie openjdk-11-jre-headless
RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install -U platformio
RUN pio platform install espressif32

# build project
COPY software /opt
WORKDIR /opt/esp32
RUN platformio run
