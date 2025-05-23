#pragma once
#define Epsilon 0.000005
#include <string>
#include <stdexcept>

namespace MathClasses
{
    struct Vector3
    {
        float x; 
        float y;
        float z;

        Vector3() {

            x = 0.0f;
            y = 0.0f;
            z = 0.0f;
        }

        Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {}

        const float Magnitude() const {
            return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        const Vector3 Normalised() const {
            const float magnitude = sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));
            if (magnitude == 0.0f) {
                return Vector3();
            }

            return Vector3(x / magnitude, y / magnitude, z / magnitude);
        }

        Vector3& Normalise() {
            const float magnitude = sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2));

            if (magnitude == 0.0f) {
                x = 0;
                y = 0;
                z = 0;
                return *this;
            }

            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
            return *this;
        }

        const float Dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        const Vector3 Cross(const Vector3& other) const {
            return Vector3(y * other.z - z * other.y, -(x * other.z - z * other.x), x * other.y - y * other.x);
        }

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }
        friend const Vector3 operator*(const Vector3& vec3, const float scalar);
        friend const Vector3 operator*(const float scalar, const Vector3& vec3);

        Vector3 operator/(const float scalar) {
            if (scalar == 0.0f) {
                throw (std::runtime_error("Attempted to divide by 0"));
            }
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        bool operator==(const Vector3& other) const {
            return (abs(x - other.x) < Epsilon && 
                    abs(y - other.y) < Epsilon &&
                    abs(z - other.z) < Epsilon);
        }

        bool operator!=(const Vector3& other) {
			if (x == other.x && y == other.y && z == other.z) {
                return false;
            }
            else {
                return true;
            }
 
        }


        const float& operator[](const int index) const {
            if (index > 2 || index <0) {
                throw std::out_of_range("Index out of range! DO BETTER");
            }
            switch (index) {
            case 0: 
                return x;
            case 1:
                return y;
            case 2:
                return z;
            }
        }

        float& operator[](const int index) {
            if (index > 2 || index < 0) {
                throw std::out_of_range("Index out of range! DO BETTER");
            }
            switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            }
        }
        
        // NOTE TO SELF - This is not a good way to do this. It would be much better for 
        // the vector components to be stored as an array so that we could just return
        // that.

        explicit operator float* () {
            return &x;
        }

        explicit operator const float*() const {
            return &x;
        } 

        std::string ToString() const { return std::to_string(x) + " , " + std::to_string(y) + " , " + std::to_string(z); }

        Vector3& clear() {
            x = 0.0f;
            y = 0.0f;
            z = 1.0f;
            return *this;
        }
  	};


inline const Vector3 operator*(const Vector3& vec3, const float scalar) {
    return Vector3(vec3.x * scalar, vec3.y * scalar, vec3.z * scalar);
}


inline const Vector3 operator*(const float scalar, const Vector3& vec3) {
    return Vector3(vec3.x * scalar, vec3.y * scalar, vec3.z * scalar);
}

}
