#include <iostream>
#include <cstring>   // for strlen, strcpy

class String
{
public:
    // Default constructor
    String() : m_data(new char[1]{'\0'}), m_size(0) {}

    // Constructor from const char*
    String(const char* str)
    {
        m_size = std::strlen(str);
        m_data = new char[m_size + 1];
        std::strcpy(m_data, str);
    }

    // Destructor
    ~String()
    {
        delete[] m_data;
    }

    // Copy constructor
    String(const String& other)
    {
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        std::strcpy(m_data, other.m_data);
    }

    // Copy assignment
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            delete[] m_data;
            m_size = other.m_size;
            m_data = new char[m_size + 1];
            std::strcpy(m_data, other.m_data);
        }
        return *this;
    }

    // Move constructor
    String(String&& other) noexcept : m_data(other.m_data), m_size(other.m_size)
    {
        other.m_data = nullptr;
        other.m_size = 0;
    }

    // Move assignment
    String& operator=(String&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_data;
            m_data = other.m_data;
            m_size = other.m_size;
            other.m_data = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    // Size getter
    size_t size() const { return m_size; }

    // C-style string getter
    const char* c_str() const { return m_data; }

    // Indexing operator
    char& operator[](size_t i) { return m_data[i]; }
    const char& operator[](size_t i) const { return m_data[i]; }

    // Print function (optional)
    void print() const { std::cout << m_data << '\n'; }

private:
    char* m_data;
    size_t m_size;
};


int main()
{
    String s1("Hello");
    String s2 = s1;           // Copy
    String s3 = std::move(s1); // Move
    s2 = s3;                  // Copy assignment
    s3 = String("World");     // Move assignment

    s3.print();               // "World"
    std::cout << s3[1] << '\n'; // 'o'
    std::cout << "Size: " << s3.size() << '\n';
}

