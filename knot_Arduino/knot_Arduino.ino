#include <WebServer.h>
#include <ESPmDNS.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FastLED.h>

WebServer server(80);

#include "assets.h"

WiFiClient client;

#define LED_TYPE NEOPIXEL 
uint8_t max_bright = 128;

#define DATA_PIN1 33          
#define NUM_LEDS1 20            
CRGBArray<NUM_LEDS1> LEDBall;

int lightnumber = 0;
bool startLight[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};


void setup(){
  Serial.begin(115200);
  delay(1000); 

  FastLED.addLeds<LED_TYPE, DATA_PIN1>(LEDBall, NUM_LEDS1);

#if 1
  const char *ssid = "my board";
  const char *password = "12345679";
  if (!WiFi.softAP(ssid))
  {
    log_e("Soft AP creation failed.");
    while (1)
      ;
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
#else
  const char *ssid = "Carrot's iphone";
  const char *password = "20010119";
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
#endif

  if (MDNS.begin("knot")) // IP：knot.local
  {
    Serial.println("MDNS responder started");
  }

  server.on("/", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/html", index_page, sizeof(index_page)); });

    
  server.on("/recordingStop", []
            { 
              server.send(200, "text/plain", "Recording Stop"); 
               });

// light on
  server.on("/lightmom", []
          { 
            server.send(200, "text/plain", "light mom"); 
            startLight[0] = true; });
  server.on("/lightdad", []
          { 
            server.send(200, "text/plain", "light dad"); 
            startLight[1] = true; });
  server.on("/lightgrandma", []
          { 
            server.send(200, "text/plain", "light grandma"); 
            startLight[2] = true; });
  server.on("/lightgrandpa", []
          { 
            server.send(200, "text/plain", "light grandpa"); 
            startLight[3] = true; });
  server.on("/lighttina", []
          { 
            server.send(200, "text/plain", "light Tina"); 
            startLight[4] = true; });

  // light off

  server.on("/recordingStart", []
            { 
              server.send(200, "text/plain", "stop lighting"); 
              });
  
  server.on("/mom.html", []
          {
  server.sendHeader("content-encoding", "gzip");
  server.send_P(200, "text/html", mom_page, sizeof(mom_page)); });

  server.on("/style.css", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/css", style_css, sizeof(style_css)); });
  
  server.on("/lib/p5.js", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/javascript", p5_js, sizeof(p5_js)); });

  server.on("/lib/p5.sound.min.js", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/javascript", p5_sound_js, sizeof(p5_sound_js)); });

  server.on("/script.js", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/javascript", script_js, sizeof(script_js)); });

  server.on("/Recording.js", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/javascript", recording_js, sizeof(recording_js)); });

  server.on("/assets/myFavicon.png", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "img/png", myFavicon, sizeof(myFavicon)); });

  server.on("/events", []
            {
     Serial.print("event triggered");
    client = server.client();

    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.sendContent_P(
      "HTTP/1.1 200 OK\n"
      "Content-Type: text/event-stream;\n"
      "Connection: keep-alive\n"
      "\n");

    if (client.connected())
      client.printf("event: test\n"
      "data: test data\n"
      "\n"); });

  server.onNotFound([]
                    { server.send(404, "text/html", "<h1>Not Found</h1>"); });
  server.begin();
}

void loop(){
  server.handleClient();
  for(int i=0;i< 20;i++){
    if (startLight[i] == true) {
      fill_solid(LEDBall + i, 1, CRGB::OrangeRed);
      FastLED.show();
    } else{
      fill_solid(LEDBall + i, 1, CRGB::Black);
      FastLED.show();
    }
  }
}

        // if (client.connected())
        //   client.printf("event: pause\n"
        //                 "data: Please Stay Away\n"
        //                 "\n"); 
        // if (client.connected())
      //   client.printf("event: time\n"
      //                 "data: %02d:%02d\n"
      //                 "\n",
      //                 minute, second);

   // if (client.connected())
    //   client.printf("event: time\n"
    //                 "data: %02d:%02d\n"
    //                 "\n",
    //                 minute, second);