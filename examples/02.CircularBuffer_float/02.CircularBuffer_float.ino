#include <BlynkGO_CircularBuffer.h>

template<>
void BlynkGO_CircularBuffer<float>::display() const
{
  for(int i = 0; i < _count; ++i) {
    Serial.printf("%f ", buffer[i]);
  }
  Serial.println();
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  BlynkGO_CircularBuffer<float> cb(10);  // สร้างบัฟเฟอร์ที่มีขนาดสูงสุด 10 สำหรับ float

  // เพิ่มข้อมูลเข้าไปในบัฟเฟอร์
  for(float f = 1.1; f <= 15.1; f += 1.0) {
    cb.insert(f);
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
