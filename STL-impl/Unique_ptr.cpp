#include <iostream>
#include <string>

template <typename T>
class unique_pointer
{
public:
  explicit unique_pointer(T *ptr = nullptr) : mPtr(ptr)
  {
    std::cout << "Unique Pointer Constructed\n";
  }

  ~unique_pointer()
  {
    if (mPtr) // no if check required, can directly delete and its safe
    {
      delete mPtr;
      std::cout << "Unique Pointer Destructed\n";
    }
  }

  // deleting copy constructor and copy assignment operator
  unique_pointer(const unique_pointer& rhs) = delete;
  unique_pointer& operator=(const unique_pointer& rhs) = delete;

  // defining move constructor and move assignment operator
  // transferring the ownership
  unique_pointer(unique_pointer&& rhs) noexcept : mPtr(rhs.mPtr)
  {
    rhs.mPtr = nullptr;
  }

  unique_pointer& operator=(unique_pointer&& rhs) noexcept
  {
    /*| Expression | Type                  |
      | ---------- | --------------------- |
      | `rhs`      | `unique_pointer<T>&&` |
      | `&rhs`     | `unique_pointer<T>*`  |
      | `this`     | `unique_pointer<T>*`  |
    */
    if (&rhs != this)
    {
      delete this->mPtr; // can also just use delete mPtr;
      this->mPtr = rhs.mPtr;
      rhs.mPtr = nullptr;
      std::cout << "Unique Pointer Moved\n";
    }
    return *this;
  }

  // dereferencing operator
  T& operator*() const { return *mPtr; }

  // arrow operator returns the underlying pointer
  T* operator->() const { return mPtr; }

  void reset(T* rhs = nullptr)
  {
    if (mPtr) // if check not needed
      delete mPtr;

    mPtr = rhs;
  }

  [[nodiscard]] T* release() noexcept // use nodiscard to avoid memory leaks by giving a compile-time warning
  {
    T* prev = mPtr;
    mPtr = nullptr;
    
    return prev;
  }

  T* get() const { return mPtr; }

  /* if (myPtr) {  do something  };
    its explicit so can be used only in boolean contexts and not for int/double etc.

    unique_pointer<int> p(new int(42));
    int x = p;   // This would compile if operator bool() weren't explicit!
  */
  explicit operator bool() const { return mPtr != nullptr; }

private:

  T *mPtr{nullptr};
};


struct A
{
  int mId;
  std::string mName;

  A(int id, const std::string &name) : mId(id), mName(name) {}
};


int main()
{
  unique_pointer<A> ptr(new A(1, "Dfs"));

  std::cout << ptr->mId << '\n';
  std::cout << ptr->mName << '\n';

  unique_pointer<A> ptr2 = std::move(ptr);
  std::cout << ptr2->mName << '\n';

  if (!ptr)
    std::cout << "First pointer is now null\n";

    return 0;
}