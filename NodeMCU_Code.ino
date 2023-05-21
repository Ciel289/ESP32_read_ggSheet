// Uncomment if use ESP 32
#include <WiFi.h> 
#include <HTTPClient.h>

//Things to change
const char * ssid = "";
const char * password = "";
String GOOGLE_SCRIPT_ID = "";
// ...../exec?read=A3
const char* host    = "script.google.com"; // only google.com not https://google.com
const int httpPort  = 443; // 80 is for HTTP / 443 is

String read_sheet(String values){
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?read=" + values;
  //   Serial.print(url);

  http.begin(url.c_str()); //Specify the URL and certificate
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  Serial.print("Making a request: ");

  int httpCode = http.GET();  // this will Delay for 4-6 Seccond
  String payload;
  if (httpCode > 0) { //Check for the returning code
    Serial.println(httpCode); // 404-Not Found, 200-Nomally
    payload = http.getString();
    
//    Serial.println(payload);  // Data
  }
  else {
    Serial.println("Error on HTTP request");
    http.end();
    return ("ERROR: " + String(httpCode));
  }
  http.end();
  return payload;
}


void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Started");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Ready to go");
}

void loop() {
  String s = read_sheet("A3");  // Read from A3 // Chang it if want to read from other values
  Serial.println(s);
  delay(2000);
}
