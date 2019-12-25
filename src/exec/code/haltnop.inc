#define KX_HALT_CODE() \
{ \
    goto LBL_KX_END_OF_CODE; \
} \
/**/

#define KX_NOP_CODE() \
{ \
    cur = cur->next; \
} \
/**/
