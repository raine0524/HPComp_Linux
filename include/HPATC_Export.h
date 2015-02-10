#ifndef __HPATC_EXPORT_H__
#define __HPATC_EXPORT_H__

#ifdef HPATC_EXPORT
#define HPATC_API _declspec(dllexport)
#elif HPATC_DLL
#define HPATC_API _declspec(dllimport)
#else
#define HPATC_API
#endif

#endif