#include <iostream>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>

inline static auto wait_for_any_key_() noexcept(false) {
    auto const source_ = ::GetStdHandle(STD_INPUT_HANDLE);
    if (NULL == source_) throw ::std::runtime_error{"NULL == ::GetStdHandle(STD_INPUT_HANDLE)"};

    ::std::clog << "Press any key to exit" << ::std::endl << ::std::flush;

    while (true) {
        ::INPUT_RECORD buffer_;
        ::DWORD received_count_ = 0;
        constexpr static ::DWORD const expected_count_ = 1;
        if (0 == ::ReadConsoleInput(
            source_, &buffer_, expected_count_, &received_count_
        )) throw ::std::runtime_error{"0 == ::ReadConsoleInput(...)"};
        if (expected_count_ != received_count_) throw ::std::runtime_error{"expected_count_ != received_count_"};
        if (KEY_EVENT == buffer_.EventType) break;
    }
}
#endif // _WIN32

int main(int, char **) {
    ::std::cout << "Ok" << ::std::endl << ::std::flush;

#ifdef _WIN32
    ::wait_for_any_key_();
#endif // _WIN32

    return 0;
}
