#include "ApiController/ApiController.h"

ApiController *apiController = new ApiController();

const char *ssid = "Jupiter";
const char *pw = "69520405008405358281";

void setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, pw);
  apiController->initialize();
}

void loop()
{
  apiController->handleConnections();
  delay(20);
}