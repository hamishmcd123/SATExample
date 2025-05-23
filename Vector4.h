#pragma once
#include <string>
#define Epsilon 0.00001
namespace MathClasses
{
    struct Vector4
    {
        float x;
        float y;
        float z;
        float w;
        
        Vector4() {
            x = 0;
            y = 0;
            z = 0;
            w = 0;
        }

        Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
        
        const float Magnitude() const {
            return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
		}

        const Vector4 Normalised() const {
            const float magnitude = sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w,2));
            if (magnitude == 0.0f) {
                return Vector4();
            }
            return Vector4(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
        }

        Vector4& Normalise() {
            const float magnitude = sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w,2));
            if (magnitude == 0) {
                x = 0; 
                y = 0;
                z = 0;
                w = 0;
                return *this;
            }
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            w /= magnitude;
        }

        const float Dot(const Vector4& other) const{
            return x * other.x + y * other.y + z * other.z + w * other.w;
        }

        const Vector4 Cross(const Vector4& other) const {
		return Vector4(y * other.z - z * other.y, -(x * other.z - z * other.x), x * other.y - y * other.x, 0);
        }

        const Vector4 operator+(const Vector4& other) const {
            return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        const Vector4 operator-(const Vector4& other) const {
            return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        friend const Vector4 operator*(const Vector4& vec4, const float scalar); 
        friend const Vector4 operator*(const float scalar, const Vector4& vec4); 
        
        const Vector4 operator/(const float scalar) const {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }

        bool operator==(const Vector4& other) const {
            return (abs(x - other.x) < Epsilon && 
                    abs(y - other.y) < Epsilon &&
                    abs(z - other.z) < Epsilon &&
                    abs(w - other.w) < Epsilon);
        }

        bool operator!=(const Vector4& other) const {
		    if (x == other.x && y == other.y && z == other.z && w == other.w) {
                return false;
            }
            else {
                return true;
            }
        }

        const float& operator[](const int index) const {
            if (index > 3 || index < 0) {
                throw std::out_of_range("Index out of range! DO BETTER");
            }
            switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            }
        }

        float& operator[](const int index) {
            if (index > 3 || index < 0) {
                throw std::out_of_range("Index out of range! DO BETTER");
            }
            switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            case 3:
                return w;
            }
        }

        explicit operator const float* () const {
            return &x;
        }

        explicit operator float* () {
            return &x;
        }

        std::string ToString() const { return std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z) + " , " + std::to_string(w); }

 	};

  inline const Vector4 operator*(const Vector4& vec4, const float scalar) {
        return Vector4(vec4.x * scalar, vec4.y * scalar, vec4.z * scalar, vec4.w * scalar);
    }
 
 inline const Vector4 operator*(const float scalar, const Vector4& vec4) {
        return Vector4(vec4.x * scalar, vec4.y * scalar, vec4.z * scalar, vec4.w * scalar);
    }


}
