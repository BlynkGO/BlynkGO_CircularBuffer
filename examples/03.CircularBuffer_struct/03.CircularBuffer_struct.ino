#include <BlynkGO_CircularBuffer.h>

struct Data {
  int id;
  float value;
};

void printData(const Data & data)
{
  Serial.print("ID: ");
  Serial.print(data.id);
  Serial.print(", Value: ");
  Serial.println(data.value);
}

template<>
void BlynkGO_CircularBuffer<Data>::display() const
{
  for(int i = 0; i < _count; ++i) {
    printData(buffer[(_cur_id + i) % _maxSize]);
  }
}

void setup()
{
  Serial.begin(115200);  // เริ่มต้นการสื่อสาร Serial
  BlynkGO_CircularBuffer<Data> cb(5);  // สร้างบัฟเฟอร์ที่มีขนาดสูงสุด 5 สำหรับ struct Data

  // เพิ่มข้อมูลเข้าไปในบัฟเฟอร์
  for(int i = 1; i <= 7; ++i) {
    cb.insert({i, i * 1.5});
    cb.display();
  }

  // แสดงข้อมูลทั้งหมดในบัฟเฟอร์
  Serial.print("Current buffer content:\n");
  cb.display();

  // การเข้าถึงข้อมูลในบัฟเฟอร์ผ่านโอเปอเรเตอร์ []
  Data d = cb[0];
  Serial.print("Accessing buffer at index 0: ");
  printData(d);

  // แก้ไขข้อมูลในบัฟเฟอร์ผ่านโอเปอเรเตอร์ []
  cb[0] = {99, 99.9};
  Serial.print("Modified buffer content:\n");
  cb.display();
}

void loop()
{

}