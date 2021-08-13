#pragma once
#include <functional>
#include <memory>

#include "Util.h"

using Interpolator = std::function<void(float)>;

template<typename Interpolatable>
static inline Interpolator makeInterpolator(Interpolatable a, Interpolatable b, std::shared_ptr<Interpolatable> out)
{
    return [a,b,out](float percentage) {
        *out = util::interpolation::linear(a, b, percentage);
    };
}

template<typename Interpolatable>
static inline Interpolator makeInterpolator(Interpolatable a, Interpolatable b, std::function<void(Interpolatable)> func)
{
    return [a,b,func](float percentage) {
        func(util::interpolation::linear(a, b, percentage));
    };
}

#define MULTILINE_MACRO_BEGIN do {
#define MULTILINE_MACRO_END } while (0);
#define _CONCAT(a, b) a##b
#define CONCAT(a, b) _CONCAT(a, b)
#define _MAKE_INTERPOLATION_VARS(type, name, start_args, end_args) \
    type CONCAT(name, _start) start_args; \
    type CONCAT(name, _end) end_args;
#define MAKE_INTERPOLATION_OUT_PARAM(type, name, start_args, end_args) \
    _MAKE_INTERPOLATION_VARS(type, name, start_args, end_args); \
    std::shared_ptr<type> name = std::make_shared<type>(CONCAT(name, _start)); \
    Interpolator CONCAT(name, _interpolator) = makeInterpolator(CONCAT(name, _start), CONCAT(name, _end), name);

#define MAKE_INTERPOLATION_FUNC(type, name, start_args, end_args, func) \
    _MAKE_INTERPOLATION_VARS(type, name, start_args, end_args); \
    Interpolator CONCAT(name, _interpolator) = makeInterpolator(CONCAT(name, _start), CONCAT(name, _end), \
        static_cast<std::function<void(type)>>(func));

#define _VAR_METHOD(var, method) var->method
#define VAR_METHOD(var, method) _VAR_METHOD(var, method)
#define CALL_SETTER(var, method) [var](auto x){var->method(x);}
