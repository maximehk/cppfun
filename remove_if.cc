#include <algorithm>
#include <iostream>
#include <vector>

void PrintVector();

struct Data {
    explicit Data(int val): val(val), old_val(val) {};
    Data(const Data& other) = delete;
    Data(Data&& other) {
        if (val!=-1) {
            std::cout << "Overwrite " << val << std::endl;
        }
        val = other.val;
        other.val = -1;
        std::cout << "Moved " << val << std::endl;
        PrintVector();
    }
    Data& operator=(Data&& other) {
        if (val!=-1) {
            std::cout << "Overwrite " << val << std::endl;
        }
        val = other.val;
        other.val = -1;
        std::cout << "Moved " << val << std::endl;
        PrintVector();
        return *this;
    }
    ~Data() {
        std::cout << "Destructor called on " << old_val << std::endl;
    }

    int val;
    int old_val;
};
bool IsEven(const Data& d) { return d.val%2==0; }

static std::vector<Data>* vec;

void PrintVector(){
    for (const Data& d: *vec) std::cout << d.val <<  " ";
    std::cout << std::endl;
}

int main() {
    vec = new std::vector<Data>();
    vec->reserve(20);
    for (int i=0 ; i<20  ; i++) vec->emplace_back(i);
    PrintVector();
    vec->erase(std::remove_if(vec->begin(), vec->end(), IsEven), vec->end());
    PrintVector();
}
