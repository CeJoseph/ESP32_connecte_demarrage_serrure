#include <Arduino.h>
#include <ArduinoJson.h>
#include <simplyprint.h>
#include <HTTPClient.h>
#include <arduino_secrets.h>

// Votre fonction GetState comme définie précédemment
void GetState(int printer_id, char *printer_state_code) {
    HTTPClient http;
    String path = "printers/Get";
    http.begin((API_HOST + path));
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    int httpResponseCode = http.POST("{}");

    if (httpResponseCode > 0) {
        String response = http.getString();

        const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, response);

        if (doc["status"] == true) {
            JsonArray data = doc["data"];

            for (JsonObject printerObj : data) {
                const char *printerState = printerObj["printer"]["state"];
                int printerId = printerObj["id"];

                if (printerId == printer_id) {
                // Utilisation correcte de sprintf pour copier la chaîne printerState dans printer_state_code
                sprintf(printer_state_code, "%s", printerState);  // Copier la chaîne printerState dans printer_state_code
                }
            }
        }
        http.end();
    }
}


int continuer_impression(int printer_id)
{
    bool status = false;
    HTTPClient http;
    String path = "printers/actions/Resume?pid=";
    http.begin((API_HOST + path + printer_id));
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    int httpResponseCode = http.POST("{}");

    if (httpResponseCode > 0)
    {
        String response = http.getString();

        const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, response);

        status = doc["status"];
    }
    else
    {
        printf("%d", httpResponseCode);
        printf("No response\r\n");
    }
    http.end();

    if (status == true)
    {
        return 1; // Resume successful
    }
    else
    {
        return 0; // cannot Resume
    }
}

int pauser_impression(int printer_id)
{
    bool status = false;
    HTTPClient http;

    String path = "printers/actions/Pause?pid=";
    http.begin((API_HOST + path + printer_id));
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);
    // Corps de la requête

    //A CHANGER EN FONCTION DU MENU
    String requestBody = "{\"success\": true, \"rating\": 4}";
    http.addHeader("Content-Type", "application/json");
    
    // Envoi de la requête POST
    int httpResponseCode = http.POST(requestBody);
    //int httpResponseCode = http.POST("{}");

    if (httpResponseCode > 0)
    {
        String response = http.getString();

        const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, response);
        status = doc["status"];
    }
    else
    {
        printf("%d", httpResponseCode);
        printf("No response\r\n");
    }
    http.end();

    if (status == true)
    {
        return 1; // pause successful
    }
    else
    {
        return 0; // cannot pause
    }
}

int impression_finit(int printer_id)
{
    bool status = false;
    HTTPClient http;

    String path = "printers/actions/ClearBed?pid=";
    http.begin((API_HOST + path + printer_id));
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);
    int httpResponseCode = http.POST("{}");


    if (status == true)
    {
        return 1; // pause successful
    }
    else
    {
        return 0; // cannot pause
    }
}