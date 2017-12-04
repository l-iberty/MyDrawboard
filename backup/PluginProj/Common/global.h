#ifndef DLL_EXPORT_H
#define DLL_EXPORT_H

#define DLL_EXPORT extern "C" __declspec(dllexport)

#pragma comment(lib, "user32")

#endif // DLL_EXPORT_H
