/* Debjyoti Ghosh*/
#include <iostream>
#include <fstream>


struct GameObject
{
    int32_t field1;
    short field2;

    GameObject(int32_t _field1, short _field2, bool _active) : field1(_field1), field2(_field2), active(_active)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const GameObject& go);

    void serialize(std::ostream& os) const
    {
        os.write(reinterpret_cast<const char*>(&field1), sizeof(field1));
        os.write(reinterpret_cast<const char*>(&field2), sizeof(field2));
        os.write(reinterpret_cast<const char*>(&active), sizeof(active));
        os.write(padding, sizeof(padding));
    }

    void deSerialize(std::istream& is)
    {
        is.read(reinterpret_cast<char*>(&field1), sizeof(field1));
        is.read(reinterpret_cast<char*>(&field2), sizeof(field2));
        is.read(reinterpret_cast<char*>(&active), sizeof(active));
        is.read(padding, sizeof(padding));
    }

private:
    bool active;
    char padding[1];
};

/*
For binary operators:
If left operand is your class → member is okay
If left operand is not your class (std::cout, int, etc.) → non-member

Examples:
a + b         // member possible
a += b        // member preferred
cout << obj   // must be non-member
*/
std::ostream& operator<<(std::ostream& os, const GameObject& go)
{
    os << go.field1 << " " << go.field2 << " " << go.active;
    return os;
}


int main()
{
    // std::ofstream will close() in new scope
    {
        std::cout << " size of GameObject: " << sizeof(GameObject) << std::endl;
        GameObject go(70, 2, true);
        std::cout << go << std::endl;


        // Text version to file
        std::ofstream textFile("text.txt");
        textFile << go << std::endl;

        // Binary version to file
        std::ofstream binFile("text.bin", std::ios::binary);
        go.serialize(binFile);
    }

    {
        GameObject go(0,0,0);

        // Binary file to obj
        std::ifstream binFile("text.bin", std::ios::binary);
        go.deSerialize(binFile);

        std::cout << "Deserialized: " << go << std::endl;
        
    }

    return 0;
}