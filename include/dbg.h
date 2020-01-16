
#ifndef KX_DBG_H
#define KX_DBG_H

#if defined(_DEBUG)

#if defined(_WIN32) || defined(_WIN64)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#else
/* _DEBUG is not supported except Windows. */
#undef _DEBUG
#endif

#endif

#endif /* KX_DBG_H */
