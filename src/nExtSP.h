#ifndef ESP_NEXT_H
#define ESP_NEXT_H

#include <WiFi.h>
#include <string>

#define SSID_ADD "nExtSP_"
#define PSSWD_ADD "o--L_"

WiFiServer server(1515);

WiFiClient client;

class ESPNext{
    public:
        ESPNext(bool isMaster,String id, void(* onReceive)(byte*,int)){
            _id = id;
            _onReceive = onReceive;
            _isMaster = isMaster;
            _counter = 0;
            _receivedData = (byte*)malloc(250 * sizeof(byte));

            
            if(_isMaster == 1){
                Serial.println("I am master!");
            }else{
                Serial.println("I am slave!");
            }
            

            WiFi.disconnect();
            String SSID = SSID_ADD;
            SSID += _id;
            String Password = PSSWD_ADD;
            Password += _id;

            if(_isMaster == 1){
                WiFi.mode(WIFI_AP);
                bool result = WiFi.softAP(SSID.c_str(), Password.c_str());
                server.begin();
            }else{
                WiFi.mode(WIFI_STA);
                WiFi.begin(SSID.c_str(), Password.c_str());
        
                while (WiFi.status() != WL_CONNECTED) {
                    delay(50);
                    Serial.println("Connecting to other ESP..");
                }
        
                Serial.println("Connected to other ESP!");
            }

        }

        void update(){
            if(!client.connected())
            {
                if(_isMaster == 1)
                {
                    client = server.available();
                }
                else
                {
                    if (!client.connect(host, port)) 
                    {
                        Serial.println("Connection failed.");
                        Serial.println("Waiting 5 seconds before retrying...");
                        delay(5000);
                        return;
                    }
                    else
                    {
                        Serial.println("Connected");
                    }
                }
            }
            
            while (client.available()) 
            {
                byte b = client.read();
                if(b == 255){
                    _onReceive(_receivedData,_counter);
                    _counter = 0;
                    break;
                }

                if(b >= 0b00001111){
                    _receivedData[_counter] = _receivedData[_counter]|b;
                    _counter++;
                }else{
                    _receivedData[_counter] = b;
                }
            }
        }

        void send(byte* bytes, int len){
            for(auto i = 0; i < len; i++){
                client.write(bytes[i]&0b00001111);
                client.write(bytes[i]&0b11110000);
            }
            client.write(0b11111111);
        }

        void send(String s){
            const char* cString = s.c_str();

            for(auto i = 0; i < s.length(); i++){
                client.write(cString[i]&0b00001111);
                client.write(cString[i]&0b11110000);
            }
            client.write(0b11111111);
        }

        void send(byte b){
            byte* arr = (byte*)malloc(1 * sizeof(byte));
            arr[0] = b;
            send(arr,1);
        }

    private:
        const uint16_t port = 1515;
        const char * host = "192.168.4.1";
        String _id;
        int _isMaster;
        int _counter;
        byte * _receivedData;
        void(*_onReceive)(byte*,int);
};

#endif
