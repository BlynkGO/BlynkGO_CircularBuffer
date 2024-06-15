#ifndef __BLYNKGO_CIRCULARBUFFER_H__
#define __BLYNKGO_CIRCULARBUFFER_H__


#include <Arduino.h>
#include <vector>

template <typename T=int>
class BlynkGO_CircularBuffer
{
  private:
    std::vector<T> buffer;  // บัฟเฟอร์เก็บข้อมูล
    int _maxSize;              // ขนาดสูงสุดของบัฟเฟอร์
    uint16_t _cur_id;          // ดัชนีเริ่มต้นของข้อมูลปัจจุบัน
    uint16_t _count;           // จำนวนของข้อมูลในบัฟเฟอร์

  public:
    // Constructor: กำหนดขนาดสูงสุดของบัฟเฟอร์
    BlynkGO_CircularBuffer(int size) : buffer(size), _maxSize(size), _cur_id(0), _count(0) {}

    void insert(const T& data) {
      // Serial.println(data,5);
      if (_count < _maxSize) {
        if(_count > 0) _cur_id = (_cur_id + 1) % _maxSize; // เพิ่ม _cur_id ตามลำดับและวนกลับเมื่อถึงขีดจำกัดของ buffer
        buffer[_cur_id] = data;
        _count++;
      } else {
        _cur_id = (_cur_id + 1) % _maxSize; // เพิ่ม _cur_id ตามลำดับและวนกลับเมื่อถึงขีดจำกัดของ buffer
        buffer[_cur_id] = data;  // เพิ่มข้อมูลใน vector ในตำแหน่ง _cur_id (ทับข้อมูลเก่า)
      }
    }

    // ฟังก์ชันสำหรับการเข้าถึงข้อมูลในบัฟเฟอร์
    T get(int index) const
    {
      if(index >= _count || index < 0) {
        throw std::out_of_range("Index out of range");
      }
      return buffer[index % _maxSize];  // คำนวณดัชนีจริงในบัฟเฟอร์
    }

    // ฟังก์ชันโอเปอเรเตอร์สำหรับการเข้าถึงข้อมูลในบัฟเฟอร์
    inline T operator[](int index) const { return get(index); }

    // ฟังก์ชันโอเปอเรเตอร์สำหรับการเข้าถึงข้อมูลในบัฟเฟอร์ที่สามารถแก้ไขได้
    T& operator[](int index) {
      if (index >= _count || index < 0) {
        throw std::out_of_range("Index out of range");
      }
      return buffer[ index % _maxSize];
    }

    // ฟังก์ชันสำหรับการแสดงข้อมูลทั้งหมดในบัฟเฟอร์
    void display() const
    {
      for(int i = 0; i < _count; ++i) {
        Serial.print(String(buffer[i % _maxSize])+ String((i<_count-1)? ", ": ""));
      }
      Serial.println();
    }

    // ฟังก์ชันสำหรับการตรวจสอบว่าบัฟเฟอร์เต็มหรือไม่
    inline bool isFull() const        { return _count == _maxSize;  }

    // ฟังก์ชันสำหรับการตรวจสอบว่าบัฟเฟอร์ว่างหรือไม่
    inline bool isEmpty() const       { return this->_count == 0;   }
    inline uint16_t cur_id() const    { return this->_cur_id;       }
    void cur_id(uint16_t id) {
      if (id > _count) id = _count-1;
      this->_cur_id = id;
    }

    // ฟังก์ชันสำหรับการรีเซ็ตบัฟเฟอร์
    void reset() {
        _cur_id = 0;
        _count = 0;
        std::fill(buffer.begin(), buffer.end(), T{}); // รีเซ็ตข้อมูลในบัฟเฟอร์ด้วยค่าเริ่มต้นของ T
    }
};


#endif //__BLYNKGO_CIRCULARBUFFER_H__