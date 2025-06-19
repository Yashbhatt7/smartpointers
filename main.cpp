#include<iostream>
#include<memory>

template<typename T> class UniquePtr {

public:
    // Constructor
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    ~UniquePtr() {
        delete ptr;
    }

    // Delete copy constructor and copy assignment to prevent copies
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Move constructor
    //
    //
    // SOON COMING...
    //
    //

    // Dereference
    T& operator*() const {
        return *ptr;
    }
    T* operator->() const {
        return ptr;
    }

    // Get raw pointer
    T* get() const {
        return ptr;
    }

private:
    T* ptr;
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
private:
    std::string weapon;
};

int main() {
    UniquePtr<Weapon> axe(new Weapon("axe"));

    {
        UniquePtr<Weapon> gun(new Weapon("gun"));
        gun->shoot();
    }

    {
        axe->shoot();
    }
    std::cin.get();
}


