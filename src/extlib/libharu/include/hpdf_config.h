#ifndef KX_HPDF_CONFIG_H
#define KX_HPDF_CONFIG_H

#if defined(_WIN32) || defined(_WIN64)
#include "hpdf_config_w32.h"
#else
#include "hpdf_config_gcc.h"
#endif

#endif /* KX_HPDF_CONFIG_H */
