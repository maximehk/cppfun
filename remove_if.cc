#include <algorithm>
#include <iostream>
#include <vector>

void PrintVector();

struct Data {
  explicit Data(int val) : val(val){};
  Data(const Data& other) = delete;
  Data(Data&& other) { *this = std::move(other); }
  Data& operator=(Data&& other) {
    int previous_val = val;
    val = other.val;
    other.val = -1;
    if (previous_val != -1) {
      std::cout << "Overwrite " << previous_val << " with " << val << std::endl;
    } else {
      std::cout << "Moved " << val << std::endl;
    }
    PrintVector();
    return *this;
  }
  static bool IsEven(const Data& d) { return d.val % 2 == 0; }

  int val;
};

static std::vector<Data>* vec;

void PrintVector() {
  for (const Data& d : *vec) std::cout << d.val << " ";
  std::cout << std::endl;
}

int main() {
  vec = new std::vector<Data>();
  vec->reserve(20);
  for (int i = 0; i < 20; i++) vec->emplace_back(i);
  PrintVector();
  vec->erase(std::remove_if(vec->begin(), vec->end(), Data::IsEven),
             vec->end());
  PrintVector();
  delete vec;
  return 0;
}
