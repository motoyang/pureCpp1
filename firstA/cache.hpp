#ifndef CACHE_HPP
#define CACHE_HPP

#include <map>
#include <unordered_map>

template <typename R, typename... Args>
std::function<R(Args...)> cache(R(*func) (Args...))
{
    auto result_map = std::make_shared<std::map<std::tuple<Args...>, R>>();

    return ([=](Args... args){
        std::tuple<Args...> t(args...);
        if (result_map->find(t) == result_map->end())
            (*result_map)[t] = func(args...);

        return (*result_map)[t];
    });
}

template <typename R, typename...  Args>
std::function<R(Args...)> sugar(R(*func)(Args...), bool needClear = false)
{
    using function_type = std::function<R(Args...)>;
    static std::unordered_map<decltype(func), function_type> functor_map;

    if (needClear)
        return functor_map[func] = cache(func);

    if (functor_map.find(func) == functor_map.end())
        functor_map[func] = cache(func);

    return functor_map[func];
}

/*test code
size_t fibonacci(size_t n)
{
return (n < 2) ? n : sugar(fibonacci2)(n - 1) + sugar(fibonacci2)(n - 2);
}
*/

// ------

// C++14的实现
template<typename F, size_t... I, typename ... Args>
static void call_helper(F f, std::index_sequence<I...>, const std::tuple<Args...>& tup)
{
    f(std::get<I>(tup)...);
}

template<typename F, typename ... Args>
static void call(F f, const std::tuple<Args...>& tp)
{
    call_helper(f, std::make_index_sequence<sizeof... (Args)>(), tp);
}

#endif // CACHE_HPP
