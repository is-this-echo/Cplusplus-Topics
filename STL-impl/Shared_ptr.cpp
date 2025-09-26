#include<iostream>


template <typename T>
class shared_ptr
{
public:
    explicit shared_ptr(T* t = nullptr) : m_ptr(t), m_refCount( t ? new int(1) : nullptr)
    {
        std::cout << "constructor invoked \n";
    }

    shared_ptr(const shared_ptr& rhs) : m_ptr(rhs.m_ptr), m_refCount(rhs.m_refCount)
    {
        std::cout << "copy constructor invoked \n";
        ++(*m_refCount);
    }

    shared_ptr& operator=(const shared_ptr& rhs)
    {
        if (this != &rhs)
        {
            std::cout << "copy assignment invoked \n";

            release();
            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;
            ++(*m_refCount);
        }
        return *this;
    }

    shared_ptr(shared_ptr&& rhs) noexcept : m_ptr(rhs.m_ptr), m_refCount(rhs.m_refCount)
    {
        std::cout << "move constructor invoked\n";
        rhs.m_ptr = nullptr;
        rhs.m_refCount = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& rhs) noexcept
    {
        if (this != &rhs)
        {
            std::cout << "move assignment invoked\n";

            release();
            m_ptr = rhs.m_ptr;
            m_refCount = rhs.m_refCount;

            rhs.m_ptr = nullptr;
            rhs.m_refCount = nullptr;
        }
        return *this;
    }

    ~shared_ptr()
    {
        std::cout << "destructor invoked\n";
        release();

        if (m_refCount)
            std::cout << "Reference count decreased to: " << *m_refCount << "\n";
    }

    T& operator*() const { return *m_ptr; }

    T* operator->() const { return m_ptr; }

    T* get() const { return m_ptr; }

    explicit operator bool() const { return m_ptr != nullptr; }

    [[nodiscard]] int use_count() const { return m_refCount ? *m_refCount : 0; }

private:
    void release()
    {
        if (m_refCount && --(*m_refCount) == 0)
        {
            delete m_ptr;
            delete m_refCount;
            std::cout << "Shared ptr deleted the managed object!\n";
        }
    }

    T* m_ptr;
    int* m_refCount;
};


int main()
{

    shared_ptr<int> sp (new int (4));


    return 0;
}