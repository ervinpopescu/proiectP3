#include <SoftwareSerial.h>
#include <TinyGPS.h>
float lat = 28.5458, lon = 77.1703;
String latitude, longitude;
SoftwareSerial gpsSerial(4, 3); // rx,tx
TinyGPS gps;                    // create gps object

void setup()
{
    Serial.begin(9600);
    gpsSerial.begin(9600); // connect gps sensor
    Serial.print("AT+CMGF=1\r\n");
    delay(100);
    Serial.print("AT+CNMI=1,2,0,0,0\r\n");
    delay(100);
    Serial.print("AT+W\r\n");
    delay(100);
}

void loop()
{
    while (gpsSerial.available())
    {                                     // check for gps data
        if (gps.encode(gpsSerial.read())) // encode gps data
        {
            gps.f_get_position(&lat, &lon);
            if (Serial.available())
            {
                String c = Serial.readString();
                c.trim();
                if (c.indexOf("GPS") >= 0)
                {
                    Serial.print("AT+CMGS=" xxxxxxxr "\r"); // phone number
                    delay(50);
                    latitude = String(lat, 6);
                    delay(50);
                    longitude = String(lon, 6);
                    delay(50);
                    Serial.print("http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=");
                    Serial.print(latitude + "," + longitude);
                    Serial.write(0x1A);
                    delay(2000);
                    Serial.print("AT+CMGD=1\r\n");
                    delay(1000);
                    Serial.print("AT+CMGD=2\r\n");
                    delay(1000);
                    Serial.print("AT+CMGD=3\r\n");
                    delay(1000);
                    Serial.print("AT+CMGD=4\r\n");
                    delay(1000);
                    Serial.flush();
                    delay(1000);
                    gpsSerial.flush();
                    delay(1000);
                }
            }
        }
    }
}