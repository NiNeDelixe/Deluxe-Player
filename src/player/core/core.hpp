#ifndef CORE_CORE_HPP_
#define CORE_CORE_HPP_

#include <stdint.h>

#include <juce_gui_extra/juce_gui_extra.h>

#include "internal_use_only/config.hpp"
#include "utils/juce/URLUtils.hpp"

#define NOMINMAX

template<class T>
using callback = std::function<T>;

using void_callback = callback<void(void)>;

#define DELETE_COPY(Class) \
Class(const Class&) = delete; \
void operator=(const Class&) = delete; \
Class(Class&&) = delete; \
Class& operator=(Class&&) = delete;

#define SIMPLE_DECLARE_CLASS(Class) \
public: \
    DELETE_COPY(Class) \
    static Class* getPtr() { static Class instance; return &instance; } \
    static Class& getInstance() { return *getPtr(); } \
private: 

#define DECLARE_CLASS(Class) \
SIMPLE_DECLARE_CLASS(Class) \
    Class() = default; \
public: \
    ~Class() = default; \
private:

#endif // CORE_CORE_HPP_
