#include "ApiController.h"

const int port = 80;
WebServer webServer(port);

void ApiController::handleConnections()
{
  webServer.handleClient();
}

void ApiController::initialize()
{
    // register http api endpoint for over the air firmware update
    webServer.on("/update", HTTP_POST, std::bind(&ApiController::performOTAUpdate, this), std::bind(&ApiController::uploadOTAUpdate, this));
    // register other http api endpoints
    webServer.on("/getDeviceInformation", std::bind(&ApiController::apiGetDeviceInformation, this));
    webServer.begin();
}

void ApiController::uploadOTAUpdate() {
    HTTPUpload& upload = webServer.upload();
    if (upload.status == UPLOAD_FILE_START) {
      Update.begin(UPDATE_SIZE_UNKNOWN);
    }
    else if (upload.status == UPLOAD_FILE_WRITE) {
      Update.write(upload.buf, upload.currentSize);
    }
    else if (upload.status == UPLOAD_FILE_END) {
      Update.end(true);
    }
 }

void ApiController::performOTAUpdate() {
    webServer.send(200, "text/plain", (Update.hasError()) ? "ERROR" : "SUCCESS");
    delay(300);
    ESP.restart();
}

void ApiController::apiGetDeviceInformation() {
    StaticJsonDocument<1000> jsonDocument;
    jsonDocument["total_flash_memory_mega_bytes"] = spi_flash_get_chip_size()/(1024*1024);
    jsonDocument["device_uptime_microseconds"] = esp_timer_get_time();  
    String json;
    serializeJson(jsonDocument, json);
    webServer.send(200, "application/json", json); 
}
