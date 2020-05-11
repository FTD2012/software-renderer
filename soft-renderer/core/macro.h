#pragma once


#define LINE_SIZE 256
#define PATH_SIZE 256

#define UNUSED_VAR(x) ((void)(x))

#if !defined(__cplusplus)
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#else
// https://www.jianshu.com/p/e7afdf30579f
// https://www.zhihu.com/search?type=content&q=arraysize%20%E5%AE%8F
extern "C++"
{
template<typename T, unsigned int N>
char (&array_size_fake_func(T(&)[N]))[N];
#define ARRAY_SIZE(array) (sizeof(array_size_fake_func(array))
}
#endif
