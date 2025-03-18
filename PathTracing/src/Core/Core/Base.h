#pragma once

// Assertions
#ifdef PT_DEBUG
    #define PT_ASSERT(condition, message) if(!(condition)) { std::cout << message << std::endl; __debugbreak(); }
#endif
#ifdef PT_RELEASE
    #define PT_ASSERT(condition, message)
#endif

// Event functions
#define BIND_EVENT_FN(function) std::bind(&function, this, std::placeholders::_1)
