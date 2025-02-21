#define BLYNK_TEMPLATE_ID "TMPL3Hvs2XNqy"
#define BLYNK_TEMPLATE_NAME "test"
#define BLYNK_AUTH_TOKEN "Qbk_g7s2gi5yFgsixW55RO614iFNIVPV"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include<Servo.h>
WiFiClient client;

String MakerIFTTT_Key ;
;String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;
int pin= D5;
int c=1;
Servo servo;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "nive";
char pass[] = "123456789"; 

BLYNK_WRITE(V0)
{
  int s0 = param.asInt(); 
  servo.write(s0);
  Blynk.virtualWrite(V1, s0);
}
void setup()
{
   Serial.begin(9600);
  servo.attach(D0);
  Blynk.begin(auth, ssid, pass);//Splash screen delay
  delay(2000);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  delay(1000);
  Serial.println("START");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(1000);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));
  while(1)
  {
    delay(1000);
    Serial.println(digitalRead(pin));
    Blynk.run();
//    pinMode(pin, INPUT);
  if (client.connect("maker.ifttt.com",80) && (digitalRead(pin)==HIGH))
  {
    Serial.println("The no of sendinng sms");
    MakerIFTTT_Key ="f5kTUqqBYUe8n0n8Kj2HW-vVtuevyfJdLptDkp5nFfH";
    MakerIFTTT_Event ="sms";
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "919749259819");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "hello world!");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, "");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);
    delay(3000);
    Serial.println(c);
    c++;
  }
 }
}
void loop()
{
Blynk.run();
}
