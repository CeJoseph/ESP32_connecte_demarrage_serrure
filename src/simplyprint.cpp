#include <Arduino.h>
#include <ArduinoJson.h>
#include <simplyprint.h>
#include <HTTPClient.h>
#include <arduino_secrets.h>
// a

String GetState(int printer_id)
{
    HTTPClient http;
    String path = "printers/Get";
    http.begin((API_HOST + path));
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    int httpResponseCode = http.POST("{}");

    if (httpResponseCode > 0)
    {
        String response = http.getString();

        const size_t capacity = 10 * JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + 1024;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, response);

        if (doc["status"] == true)
        {
            JsonArray data = doc["data"];

            for (JsonObject printerObj : data)
            {
                const char *printerName = printerObj["printer"]["name"];
                const char *printerState = printerObj["printer"]["state"];

                int printerId = printerObj["id"];

                if (printerId == printer_id)
                {
                    return printerState;
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
        printf("\r\nNo response\r\n");
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
        printf("\r\nNo response\r\n");
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

int annuler_impression(int printer_id, int raison)//cant currently be tested, remove this comment once prints are finished and the function can be tested.
{
    bool status = false;
    HTTPClient http;

    String path = "printers/actions/Cancel?pid=";
    http.begin((API_HOST + path + printer_id));
    http.addHeader("accept", "application/json");
    http.addHeader("X-API-KEY", API_KEY);

    int httpResponseCode = http.POST("{\"reason\": " + (String)raison + "}");

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
        printf("\r\nNo response\r\n");
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

//a
