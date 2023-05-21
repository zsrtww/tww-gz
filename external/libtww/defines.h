#ifndef LIBTWW_DEFINES_H
#define LIBTWW_DEFINES_H

#include <utility>

#define LIBTWW_DEFINE_FUNC(gcLabel, rettype, name, args)                                           \
    extern "C" {                                                                                   \
    rettype gcLabel args;                                                                          \
    }                                                                                              \
    template <typename... Args>                                                                    \
    inline auto name(Args&&... a)->decltype(gcLabel(std::forward<Args>(a)...)) {                   \
        return gcLabel(std::forward<Args>(a)...);                                                  \
    }

// Required for keeping certain unused functions/variables from being removed
#define KEEP_FUNC __attribute__((used, visibility("default")))
#define KEEP_VAR __attribute__((visibility("default")))

#endif  // !LIBTWW_C_DEFINES_H