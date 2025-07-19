
/*
    Problems in the below class design :
    ----------------------------------
    1) Compilation Bottlenecks: Any file that includes Widget.hpp will need to recompile if we  change the definition of ThirdPartyObject or even just the order of private members.

    2) Leaky Encapsulation: The header reveals internal details like the use of ThirdPartyObject, which might be an implementation choice we want to keep flexible.

    3) Rigidity and Tight Coupling: Our code is now directly tied to third_party_lib.h. If this library changes, our code might break
*/

#include <vector>
#include <third_party_lib.h> // Imagine a large external library

class Widget
{
public:
    Widget();
    void process(const std::vector<unsigned char>& imageData);

private:
    ThirdPartyObject complexInternalObject;
    int width, height;
    std::vector<unsigned char> processedData;
};



// Improved design of Widget class
/*
    Faster Compilation :
    -------------------
    Reduced Header Dependencies: Changes in the implementation details won’t trigger recompilation of files that include the handle class’s header. This is especially valuable in large projects

    Minimal Recompilation Cascade: Modifications are confined to the implementation file, speeding up your build process

    Improved Encapsulation :
    ----------------------
    Hidden Implementation: The handle class’s header reveals only the public interface. Internal data structures and implementation-specific headers are kept out of sight

    ABI Stability: The layout of the handle class remains stable, even if its implementation changes. This prevents compatibility issues in shared libraries or when distributing headers to clients.

    Flexible Design :
    ---------------
    Easy Refactoring: You can change internal implementation details without affecting client code that uses the handle class

    Dependency Management: You can isolate 3rd-party library dependencies to the implementation file
*/

#include <memory>
#include <vector> 

namespace ylia::widget
{

class Widget
{
public:
    Widget();
    ~Widget();
    void process(const std::vector<unsigned char>& imageData);

private:
    class Impl; // Forward declaration
    std::unique_ptr<Impl> pImpl;
};

}

