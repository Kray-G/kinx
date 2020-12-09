
#ifndef KX_PARSER_H
#define KX_PARSER_H

#include <stdint.h>
#include <kinx.h>

typedef struct arytype_t_ {
    int type;
    int depth;
} arytype_t;

#ifndef KX_NO_INCLUDE_PARSER_TAB_H
#include <parser.tab.h>
#endif /* KX_PARSER */

#endif /* KX_PARSER_H */
