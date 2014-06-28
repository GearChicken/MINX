#ifndef API_H_
#define API_H_

#define MINX_API

#ifdef _WIN32
#ifdef _WINDLL
#define MINX_API __declspec(dllexport)
#else
#define MINX_API __declspec(dllimport)
#endif
#else
#define MINX_API
#endif

#endif
