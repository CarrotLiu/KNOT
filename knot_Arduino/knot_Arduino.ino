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
bool colorLight[] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

void setup()
{
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

  // index.html
  server.on("/",  []
    {
      server.sendHeader("content-encoding", "gzip");
      server.send_P(200, "text/html", index_page, sizeof(index_page)); 
    });
  // css
  server.on("/style.css", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/css", style_css, sizeof(style_css)); });
  
  // js
  server.on("/script.js", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/javascript", script_js, sizeof(script_js)); });

  server.on("/Recording.js", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "text/javascript", recording_js, sizeof(recording_js)); });
  
  // Favicon
  server.on("/assets/myFavicon.png", []
            {
    server.sendHeader("content-encoding", "gzip");
    server.send_P(200, "img/png", myFavicon, sizeof(myFavicon)); });

  // friends pages
  server.on("/mom.html", []
            {
  server.sendHeader("content-encoding", "gzip");
  server.send_P(200, "text/html", mom_page, sizeof(mom_page)); });

  server.on("/dad.html", []
            {
  server.sendHeader("content-encoding", "gzip");
  server.send_P(200, "text/html", dad_page, sizeof(dad_page)); });

  server.on("/grandma.html", []
            {
  server.sendHeader("content-encoding", "gzip");
  server.send_P(200, "text/html", grandma_page, sizeof(grandma_page)); });

  server.on("/grandpa.html", []
            {
  server.sendHeader("content-encoding", "gzip");
  server.send_P(200, "text/html", grandpa_page, sizeof(grandpa_page)); });

  server.on("/jt.html", []
            {
  server.sendHeader("content-encoding", "gzip");
  server.send_P(200, "text/html", jt_page, sizeof(jt_page)); });

  // light corresponding LED when a friend reply digitally
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
  server.on("/lightdoudou", []
            { 
            server.send(200, "text/plain", "light Doudou"); 
            startLight[4] = true; });
  server.on("/lighttina", []
            { 
            server.send(200, "text/plain", "light Tina"); 
            startLight[5] = true; });
  server.on("/lightnadine", []
            { 
            server.send(200, "text/plain", "light Nadine"); 
            startLight[17] = true; });
  server.on("/lightjt", []
            { 
            server.send(200, "text/plain", "light Jt"); 
            startLight[19] = true; });

// connect client
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

void loop()
{
  server.handleClient();
  for (int i = 0; i < 20; i++)
  {
    if (startLight[i] == true)
    {
      fill_solid(LEDBall + i, 1, CRGB::OrangeRed);
      FastLED.show();
    }
    else
    {
      fill_solid(LEDBall + i, 1, CRGB::Black);
      FastLED.show();
    }
    if (colorLight[i] == true)
    {
      fill_solid(LEDBall + i, 1, CRGB::OrangeRed);
      FastLED.show();
      delay(1000);
      fill_solid(LEDBall + i, 1, CRGB::Black);
      FastLED.show();
      delay(1000);
    }
    else
    {
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