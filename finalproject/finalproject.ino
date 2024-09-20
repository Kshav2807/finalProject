
#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
//#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7920_128X64_1_HW_SPI u8g2(U8G2_R0, /* CS=*/ 15, /* reset=*/ 16); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

void printDetail(uint8_t type, int value);
//LiquidCrystal_I2C //lcd(0x3f, 16, 2);
const char* ssid = "realme";
const char* password = "12345678";
ESP8266WebServer server(80);
String page = "";
char input[12];
int count = 0;
int a;
int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
int c1 = 35, c2 = 25, c3 = 0, c4 = 0;

double total = 0;
int count_prod = 0;

int led1 = D5;
int led2 = D7;
int buzzer = D0;

void setup()
{
    u8g2.begin();
      u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24,"   WELCOME TO ");
    u8g2.drawStr(0,54,"SMART TROLLY!!  ");
  } while ( u8g2.nextPage() );
  delay(1000);
    
  Serial.begin(115200);
  pinMode(D4, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Wire.begin(D2, D1);

  ////lcd.begin();
  

    
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    u8g2.firstPage();
  
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24," wifi connecting.... ");
    //u8g2.drawStr(0,54,"SMART TROLLY!!  ");
  
    
    Serial.print("WiFi Connecting...  ");
     delay(1000);
  }
  Serial.print(WiFi.localIP());
   u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24," wifi connected ");
    //u8g2.drawStr(0,54,"SMART TROLLY!!  ");
  } while ( u8g2.nextPage() );
  delay(2000);
  Serial.print("WiFi Connected");
  //lcd.setCursor(0, 1);
  //lcd.print(WiFi.localIP());
 // delay(2000);
   u8g2.begin();
      u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.drawStr(0,24,"plz scan");
  } while ( u8g2.nextPage() );
  delay(1000);
  server.on("/", []()
  {
    page = "<html><head><title>Smart Shopping Cart</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color: #4444db ;color: black;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Welcome To Smart Cart Trolly</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>Suger</td><td>" + String(p1) + "</td><td>" + String(c1) + "</td></tr>";
    page += "<tr><td>Milk</td><td>" + String(p2) + "</td><td>" + String(c2) + "</td></tr><tr><td>Biscuits</td><td>" + String(p3) + "</td><td>" + String(c3) + "</td>";
    page += "</tr><tr><td>Dairy Mlik</td><td>" + String(p4) + "</td><td>" + String(c4) + "</td></tr><tr><th>Grand Total</th><th>" + String(count_prod) + "</th><th>" + String(total) + "</th>";
    page += "</tr></table><br><input type=\"button\" name=\"Pay Online Now\" value=\"Pay Online Now\" style=\"width: 200px;height: 50px\"></center></body></html>";
    page += "<meta http-equiv=\"refresh\" content=\"2\">";
    server.send(200, "text/html", page);
  });
  server.begin();
 
}
void loop() {
  u8g2.firstPage();
  digitalWrite(buzzer, LOW);
//    char m_str[5];
//   strcpy(m_str, u8x8_u8toa(total, 3));
  int a = digitalRead(D4);
  if (Serial.available()) {
    count = 0;
    while (Serial.available() && count < 12) {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    if (count == 12) {
      if ((strncmp(input, "31002B8827B5", 12) == 0) && (a == 1)) {

        total = total + 35.00;
        count_prod++;
         char m_str[5];
   strcpy(m_str, u8x8_u8toa(total, 3));
        u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24," Sugar Added ");
    u8g2.drawStr(0,34,"Price: 35.00  ");
    u8g2.drawStr(0,54,"Total Bill:" );
        u8g2.drawStr(80,54, m_str);


  } while ( u8g2.nextPage() );
  delay(1000);
        p1++;
        digitalWrite(led1, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(1000);
//        total = total + 35.00;
//        count_prod++;
        digitalWrite(led1, LOW);
        digitalWrite(buzzer, LOW);
        
        //lcd.clear();
        //lcd.setCursor(0, 0);
        //lcd.print("Total Price:-");
        //lcd.setCursor(0, 1);
        //lcd.print(total);

      } else if ((strncmp(input, "31002B8827B5", 12) == 0) && (a == 0)) {
        if (p1 > 0) {
           
          total = total - 35.00;
          count_prod--;
           char m_str[5];
   strcpy(m_str, u8x8_u8toa(total, 3));
         do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24," Sugar removed ");
    u8g2.drawStr(0,34,"Price: -35.00  ");
     u8g2.drawStr(0,54,"Total Bill:" );
        u8g2.drawStr(80,54, m_str);
  } while ( u8g2.nextPage() );
  delay(1000);
          digitalWrite(led2, HIGH);
          digitalWrite(buzzer, HIGH);
          delay(2000);
          p1--;
          
          digitalWrite(led2, LOW);
          digitalWrite(buzzer, LOW);
          //lcd.clear();
          //lcd.setCursor(0, 0);
          //lcd.print("Total Price:-");
          //lcd.setCursor(0, 1);
          //lcd.print(total);
        }
      }
        else if ((strncmp(input, "310028C6E738", 12) == 0) && (a == 1)) {

        total = total + 25.00;
        count_prod++;
        char m_str[5];
        strcpy(m_str, u8x8_u8toa(total, 3));
        do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24," Milk Added ");
    u8g2.drawStr(0,34,"Price: 25.00  ");
    u8g2.drawStr(0,54,"Total Bill:" );
        u8g2.drawStr(80,54, m_str);


  } while ( u8g2.nextPage() );
  delay(1000);
        p2++;
        digitalWrite(led1, HIGH);
        digitalWrite(buzzer, HIGH);
        delay(1000);
//        total = total + 25.00;
//        count_prod++;
        digitalWrite(led1, LOW);
        digitalWrite(buzzer, LOW);
        //lcd.clear();
        //lcd.setCursor(0, 0);
        //lcd.print("Total Price:-");
        //lcd.setCursor(0, 1);
        //lcd.print(total);

      }
      else if ((strncmp(input, "310028C6E738", 12) == 0) && (a == 0)) {
        
        if (p2 > 0) {
            total = total - 25.00;
          count_prod--;
           char m_str[5];
   strcpy(m_str, u8x8_u8toa(total, 3));
           do {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,24," Milk Removed ");
    u8g2.drawStr(0,34,"Price: -25.00  ");
    u8g2.drawStr(0,54,"Total Bill:" );
        u8g2.drawStr(80,54, m_str);


  } while ( u8g2.nextPage() );
  delay(1000);
          digitalWrite(led2, HIGH);
          digitalWrite(buzzer, HIGH);
          delay(2000);
          p2--;
//          total = total - 25.00;
//          count_prod--;
          digitalWrite(led2, LOW);
          digitalWrite(buzzer, LOW);
          //lcd.clear();
          //lcd.setCursor(0, 0);
          //lcd.print("Total Price:-");
          //lcd.setCursor(0, 1);
          //lcd.print(total);
        }
      }
        else {
          //lcd.clear();
          //lcd.setCursor(0, 0);
          //lcd.print(" PLZ SCAN ITEMS");
          //lcd.setCursor(0, 1);
          //lcd.print("   TO CART");
        }
      }
      else {
        //lcd.clear();
        //lcd.setCursor(0, 0);
        //lcd.print(" PLZ SCAN ITEMS");
        //lcd.setCursor(0, 1);
        //lcd.print("   TO CART");
      }
    } 
    else {
      //lcd.clear();
      //lcd.setCursor(0, 0);
      //lcd.print(" PLZ SCAN ITEMS");
      //lcd.setCursor(0, 1);
      //lcd.print("   TO CART");
    }
    server.handleClient();
  }
 
