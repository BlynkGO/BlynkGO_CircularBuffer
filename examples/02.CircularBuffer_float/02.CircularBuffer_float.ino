#include <BlynkGO_CircularBuffer.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();

  BlynkGO_CircularBuffer<float> cb(10);  // สร้างบัฟเฟอร์ที่มีขนาดสูงสุด 10 สำหรับ float

  // เพิ่มข้อมูลเข้าไปในบัฟเฟอร์
  for(float i = 1.1; i <= 15.1; i += 1.0) {
    cb.insert(i);
    cb.display();
  }

  // แสดงข้อมูลทั้งหมดในบัฟเฟอร์
  Serial.print("Current buffer content: ");
  cb.display();

  // การเข้าถึงข้อมูลในบัฟเฟอร์ผ่านโอเปอเรเตอร์ []
  Serial.print("Accessing buffer at index 0: ");
  Serial.println(cb[0]);
  Serial.print("Accessing buffer at index 5: ");
  Serial.println(cb[5]);

  // แก้ไขข้อมูลในบัฟเฟอร์ผ่านโอเปอเรเตอร์ []
  cb[0] = 100.5;
  Serial.print("Modified buffer content: ");
  cb.display();
}

void loop()
{

}