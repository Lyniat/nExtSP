#ifndef ESP_NEXT_H
#define ESP_NEXT_H

#if defined(ESP8266)

#include <ESP8266WiFi.h>

#else

#include <WiFi.h>

#endif

#include <string>

#define SSID_ADD "nExtSP_"
#define PSSWD_ADD "o--L_"

WiFiServer server(1515);

WiFiClient client;

class NEXTSP{
    public:
        void begin(bool isMaster,String id, void(* onReceive)(byte*,int)){
            _id = id;
            _onReceive = onReceive;
            _isMaster = isMaster;
            _counter = 0;
            _flip = false;
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
                    if(_counter > 0){
                        _onReceive(_receivedData,_counter);
                    }
                    _counter = 0;
                    _flip = false;
                    continue;
                }
                if(_flip){
                    _receivedData[_counter] = _receivedData[_counter]|b;
                    _counter++;
                    _flip = !_flip;
                }else{
                    _receivedData[_counter] = b;
                    _flip = !_flip;
                }
            }
        }

        void send(byte* bytes, int len){
            byte* toSend = (byte*)malloc((len*2 +1 ) * sizeof(byte));

            int byteNum = 0;

            for(auto i = 0; i < len; i++){
                toSend[byteNum] = bytes[i]&0b00001111;
                byteNum++;
                toSend[byteNum] = bytes[i]&0b11110000;
                byteNum++;
            }
            toSend[byteNum] = 0b11111111;
            client.write(toSend,(len*2 +1 ));
            delay(5); // needed to prevent crashing, but not a good solution. should be changed
        }

        void send(String s){
            const char* cString = s.c_str();

            byte* toSend = (byte*)malloc((s.length()*2 +1 ) * sizeof(byte));

            int byteNum = 0;

            for(auto i = 0; i < s.length(); i++){
                toSend[byteNum] = cString[i]&0b00001111;
                byteNum++;
                toSend[byteNum] = cString[i]&0b11110000;
                byteNum++;
            }
            toSend[byteNum] = 0b11111111;
            client.write(toSend,(s.length()*2 +1 ));
            delay(5); // needed to prevent crashing, but not a good solution. should be changed
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
        bool _flip;
        byte * _receivedData;
        void(*_onReceive)(byte*,int);
};
extern NEXTSP nextsp;

#endif
