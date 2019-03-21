#include "DHT.h"    // 使用 ESP8266 自帶的 DHT11 函式庫
                    // 如果 libraries 已有其他的 DHT 函式庫，請先移除
#include <ESP8266WiFi.h>

//*-- Hardware Serial
#define _baudrate   9600

//*-- DHT11
#define _dhtpin     D8
#define _dhttype    DHT11

// Initialize DHT sensor 
DHT dht11( _dhtpin, _dhttype );
float temperature, humidity;

//*-- IoT Information
#define SSID    "分享器ID名稱"
#define PASS    "密碼"
#define HOST    "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149//api.thingspeak.com
#define PORT    80
// 使用 GET 傳送資料的格式
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String GET = "GET /update?key=0VD8RROGTK2MTIFT";

void setup() {
    Serial.begin( _baudrate );
    Serial.println( "ESP8266 Ready!" );
    // Connecting to a WiFi network
    Serial.print("Connect to ");
    Serial.println( SSID );
    WiFi.begin( SSID, PASS );

    // 持續等待並連接到指定的 WiFi SSID
    while( WiFi.status() != WL_CONNECTED )
    {
        delay(500);
        Serial.print( "." );
    }
    Serial.println( "" );

    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP() );
    Serial.println( "" );
    
    // DHT11
    dht11.begin();
    Serial.println( "DHT11 Ready!" );
    delay(2000);
}

void loop() {
    humidity    = dht11.readHumidity();
    temperature = dht11.readTemperature();

    // 確認取回的溫溼度數據可用
    if( isnan( humidity ) || isnan( temperature ) )
    {
        Serial.println( "Failed to read form DHT11" );
    return;
    }
    else
    {
        // DHT11 溫度與濕度傳送      
        Serial.print( "Humidity: " );
        Serial.print( humidity );
        Serial.print( ", Temperature: " );
        Serial.println( temperature );
        updateDHT11();
    }

    // 每隔多久傳送一次資料
    delay( 20000 ); // 20 second
}

void updateDHT11()
{
    // 設定 ESP8266 作為 Client 端
    WiFiClient client;
    if( !client.connect( HOST, PORT ) )
    {
        Serial.println( "connection failed" );
        return;
    }
    else
    {
        // 準備上傳到 ThingSpeak IoT Server 的資料
        // 已經預先設定好 ThingSpeak IoT Channel 的欄位
        // field1：溫度；field2：濕度
        String getStr = GET + "&field1=" + String((int)temperature) + 
                              "&field2=" + String((int)humidity) +
                              " HTTP/1.1\r\n";;
        client.print( getStr );
        client.print( "Host: api.thingspeak.com\n" );
        client.print( "Connection: close\r\n\r\n" );
        
        delay(10);
        //
        // 處理遠端伺服器回傳的訊息，程式碼可以寫在這裡！
        //


        client.stop();
    }
}