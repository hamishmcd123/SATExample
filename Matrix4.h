#pragma once
#define Epsilon 0.005
#include "Vector4.h"
#include "Vector3.h"
#include <string>
#include <stdexcept>

namespace MathClasses
{
    struct Matrix4
    {
        float m1, m2, m3, m4,
            m5, m6, m7, m8,
            m9, m10, m11, m12,
            m13, m14, m15, m16;

        Matrix4() {
            m1 = m2 = m3 = m4 =
                m5 = m6 = m7 = m8 =
                m9 = m10 = m11 = m12 =
                m13 = m14 = m15 = m16 = 0.0f;
        }

        Matrix4(float _m1, float _m2, float _m3, float _m4,
            float _m5, float _m6, float _m7, float _m8,
            float _m9, float _m10, float _m11, float _m12,
            float _m13, float _m14, float _m15, float _m16) :
            m1(_m1), m2(_m2), m3(_m3), m4(_m4),
            m5(_m5), m6(_m6), m7(_m7), m8(_m8),
            m9(_m9), m10(_m10), m11(_m11), m12(_m12),
            m13(_m13), m14(_m14), m15(_m15), m16(_m16) {
        }

        Matrix4(const float* numbers) {
            m1 = numbers[0];
            m2 = numbers[1];
            m3 = numbers[2];
            m4 = numbers[3];
            m5 = numbers[4];
            m6 = numbers[5];
            m7 = numbers[6];
            m8 = numbers[7];
            m9 = numbers[8];
            m10 = numbers[9];
            m11 = numbers[10];
            m12 = numbers[11];
            m13 = numbers[12];
            m14 = numbers[13];
            m15 = numbers[14];
            m16 = numbers[15];
        }

        static const Matrix4 MakeIdentity() {
            return Matrix4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
        }

        friend const Vector4 operator*(const Matrix4& matrix4, const Vector4& vec4);

        const Matrix4 operator*(const Matrix4& other) const {
            Vector4 r1 = Vector4(m1, m5, m9, m13);
            Vector4 r2 = Vector4(m2, m6, m10, m14);
            Vector4 r3 = Vector4(m3, m7, m11, m15);
            Vector4 r4 = Vector4(m4, m8, m12, m16);

            Vector4 c1 = Vector4(other.m1, other.m2, other.m3, other.m4);
            Vector4 c2 = Vector4(other.m5, other.m6, other.m7, other.m8);
            Vector4 c3 = Vector4(other.m9, other.m10, other.m11, other.m12);
            Vector4 c4 = Vector4(other.m13, other.m14, other.m15, other.m16);

            return Matrix4(r1.Dot(c1), r2.Dot(c1), r3.Dot(c1), r4.Dot(c1),
                r1.Dot(c2), r2.Dot(c2), r3.Dot(c2), r4.Dot(c2),
                r1.Dot(c3), r2.Dot(c3), r3.Dot(c3), r4.Dot(c3),
                r1.Dot(c4), r2.Dot(c4), r3.Dot(c4), r4.Dot(c4));
        }

        explicit operator const float* () const {
            return &m1;
        }

        explicit operator float* () {
            return &m1;
        }

        float& operator[](int index) {
            if (index > 15 || index < 0) {
                throw std::out_of_range("Index out of range");
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
            case 9:
                return m10;
            case 10:
                return m11;
            case 11:
                return m12;
            case 12:
                return m13;
            case 13:
                return m14;
            case 14:
                return m15;
            case 15:
                return m16;
            }
        }

        const static Matrix4 MakeTranslation(const float x, const float y, const float z) {
            return Matrix4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                x, y, z, 1);
        }
        const static Matrix4 MakeTranslation(const Vector3& vec3) {
            return Matrix4(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                vec3.x,vec3.y,vec3.z , 1);
        }

        const static Matrix4 MakeRotateX(const float theta) {
            return Matrix4(1, 0, 0, 0,
                0, cosf(theta), -sinf(theta), 0,
                0, sinf(theta), cosf(theta), 0,
                0, 0, 0, 1);
        }

        const static Matrix4 MakeRotateY(const float theta) {
            return Matrix4(cosf(theta), 0, sinf(theta), 0,
                0, 1, 0, 0,
                -sinf(theta), 0, cosf(theta), 0,
                0, 0, 0, 1);
        }

        const static Matrix4 MakeRotateZ(const float theta) {
            return Matrix4(cosf(theta), sinf(theta), 0, 0,
                -sinf(theta), cosf(theta), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1);
        }

        const static Matrix4 MakeEuler(const float pitch, const float yaw, const float roll) {
            Matrix4 x = MakeRotateX(pitch);
            Matrix4 y = MakeRotateY(yaw);
            Matrix4 z = MakeRotateZ(roll);
            return z * y * x;
        }

        const static Matrix4 MakeEuler(const Vector3& vec3) {
            Matrix4 x = MakeRotateX(vec3.x);
            Matrix4 y = MakeRotateY(vec3.y);
            Matrix4 z = MakeRotateZ(vec3.z);
            return z * y * x;
        }

        const static Matrix4 MakeScale(const float xscale, const float yscale, const float zscale) {
            return Matrix4(xscale, 0, 0, 0,
                0, yscale, 0, 0,
                0, 0, zscale, 0,
                0, 0, 0, 1);
        }

        const static Matrix4 MakeScale(const Vector3& vec3) {
            return Matrix4(vec3.x, 0, 0, 0,
                0, vec3.y, 0, 0,
                0, 0, vec3.z, 0,
                0, 0, 0, 1);
        }

        bool operator==(const Matrix4& other) const {
            return (abs(this->m1 - other.m1) < Epsilon &&
                abs(this->m2 - other.m2) < Epsilon &&
                abs(this->m3 - other.m3) < Epsilon &&
                abs(this->m4 - other.m4) < Epsilon &&
                abs(this->m5 - other.m5) < Epsilon &&
                abs(this->m6 - other.m6) < Epsilon &&
                abs(this->m7 - other.m7) < Epsilon &&
                abs(this->m8 - other.m8) < Epsilon &&
                abs(this->m9 - other.m9) < Epsilon &&
                abs(this->m10 - other.m10) < Epsilon &&
                abs(this->m11 - other.m11) < Epsilon &&
                abs(this->m12 - other.m12) < Epsilon &&
                abs(this->m13 - other.m13) < Epsilon &&
                abs(this->m14 - other.m14) < Epsilon &&
                abs(this->m15 - other.m15) < Epsilon &&
                abs(this->m16 - other.m16) < Epsilon);
        }

        std::string ToString() const {
            return std::to_string(m1) + " , " +
                std::to_string(m2) + " , " +
                std::to_string(m3) + " , " +
                std::to_string(m4) + " , " + '\n' +
                std::to_string(m5) + " , " +
                std::to_string(m6) + " , " +
                std::to_string(m7) + " , " +
                std::to_string(m8) + " , " + '\n' +
                std::to_string(m9) + " , " +
                std::to_string(m10) + " , " +
                std::to_string(m11) + " , " +
                std::to_string(m12) + " , " + '\n' +
                std::to_string(m13) + " , " +
                std::to_string(m14) + " , " +
                std::to_string(m15) + " , " +
                std::to_string(m16);
        } 


    };


    inline const Vector4 operator*(const Matrix4& matrix4, const Vector4& vec4) {
        return Vector4(
            vec4.x * matrix4.m1 + vec4.y * matrix4.m5 + vec4.z * matrix4.m9 + vec4.w * matrix4.m13,
            vec4.x * matrix4.m2 + vec4.y * matrix4.m6 + vec4.z * matrix4.m10 + vec4.w * matrix4.m14,
            vec4.x * matrix4.m3 + vec4.y * matrix4.m7 + vec4.z * matrix4.m11 + vec4.w * matrix4.m15,
            vec4.x * matrix4.m4 + vec4.y * matrix4.m8 + vec4.z * matrix4.m12 + vec4.w * matrix4.m16
        );
    }

}