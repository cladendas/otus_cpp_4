/**
    \brief Печать ip-адреса

    Функция print_ip, которая способна выводить в консоль ip-адрес, который передан ей в типах, указанных далее    

    print_ip( int8_t{-1} ); // 255 
    print_ip( int16_t{0} ); // 0.0 
    print_ip( int32_t{2130706433} ); // 127.0.0.1 
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41 
    print_ip( std::string{“Hello, World!”} ); // Hello, World! 
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400 
    print_ip( std::list<shot>{400, 300, 200, 100} ); // 400.300.200.100 
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
*/


#include <iostream>
#include <tuple>
#include <cstdint>
#include <typeinfo>
#include <list>
#include <vector>

template <typename Container>
struct is_container : std::false_type{};

template <typename... Ts> 
struct is_container<std::list<Ts...>> : std::true_type{};

template <typename... Ts> 
struct is_container<std::vector<Ts...>> : std::true_type{};

/**
    \brief Шаблон для вывода ip-адреса из std::vector и std::list
*/
template<typename T>
typename std::enable_if<is_container<T>::value>::type
print_ip(T value) {
    for (auto iter = value.begin(); iter != value.end(); iter++) {
        if (iter != --value.end()) {
            std::cout << *iter << '.';
        } else {
            std::cout << *iter;
        }
    }
    std::cout << std::endl;
};

//-------------------------------------------------//

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value>::type
print_ip(T value) {
    uint8_t* bytePtr = reinterpret_cast<uint8_t*>(&value);
    std::vector<int> vec(sizeof(value));

    for (size_t i = 0; i < sizeof(value); ++i) {
        vec[sizeof(value) - 1 - i] = static_cast<int>(bytePtr[i]);
    }
    print_ip(vec);
}

//-------------------------------------------------//

template<typename T>
struct is_string : std::false_type{};


template<>
struct is_string<std::string> {
    static const bool value = true;
};

/**
    \brief Шаблон для вывода ip-адреса из std::string
*/
template<typename T>
typename std::enable_if<is_string<T>::value>::type
print_ip(T value) {
    std::cout << value << std::endl;
}

//-------------------------------------------------//

template<typename T>
struct is_vector_int : std::false_type{};

template<>
struct is_vector_int<std::vector<int>> {
    static const bool value = true;
};

//-------------------------------------------------//

template <typename Tuple, size_t Index = 0>
void print_tuple_element(const Tuple& tuple) {
    std::cout << std::get<Index>(tuple);
    if constexpr (Index + 1 < std::tuple_size_v<Tuple>) {
        std::cout << ".";
        print_tuple_element<Tuple, Index + 1>(tuple);
    }
}

template <typename... Types>
void print_ip(const std::tuple<Types...>& tuple) {
    print_tuple_element(tuple);
    std::cout << std::endl;
}

int main() {
    print_ip( int8_t{-1} ); //255
    print_ip( int16_t{0} ); // 0.0 
    print_ip( int32_t{2130706433} ); // 127.0.0.1 
    print_ip( int64_t{8875824491850138409} ); // 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} );
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0

    return 0;
}
