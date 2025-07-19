#include <iostream>
#include <algorithm>  // for std::copy

class Vector
{
public:
    // Default constructor
    Vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

    // Destructor
    ~Vector()
    {
        delete[] m_data;
    }

    // Copy constructor
    Vector(const Vector& other) : m_data(new int[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        std::copy(other.m_data, other.m_data + other.m_size, m_data);
    }

    // Copy assignment
    Vector& operator=(const Vector& other)
    {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new int[m_capacity];
            std::copy(other.m_data, other.m_data + m_size, m_data);
        }
        return *this;
    }

    // Move constructor
    Vector(Vector&& other) noexcept: m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity)
    {
        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    // Move assignment
    Vector& operator=(Vector&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }
        return *this;
    }

    void push_back(int val)
    {
        if (m_size == m_capacity)
            grow();
        m_data[m_size++] = val;
    }

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }

    int& operator[](size_t i) { return m_data[i]; }
    const int& operator[](size_t i) const { return m_data[i]; }

    void print() const
    {
        for (size_t i = 0; i < m_size; ++i)
            std::cout << m_data[i] << ' ';
        std::cout << '\n';
    }

private:
    void grow()
    {
        m_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        int* new_data = new int[m_capacity];
        std::copy(m_data, m_data + m_size, new_data);
        delete[] m_data;
        m_data = new_data;
    }

    int* m_data;
    size_t m_size;
    size_t m_capacity;
};


int main()
{
    Vector v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v[0] = 100;

    v.print();  // Output: 100 20 30
    std::cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << '\n';

    Vector v2 = v;  // Copy
    v2.push_back(40);
    v2.print();     // Output: 100 20 30 40

    Vector v3 = std::move(v);  // Move
    v3.print();  // Output: 100 20 30
}

