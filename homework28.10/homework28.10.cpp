#include <iostream>

//надеюсь правильно поняла задание

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T* p) : ptr(p) {}

    UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* get() const {
        return ptr;
    }

    bool empty() const {
        return ptr == nullptr;
    }

    void free() {
        delete ptr;
        ptr = nullptr;
    }

    void release() {
        T* tmp = ptr;
        ptr = nullptr;
        tmp; 
    }

    void swap(UniquePtr& other) noexcept {
        std::swap(ptr, other.ptr);
    }

    ~UniquePtr() {
        delete ptr;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }
};

int main() {
    UniquePtr<int> up1(new int(5));
    UniquePtr<int> up2(new int(10));

    std::cout << "up1: " << *up1 << std::endl;
    std::cout << "up2: " << *up2 << std::endl;

    up1.swap(up2);

    std::cout << "up1: " << *up1 << std::endl;
    std::cout << "up2: " << *up2 << std::endl;

    up1.free();
    up2.release();

    system("pause");
    return 0;
}
