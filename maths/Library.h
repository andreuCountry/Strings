#include <stdio.h>
#include <math.h>
#include <esat/window.h>
#include <esat/draw.h>
#include <esat/input.h>
#include <esat/sprite.h>
#include <esat/math.h>

namespace KOBE {
    struct Vec2 {
        float x, y;
    };

    struct Vec3 {
        float x, y, z;
    };

    struct Vec4 {
        float x, y, z, w;
    };

    struct Mat2 {
    /*
        m = 0 2
            1 3
    */
        float m[4];
    };

    struct Mat3 {
        float m[9];
    };

    struct Mat4 {
        float m[16];
    };

    Vec2 Vec2MultMat2Vec2(Mat2 mat, Vec2 vec) {
        Vec2 tmp = {
            mat.m[0] * vec.x + mat.m[2] * vec.y,
            mat.m[1] * vec.x + mat.m[3] * vec.y
        };

        return tmp;
    };

    void Vec2Print(Vec2 v) {
        printf("[X]: %f [Y]: %f\n", v.x, v.y);
    }

    void Vec3Print(Vec3 v) {
        printf("[X]: %f [Y]: %f [Z]: %f\n", v.x, v.y, v.z);
    }

    void Vec4Print(Vec4 v) {
        printf("[X]: %f [Y]: %f [Z]: %f [W]: %f\n", v.x, v.y, v.z, v.w);
    }

    Vec2 VPlusV2(Vec2 vector1, Vec2 vector2) {
        Vec2 newVector;

        newVector.x = vector1.x + vector2.x;
        newVector.y = vector1.y + vector2.y;

        return newVector;
    }

    Vec3 VPlusV3(Vec3 vector1, Vec3 vector2, Vec3 vector3) {
        Vec3 newVector;

        newVector.x = vector1.x + vector2.x + vector3.x;
        newVector.y = vector1.y + vector2.y + vector3.y;
        newVector.z = vector1.z + vector2.z + vector3.z;

        return newVector;
    }

    Vec4 VPlusV4(Vec4 vector1, Vec4 vector2, Vec4 vector3, Vec4 vector4) {
        Vec4 newVector;

        newVector.x = vector1.x + vector2.x + vector3.x + vector4.x;
        newVector.y = vector1.y + vector2.y + vector3.y + vector4.y;
        newVector.z = vector1.z + vector2.z + vector3.z + vector4.z;
        newVector.w = vector1.w + vector2.w + vector3.w + vector4.w;

        return newVector;
    }

    Vec2 VMinusV2(Vec2 vector1, Vec2 vector2) {
        Vec2 newVector;

        newVector.x = vector1.x - vector2.x;
        newVector.y = vector1.y - vector2.y;

        return newVector;
    }

    Vec3 VMinusV3(Vec3 vector1, Vec3 vector2, Vec3 vector3) {
        Vec3 newVector;

        newVector.x = vector1.x - vector2.x - vector3.x;
        newVector.y = vector1.y - vector2.y - vector3.y;
        newVector.z = vector1.z - vector2.z - vector3.z;

        return newVector;
    }

    Vec4 VMinusV4(Vec4 vector1, Vec4 vector2, Vec4 vector3, Vec4 vector4) {
        Vec4 newVector;

        newVector.x = vector1.x - vector2.x - vector3.x - vector4.x;
        newVector.y = vector1.y - vector2.y - vector3.y - vector4.y;
        newVector.z = vector1.z - vector2.z - vector3.z - vector4.z;
        newVector.w = vector1.w - vector2.w - vector3.w - vector4.w;

        return newVector;
    }

    Vec2 VMultpV2(Vec2 vector, float scalable) {
        Vec2 newScalableVector;

        newScalableVector.x = vector.x * scalable;
        newScalableVector.y = vector.y * scalable;

        return newScalableVector;
    }

    Vec3 VMultpV3(Vec3 vector, float scalable) {
        Vec3 newScalableVector;

        newScalableVector.x = vector.x * scalable;
        newScalableVector.y = vector.y * scalable;
        newScalableVector.z = vector.z * scalable;

        return newScalableVector;
    }

    Vec4 VMultpV4(Vec4 vector, float scalable) {
        Vec4 newScalableVector;

        newScalableVector.x = vector.x * scalable;
        newScalableVector.y = vector.y * scalable;
        newScalableVector.z = vector.z * scalable;
        newScalableVector.w = vector.w * scalable;

        return newScalableVector;
    }

    Vec2 VDivV2(Vec2 vector, float divisor) {
        Vec2 newDivisorVector;

        newDivisorVector.x = vector.x / divisor;
        newDivisorVector.y = vector.y / divisor;

        return newDivisorVector;
    }

    Vec3 VDivV3(Vec3 vector, float divisor) {
        Vec3 newDivisorVector;

        newDivisorVector.x = vector.x / divisor;
        newDivisorVector.y = vector.y / divisor;
        newDivisorVector.z = vector.z / divisor;

        return newDivisorVector;
    }

    Vec4 VDivV4(Vec4 vector, float divisor) {
        Vec4 newDivisorVector;

        newDivisorVector.x = vector.x / divisor;
        newDivisorVector.y = vector.y / divisor;
        newDivisorVector.z = vector.z / divisor;
        newDivisorVector.w = vector.w / divisor;

        return newDivisorVector;
    }

    float Vec2Length(Vec2 vector) {
        return sqrtf(vector.x * vector.x + vector.y * vector.y);
    }

    float Vec3Length(Vec3 vector) {
        return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    }

    float Vec4Length(Vec4 vector) {
        return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w);
    }

    Vec2 Vec2Normalize(Vec2 vector) {
        float divisor = sqrtf(vector.x * vector.x + vector.y * vector.y);

        Vec2 newVector;

        newVector.x = vector.x / divisor;
        newVector.y = vector.y / divisor;

        return newVector;
    }

    Vec3 Vec3Normalize(Vec3 vector) {
        float divisor = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

        Vec3 newVector;

        newVector.x = vector.x / divisor;
        newVector.y = vector.y / divisor;
        newVector.z = vector.z / divisor;

        return newVector;
    }

    Vec4 Vec4Normalize(Vec4 vector) {
        float divisor = sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z + vector.w * vector.w);

        Vec4 newVector;

        newVector.x = vector.x / divisor;
        newVector.y = vector.y / divisor;
        newVector.z = vector.z / divisor;
        newVector.w = vector.w / divisor;

        return newVector;
    }

    bool IsVector2Normalize(Vec2 vector) {
        if (Vec2Length(vector) == 1) {
            return true;
        }

        return false;
    }

    bool IsVector3Normalize(Vec3 vector) {
        if (Vec3Length(vector) == 1) {
            return true;
        }

        return false;
    }

    bool IsVector4Normalize(Vec4 vector) {
        if (Vec4Length(vector) == 1) {
            return true;
        }

        return false;
    }

    Vec2 InitializeVec2(float x, float y) {

        Vec2 v = {x, y};

        return v;
    }

    Vec3 InitializeVec3(float x, float y, float z) {

        Vec3 v = {x, y, z};

        return v;
    }

    Vec4 InitializeVec4(float x, float y, float z, float w) {

        Vec4 v = {x, y, z, w};

        return v;
    }

    Vec2 PerpendicularVec2Metod1(Vec2 vector) {
        Vec2 newVector;

        newVector.x = -vector.y;
        newVector.y = vector.x;

        return newVector;
    }

    Vec2 PerpendicularVec2Metod2(Vec2 vector) {
        Vec2 newVector;

        newVector.x = vector.y;
        newVector.y = -vector.x;

        return newVector;
    }
}