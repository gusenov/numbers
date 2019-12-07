#ifndef UTILS
#define UTILS

template <class T, int N>
constexpr int SizeOfStaticArray(const T (&array)[N]) noexcept
{
    return N;
}

#endif
