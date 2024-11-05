#include <Adafruit_MPU6050.h> //Bu kütüphane, MPU6050 sensörünü kullanmak için gerekli olan fonksiyonları ve sınıfları sağlar.
#include <Adafruit_Sensor.h> //Bu kütüphane, MPU6050 sensörünü kullanmak için gerekli olan fonksiyonları ve sınıfları sağlar.
#include <Wire.h> //Bu kütüphane, I2C haberleşme işlemleri için kullanılmaktadır.

#include <Adafruit_GFX.h> //SSD1306 OLED ekranına bilgi yazdırabilmek için bu kütüphaneden yararlanılmaktadır.
#include <Adafruit_SSD1306.h> //SSD1306 OLED ekranına bilgi yazdırabilmek için bu kütüphaneden yararlanılmaktadır.

#include <Servo.h> //Servo motor kontrollerini gerçekleştirebilmek için, bu kütüphane kullanılmaktadır.

#include <SD.h> // SD karta erişim sağlamak için kullanıldı.

Adafruit_MPU6050 mpu; // "mpu" adında bir MPU6050 nesnesi oluşturur.

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Oled nesnemizi oluşturuduk.

Servo myservo1, myservo2; // Serfo motor değişkenleri oluşturulmaktadır.
int Minmyservo1 = 0, Maxmyservo1 = 180; // Servo motor minimum ve maximum posizyonu belirlenmektedir
int Minmyservo2 = 0, Maxmyservo2 = 180; // Servo motor minimum ve maximum posizyonu belirlenmektedir

#define CS_PIN 53 // SD kart ile iletişim kurulurken hangi pine bağlandığını belirtmek için kullanıldı.

File myFile; // myFile nesnesi olusturulmaktadir.


sensors_event_t accelerometer_event, gyroscope_event, temperature_event; // Sensör verilerini tutmak için "event" isminde bir nesne oluşturur.


void setup(void) {
  Serial.begin(115200);

  while (!mpu.begin()) { // mpu.begin() fonksiyonu ile MPU6050 sensörünün başlatılmaya çalışıldığı bir döngü vardır. Eğer sensör bağlanmamışsa, her saniye bir hata mesajı yazdırılır.
    Serial.println("MPU6050 not connected!");
    delay(1000);
  }
  Serial.println("MPU6050 ready!"); // Sensör başarılı bir şekilde başlatıldığında "MPU6050 ready!" mesajı yazdırılır.
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // OLED ekranı başlatır. 0x3C, OLED ekranın I2C adresidir.
    Serial.println(F("SSD1306 allocation failed"));
    while (1) {
      delay(10);
    }
  }


  display.display(); // Ekranı başlatır ve gösterir.
  delay(2000); 
  display.clearDisplay(); // OLED ekranı temizlenir
  display.setTextSize(1); // Normal 1:1 piksel ölçeği ile yazı boyutunu ayarlar
  display.setTextColor(SSD1306_WHITE); // Ekrana beyaz renkte yazı yazılır.
  display.setCursor(0, 0); // Cursor'u OLED ekranın 0.satir - 0.stun 'una tasir.

  myservo1.attach(9); //Pin 9 daki servoyu myservo1 nesnesine bağlar.
  myservo2.attach(8); //Pin 8 daki servoyu myservo2 nesnesine bağlar.


  while (!SD.begin(CS_PIN)) {
  Serial.println("SD initialization failed.");
  }

  myFile = SD.open("mpu6050.txt", FILE_WRITE); // Dosyayı yazma modunda aç
  if (myFile) {
    Serial.println("Dosya oluşturuldu.");
    myFile.close(); // Dosyayı kapat
  } else {
    Serial.println("Dosya oluşturulamadı.");
  }


  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // İvmeölçer için aralık belirlenir.
  mpu.setGyroRange(MPU6050_RANGE_500_DEG); // Jiroskop için aralık belirlenir.
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ); // Filtre bant için aralık belirlenir.


}

void loop() {
  mpu.getAccelerometerSensor()->getEvent(&accelerometer_event); // Sensörden ivme verileri alınır ve accelerometer_event nesnesine kaydedilir.
  mpu.getGyroSensor()->getEvent(&gyroscope_event); // Sensörden yön verileri alınır ve gyroscope_event nesnesine kaydedilir.
  mpu.getTemperatureSensor()->getEvent(&temperature_event); // Sensörden sıcaklık verileri alınır ve temperature_event nesnesine kaydedilir.

  Terminale_yaz();
  OLED_ekrana_yaz();
  Dosyaya_yaz();


  myservo1.write(map(gyroscope_event.gyro.x, -4.3, +4.3, Minmyservo1, Maxmyservo1)); // Pin 9'a bağlı olan servo "gyroscope_event.gyro.x" değişkeninin değerine göre hareket edecektir.
  myservo2.write(map(gyroscope_event.gyro.y, -4.3, +4.3, Minmyservo2, Maxmyservo2)); // Pin 8'a bağlı olan servo "gyroscope_event.gyro.y" değişkeninin değerine göre hareket edecektir.

}

void Terminale_yaz() // Serial.print() ile terminale yazma işlemi gerçekleştirilir.
{
  Serial.println("SD karta yazılan ölçümler:\n");

  Serial.println("Accelerometer – m/s^2");
  Serial.print(accelerometer_event.acceleration.x);
  Serial.print(", ");
  Serial.print(accelerometer_event.acceleration.y);
  Serial.print(", ");
  Serial.println(accelerometer_event.acceleration.z);

  Serial.println("Gyroscope – rps");
  Serial.print(gyroscope_event.gyro.x);
  Serial.print(", ");
  Serial.print(gyroscope_event.gyro.y);
  Serial.print(", ");
  Serial.println(gyroscope_event.gyro.z);

  Serial.println("Temperature");
  Serial.print(temperature_event.temperature);
  Serial.println(" degC");

}

void OLED_ekrana_yaz() // display.print() ile Oled ekrana yazma işlemi gerçekleştirilir.
{
  display.clearDisplay(); // OLED ekranı temizler.
  display.setTextSize(1); // Metnin boyutunu belirledik
  display.setTextColor(WHITE); // Metnin rengini belirledik.
  display.setCursor(0, 0); // Cursor'u OLED ekranın 0.satir - 0.stun 'una tasir.


  display.println("Accelerometer - m/s^2");
  display.print(accelerometer_event.acceleration.x);
  display.print(", ");
  display.print(accelerometer_event.acceleration.y);
  display.print(", ");
  display.println(accelerometer_event.acceleration.z);

  display.println("Gyroscope - rps");
  display.print(gyroscope_event.gyro.x);
  display.print(", ");
  display.print(gyroscope_event.gyro.y);
  display.print(", ");
  display.println(gyroscope_event.gyro.z);

  display.println("Temperature");
  display.print(temperature_event.temperature);
  display.println(" degC");
  display.display();
  
}

void Dosyaya_yaz() // myFile.print() ile "mpu6050.txt" dosyasına yazma işlemi gerçekleştirilir.
{
  myFile = SD.open("mpu6050.txt", FILE_WRITE); // Dosyayı yazma modunda aç

  myFile.println("SD karta yazılan ölçümler:\n");

  myFile.println("Accelerometer – m/s^2");
  myFile.print(accelerometer_event.acceleration.x);
  myFile.print(", ");
  myFile.print(accelerometer_event.acceleration.y);
  myFile.print(", ");
  myFile.println(accelerometer_event.acceleration.z);

  myFile.println("Gyroscope – rps");
  myFile.print(gyroscope_event.gyro.x);
  myFile.print(", ");
  myFile.print(gyroscope_event.gyro.y);
  myFile.print(", ");
  myFile.println(gyroscope_event.gyro.z);

  myFile.println("Temperature");
  myFile.print(temperature_event.temperature);
  myFile.println(" degC");

  myFile.close(); // Dosyayı kapat

}