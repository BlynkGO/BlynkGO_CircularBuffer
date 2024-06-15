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
    int _cur_id;                // ดัชนีเริ่มต้นของข้อมูลปัจจุบัน
    int _count;                // จำนวนของข้อมูลในบัฟเฟอร์

  public:
    // Constructor: กำหนดขนาดสูงสุดของบัฟเฟอร์
    BlynkGO_CircularBuffer(int size) : buffer(size), _maxSize(size), _cur_id(0), _count(0) {}

    // ฟังก์ชันสำหรับการเพิ่มข้อมูล
    // ฟังก์ชันสำหรับการเพิ่มข้อมูล
    void insert(const T& data) {
      buffer[(_cur_id + _count) % _maxSize] = data;  // วางข้อมูลในตำแหน่งที่คำนวณจาก _cur_id และ _count
      if (_count < _maxSize) {
        _count++;
      } else {
        _cur_id = (_cur_id + 1) % _maxSize;  // วนดัชนี _cur_id ไปเรื่อยๆ เมื่อบัฟเฟอร์เต็ม
      }
    }
    // ฟังก์ชันสำหรับการเข้าถึงข้อมูลในบัฟเฟอร์
    T get(int index) const
    {
      if(index >= _count || index < 0) {
        throw std::out_of_range("Index out of range");
      }
      return buffer[(_cur_id + index) % _maxSize];  // คำนวณดัชนีจริงในบัฟเฟอร์
    }

    // ฟังก์ชันโอเปอเรเตอร์สำหรับการเข้าถึงข้อมูลในบัฟเฟอร์
    inline T operator[](int index) const { return get(index); }

    // ฟังก์ชันโอเปอเรเตอร์สำหรับการเข้าถึงข้อมูลในบัฟเฟอร์ที่สามารถแก้ไขได้
    T& operator[](int index) {
      if (index >= _count || index < 0) {
        throw std::out_of_range("Index out of range");
      }
      return buffer[(_cur_id + index) % _maxSize];
    }

    // ฟังก์ชันสำหรับการแสดงข้อมูลทั้งหมดในบัฟเฟอร์
    void display() const
    {
      for(int i = 0; i < _count; ++i) {
        Serial.print(String(buffer[(_cur_id + i) % _maxSize])+ String((i<_count-1)? ", ": ""));
      }
      Serial.println();
    }

    // ฟังก์ชันสำหรับการตรวจสอบว่าบัฟเฟอร์เต็มหรือไม่
    inline bool isFull() const  { return _count == _maxSize;  }

    // ฟังก์ชันสำหรับการตรวจสอบว่าบัฟเฟอร์ว่างหรือไม่
    inline bool isEmpty() const { return this->_count == 0;   }
    inline int cur_id() const   { return this->_cur_id;       }
};


#endif //__BLYNKGO_CIRCULARBUFFER_H__