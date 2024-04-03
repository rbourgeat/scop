/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Math.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 17:55:33 by rbourgea          #+#    #+#             */
/*   Updated: 2024/04/03 21:49:27 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <iostream>

class vec2 {
public:
    float x, y;

    // Constructors
    vec2() : x(0.0f), y(0.0f) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}

    // Basic operations
    vec2 operator+(const vec2& other) const {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator-(const vec2& other) const {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator*(float scalar) const {
        return vec2(x * scalar, y * scalar);
    }

    vec2 operator/(float scalar) const {
        float invScalar = 1.0f / scalar;
        return vec2(x * invScalar, y * invScalar);
    }

    // Dot product
    float dot(const vec2& other) const {
        return x * other.x + y * other.y;
    }

    // Magnitude (length) of the vector
    float length() const {
        return std::sqrt(x * x + y * y);
    }

    // Normalize the vector
    vec2 normalize() const {
        float len = length();
        if (len != 0.0f)
            return *this / len;
        else
            return *this;
    }
};

class vec3 {
public:
    float x, y, z;

    // Constructors
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    vec3(float value) : x(value), y(value), z(value) {}

    // Unary minus operator
    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }

    // Basic operations
    vec3 operator+(const vec3& other) const {
        return vec3(x + other.x, y + other.y, z + other.z);
    }

    vec3 operator-(const vec3& other) const {
        return vec3(x - other.x, y - other.y, z - other.z);
    }

    vec3 operator*(float scalar) const {
        return vec3(x * scalar, y * scalar, z * scalar);
    }

    vec3 operator/(float scalar) const {
        float invScalar = 1.0f / scalar;
        return vec3(x * invScalar, y * invScalar, z * invScalar);
    }

    vec3& operator/=(float scalar) {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        }
        return *this;
    }

    friend vec3 operator*(float scalar, const vec3& v) {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    vec3& operator+=(const vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec3& operator-=(const vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // Subscript operator
    float& operator[](int index) {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else if (index == 2)
            return z;
        else
            throw std::out_of_range("Index out of range in vec3 subscript operator");
    }

    const float& operator[](int index) const {
        if (index == 0)
            return x;
        else if (index == 1)
            return y;
        else if (index == 2)
            return z;
        else
            throw std::out_of_range("Index out of range in vec3 subscript operator");
    }

    // Dot product
    float dot(const vec3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    // Cross product
    vec3 cross(const vec3& other) const {
        return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    // Magnitude (length) of the vector
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Normalize the vector
    vec3 normalize() const {
        float len = length();
        if (len != 0.0f)
            return *this / len;
        else
            return *this;
    }
};

class mat4 {
public:
    float elements[4][4];

    // Constructors
    mat4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                elements[i][j] = (i == j) ? 1.0f : 0.0f;
    }

    // Constructor that initializes all elements to a single float value
    mat4(float value) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                elements[i][j] = value;
    }

    // Copy constructor
    mat4(const mat4& other) {
        std::memcpy(elements, other.elements, sizeof(elements));
    }

    // Copy assignment operator
    mat4& operator=(const mat4& other) {
        if (this != &other) {
            std::memcpy(elements, other.elements, sizeof(elements));
        }
        return *this;
    }

    // Access individual elements
    float& operator()(int row, int col) {
        return elements[row][col];
    }

    const float& operator()(int row, int col) const {
        return elements[row][col];
    }

    // Matrix subtraction
    mat4 operator-(const mat4& other) const {
        mat4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result(i, j) = elements[i][j] - other(i, j);
        return result;
    }

    // Matrix multiplication
    mat4 operator*(const mat4& other) const {
        mat4 result(0);
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                for (int k = 0; k < 4; ++k)
                    result(i, j) += elements[i][k] * other(k, j);
        return result;
    }

    // Subscript operator to allow access like mat[1][2]
    float* operator[](int index) {
        return elements[index];
    }

    const float* operator[](int index) const {
        return elements[index];
    }

    // Output to stream for debugging
    friend std::ostream& operator<<(std::ostream& os, const mat4& m) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                os << m(i, j) << ' ';
            }
            os << '\n';
        }
        return os;
    }
};

class quat {
public:
    float x, y, z, w;

    // Constructors
    quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
    quat(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}

    // Quaternion multiplication
    quat operator*(const quat& other) const {
        return quat(
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y + y * other.w + z * other.x - x * other.z,
            w * other.z + z * other.w + x * other.y - y * other.x,
            w * other.w - x * other.x - y * other.y - z * other.z
        );
    }

    // Normalize the quaternion
    quat normalize() const {
        float len = std::sqrt(x * x + y * y + z * z + w * w);
        if (len != 0.0f)
            return quat(x / len, y / len, z / len, w / len);
        else
            return *this;
    }

    // Convert quaternion to a 4x4 matrix (rotation matrix)
    mat4 toMat4() const {
        // const float xx = x * x;
        const float xy = x * y;
        const float xz = x * z;
        const float xw = x * w;

        const float yy = y * y;
        const float yz = y * z;
        const float yw = y * w;

        const float zz = z * z;
        const float zw = z * w;

        const float ww = w * w;

        mat4 result;

        result[0][0] = 1 - 2 * (zz + ww);
        result[0][1] = 2 * (yz - xw);
        result[0][2] = 2 * (yw + xz);

        result[1][0] = 2 * (yz + xw);
        result[1][1] = 1 - 2 * (yy + ww);
        result[1][2] = 2 * (zw - xy);

        result[2][0] = 2 * (yw - xz);
        result[2][1] = 2 * (zw + xy);
        result[2][2] = 1 - 2 * (yy + zz);

        return result;
    }
};

class math {
public:
    static vec3 min(const vec3& a, const vec3& b) {
        return vec3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    }

    static vec3 max(const vec3& a, const vec3& b) {
        return vec3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
    }

    static float length(vec3 v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    static vec3 normalize(const vec3& v) {
        vec3 result = v;
        result.normalize();
        return result;
    }

    static float lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    static vec3 lerp(const vec3& a, const vec3& b, float t) {
        return a + t * (b - a);
    }

    static float radians(float degrees) {
        return degrees * 0.0174533f;
    }

    static float degrees(float radians) {
        return radians * 57.2958f; // 180/π
    }

    static mat4 translate(const mat4& matrix, const vec3& translation) {
        mat4 result = matrix;

        for (int i = 0; i < 3; ++i) {
            result(3, i) += translation[i];
        }

        return result;
    }

    static mat4 rotate(float angle, const vec3& axis) {
        float c = cos(angle);
        float s = sin(angle);
        float t = 1.0f - c;
        
        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        mat4 rotationMatrix;

        rotationMatrix(0, 0) = t * x * x + c;
        rotationMatrix(0, 1) = t * x * y + s * z;
        rotationMatrix(0, 2) = t * x * z - s * y;

        rotationMatrix(1, 0) = t * x * y - s * z;
        rotationMatrix(1, 1) = t * y * y + c;
        rotationMatrix(1, 2) = t * y * z + s * x;

        rotationMatrix(2, 0) = t * x * z + s * y;
        rotationMatrix(2, 1) = t * y * z - s * x;
        rotationMatrix(2, 2) = t * z * z + c;

        return rotationMatrix;
    }

    static mat4 lookAt(const vec3& eye, const vec3& center, const vec3& up)
    {
        vec3 f = (center - eye).normalize();
        vec3 u = up.normalize();
        vec3 s = f.cross(u).normalize();
        u = s.cross(f);

        mat4 Result;

        Result[0][0] = s.x;
        Result[1][0] = s.y;
        Result[2][0] = s.z;
        Result[0][1] = u.x;
        Result[1][1] = u.y;
        Result[2][1] = u.z;
        Result[0][2] = -f.x;
        Result[1][2] = -f.y;
        Result[2][2] = -f.z;
        Result[3][0] = -s.dot(eye);
        Result[3][1] = -u.dot(eye);
        Result[3][2] = f.dot(eye);
        
        return Result;
    }

    static mat4 perspective(float fov, float aspectRatio, float near, float far) {
        float tanHalfFov = tan(fov * 0.5f);

        mat4 projMatrix;

        projMatrix(0, 0) = 1.0f / (aspectRatio * tanHalfFov);
        projMatrix(1, 1) = 1.0f / tanHalfFov;
        projMatrix(2, 2) = -(far + near) / (far - near);
        projMatrix(2, 3) = -1.0f;
        projMatrix(3, 2) = -(2.0f * far * near) / (far - near);

#ifdef MATH_FORCE_DEPTH_ZERO_TO_ONE
        // Adjust projection matrix for [0, 1] depth range
        projMatrix(2, 2) = -2.0f / (far - near);
        projMatrix(2, 3) = -(far + near) / (far - near);
#endif

        return projMatrix;
    }

    static vec3 cross(const vec3& a, const vec3& b) {
        return vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    static quat angleAxis(float angle, const vec3& axis) {
        float halfAngle = angle * 0.5f;
        float sinHalf = std::sin(halfAngle);
        return quat(std::cos(halfAngle), axis.x * sinHalf, axis.y * sinHalf, axis.z * sinHalf).normalize();
    }

    static mat4 toMat4(const quat& q) {
        return q.toMat4();
    }
};

#endif
