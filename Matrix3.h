#pragma once
#define Epsilon 0.005f
#include "Vector3.h"
#include <string>
#include <stdexcept>

namespace MathClasses
{
    struct Matrix3
    {
        float m1, m2, m3,
			  m4, m5, m6,
              m7, m8, m9;

        Matrix3() {
            m1 = 0;
            m2 = 0;
            m3 = 0;
            m4 = 0;
            m5 = 0;
            m6 = 0;
            m7 = 0;
            m8 = 0;
            m9 = 0;
        }

        Matrix3(float _m1, float _m2, float _m3,
            float _m4, float _m5, float _m6,
            float _m7, float _m8, float _m9) :
            m1(_m1), m2(_m2), m3(_m3),
            m4(_m4), m5(_m5), m6(_m6),
            m7(_m7), m8(_m8), m9(_m9) {}

        Matrix3(float* numbers) {
            m1 = numbers[0];
            m2 = numbers[1];
            m3 = numbers[2];
            m4 = numbers[3];
            m5 = numbers[4];
            m6 = numbers[5];
            m7 = numbers[6];
            m8 = numbers[7];
            m9 = numbers[8];
        }
        
        const static Matrix3 MakeIdentity() {
           return Matrix3(1, 0, 0,
					      0, 1, 0,
						  0, 0, 1);
        }

        friend const Vector3 operator*(const Matrix3& matrix3, const Vector3& vec3);

        const Matrix3 operator*(const Matrix3& other) const {
            Vector3 r1 = Vector3(m1, m4, m7);
            Vector3 r2 = Vector3(m2, m5, m8);
            Vector3 r3 = Vector3(m3, m6, m9);

            Vector3 c1 = Vector3(other.m1, other.m2, other.m3);
            Vector3 c2 = Vector3(other.m4, other.m5, other.m6);
            Vector3 c3 = Vector3(other.m7, other.m8, other.m9);

            return Matrix3(r1.Dot(c1), r2.Dot(c1), r3.Dot(c1),
						   r1.Dot(c2), r2.Dot(c2), r3.Dot(c2),
                           r1.Dot(c3), r2.Dot(c3), r3.Dot(c3));
        }

        const Matrix3 Transposed() const {
            return Matrix3(m1, m4, m7,
						   m2, m5, m8,
					       m3, m6, m9);
        }

        float& operator[](int index) {
            if (index > 8 || index < 0) {

                throw (std::out_of_range("Index out of range"));
            }
            switch (index) {
            case 0:
                return m1;
            case 1:
                return m2;
            case 2: 
                return m3;
            case 3:
                return m4;
            case 4:
                return m5;
            case 5:
                return m6;
            case 6:
                return m7;
            case 7:
                return m8;
            case 8:
                return m9;
            }
        }

        explicit operator const float* () const {
            return &m1;
       }
        
        explicit operator float* () {
            return &m1;
        }

        static const Matrix3 MakeTranslation(const float x, const float y, const float z) {
            return Matrix3(1, 0, 0,
						   0, 1, 0,
						   x, y, 1);
        }
        
        static const Matrix3 MakeTranslation(const Vector3& other) {
            return Matrix3(1, 0, 0,
						   0, 1, 0,
						   other.x, other.y, 1);
        }

        static const Matrix3 MakeRotateX(const float theta) {
            return Matrix3(1, 0, 0,
                0, cosf(theta), -sinf(theta),
                0, sinf(theta), cosf(theta));
        }

        static const Matrix3 MakeRotateY(const float theta) {
            return Matrix3(cosf(theta), 0, sinf(theta),
								0, 1, 0,
						-sinf(theta), 0, cosf(theta));
        }

        static const Matrix3 MakeRotateZ(const float theta) {

            return Matrix3(cosf(theta), sinf(theta), 0,
					-sinf(theta), cosf(theta), 0,
						0, 0, 1);
        }
        
        static const Matrix3 MakeEuler(const float pitch, const float yaw, const float roll) {
            Matrix3 x = MakeRotateX(pitch);
            Matrix3 y = MakeRotateY(yaw);
            Matrix3 z = MakeRotateZ(roll);
            return z * y * x;
        }

        static const Matrix3 MakeEuler(const Vector3& vec3) {
            Matrix3 x = MakeRotateX(vec3.x);
            Matrix3 y = MakeRotateY(vec3.y);
            Matrix3 z = MakeRotateZ(vec3.z);
            return z * y * x;
        }

        static const Matrix3 MakeScale(const float xscale, const float yscale, const float zscale) {
            return Matrix3(xscale, 0, 0,
						   0, yscale, 0,
						   0, 0, zscale);
        }

        static const Matrix3 MakeScale(const float xscale, const float yscale) {
		return Matrix3(xscale, 0, 0,
						0, yscale, 0,
						0, 0, 1);
        }
        
        static const Matrix3 MakeScale(const Vector3& vec3) {
            return Matrix3(vec3.x, 0, 0,
						   0, vec3.y, 0,
						   0, 0, vec3.z);
        }
        

        
        bool operator==(const Matrix3& other) const {
            if (abs(this->m1 - other.m1) < Epsilon &&
                abs(this->m2 - other.m2) < Epsilon &&
                abs(this->m3 - other.m3) < Epsilon &&
                abs(this->m4 - other.m4) < Epsilon &&
                abs(this->m5 - other.m5) < Epsilon &&
                abs(this->m6 - other.m6) < Epsilon &&
                abs(this->m7 - other.m7) < Epsilon &&
                abs(this->m8 - other.m8) < Epsilon &&
                abs(this->m9 - other.m9) < Epsilon) {
                return true;
            }
            return false;
        }

        std::string ToString() const {
            return std::to_string(m1) + " , " +
                std::to_string(m2) + " , " +
                std::to_string(m3) + " , " + '\n' +
                std::to_string(m4) + " , " +
                std::to_string(m5) + " , " +
                std::to_string(m6) + " , " + '\n' +
                std::to_string(m7) + " , " +
                std::to_string(m8) + " , " +
                std::to_string(m9);
                                }
};

	inline const Vector3 operator*(const Matrix3& matrix3, const Vector3& vec3) {
        return Vector3(
            matrix3.m1 * vec3.x + matrix3.m4 * vec3.y + matrix3.m7 * vec3.z,
            matrix3.m2 * vec3.x + matrix3.m5 * vec3.y + matrix3.m8 * vec3.z,
            matrix3.m3 * vec3.x + matrix3.m6 * vec3.y + matrix3.m9 * vec3.z
        );
    }



}