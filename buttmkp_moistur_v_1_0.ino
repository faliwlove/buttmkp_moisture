#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//masukan username dan password agar andika_doorlock dapat terhubung ke server
const char* ssid = "EduFarm RR#1"; // masukan Nama Wifi nya
const char* password = "rasana#1"; // isi password dari wifi

const int moist_pin = A0;
int moist_value_map = 0;
int moist_value = 0;
String moist_value_string;
String postData;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

  WiFi.begin(ssid, password); //--> menghubungkan ke router wifi
  Serial.println("");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.print("Sudah Terhubung ke : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  moist_value = analogRead(moist_pin);
  moist_value_map = map(moist_value, 775, 386, 0, 100);
  Serial.print("moist_value = ");
  Serial.println(moist_value_map);
  moist_value_string = String(moist_value_map);
  //program koneksi ke server
  WiFiClient client;
  HTTPClient http;
  postData = "a=" + moist_value_string;
  Serial.println(postData);
  http.begin(client, "http://e-farmingcorpora.com/rasana/getdata.php");
  //http.begin("http://192.168.137.1/rasana/getdata.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);
  String payload = http.getString();
  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
  http.end();  //Close connection
  // read the analog in value:
  delay(1000);
}
