#ifndef ESP_NEXT_H
#define ESP_NEXT_H

#include <WiFi.h>
#include <String.h>

#define ID "43750697"

#define SSID_ADD "nExtSP_"
#define PSSWD_ADD "o--L_"

WiFiServer server(1515);

WiFiClient client;

class ESPNext{
    public:
        ESPNext(int pin){
            _pin = pin;
            pinMode(_pin, INPUT);
            _isMaster = digitalRead(_pin);

            if(_isMaster == 1){
                Serial.println("I am master!");
            }else{
                Serial.println("I am slave!");
            }

            WiFi.disconnect();
            String SSID = SSID_ADD;
            SSID += ID;
            String Password = PSSWD_ADD;
            Password += ID;

            if(_isMaster == 1){
                bool result = WiFi.softAP(SSID.c_str(), Password.c_str());
                server.begin();
            }else{
                WiFi.begin(SSID.c_str(), Password.c_str());
        
                while (WiFi.status() != WL_CONNECTED) {
                    delay(50);
                    Serial.println("Connecting to other ESP..");
                }
        
                Serial.println("Connected to other ESP!");
            }

        }

        void update(){
            if(_isMaster == 1){
                client = server.available();
            }else{
                if (!client.connect(host, port)) {
                    Serial.println("Connection failed.");
                    Serial.println("Waiting 5 seconds before retrying...");
                    delay(5000);
                    return;
                }else{
                    Serial.println("Connected");
                }
            }
            
            /*
            if (!client.available()>0) {
                Serial.println("not avialbale");
                return;
            }
            */

           if (client.available()) {
                char c = client.read();
                Serial.println(c);
            }
            

            if(_isMaster == 1){
                Serial.println("sending m");
                client.write('m');
            }else{
                Serial.println("sending s");
                server.write('s');
            }  

        }
    private:
        const uint16_t port = 1515;
        const char * host = "192.168.4.1";
        int _pin;
        int _isMaster;
};

#endif