#include <BlynkGO_CircularBuffer.h>

void setup()
{
  Serial.begin(115200);
  Serial.println();

  BlynkGO_CircularBuffer<int> cbuf(10);  // สร้างบัฟเฟอร์ที่มีขนาดสูงสุด 10

  // เพิ่มข้อมูลเข้าไปในบัฟเฟอร์
  for(int i = 1; i <= 15; ++i) {
    cbuf.insert(i);
    cbuf.display();
  }

  // แสดงข้อมูลทั้งหมดในบัฟเฟอร์
  Serial.print("Current buffer content: ");
  cbuf.display();

  // การเข้าถึงข้อมูลในบัฟเฟอร์ผ่านโอเปอเรเตอร์ []
  Serial.print("Accessing buffer at index 0: ");
  Serial.println(cbuf[0]);
  Serial.print("Accessing buffer at index 5: ");
  Serial.println(cbuf[5]);

  // แก้ไขข้อมูลในบัฟเฟอร์ผ่านโอเปอเรเตอร์ []
  cbuf[0] = 100;
  Serial.print("Modified buffer content: ");
  cbuf.display();

}

void loop()
{

}
