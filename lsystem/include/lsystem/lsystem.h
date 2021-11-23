#pragma once

#include "common.h"

enum class Axis
{
    X,
    Y,
    Z
};

class Matrix
{

public:

    Matrix()
    {
    }

    Matrix(std::initializer_list<float[4]> matrix)
    {
        unsigned i = 0;
        for (auto row : matrix)
        {
            for(unsigned j = 0; j < 4; ++j)
                _4x4[i][j] = row[j];
            ++i;
        }
    }

    Matrix(const Matrix& other)
        : _data(other._data)
    {
    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix result;
        for (unsigned i = 0; i < 4; ++i)
        {
            const float* row = _4x4[i];
            float* resultRow = result[i];
            for (unsigned j = 0; j < 4; ++j)
            {
                float sum = 0;
                for (unsigned k = 0; k < 4; ++k)
                    sum += row[k] * other[k][j];
                resultRow[j] = sum;
            }
        }
        return result;
    }

    float* operator [] (unsigned n) const
    {
        return (float*)_4x4[n];
    }

private:

    union
    {
        struct { float _4x4[4][4]; };
        struct { float _flat[16]; } _data;
    };
};

class Data
{
public:

    Data() = delete;

protected:

    Data(float x = 0, float y = 0, float z = 0, float w = 0)
        : _x(x)
        , _y(y)
        , _z(z)
        , _w(w)
    {
    }

    Data(const Data& other)
        : _data(other._data)
    {
    }

    void Multiply(const Matrix& matrix)
    {
        Data data = {
            _x * matrix[0][0] + _y * matrix[1][0] + _z * matrix[2][0] + _w * matrix[3][0],
            _x * matrix[0][1] + _y * matrix[1][1] + _z * matrix[2][1] + _w * matrix[3][1],
            _x * matrix[0][2] + _y * matrix[1][2] + _z * matrix[2][2] + _w * matrix[3][2],
            _x * matrix[0][3] + _y * matrix[1][3] + _z * matrix[2][3] + _w * matrix[3][3] };
        _data = data._data;
    }

    union
    {
        struct { float _x, _y, _z, _w; };
        struct { float _xywz[4]; } _data;
    };
};

class Vector : public Data
{
public:

    Vector(float x = 0, float y = 0, float z = 0)
        : Data(x, y, z, 0)
    {}

    inline float getX() const { return _x; }
    inline float getY() const { return _y; }
    inline float getZ() const { return _z; }

    Vector normalize() const
    {
        float length = getLength();
        return { _x / length, _y / length, _z / length };
    }

    float getLength() const
    {
        return sqrt(float(_x * _x + _y * _y + _z * _z));
    }
};

class Vertex : public Data
{
public:

    Vertex(float x = 0, float y = 0, float z = 0)
        : Data(x, y, z, 1)
    {
    }

    inline float getX() const { return _x; }
    inline float getY() const { return _y; }
    inline float getZ() const { return _z; }

    Vertex operator+(const Vector& vector) const
    {
        return Vertex{_x + vector.getX(), _y + vector.getY(), _z + vector.getZ()};
    }

    Vector operator-(const Vertex& vertex) const
    {
        return Vector{_x - vertex._x, _y - vertex._y, _z - vertex._z};
    }
};

class Line
{
public:

    Line(const Vertex& origin, const Vector& vector)
        : _origin(origin)
        , _vector(vector)
    {
    }

private:

    Vertex _origin;
    Vector _vector;
};

class Renderer
{
public:

    Renderer()
        : _orientation({0, 1, 0})
    {
        _stack.push({0, 0, 0});
    }

    const Vertex& getCurrentPosition()
    {
        return _stack.top();
    }

    void pushStack()
    {
        _stack.push(getCurrentPosition());
    }

    void popStack()
    {
        if(_stack.size() == 1)
            throw std::runtime_error("Vertex stack is empty");
        _stack.pop();
    }

    void drawLength(float length)
    {
        const Vertex& current = getCurrentPosition();


        _lines.emplace_back(current, current);
    }

    void moveLength(float length)
    {

    }


    void rotate(Axis axis, float degreesRotation)
    {

    }

private:

    std::stack<Vertex> _stack;
    Vertex _orientation;
    std::vector<Line> _lines;

};

class Module
{
public:

    Module(const std::string& symbol, Renderer& renderer)
        : _symbol(symbol)
        , _renderer(renderer)
    {

    }

private:

    const std::string _symbol;
    Renderer& _renderer;
};

class LSystem
{
    
};
