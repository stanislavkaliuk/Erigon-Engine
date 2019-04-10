#pragma once

#ifdef ERIGON_WINDOWS
#ifdef ERIGON_DLL
#define ERIGON_API __declspec(dllexport)
#else // ERIGON_DLL
#define ERIGON_API __declspec(dllimport)
#endif
#else
#error Erigon Engine supports Windows only
#endif // ERIGON_WINDOWS
