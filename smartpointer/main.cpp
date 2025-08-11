#include<iostream>
#include<memory>

// Learnings: Lvalues: a variable with a location in memory,
// Rvalue: simply a value just a numeric literel,
// rvalues do exist in memory during their temporary lifetime lifetime,
// rvalues are often used in expressions and can be assigned to lvalues.

template<typename T>
class uniquePtr {
private:
    T* ptr;

public:
    // Constructor
    explicit uniquePtr(T* p = nullptr) : ptr(p) {}

    // Destructor
    ~uniquePtr() {
        delete ptr;
    }

    // Delete copy constructor
    uniquePtr(const uniquePtr&) = delete;

    // Delete the copy assignment operator
    uniquePtr& operator=(const uniquePtr&) = delete;

    // Move constructor
    uniquePtr (uniquePtr&& other) noexcept
        : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // operator overloading for move constructor
    uniquePtr& operator=(uniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Dereference operator
    T& operator*() const {
        if (!ptr) throw std::runtime_error("Dereferencing null uniquePtr");
        return *ptr;
    }

    // Member access operator
    T* operator->() const {
        if (!ptr) throw std::runtime_error("Dereferencing null uniquePtr");
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

};

class Weapon {
public:
    Weapon(const std::string& weapon) : weapon(weapon){
        std::cout << "Weapon created: " << weapon << "\n";
    }
    ~Weapon() {
        std::cout << "Weapon destroyed: " << weapon << "\n";
    }
    void shoot() {
        std::cout << "Bang!" << "\n";
    }

    void rename(std::string&& name) {
        weapon = name;
    }

private:
    std::string weapon;
};

int main() {
    uniquePtr<Weapon> axe(new Weapon("axe"));
    uniquePtr<Weapon> sword = std::move(axe);

    if (sword.get()) sword->rename("sword");

    {
        uniquePtr<Weapon> gun(new Weapon("gun"));
        gun->shoot();
    }


    // axe->shoot();


    std::cin.get();
}


