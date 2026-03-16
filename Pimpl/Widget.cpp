#include <Widget.hpp>
#include <third_party_lib.h> 


// https://herbsutter.com/gotw/_100/


/*
    When to use pIMpl class design :
    -------------------------------
    1) We have a class with complex internal details that you want to hide from the user
    2) Compilation times are a concern in the project
    3) We need ABI stability for shared libraries or distributed headers
    4) We anticipate frequent changes to a class’s internal implementation
*/

namespace ylia::widget
{

class Widget::Impl
{
public:
    void process(const std::vector<unsigned char>& imageData)
    {
    // ... (process widget logic using ThirdPartyObject)
    }

private:
    ThirdPartyObject complexInternalObject;
    // ... other private members
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {}
Widget::~Widget() = default; 

void Widget::process(const std::vector<unsigned char>& imageData)
{
    pImpl->process(imageData); 
}

}
