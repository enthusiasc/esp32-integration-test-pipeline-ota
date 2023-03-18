# ESP32 Integrationtest Pipeline

## About
The objective of this repository is to demonstrate the use of a continuous integration pipeline with an IoT device such as the ESP32 microcontroller.
This repository includes a [PlatformIO](https://docs.platformio.org/en/latest/what-is-platformio.html) project which makes use of the [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html) (Espressif IoT Development Framework) to implement Over-The-Air firmware update capabilities for the ESP32. The github actions pipeline provided with this repository enables for building, deploying and testing of software automatically when pushing code to the repository.


## Github Actions Pipeline  
The idea is to connect a [self-hosted github action runner](https://docs.github.com/en/actions/hosting-your-own-runners/about-self-hosted-runners) to the github repository. The self-hosted runner uses [docker](https://www.docker.com/get-started) to build and deploy the firmware to the ESP32 microcontroller. A successful deployment will trigger the execution of a java based integration test on the HTTP API of the ESP32 to validate the device is behaving properly. This requires the ESP32 and the self-hosted runner to be in the same local network. The self-hosted runner is required to have docker installed. This pipeline was tested for Linux(x64), Windows(x64) and Mac(M1) based self-hosted github action runners.

### Pipeline configuration
Configure the IP address of the ESP32 microcontroller in the [pipeline.yml](.github/workflows/pipeline.yml) file. The pipeline will deploy the build artifact to the provided ip address via the HTTP API implemented in the sample project. The same IP address will also be used as target endpoint for the integration tests.

```
env:
      ESP32_HOSTNAME: 192.168.178.43
```


## ESP32 PlatformIO Project
> :warning: The code must be flashed to the ESP32 manually at first. This can be done by importing the project within PlatformIO and uploading it to the ESP32 e.g. using a USB to Serial converter. Once the ESP32 is up and running, the pipeline will be able to upgrade the firmware over the air.

The [sample project](software/esp32) provides an HTTP API endpoint for updating the ESP32 firmware.
```
# HTTP POST a binary firmware package in order to perform an over the air update
curl "http://${ESP32_HOSTNAME}/update" -F upload=@firmware.bin
```

### Project configuration
Configure WIFI credentials in [main.cpp](software/esp32/src/main.cpp):
```
const char* ssid = "SSID";
const char* pw = "SecretPassword";
```
 
## Integration Testing
The PlatformIO project implements an HTTP API endpoint that returns device information like the system uptime and the total available flash storage from the ESP32.
```
# get device information
curl "http://${ESP32_HOSTNAME}/getDeviceInformation"
```
The [gradle project](software/integrationtests) included in this repository implements a java based integration test to verify this API endpoint. 
The integration tests will build and execute from within the docker container after a successful over the air update.

## Get Started
* Fork this repository
* Import ESP32 project within PlatformIO
* Configure WIFI credentials in [main.cpp](software/esp32/src/main.cpp)
* Upload sketch to ESP32
* Insert local IP address of ESP32 into [pipeline.yml](.github/workflows/pipeline.yml)
* Connect a self-hosted github action runner to the repository (with docker installed)
* Commit and push the changes in main.cpp and pipeline.yml to the repository 
* Benefit from the automated build, deployment and integration testing of the ESP32 sketch

