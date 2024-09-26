#ifndef _PGMTools_h
#define _PGMTools_h

#ifdef __AVR__

#include <avr/pgmspace.h>

#else

#include <pgmspace.h>

#endif

template <typename T>
class PGMData {
protected:
    T *data = nullptr;
    
public:

    PGMData(const T &data) {
        this->data = (T*)&data;
    }
    
    operator const T() const {
        switch (sizeof(T)) {
            case 1: return (const T)pgm_read_byte(data);
            case 2: return (const T)pgm_read_word(data);
            case 4: return (const T)pgm_read_dword(data);
            
            default: 
            break;
        }
        return (const T) 0;
    }
};

template <>
class PGMData<double> {
protected:
    double *data = nullptr;
    
public:

    PGMData(const double &data) {
        this->data = (double*)&data;
    }
 
    operator const double() const { return (const double)pgm_read_float(data);   }

};

template <>
class PGMData<float> {
protected:
    float *data = nullptr;
    
public:

    PGMData(const float &data) {
        this->data = (float*)&data;
    }

    operator const float() const { return (const float)pgm_read_float(data);   }

};



template <typename T, uint32_t sizeArr>
class PGMArray {
protected:
    T *data = nullptr;
    
public:

    PGMArray(const T *data) {
        this->data = (T*)data;
    }
    
    const T operator[](uint32_t index) const {
        index = constrain(index, 0, sizeArr - 1);
        switch (sizeof(T)) {
            case 1: return (const T)pgm_read_byte(&data[index]);
            case 2: return (const T)pgm_read_word(&data[index]);
            case 4: return (const T)pgm_read_dword(&data[index]);
            
            default: 
            break;
        }
        return (const T) 0;
    }
    
    uint32_t size() const { return sizeArr; }
};

template <uint32_t sizeArr>
class PGMArray<double, sizeArr> {
public: 
    const double operator[](uint32_t index) const { index = constrain(index, 0, sizeArr - 1);  return (const double)pgm_read_float(&(this->data[index]));   }

};

template <uint32_t sizeArr>
class PGMArray<float, sizeArr> {
public: 
    const float operator[](uint32_t index) const { index = constrain(index, 0, sizeArr - 1);  return (const float)pgm_read_float(&(this->data[index]));   }

};

#endif