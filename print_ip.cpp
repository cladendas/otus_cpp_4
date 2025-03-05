
// print_ip( int8_t{-1} ); // 255 
// print_ip( int16_t{0} ); // 0.0 
// print_ip( int32_t{2130706433} ); // 127.0.0.1 
// print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41 
// print_ip( std::string{“Hello, World!”} ); // Hello, World! 
// print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400 
// print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100 
// print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0


#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <list>

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
print_ip(T value) {
    uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);

    for (size_t i = 0; i < sizeof(value); ++i) {

        if (i == sizeof(value) - 1) {
            std::cout << static_cast<int>(bytePtr[i]);
        } else {
            std::cout << static_cast<int>(bytePtr[i]) << '.';
        }
    }
    std::cout << std::endl;
}

//-------------------------------------------------//

template<typename T>
struct is_string {
    static const bool value = false;
};

template<>
struct is_string<std::string> {
    static const bool value = true;
};

template<typename T>
typename std::enable_if<is_string<T>::value>::type
print_ip(T value) {
    std::cout << value << std::endl;
}

//-------------------------------------------------//

template<typename T>
struct is_vector_int {
    static const bool value = false;
};

template<>
struct is_vector_int<std::vector<int>> {
    static const bool value = true;
};

template<typename T>
typename std::enable_if<is_vector_int<T>::value>::type
print_ip(T value) {
    for (auto oktet: value) {
        if (*(value.end() - 1) != oktet) {
            std::cout << oktet << '.';
        } else {
            std::cout << oktet; 
        }
    }
    std::cout << std::endl;
};

//-------------------------------------------------//

template<typename T>
struct is_list_short {
    static const bool value = false;
};

template<>
struct is_list_short<std::list<short>> {
    static const bool value = true;
};

template<typename T>
typename std::enable_if<is_list_short<T>::value>::type
print_ip(T value) {
    for (auto iter = value.begin(); iter != value.end(); iter++) {
        if (*iter != value.back()) { 
            std::cout << *iter << '.';
        } else {
            std::cout << *iter;
        }
    }
    std::cout << std::endl;
};

int main() {
    print_ip( int8_t{-1} ); //255
    print_ip( int16_t{0} ); // 0.0 
    print_ip( int32_t{2130706433} ); // 127.0.0.1 
    print_ip( int64_t{8875824491850138409} ); // 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} );
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    // print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0

    return 0;
}
