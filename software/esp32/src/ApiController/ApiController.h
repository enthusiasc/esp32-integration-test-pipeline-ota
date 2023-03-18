#define ARDUINOJSON_USE_LONG_LONG 1
#include "ArduinoJson.h"
#include "WebServer.h"
#include "Update.h"

class ApiController
{
    public:
        void initialize();
        void handleConnections();
    private:
        void uploadOTAUpdate();
        void performOTAUpdate();
        void apiGetDeviceInformation();
};