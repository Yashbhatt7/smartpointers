#include<iostream>

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

    //Move constructor
    //
    //
    // SOON COMING...
    //
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
    Weapon() {
        std::cout << "Weapon created\n";
    }

    ~Weapon() {
        std::cout << "Weapon destroyed\n";
    }
    void shoot() {
        std::cout << "Bang!\n";
    }
};

int main() {
    UniquePtr<Weapon> gun(new Weapon());
    gun->shoot();

    std::cin.get();
}


