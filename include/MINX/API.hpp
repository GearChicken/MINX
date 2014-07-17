#ifndef MINX_API_HPP_
#define MINX_API_HPP_

#ifdef _WIN32
	#pragma warning( disable : 4251 )
	#ifdef _WINDLL
		#define MINX_API __declspec(dllexport)
	#else
		#define MINX_API __declspec(dllimport)
	#endif
#else
	#define MINX_API
#endif

#endif
