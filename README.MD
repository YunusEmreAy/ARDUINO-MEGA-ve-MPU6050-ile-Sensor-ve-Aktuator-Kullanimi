# IoT Projesi - ARDUINO MEGA ve MPU6050 ile Sensör ve Aktüatör Kullanımı

Bu proje, ARDUINO MEGA geliştirme kartı, MPU6050 ivmeölçer ve jiroskop sensörü, SSD1306 OLED ekran, microSD kart modülü ve iki adet servo motor kullanılarak tasarlanmış bir Nesnelerin İnterneti (IoT) uygulamasıdır. Projenin amacı, MPU6050 sensörü ile ölçülen ivme, yön ve sıcaklık verilerini elde edip, bu verileri hem OLED ekrana yazdırmak hem de microSD karta kaydetmektir. Ek olarak, servo motorlar jiroskop değerlerine göre kontrol edilir.

## Kullanılan Bileşenler
- **ARDUINO MEGA**: Projenin merkezi kontrol birimi.
- **MPU6050**: İvme, jiroskop ve sıcaklık ölçümleri için kullanılan bir sensör.
- **SSD1306 OLED Ekran**: Ölçüm verilerinin görselleştirilmesi için kullanılır.
- **microSD Kart Modülü**: Ölçüm verilerinin kaydedilmesi için kullanılır.
- **Servo Motorlar**: Jiroskop verilerine göre konumlandırılan iki adet servo motor.
- **Full BreadBoard**: Devre elemanlarının bağlanması için kullanılan bağlantı kartı.

## Proje Fonksiyonları
1. **Sensör Ölçümleri**: MPU6050 sensöründen ivme, jiroskop ve sıcaklık verileri okunur.
2. **Veri Görselleştirme**: SSD1306 OLED ekranda, ivmeölçer (m/s²), jiroskop (rps) ve sıcaklık (°C) değerleri gösterilir.
3. **Veri Kaydetme**: Ölçülen veriler, microSD karta "mpu6050.txt" dosyasına kaydedilir. Kaydedilen veriler terminalde de gösterilir.
4. **Servo Motor Kontrolü**: İlk servo motor, jiroskopun x eksenine göre, ikinci servo motor ise y eksenine göre konumlandırılır.
5. **Terminal Çıktısı**: Veriler terminal ekranına, microSD'ye yazılan ölçümlerle birlikte çıktılanır.

## Devre Bağlantıları
- **MPU6050 Sensörü**:
  - VCC: 5V
  - GND: GND
  - SCL: ARDUINO MEGA'nın SCL pinine
  - SDA: ARDUINO MEGA'nın SDA pinine
- **SSD1306 OLED Ekran**:
  - VCC: 5V
  - GND: GND
  - SCL: ARDUINO MEGA'nın SCL pinine
  - SDA: ARDUINO MEGA'nın SDA pinine
- **microSD Kart Modülü**:
  - CS: Pin 53
  - DI: Pin 51
  - SCK: Pin 52
  - DO: Pin 50
  - VCC: 5V
  - GND: GND
- **Servo Motorlar**:
  - Servo 1 PWM: Pin 8
  - Servo 2 PWM: Pin 9
  - Her iki motorun da VCC pinleri: 5V
  - Her iki motorun da GND pinleri: GND

## Gerekli Kütüphaneler
Aşağıdaki kütüphanelerin Arduino IDE'ye yüklü olması gerekmektedir:
- `Adafruit GFX Library`
- `Adafruit MPU6050`
- `Servo`
- `SD`
- `SdFat`

Kütüphaneler hakkında daha fazla bilgi için: [Wokwi Kütüphane Rehberi](https://docs.wokwi.com/guides/libraries).

## Kurulum Talimatları
1. Bu depoyu klonlayın ve Arduino IDE'yi açın.
2. Yukarıda belirtilen kütüphaneleri yükleyin.
3. `sketch.ino` dosyasını açın ve kodu ARDUINO MEGA'ya yükleyin.
4. **Wokwi Simülasyonu**: Bu projeyi Wokwi platformunda simüle etmek için [buraya tıklayın](https://wokwi.com/projects/398934849047279617).

## OLED ve microSD Gösterimleri
- **OLED Ekran**: İvme, jiroskop ve sıcaklık ölçümleri OLED ekranda aşağıdaki formatta gösterilecektir:
Accelerometer - m/s² 
-0.5, -0.2, 9.0 
Gyroscope - rps 
-1.13, -4.10, -0.4 
Temperature 
80.00 degC

- **microSD Kayıt Formatı**: Veriler "mpu6050.txt" dosyasına aynı formatta kaydedilir ve terminalde "SD karta yazılan ölçümler: " ifadesi ile gösterilir.

## Simülasyon ve Test
- Projenizi Wokwi üzerinde simüle edebilir ve devre elemanlarının doğru bağlandığından emin olabilirsiniz.
- Servo motorların MPU6050 jiroskop verilerine göre doğru hareket ettiğini kontrol edin.
- Ölçümlerinizin microSD karta doğru şekilde kaydedildiğini ve terminalde çıktılanmasını sağlayın.

## Notlar
- Kodda her satır için açıklayıcı yorumlar eklenmiştir. Kodu anlamak ve düzenlemek için bu yorumları takip edebilirsiniz.
- Tüm ölçümler için çevrim ve gerekli matematiksel işlemler kod içerisinde belirtilmiştir.
- Proje üzerinde çalışırken, verilerin doğru bir şekilde gösterildiğinden ve kaydedildiğinden emin olun.

## Referanslar
- [MPU6050 Sensör Dokümantasyonu](https://docs.wokwi.com/parts/wokwi-mpu6050)
- [Servo Motor Uygulama Rehberi](https://blog.wokwi.com/learn-servo-motor-using-wokwi-logic-analyzer)
- [microSD Kart Modülü Dokümantasyonu](https://docs.wokwi.com/parts/wokwi-microsd-card)
- [SSD1306 OLED Ekran Projesi](https://wokwi.com/projects/385987811439126529).
