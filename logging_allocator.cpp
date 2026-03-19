#include <iostream>
#include <vector>

template <typename T>
struct logging_allocator {
    using value_type = T;
    using pointter = T*;
    using const_pointter = const T*;
    using reference = T&;
    using const_reference = const T&;

    template <typename U>
    struct rebind{
        using other = logging_allocator<U>;
    };

    logging_allocator() = default;
    ~logging_allocator() = default;

    // template <typename U>
    // logging_allocator(const logging_allocator<U>&) {}

    T* allocate(std::size_t n){
        std::cout << __PRETTY_FUNCTION__ << " [n = ]" << n << "]" << std::endl;

        void* p = malloc(n * sizeof(T));
        if(!p){
            throw std::bad_alloc();
        }
        return reinterpret_cast<T*>(p);
    }

    void deallocate(T* p, std::size_t n){
        std::cout << __PRETTY_FUNCTION__ << " [n = ]" << n << "]" << std::endl;
        free(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p)
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~U();
    }
};

int main(int argc, char const *argv[]){
    std::vector<int, logging_allocator<int>> v;

    for(int i = 0; i < 6; ++i){
        std::cout << "Vector size = " << v.size() << '\n';
        v.emplace_back(i);
        std::cout << '\n';
    }
    return 0;
}
