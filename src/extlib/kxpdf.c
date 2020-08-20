
#include <dbg.h>
#include <inttypes.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include "libharu/include/hpdf.h"

KX_DECL_MEM_ALLOCATORS();

#define KX_GET_VOIDP(args, ctx, vn, n) \
void *vn = NULL; { \
    kx_obj_t *vobj = get_arg_obj(n, args, ctx); \
    KX_GET_RAW(void*, "_voidp", vp, vobj, "PdflibException", "Invalid Pdflib object"); \
    vn = vp; \
} \
/**/
#define KX_GET_CORE_SET(args, ctx, vn, n, p1, cast) \
    if (p1) { \
        if (p1->type == KX_INT_T) { \
            vn.p1  = (cast)p1->value.iv; \
        } else if (p1->type == KX_DBL_T) { \
            vn.p1 = (cast)p1->value.dv; \
        } \
    } \
/**/
#define KX_MAKE_VOIDP(rv, r) \
    kx_obj_t *rv = allocate_obj(ctx); \
    kx_any_t *anyv = allocate_any(ctx); \
    anyv->p = r; \
    anyv->any_free = NULL; \
    KEX_SET_PROP_ANY(rv, "_voidp", anyv); \
/**/
#define KX_GET_POINT(args, ctx, vn, n) \
HPDF_Point vn = {0}; { \
    kx_obj_t *vobj = get_arg_obj(n, args, ctx); \
    kx_val_t *x = NULL; \
    kx_val_t *y = NULL; \
    KEX_GET_PROP(x, vobj, "x"); \
    KEX_GET_PROP(y, vobj, "y"); \
    KX_GET_CORE_SET(args, ctx, vn, n, x, float); \
    KX_GET_CORE_SET(args, ctx, vn, n, y, float); \
} \
/**/
#define KX_MAKE_POINT(rv, r) \
    kx_obj_t *rv = allocate_obj(ctx); \
    KEX_SET_PROP_DBL(rv, "x", r.x); \
    KEX_SET_PROP_DBL(rv, "y", r.y); \
/**/
#define KX_GET_CORE4(args, ctx, vn, n, type, p1, p2, p3, p4, cast) \
type vn = {0}; { \
    kx_obj_t *vobj = get_arg_obj(n, args, ctx); \
    kx_val_t *p1 = NULL; \
    kx_val_t *p2 = NULL; \
    kx_val_t *p3 = NULL; \
    kx_val_t *p4 = NULL; \
    KEX_GET_PROP(p1, vobj, #p1); \
    KEX_GET_PROP(p2, vobj, #p2); \
    KEX_GET_PROP(p3, vobj, #p3); \
    KEX_GET_PROP(p4, vobj, #p4); \
    KX_GET_CORE_SET(args, ctx, vn, n, p1, cast); \
    KX_GET_CORE_SET(args, ctx, vn, n, p2, cast); \
    KX_GET_CORE_SET(args, ctx, vn, n, p3, cast); \
    KX_GET_CORE_SET(args, ctx, vn, n, p4, cast); \
} \
/**/
#define KX_MAKE_CORE4_DBL(rv, r, p1, p2, p3, p4) \
    kx_obj_t *rv = allocate_obj(ctx); \
    KEX_SET_PROP_DBL(rv, #p1, r.p1); \
    KEX_SET_PROP_DBL(rv, #p2, r.p2); \
    KEX_SET_PROP_DBL(rv, #p3, r.p3); \
    KEX_SET_PROP_DBL(rv, #p4, r.p4); \
/**/
#define KX_MAKE_CORE4_INT(rv, r, p1, p2, p3, p4) \
    kx_obj_t *rv = allocate_obj(ctx); \
    KEX_SET_PROP_INT(rv, #p1, r.p1); \
    KEX_SET_PROP_INT(rv, #p2, r.p2); \
    KEX_SET_PROP_INT(rv, #p3, r.p3); \
    KEX_SET_PROP_INT(rv, #p4, r.p4); \
/**/

#define KX_GET_TEXTWIDTH(args, ctx, vn, n) KX_GET_CORE4(args, ctx, vn, n, HPDF_TextWidth, numchars, numwords, width, numspace, int)
#define KX_MAKE_TEXTWIDTH(rv, r) KX_MAKE_CORE4_INT(rv, r, numchars, numwords, width, numspace)
#define KX_GET_RECT(args, ctx, vn, n) KX_GET_CORE4(args, ctx, vn, n, HPDF_Rect, left, bottom, right, top, float)
#define KX_MAKE_RECT(rv, r) KX_MAKE_CORE4_DBL(rv, r, left, bottom, right, top)

/* TODO: multi-thread unsafe */
static int sg_error = 0;
static int sg_detail = 0;

void kxpdf_error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data)
{
    sg_error = error_no;
    sg_detail = detail_no;
}

/* function prototype */
int kxpdf_HPDF_GetVersion(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_NewEx(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_New(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetErrorHandler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Free(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_NewDoc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_FreeDoc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_HasDoc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_FreeDocAll(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SaveToStream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetContents(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetStreamSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ReadFromStream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ResetStream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SaveToFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetError(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetErrorDetail(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ResetError(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_CheckError(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetPagesConfiguration(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetPageByIndex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetPageMMgr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetPageLayout(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetPageLayout(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetPageMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetPageMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetViewerPreference(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetViewerPreference(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetOpenAction(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetCurrentPage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_AddPage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_InsertPage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetRotate(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetZoom(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetFont(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadType1FontFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetTTFontDefFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadTTFontFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadTTFontFromFile2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_AddPageLabel(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseJPFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseKRFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseCNSFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseCNTFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_CreateOutline(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Outline_SetOpened(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Outline_SetDestination(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateDestination(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetXYZ(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFit(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFitH(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFitV(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFitR(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFitB(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFitBH(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Destination_SetFitBV(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetEncoder(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetCurrentEncoder(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetCurrentEncoder(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Encoder_GetType(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Encoder_GetByteType(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Encoder_GetUnicode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Encoder_GetWritingMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseJPEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseKREncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseCNSEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseCNTEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_UseUTFEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateXObjectFromImage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateXObjectAsWhiteRect(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Create3DAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateTextAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateFreeTextAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateLineAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateWidgetAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateLinkAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateURILinkAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateHighlightAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateUnderlineAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateSquigglyAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateStrikeOutAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreatePopupAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateStampAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateProjectionAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateSquareAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreateCircleAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LinkAnnot_SetHighlightMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LinkAnnot_SetJavaScript(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LinkAnnot_SetBorderStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_TextAnnot_SetIcon(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_TextAnnot_SetOpened(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Annot_SetRGBColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Annot_SetCMYKColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Annot_SetGrayColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Annot_SetNoColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetTitle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetSubject(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetCreationDate(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetTransparency(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetIntent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetPopup(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetRectDiff(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetCloudEffect(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetInteriorRGBColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetInteriorCMYKColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetInteriorGrayColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_MarkupAnnot_SetInteriorTransparent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_TextMarkupAnnot_SetQuadPoints(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Annot_Set3DView(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_PopupAnnot_SetOpened(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_FreeTextAnnot_SetLineEndingStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_FreeTextAnnot_Set3PointCalloutLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_FreeTextAnnot_Set2PointCalloutLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_FreeTextAnnot_SetDefaultStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LineAnnot_SetPosition(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LineAnnot_SetLeader(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LineAnnot_SetCaption(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Annotation_SetBorderStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ProjectionAnnot_SetExData(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Create3DC3DMeasure(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CreatePD33DMeasure(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DMeasure_SetName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DMeasure_SetColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DMeasure_SetTextSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DC3DMeasure_SetTextBoxSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DC3DMeasure_SetText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DC3DMeasure_SetProjectionAnotation(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Create3DAnnotExData(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DAnnotExData_Set3DMeasurement(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Create3DView(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_3DView_Add3DC3DMeasure(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadPngImageFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadPngImageFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadPngImageFromFile2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadJpegImageFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadJpegImageFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadU3DFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadU3DFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_LoadRaw1BitImageFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadRawImageFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadRawImageFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_AddSMask(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_GetSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_GetSize2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_GetWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_GetHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_GetBitsPerComponent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_GetColorSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_SetColorMask(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Image_SetMaskImage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetInfoAttr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_GetInfoAttr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetInfoDateAttr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetPassword(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetPermission(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetEncryptionMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_SetCompressionMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetFontName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetEncodingName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetUnicodeWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetBBox(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetAscent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetDescent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetXHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_GetCapHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_TextWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Font_MeasureText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_AttachFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_CreateExtGState(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ExtGState_SetAlphaStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ExtGState_SetAlphaFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ExtGState_SetBlendMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_TextWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_MeasureText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetGMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCurrentPos(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCurrentPos2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCurrentTextPos(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCurrentTextPos2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCurrentFont(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCurrentFontSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetTransMatrix(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetLineWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetLineCap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetLineJoin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetMiterLimit(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetDash(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetFlat(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCharSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetWordSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetHorizontalScalling(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetTextLeading(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetTextRenderingMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetTextRaise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetTextRise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetRGBFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetRGBStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCMYKFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetCMYKStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetGrayFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetGrayStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetStrokingColorSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetFillingColorSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetTextMatrix(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GetGStateDepth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetLineWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetLineCap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetLineJoin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetMiterLimit(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetDash(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetFlat(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetExtGState(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GSave(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_GRestore(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Concat(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_MoveTo(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_LineTo(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CurveTo(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CurveTo2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_CurveTo3(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ClosePath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Rectangle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Stroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ClosePathStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Fill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Eofill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_FillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_EofillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ClosePathFillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ClosePathEofillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_EndPath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Clip(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Eoclip(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_BeginText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_EndText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetCharSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetWordSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetHorizontalScalling(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetTextLeading(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetFontAndSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetTextRenderingMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetTextRise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetTextRaise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_MoveTextPos(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_MoveTextPos2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetTextMatrix(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_MoveToNextLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ShowText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ShowTextNextLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ShowTextNextLineEx(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetGrayFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetGrayStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetRGBFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetRGBStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetCMYKFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetCMYKStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_ExecuteXObject(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_New_Content_Stream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Insert_Shared_Content_Stream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_DrawImage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Circle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Ellipse(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_Arc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_TextOut(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_TextRect(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_Page_SetSlideShow(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_ICC_LoadIccFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);
int kxpdf_HPDF_LoadIccProfileFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);

int kxpdf_HPDF_GetVersion(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{

    sg_error = sg_detail = 0;
    const char *r = HPDF_GetVersion();
    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["HPDF_Error_Handler", "user_error_fn", "HPDF_Error_Handler"], ["HPDF_Alloc_Func", "user_alloc_fn", "HPDF_Alloc_Func"], ["HPDF_Free_Func", "user_free_fn", "HPDF_Free_Func"], ["unsigned int", "mem_pool_buf_size", "HPDF_UINT"], ["void *", "user_data", "void *"]],
    "name": "HPDF_NewEx",
    "rtype": {
        "name": "HPDF_Doc",
        "type": "void *"
    }
}
*/
/*
{
    "args": [["HPDF_Error_Handler", "user_error_fn", "HPDF_Error_Handler"], ["void *", "user_data", "void *"]],
    "name": "HPDF_New",
    "rtype": {
        "name": "HPDF_Doc",
        "type": "void *"
    }
}
*/
/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["HPDF_Error_Handler", "user_error_fn", "HPDF_Error_Handler"]],
    "name": "HPDF_SetErrorHandler",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Free(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_Free(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int kxpdf_HPDF_NewDoc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_NewDoc(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_FreeDoc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_FreeDoc(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int kxpdf_HPDF_HasDoc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    signed int r = HPDF_HasDoc(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_FreeDocAll(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_FreeDocAll(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int kxpdf_HPDF_SaveToStream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SaveToStream(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["HPDF_BYTE *", "buf", "HPDF_BYTE *"], ["HPDF_UINT32 *", "size", "HPDF_UINT32 *"]],
    "name": "HPDF_GetContents",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_GetStreamSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_GetStreamSize(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["HPDF_BYTE *", "buf", "HPDF_BYTE *"], ["HPDF_UINT32 *", "size", "HPDF_UINT32 *"]],
    "name": "HPDF_ReadFromStream",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_ResetStream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_ResetStream(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SaveToFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *file_name          */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SaveToFile(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_GetError(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_GetError(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_GetErrorDetail(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_GetErrorDetail(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_ResetError(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_ResetError(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

int kxpdf_HPDF_CheckError(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Error error               */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_CheckError(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetPagesConfiguration(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT page_per_pages       */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetPagesConfiguration(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Page(kx_context_t *ctx, void *r)
{

    /* HPDF_Page */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("GetPageMMgr", rv, kxpdf_HPDF_GetPageMMgr);
    KEX_SET_METHOD("SetWidth", rv, kxpdf_HPDF_Page_SetWidth);
    KEX_SET_METHOD("SetHeight", rv, kxpdf_HPDF_Page_SetHeight);
    KEX_SET_METHOD("SetSize", rv, kxpdf_HPDF_Page_SetSize);
    KEX_SET_METHOD("SetRotate", rv, kxpdf_HPDF_Page_SetRotate);
    KEX_SET_METHOD("SetZoom", rv, kxpdf_HPDF_Page_SetZoom);
    KEX_SET_METHOD("CreateDestination", rv, kxpdf_HPDF_Page_CreateDestination);
    KEX_SET_METHOD("Create3DAnnot", rv, kxpdf_HPDF_Page_Create3DAnnot);
    KEX_SET_METHOD("CreateTextAnnot", rv, kxpdf_HPDF_Page_CreateTextAnnot);
    KEX_SET_METHOD("CreateFreeTextAnnot", rv, kxpdf_HPDF_Page_CreateFreeTextAnnot);
    KEX_SET_METHOD("CreateLineAnnot", rv, kxpdf_HPDF_Page_CreateLineAnnot);
    KEX_SET_METHOD("CreateWidgetAnnot", rv, kxpdf_HPDF_Page_CreateWidgetAnnot);
    KEX_SET_METHOD("CreateLinkAnnot", rv, kxpdf_HPDF_Page_CreateLinkAnnot);
    KEX_SET_METHOD("CreateURILinkAnnot", rv, kxpdf_HPDF_Page_CreateURILinkAnnot);
    KEX_SET_METHOD("CreateHighlightAnnot", rv, kxpdf_HPDF_Page_CreateHighlightAnnot);
    KEX_SET_METHOD("CreateUnderlineAnnot", rv, kxpdf_HPDF_Page_CreateUnderlineAnnot);
    KEX_SET_METHOD("CreateSquigglyAnnot", rv, kxpdf_HPDF_Page_CreateSquigglyAnnot);
    KEX_SET_METHOD("CreateStrikeOutAnnot", rv, kxpdf_HPDF_Page_CreateStrikeOutAnnot);
    KEX_SET_METHOD("CreatePopupAnnot", rv, kxpdf_HPDF_Page_CreatePopupAnnot);
    /* KEX_SET_METHOD("CreateStampAnnot", rv, kxpdf_HPDF_Page_CreateStampAnnot); */
    KEX_SET_METHOD("CreateProjectionAnnot", rv, kxpdf_HPDF_Page_CreateProjectionAnnot);
    KEX_SET_METHOD("CreateSquareAnnot", rv, kxpdf_HPDF_Page_CreateSquareAnnot);
    KEX_SET_METHOD("CreateCircleAnnot", rv, kxpdf_HPDF_Page_CreateCircleAnnot);
    /* KEX_SET_METHOD("Create3DC3DMeasure", rv, kxpdf_HPDF_Page_Create3DC3DMeasure); */
    /* KEX_SET_METHOD("CreatePD33DMeasure", rv, kxpdf_HPDF_Page_CreatePD33DMeasure); */
    KEX_SET_METHOD("Create3DAnnotExData", rv, kxpdf_HPDF_Page_Create3DAnnotExData);
    KEX_SET_METHOD("Create3DView", rv, kxpdf_HPDF_Page_Create3DView);
    KEX_SET_METHOD("TextWidth", rv, kxpdf_HPDF_Page_TextWidth);
    /* KEX_SET_METHOD("MeasureText", rv, kxpdf_HPDF_Page_MeasureText); */
    KEX_SET_METHOD("GetWidth", rv, kxpdf_HPDF_Page_GetWidth);
    KEX_SET_METHOD("GetHeight", rv, kxpdf_HPDF_Page_GetHeight);
    KEX_SET_METHOD("GetGMode", rv, kxpdf_HPDF_Page_GetGMode);
    KEX_SET_METHOD("GetCurrentPos", rv, kxpdf_HPDF_Page_GetCurrentPos);
    /* KEX_SET_METHOD("GetCurrentPos2", rv, kxpdf_HPDF_Page_GetCurrentPos2); */
    KEX_SET_METHOD("GetCurrentTextPos", rv, kxpdf_HPDF_Page_GetCurrentTextPos);
    /* KEX_SET_METHOD("GetCurrentTextPos2", rv, kxpdf_HPDF_Page_GetCurrentTextPos2); */
    KEX_SET_METHOD("GetCurrentFont", rv, kxpdf_HPDF_Page_GetCurrentFont);
    KEX_SET_METHOD("GetCurrentFontSize", rv, kxpdf_HPDF_Page_GetCurrentFontSize);
    /* KEX_SET_METHOD("GetTransMatrix", rv, kxpdf_HPDF_Page_GetTransMatrix); */
    KEX_SET_METHOD("GetLineWidth", rv, kxpdf_HPDF_Page_GetLineWidth);
    KEX_SET_METHOD("GetLineCap", rv, kxpdf_HPDF_Page_GetLineCap);
    KEX_SET_METHOD("GetLineJoin", rv, kxpdf_HPDF_Page_GetLineJoin);
    KEX_SET_METHOD("GetMiterLimit", rv, kxpdf_HPDF_Page_GetMiterLimit);
    /* KEX_SET_METHOD("GetDash", rv, kxpdf_HPDF_Page_GetDash); */
    KEX_SET_METHOD("GetFlat", rv, kxpdf_HPDF_Page_GetFlat);
    KEX_SET_METHOD("GetCharSpace", rv, kxpdf_HPDF_Page_GetCharSpace);
    KEX_SET_METHOD("GetWordSpace", rv, kxpdf_HPDF_Page_GetWordSpace);
    KEX_SET_METHOD("GetHorizontalScalling", rv, kxpdf_HPDF_Page_GetHorizontalScalling);
    KEX_SET_METHOD("GetTextLeading", rv, kxpdf_HPDF_Page_GetTextLeading);
    KEX_SET_METHOD("GetTextRenderingMode", rv, kxpdf_HPDF_Page_GetTextRenderingMode);
    KEX_SET_METHOD("GetTextRaise", rv, kxpdf_HPDF_Page_GetTextRaise);
    KEX_SET_METHOD("GetTextRise", rv, kxpdf_HPDF_Page_GetTextRise);
    /* KEX_SET_METHOD("GetRGBFill", rv, kxpdf_HPDF_Page_GetRGBFill); */
    /* KEX_SET_METHOD("GetRGBStroke", rv, kxpdf_HPDF_Page_GetRGBStroke); */
    /* KEX_SET_METHOD("GetCMYKFill", rv, kxpdf_HPDF_Page_GetCMYKFill); */
    /* KEX_SET_METHOD("GetCMYKStroke", rv, kxpdf_HPDF_Page_GetCMYKStroke); */
    KEX_SET_METHOD("GetGrayFill", rv, kxpdf_HPDF_Page_GetGrayFill);
    KEX_SET_METHOD("GetGrayStroke", rv, kxpdf_HPDF_Page_GetGrayStroke);
    KEX_SET_METHOD("GetStrokingColorSpace", rv, kxpdf_HPDF_Page_GetStrokingColorSpace);
    KEX_SET_METHOD("GetFillingColorSpace", rv, kxpdf_HPDF_Page_GetFillingColorSpace);
    /* KEX_SET_METHOD("GetTextMatrix", rv, kxpdf_HPDF_Page_GetTextMatrix); */
    KEX_SET_METHOD("GetGStateDepth", rv, kxpdf_HPDF_Page_GetGStateDepth);
    KEX_SET_METHOD("SetLineWidth", rv, kxpdf_HPDF_Page_SetLineWidth);
    KEX_SET_METHOD("SetLineCap", rv, kxpdf_HPDF_Page_SetLineCap);
    KEX_SET_METHOD("SetLineJoin", rv, kxpdf_HPDF_Page_SetLineJoin);
    KEX_SET_METHOD("SetMiterLimit", rv, kxpdf_HPDF_Page_SetMiterLimit);
    /* KEX_SET_METHOD("SetDash", rv, kxpdf_HPDF_Page_SetDash); */
    KEX_SET_METHOD("SetFlat", rv, kxpdf_HPDF_Page_SetFlat);
    KEX_SET_METHOD("SetExtGState", rv, kxpdf_HPDF_Page_SetExtGState);
    KEX_SET_METHOD("GSave", rv, kxpdf_HPDF_Page_GSave);
    KEX_SET_METHOD("GRestore", rv, kxpdf_HPDF_Page_GRestore);
    KEX_SET_METHOD("Concat", rv, kxpdf_HPDF_Page_Concat);
    KEX_SET_METHOD("MoveTo", rv, kxpdf_HPDF_Page_MoveTo);
    KEX_SET_METHOD("LineTo", rv, kxpdf_HPDF_Page_LineTo);
    KEX_SET_METHOD("CurveTo", rv, kxpdf_HPDF_Page_CurveTo);
    KEX_SET_METHOD("CurveTo2", rv, kxpdf_HPDF_Page_CurveTo2);
    KEX_SET_METHOD("CurveTo3", rv, kxpdf_HPDF_Page_CurveTo3);
    KEX_SET_METHOD("ClosePath", rv, kxpdf_HPDF_Page_ClosePath);
    KEX_SET_METHOD("Rectangle", rv, kxpdf_HPDF_Page_Rectangle);
    KEX_SET_METHOD("Stroke", rv, kxpdf_HPDF_Page_Stroke);
    KEX_SET_METHOD("ClosePathStroke", rv, kxpdf_HPDF_Page_ClosePathStroke);
    KEX_SET_METHOD("Fill", rv, kxpdf_HPDF_Page_Fill);
    KEX_SET_METHOD("Eofill", rv, kxpdf_HPDF_Page_Eofill);
    KEX_SET_METHOD("FillStroke", rv, kxpdf_HPDF_Page_FillStroke);
    KEX_SET_METHOD("EofillStroke", rv, kxpdf_HPDF_Page_EofillStroke);
    KEX_SET_METHOD("ClosePathFillStroke", rv, kxpdf_HPDF_Page_ClosePathFillStroke);
    KEX_SET_METHOD("ClosePathEofillStroke", rv, kxpdf_HPDF_Page_ClosePathEofillStroke);
    KEX_SET_METHOD("EndPath", rv, kxpdf_HPDF_Page_EndPath);
    KEX_SET_METHOD("Clip", rv, kxpdf_HPDF_Page_Clip);
    KEX_SET_METHOD("Eoclip", rv, kxpdf_HPDF_Page_Eoclip);
    KEX_SET_METHOD("BeginText", rv, kxpdf_HPDF_Page_BeginText);
    KEX_SET_METHOD("EndText", rv, kxpdf_HPDF_Page_EndText);
    KEX_SET_METHOD("SetCharSpace", rv, kxpdf_HPDF_Page_SetCharSpace);
    KEX_SET_METHOD("SetWordSpace", rv, kxpdf_HPDF_Page_SetWordSpace);
    KEX_SET_METHOD("SetHorizontalScalling", rv, kxpdf_HPDF_Page_SetHorizontalScalling);
    KEX_SET_METHOD("SetTextLeading", rv, kxpdf_HPDF_Page_SetTextLeading);
    KEX_SET_METHOD("SetFontAndSize", rv, kxpdf_HPDF_Page_SetFontAndSize);
    KEX_SET_METHOD("SetTextRenderingMode", rv, kxpdf_HPDF_Page_SetTextRenderingMode);
    KEX_SET_METHOD("SetTextRise", rv, kxpdf_HPDF_Page_SetTextRise);
    KEX_SET_METHOD("SetTextRaise", rv, kxpdf_HPDF_Page_SetTextRaise);
    KEX_SET_METHOD("MoveTextPos", rv, kxpdf_HPDF_Page_MoveTextPos);
    KEX_SET_METHOD("MoveTextPos2", rv, kxpdf_HPDF_Page_MoveTextPos2);
    KEX_SET_METHOD("SetTextMatrix", rv, kxpdf_HPDF_Page_SetTextMatrix);
    KEX_SET_METHOD("MoveToNextLine", rv, kxpdf_HPDF_Page_MoveToNextLine);
    KEX_SET_METHOD("ShowText", rv, kxpdf_HPDF_Page_ShowText);
    KEX_SET_METHOD("ShowTextNextLine", rv, kxpdf_HPDF_Page_ShowTextNextLine);
    KEX_SET_METHOD("ShowTextNextLineEx", rv, kxpdf_HPDF_Page_ShowTextNextLineEx);
    KEX_SET_METHOD("SetGrayFill", rv, kxpdf_HPDF_Page_SetGrayFill);
    KEX_SET_METHOD("SetGrayStroke", rv, kxpdf_HPDF_Page_SetGrayStroke);
    KEX_SET_METHOD("SetRGBFill", rv, kxpdf_HPDF_Page_SetRGBFill);
    KEX_SET_METHOD("SetRGBStroke", rv, kxpdf_HPDF_Page_SetRGBStroke);
    KEX_SET_METHOD("SetCMYKFill", rv, kxpdf_HPDF_Page_SetCMYKFill);
    KEX_SET_METHOD("SetCMYKStroke", rv, kxpdf_HPDF_Page_SetCMYKStroke);
    KEX_SET_METHOD("ExecuteXObject", rv, kxpdf_HPDF_Page_ExecuteXObject);
    /* KEX_SET_METHOD("New_Content_Stream", rv, kxpdf_HPDF_Page_New_Content_Stream); */
    KEX_SET_METHOD("Insert_Shared_Content_Stream", rv, kxpdf_HPDF_Page_Insert_Shared_Content_Stream);
    KEX_SET_METHOD("DrawImage", rv, kxpdf_HPDF_Page_DrawImage);
    KEX_SET_METHOD("Circle", rv, kxpdf_HPDF_Page_Circle);
    KEX_SET_METHOD("Ellipse", rv, kxpdf_HPDF_Page_Ellipse);
    KEX_SET_METHOD("Arc", rv, kxpdf_HPDF_Page_Arc);
    KEX_SET_METHOD("TextOut", rv, kxpdf_HPDF_Page_TextOut);
    /* KEX_SET_METHOD("TextRect", rv, kxpdf_HPDF_Page_TextRect); */
    KEX_SET_METHOD("SetSlideShow", rv, kxpdf_HPDF_Page_SetSlideShow);

    return rv;
}

int kxpdf_HPDF_GetPageByIndex(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT index                */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetPageByIndex(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Page(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_MMgr(kx_context_t *ctx, void *r)
{

    /* HPDF_MMgr */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("Annot_Set3DView", rv, kxpdf_HPDF_Annot_Set3DView);

    return rv;
}

int kxpdf_HPDF_GetPageMMgr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetPageMMgr(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_MMgr(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_GetPageLayout(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_GetPageLayout(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetPageLayout(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_PageLayout layout         */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetPageLayout(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_GetPageMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_GetPageMode(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetPageMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_PageMode mode             */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetPageMode(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_GetViewerPreference(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_GetViewerPreference(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetViewerPreference(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT value                */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetViewerPreference(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetOpenAction(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Destination open_action   */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetOpenAction(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_GetCurrentPage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetCurrentPage(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Page(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_AddPage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_AddPage(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Page(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_InsertPage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    void *r = HPDF_InsertPage(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Page(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_SetWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetWidth(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetHeight(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_PageSizes size            */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_PageDirection direction   */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetSize(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetRotate(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT16 angle              */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetRotate(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetZoom(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL zoom                 */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetZoom(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Font(kx_context_t *ctx, void *r)
{

    /* HPDF_Font */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("GetFontName", rv, kxpdf_HPDF_Font_GetFontName);
    KEX_SET_METHOD("GetEncodingName", rv, kxpdf_HPDF_Font_GetEncodingName);
    KEX_SET_METHOD("GetUnicodeWidth", rv, kxpdf_HPDF_Font_GetUnicodeWidth);
    KEX_SET_METHOD("GetBBox", rv, kxpdf_HPDF_Font_GetBBox);
    KEX_SET_METHOD("GetAscent", rv, kxpdf_HPDF_Font_GetAscent);
    KEX_SET_METHOD("GetDescent", rv, kxpdf_HPDF_Font_GetDescent);
    KEX_SET_METHOD("GetXHeight", rv, kxpdf_HPDF_Font_GetXHeight);
    KEX_SET_METHOD("GetCapHeight", rv, kxpdf_HPDF_Font_GetCapHeight);
    /* KEX_SET_METHOD("TextWidth", rv, kxpdf_HPDF_Font_TextWidth); */
    /* KEX_SET_METHOD("MeasureText", rv, kxpdf_HPDF_Font_MeasureText); */

    return rv;
}

int kxpdf_HPDF_GetFont(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *font_name          */ const char *v2 = get_arg_str(2, args, ctx);
    /* const char *encoding_name      */ const char *v3 = get_arg_str(3, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetFont(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Font(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LoadType1FontFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *afm_file_name      */ const char *v2 = get_arg_str(2, args, ctx);
    /* const char *data_file_name     */ const char *v3 = get_arg_str(3, args, ctx);

    sg_error = sg_detail = 0;
    const char *r = HPDF_LoadType1FontFromFile(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_FontDef(kx_context_t *ctx, void *r)
{

    /* HPDF_FontDef */
    KX_MAKE_VOIDP(rv, r);

    return rv;
}

int kxpdf_HPDF_GetTTFontDefFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *file_name          */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_BOOL embedding            */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetTTFontDefFromFile(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_FontDef(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LoadTTFontFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *file_name          */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_BOOL embedding            */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    const char *r = HPDF_LoadTTFontFromFile(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LoadTTFontFromFile2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *file_name          */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_UINT index                */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_BOOL embedding            */ int64_t v4 = get_arg_int(4, args, ctx);

    sg_error = sg_detail = 0;
    const char *r = HPDF_LoadTTFontFromFile2(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_AddPageLabel(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT page_num             */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_PageNumStyle style        */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_UINT first_page           */ int64_t v4 = get_arg_int(4, args, ctx);
    /* const char *prefix             */ const char *v5 = get_arg_str(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_AddPageLabel(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseJPFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseJPFonts(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseKRFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseKRFonts(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseCNSFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseCNSFonts(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseCNTFonts(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseCNTFonts(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Outline(kx_context_t *ctx, void *r)
{

    /* HPDF_Outline */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("SetOpened", rv, kxpdf_HPDF_Outline_SetOpened);
    KEX_SET_METHOD("SetDestination", rv, kxpdf_HPDF_Outline_SetDestination);

    return rv;
}

int kxpdf_HPDF_CreateOutline(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Outline parent            */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* const char *title              */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_CreateOutline(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Outline(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Outline_SetOpened(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Outline outline           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_BOOL opened               */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Outline_SetOpened(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Outline_SetDestination(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Outline outline           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Outline_SetDestination(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Destination(kx_context_t *ctx, void *r)
{

    /* HPDF_Destination */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("SetXYZ", rv, kxpdf_HPDF_Destination_SetXYZ);
    KEX_SET_METHOD("SetFit", rv, kxpdf_HPDF_Destination_SetFit);
    KEX_SET_METHOD("SetFitH", rv, kxpdf_HPDF_Destination_SetFitH);
    KEX_SET_METHOD("SetFitV", rv, kxpdf_HPDF_Destination_SetFitV);
    KEX_SET_METHOD("SetFitR", rv, kxpdf_HPDF_Destination_SetFitR);
    KEX_SET_METHOD("SetFitB", rv, kxpdf_HPDF_Destination_SetFitB);
    KEX_SET_METHOD("SetFitBH", rv, kxpdf_HPDF_Destination_SetFitBH);
    KEX_SET_METHOD("SetFitBV", rv, kxpdf_HPDF_Destination_SetFitBV);

    return rv;
}

int kxpdf_HPDF_Page_CreateDestination(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateDestination(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Destination(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Destination_SetXYZ(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL left                 */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL top                  */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL zoom                 */ float v4 = (float)get_arg_dbl(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetXYZ(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFit(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFit(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFitH(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL top                  */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFitH(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFitV(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL left                 */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFitV(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFitR(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL left                 */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL bottom               */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL right                */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL top                  */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFitR(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFitB(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFitB(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFitBH(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL top                  */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFitBH(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Destination_SetFitBV(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL left                 */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Destination_SetFitBV(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Encoder(kx_context_t *ctx, void *r)
{

    /* HPDF_Encoder */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("GetType", rv, kxpdf_HPDF_Encoder_GetType);
    KEX_SET_METHOD("GetByteType", rv, kxpdf_HPDF_Encoder_GetByteType);
    KEX_SET_METHOD("GetUnicode", rv, kxpdf_HPDF_Encoder_GetUnicode);
    KEX_SET_METHOD("GetWritingMode", rv, kxpdf_HPDF_Encoder_GetWritingMode);

    return rv;
}

int kxpdf_HPDF_GetEncoder(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *encoding_name      */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetEncoder(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Encoder(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_GetCurrentEncoder(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_GetCurrentEncoder(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Encoder(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_SetCurrentEncoder(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *encoding_name      */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetCurrentEncoder(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Encoder_GetType(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Encoder_GetType(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Encoder_GetByteType(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *text               */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_UINT index                */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    int r = HPDF_Encoder_GetByteType(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Encoder_GetUnicode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT16 code               */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint16_t r = HPDF_Encoder_GetUnicode(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Encoder_GetWritingMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Encoder_GetWritingMode(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseJPEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseJPEncodings(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseKREncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseKREncodings(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseCNSEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseCNSEncodings(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseCNTEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseCNTEncodings(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_UseUTFEncodings(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_UseUTFEncodings(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["void *", "page", "HPDF_Page"], ["HPDF_Rect", "rect", "HPDF_Rect"], ["void *", "image", "HPDF_Image"], ["HPDF_Boolean", "zoom", "HPDF_Boolean"]],
    "name": "HPDF_Page_CreateXObjectFromImage",
    "rtype": {
        "name": "HPDF_XObject",
        "type": "void *"
    }
}
*/
static kx_obj_t *kxpdf_append_method_HPDF_XObject(kx_context_t *ctx, void *r)
{

    /* HPDF_XObject */
    KX_MAKE_VOIDP(rv, r);

    return rv;
}

int kxpdf_HPDF_Page_CreateXObjectAsWhiteRect(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateXObjectAsWhiteRect(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_XObject(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Annotation(kx_context_t *ctx, void *r)
{

    /* HPDF_Annotation */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("LinkAnnot_SetHighlightMode", rv, kxpdf_HPDF_LinkAnnot_SetHighlightMode);
    KEX_SET_METHOD("LinkAnnot_SetJavaScript", rv, kxpdf_HPDF_LinkAnnot_SetJavaScript);
    KEX_SET_METHOD("LinkAnnot_SetBorderStyle", rv, kxpdf_HPDF_LinkAnnot_SetBorderStyle);
    KEX_SET_METHOD("TextAnnot_SetIcon", rv, kxpdf_HPDF_TextAnnot_SetIcon);
    KEX_SET_METHOD("TextAnnot_SetOpened", rv, kxpdf_HPDF_TextAnnot_SetOpened);
    /* KEX_SET_METHOD("Annot_SetRGBColor", rv, kxpdf_HPDF_Annot_SetRGBColor); */
    /* KEX_SET_METHOD("Annot_SetCMYKColor", rv, kxpdf_HPDF_Annot_SetCMYKColor); */
    KEX_SET_METHOD("Annot_SetGrayColor", rv, kxpdf_HPDF_Annot_SetGrayColor);
    KEX_SET_METHOD("Annot_SetNoColor", rv, kxpdf_HPDF_Annot_SetNoColor);
    KEX_SET_METHOD("MarkupAnnot_SetTitle", rv, kxpdf_HPDF_MarkupAnnot_SetTitle);
    KEX_SET_METHOD("MarkupAnnot_SetSubject", rv, kxpdf_HPDF_MarkupAnnot_SetSubject);
    /* KEX_SET_METHOD("MarkupAnnot_SetCreationDate", rv, kxpdf_HPDF_MarkupAnnot_SetCreationDate); */
    KEX_SET_METHOD("MarkupAnnot_SetTransparency", rv, kxpdf_HPDF_MarkupAnnot_SetTransparency);
    KEX_SET_METHOD("MarkupAnnot_SetIntent", rv, kxpdf_HPDF_MarkupAnnot_SetIntent);
    KEX_SET_METHOD("MarkupAnnot_SetPopup", rv, kxpdf_HPDF_MarkupAnnot_SetPopup);
    KEX_SET_METHOD("MarkupAnnot_SetRectDiff", rv, kxpdf_HPDF_MarkupAnnot_SetRectDiff);
    KEX_SET_METHOD("MarkupAnnot_SetCloudEffect", rv, kxpdf_HPDF_MarkupAnnot_SetCloudEffect);
    /* KEX_SET_METHOD("MarkupAnnot_SetInteriorRGBColor", rv, kxpdf_HPDF_MarkupAnnot_SetInteriorRGBColor); */
    /* KEX_SET_METHOD("MarkupAnnot_SetInteriorCMYKColor", rv, kxpdf_HPDF_MarkupAnnot_SetInteriorCMYKColor); */
    KEX_SET_METHOD("MarkupAnnot_SetInteriorGrayColor", rv, kxpdf_HPDF_MarkupAnnot_SetInteriorGrayColor);
    KEX_SET_METHOD("MarkupAnnot_SetInteriorTransparent", rv, kxpdf_HPDF_MarkupAnnot_SetInteriorTransparent);
    KEX_SET_METHOD("TextMarkupAnnot_SetQuadPoints", rv, kxpdf_HPDF_TextMarkupAnnot_SetQuadPoints);
    KEX_SET_METHOD("PopupAnnot_SetOpened", rv, kxpdf_HPDF_PopupAnnot_SetOpened);
    KEX_SET_METHOD("SetLineEndingStyle", rv, kxpdf_HPDF_FreeTextAnnot_SetLineEndingStyle);
    KEX_SET_METHOD("Set3PointCalloutLine", rv, kxpdf_HPDF_FreeTextAnnot_Set3PointCalloutLine);
    KEX_SET_METHOD("Set2PointCalloutLine", rv, kxpdf_HPDF_FreeTextAnnot_Set2PointCalloutLine);
    KEX_SET_METHOD("SetDefaultStyle", rv, kxpdf_HPDF_FreeTextAnnot_SetDefaultStyle);
    KEX_SET_METHOD("LineAnnot_SetPosition", rv, kxpdf_HPDF_LineAnnot_SetPosition);
    KEX_SET_METHOD("LineAnnot_SetLeader", rv, kxpdf_HPDF_LineAnnot_SetLeader);
    /* KEX_SET_METHOD("LineAnnot_SetCaption", rv, kxpdf_HPDF_LineAnnot_SetCaption); */
    KEX_SET_METHOD("Annotation_SetBorderStyle", rv, kxpdf_HPDF_Annotation_SetBorderStyle);
    KEX_SET_METHOD("ProjectionAnnot_SetExData", rv, kxpdf_HPDF_ProjectionAnnot_SetExData);

    return rv;
}

int kxpdf_HPDF_Page_Create3DAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* HPDF_BOOL tb                   */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_BOOL np                   */ int64_t v4 = get_arg_int(4, args, ctx);
    /* HPDF_U3D u3d                   */ KX_GET_VOIDP(args, ctx, v5, 5);
    /* HPDF_Image ap                  */ KX_GET_VOIDP(args, ctx, v6, 6);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_Create3DAnnot(v1, v2, v3, v4, v5, v6);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateTextAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateTextAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateFreeTextAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateFreeTextAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateLineAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *text               */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateLineAnnot(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateWidgetAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateWidgetAnnot(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateLinkAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* HPDF_Destination dst           */ KX_GET_VOIDP(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateLinkAnnot(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateURILinkAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *uri                */ const char *v3 = get_arg_str(3, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateURILinkAnnot(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateHighlightAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateHighlightAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateUnderlineAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateUnderlineAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateSquigglyAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateSquigglyAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateStrikeOutAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateStrikeOutAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreatePopupAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* HPDF_Annotation parent         */ KX_GET_VOIDP(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreatePopupAnnot(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["HPDF_Rect", "rect", "HPDF_Rect"], ["HPDF_StampAnnotName", "name", "HPDF_StampAnnotName"], ["const char *", "text", "const char *"], ["void *", "encoder", "HPDF_Encoder"]],
    "name": "HPDF_Page_CreateStampAnnot",
    "rtype": {
        "name": "HPDF_Annotation",
        "type": "void *"
    }
}
*/
int kxpdf_HPDF_Page_CreateProjectionAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateProjectionAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateSquareAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateSquareAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_CreateCircleAnnot(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);
    /* const char *text               */ const char *v3 = get_arg_str(3, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_CreateCircleAnnot(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Annotation(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LinkAnnot_SetHighlightMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_AnnotHighlightMode mode   */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_LinkAnnot_SetHighlightMode(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_LinkAnnot_SetJavaScript(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_JavaScript javascript     */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_LinkAnnot_SetJavaScript(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_LinkAnnot_SetBorderStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL width                */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_UINT16 dash_on            */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_UINT16 dash_off           */ int64_t v4 = get_arg_int(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_LinkAnnot_SetBorderStyle(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_TextAnnot_SetIcon(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_AnnotIcon icon            */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_TextAnnot_SetIcon(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_TextAnnot_SetOpened(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_BOOL opened               */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_TextAnnot_SetOpened(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "annot", "HPDF_Annotation"], ["HPDF_RGBColor", "color", "HPDF_RGBColor"]],
    "name": "HPDF_Annot_SetRGBColor",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
/*
{
    "args": [["void *", "annot", "HPDF_Annotation"], ["HPDF_CMYKColor", "color", "HPDF_CMYKColor"]],
    "name": "HPDF_Annot_SetCMYKColor",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Annot_SetGrayColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL color                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Annot_SetGrayColor(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Annot_SetNoColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Annot_SetNoColor(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetTitle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *name               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetTitle(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetSubject(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *name               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetSubject(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "annot", "HPDF_Annotation"], ["HPDF_Date", "value", "HPDF_Date"]],
    "name": "HPDF_MarkupAnnot_SetCreationDate",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_MarkupAnnot_SetTransparency(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetTransparency(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetIntent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_AnnotIntent intent        */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetIntent(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetPopup(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Annotation popup          */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetPopup(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetRectDiff(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Rect rect                 */ KX_GET_RECT(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetRectDiff(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetCloudEffect(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_INT cloudIntensity        */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetCloudEffect(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "annot", "HPDF_Annotation"], ["HPDF_RGBColor", "color", "HPDF_RGBColor"]],
    "name": "HPDF_MarkupAnnot_SetInteriorRGBColor",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
/*
{
    "args": [["void *", "annot", "HPDF_Annotation"], ["HPDF_CMYKColor", "color", "HPDF_CMYKColor"]],
    "name": "HPDF_MarkupAnnot_SetInteriorCMYKColor",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_MarkupAnnot_SetInteriorGrayColor(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL color                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetInteriorGrayColor(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_MarkupAnnot_SetInteriorTransparent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_MarkupAnnot_SetInteriorTransparent(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_TextMarkupAnnot_SetQuadPoints(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Point lb                  */ KX_GET_POINT(args, ctx, v2, 2);
    /* HPDF_Point rb                  */ KX_GET_POINT(args, ctx, v3, 3);
    /* HPDF_Point rt                  */ KX_GET_POINT(args, ctx, v4, 4);
    /* HPDF_Point lt                  */ KX_GET_POINT(args, ctx, v5, 5);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_TextMarkupAnnot_SetQuadPoints(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Annot_Set3DView(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_MMgr mmgr                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_Annotation annot3d        */ KX_GET_VOIDP(args, ctx, v3, 3);
    /* HPDF_Dict view                 */ KX_GET_VOIDP(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Annot_Set3DView(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_PopupAnnot_SetOpened(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_BOOL opened               */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_PopupAnnot_SetOpened(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_FreeTextAnnot_SetLineEndingStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_LineAnnotEndingStyle startStyle */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_LineAnnotEndingStyle endStyle */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_FreeTextAnnot_SetLineEndingStyle(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_FreeTextAnnot_Set3PointCalloutLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Point startPoint          */ KX_GET_POINT(args, ctx, v2, 2);
    /* HPDF_Point kneePoint           */ KX_GET_POINT(args, ctx, v3, 3);
    /* HPDF_Point endPoint            */ KX_GET_POINT(args, ctx, v4, 4);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_FreeTextAnnot_Set3PointCalloutLine(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_FreeTextAnnot_Set2PointCalloutLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Point startPoint          */ KX_GET_POINT(args, ctx, v2, 2);
    /* HPDF_Point endPoint            */ KX_GET_POINT(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_FreeTextAnnot_Set2PointCalloutLine(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_FreeTextAnnot_SetDefaultStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *style              */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_FreeTextAnnot_SetDefaultStyle(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_LineAnnot_SetPosition(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Point startPoint          */ KX_GET_POINT(args, ctx, v2, 2);
    /* HPDF_LineAnnotEndingStyle startStyle */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_Point endPoint            */ KX_GET_POINT(args, ctx, v4, 4);
    /* HPDF_LineAnnotEndingStyle endStyle */ int64_t v5 = get_arg_int(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_LineAnnot_SetPosition(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_LineAnnot_SetLeader(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_INT leaderLen             */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_INT leaderExtLen          */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_INT leaderOffsetLen       */ int64_t v4 = get_arg_int(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_LineAnnot_SetLeader(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "annot", "HPDF_Annotation"], ["signed int", "showCaption", "HPDF_BOOL"], ["HPDF_LineAnnotCapPosition", "position", "HPDF_LineAnnotCapPosition"], ["int", "horzOffset", "HPDF_INT"], ["int", "vertOffset", "HPDF_INT"]],
    "name": "HPDF_LineAnnot_SetCaption",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Annotation_SetBorderStyle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_BSSubtype subtype         */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_REAL width                */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_UINT16 dash_on            */ int64_t v4 = get_arg_int(4, args, ctx);
    /* HPDF_UINT16 dash_off           */ int64_t v5 = get_arg_int(5, args, ctx);
    /* HPDF_UINT16 dash_phase         */ int64_t v6 = get_arg_int(6, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Annotation_SetBorderStyle(v1, v2, v3, v4, v5, v6);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_ProjectionAnnot_SetExData(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Annotation annot          */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_ExData exdata             */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_ProjectionAnnot_SetExData(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["HPDF_Point3D", "firstanchorpoint", "HPDF_Point3D"], ["HPDF_Point3D", "textanchorpoint", "HPDF_Point3D"]],
    "name": "HPDF_Page_Create3DC3DMeasure",
    "rtype": {
        "name": "HPDF_3DMeasure",
        "type": "void *"
    }
}
*/
/*
{
    "args": [["void *", "page", "HPDF_Page"], ["HPDF_Point3D", "annotationPlaneNormal", "HPDF_Point3D"], ["HPDF_Point3D", "firstAnchorPoint", "HPDF_Point3D"], ["HPDF_Point3D", "secondAnchorPoint", "HPDF_Point3D"], ["HPDF_Point3D", "leaderLinesDirection", "HPDF_Point3D"], ["HPDF_Point3D", "measurementValuePoint", "HPDF_Point3D"], ["HPDF_Point3D", "textYDirection", "HPDF_Point3D"], ["float", "value", "HPDF_REAL"], ["const char *", "unitsString", "const char *"]],
    "name": "HPDF_Page_CreatePD33DMeasure",
    "rtype": {
        "name": "HPDF_3DMeasure",
        "type": "void *"
    }
}
*/
int kxpdf_HPDF_3DMeasure_SetName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *name               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DMeasure_SetName(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "measure", "HPDF_3DMeasure"], ["HPDF_RGBColor", "color", "HPDF_RGBColor"]],
    "name": "HPDF_3DMeasure_SetColor",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_3DMeasure_SetTextSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL textsize             */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DMeasure_SetTextSize(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_3DC3DMeasure_SetTextBoxSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_INT32 x                   */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_INT32 y                   */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DC3DMeasure_SetTextBoxSize(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_3DC3DMeasure_SetText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *text               */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_Encoder encoder           */ KX_GET_VOIDP(args, ctx, v3, 3);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DC3DMeasure_SetText(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_3DC3DMeasure_SetProjectionAnotation(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Annotation projectionanotation */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DC3DMeasure_SetProjectionAnotation(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_ExData(kx_context_t *ctx, void *r)
{

    /* HPDF_ExData */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("Set3DMeasurement", rv, kxpdf_HPDF_3DAnnotExData_Set3DMeasurement);

    return rv;
}

int kxpdf_HPDF_Page_Create3DAnnotExData(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_Create3DAnnotExData(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_ExData(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_3DAnnotExData_Set3DMeasurement(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_ExData exdata             */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DAnnotExData_Set3DMeasurement(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_Dict(kx_context_t *ctx, void *r)
{

    /* HPDF_Dict */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("Add3DC3DMeasure", rv, kxpdf_HPDF_3DView_Add3DC3DMeasure);

    return rv;
}

int kxpdf_HPDF_Page_Create3DView(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_U3D u3d                   */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_Annotation annot3d        */ KX_GET_VOIDP(args, ctx, v3, 3);
    /* const char *name               */ const char *v4 = get_arg_str(4, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_Create3DView(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Dict(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_3DView_Add3DC3DMeasure(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Dict view                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_3DMeasure measure         */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_3DView_Add3DC3DMeasure(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["const HPDF_BYTE *", "buffer", "const HPDF_BYTE *"], ["unsigned int", "size", "HPDF_UINT"]],
    "name": "HPDF_LoadPngImageFromMem",
    "rtype": {
        "name": "HPDF_Image",
        "type": "void *"
    }
}
*/
static kx_obj_t *kxpdf_append_method_HPDF_Image(kx_context_t *ctx, void *r)
{

    /* HPDF_Image */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("AddSMask", rv, kxpdf_HPDF_Image_AddSMask);
    KEX_SET_METHOD("GetSize", rv, kxpdf_HPDF_Image_GetSize);
    /* KEX_SET_METHOD("GetSize2", rv, kxpdf_HPDF_Image_GetSize2); */
    KEX_SET_METHOD("GetWidth", rv, kxpdf_HPDF_Image_GetWidth);
    KEX_SET_METHOD("GetHeight", rv, kxpdf_HPDF_Image_GetHeight);
    KEX_SET_METHOD("GetBitsPerComponent", rv, kxpdf_HPDF_Image_GetBitsPerComponent);
    KEX_SET_METHOD("GetColorSpace", rv, kxpdf_HPDF_Image_GetColorSpace);
    KEX_SET_METHOD("SetColorMask", rv, kxpdf_HPDF_Image_SetColorMask);
    KEX_SET_METHOD("SetMaskImage", rv, kxpdf_HPDF_Image_SetMaskImage);

    return rv;
}

int kxpdf_HPDF_LoadPngImageFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *filename           */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_LoadPngImageFromFile(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Image(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LoadPngImageFromFile2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *filename           */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_LoadPngImageFromFile2(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Image(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LoadJpegImageFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *filename           */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_LoadJpegImageFromFile(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Image(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["const HPDF_BYTE *", "buffer", "const HPDF_BYTE *"], ["unsigned int", "size", "HPDF_UINT"]],
    "name": "HPDF_LoadJpegImageFromMem",
    "rtype": {
        "name": "HPDF_Image",
        "type": "void *"
    }
}
*/
int kxpdf_HPDF_LoadU3DFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *filename           */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_LoadU3DFromFile(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Image(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["const HPDF_BYTE *", "buffer", "const HPDF_BYTE *"], ["unsigned int", "size", "HPDF_UINT"]],
    "name": "HPDF_LoadU3DFromMem",
    "rtype": {
        "name": "HPDF_Image",
        "type": "void *"
    }
}
*/
/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["const HPDF_BYTE *", "buf", "const HPDF_BYTE *"], ["unsigned int", "width", "HPDF_UINT"], ["unsigned int", "height", "HPDF_UINT"], ["unsigned int", "line_width", "HPDF_UINT"], ["signed int", "black_is1", "HPDF_BOOL"], ["signed int", "top_is_first", "HPDF_BOOL"]],
    "name": "HPDF_Image_LoadRaw1BitImageFromMem",
    "rtype": {
        "name": "HPDF_Image",
        "type": "void *"
    }
}
*/
int kxpdf_HPDF_LoadRawImageFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *filename           */ const char *v2 = get_arg_str(2, args, ctx);
    /* HPDF_UINT width                */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_UINT height               */ int64_t v4 = get_arg_int(4, args, ctx);
    /* HPDF_ColorSpace color_space    */ int64_t v5 = get_arg_int(5, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_LoadRawImageFromFile(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Image(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["const HPDF_BYTE *", "buf", "const HPDF_BYTE *"], ["unsigned int", "width", "HPDF_UINT"], ["unsigned int", "height", "HPDF_UINT"], ["int", "color_space", "HPDF_ColorSpace"], ["unsigned int", "bits_per_component", "HPDF_UINT"]],
    "name": "HPDF_LoadRawImageFromMem",
    "rtype": {
        "name": "HPDF_Image",
        "type": "void *"
    }
}
*/
int kxpdf_HPDF_Image_AddSMask(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Image smask               */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Image_AddSMask(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Image_GetSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_Point r = HPDF_Image_GetSize(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_MAKE_POINT(rv, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "image", "HPDF_Image"], ["HPDF_Point *", "size", "HPDF_Point *"]],
    "name": "HPDF_Image_GetSize2",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Image_GetWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_Image_GetWidth(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Image_GetHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_Image_GetHeight(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Image_GetBitsPerComponent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_Image_GetBitsPerComponent(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Image_GetColorSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    const char *r = HPDF_Image_GetColorSpace(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Image_SetColorMask(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT rmin                 */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_UINT rmax                 */ int64_t v3 = get_arg_int(3, args, ctx);
    /* HPDF_UINT gmin                 */ int64_t v4 = get_arg_int(4, args, ctx);
    /* HPDF_UINT gmax                 */ int64_t v5 = get_arg_int(5, args, ctx);
    /* HPDF_UINT bmin                 */ int64_t v6 = get_arg_int(6, args, ctx);
    /* HPDF_UINT bmax                 */ int64_t v7 = get_arg_int(7, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Image_SetColorMask(v1, v2, v3, v4, v5, v6, v7);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Image_SetMaskImage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Image mask_image          */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Image_SetMaskImage(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetInfoAttr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_InfoType type             */ int64_t v2 = get_arg_int(2, args, ctx);
    /* const char *value              */ const char *v3 = get_arg_str(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetInfoAttr(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_GetInfoAttr(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_InfoType type             */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    const char *r = HPDF_GetInfoAttr(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "pdf", "HPDF_Doc"], ["int", "type", "HPDF_InfoType"], ["HPDF_Date", "value", "HPDF_Date"]],
    "name": "HPDF_SetInfoDateAttr",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_SetPassword(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *owner_passwd       */ const char *v2 = get_arg_str(2, args, ctx);
    /* const char *user_passwd        */ const char *v3 = get_arg_str(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetPassword(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetPermission(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT permission           */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetPermission(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetEncryptionMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_EncryptMode mode          */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_UINT key_len              */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetEncryptionMode(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_SetCompressionMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UINT mode                 */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_SetCompressionMode(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Font_GetFontName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    const char *r = HPDF_Font_GetFontName(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Font_GetEncodingName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    const char *r = HPDF_Font_GetEncodingName(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    kstr_t *rv = allocate_str(ctx);
    ks_append(rv, r);
    KX_ADJST_STACK();
    push_sv(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Font_GetUnicodeWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_UNICODE code              */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    int r = HPDF_Font_GetUnicodeWidth(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Font_GetBBox(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_Rect r = HPDF_Font_GetBBox(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_MAKE_RECT(rv, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Font_GetAscent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Font_GetAscent(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Font_GetDescent(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Font_GetDescent(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Font_GetXHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_Font_GetXHeight(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Font_GetCapHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_Font_GetCapHeight(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "font", "HPDF_Font"], ["const HPDF_BYTE *", "text", "const HPDF_BYTE *"], ["unsigned int", "len", "HPDF_UINT"]],
    "name": "HPDF_Font_TextWidth",
    "rtype": {
        "name": "HPDF_TextWidth",
        "type": "HPDF_TextWidth"
    }
}
*/
/*
{
    "args": [["void *", "font", "HPDF_Font"], ["const HPDF_BYTE *", "text", "const HPDF_BYTE *"], ["unsigned int", "len", "HPDF_UINT"], ["float", "width", "HPDF_REAL"], ["float", "font_size", "HPDF_REAL"], ["float", "char_space", "HPDF_REAL"], ["float", "word_space", "HPDF_REAL"], ["signed int", "wordwrap", "HPDF_BOOL"], ["HPDF_REAL *", "real_width", "HPDF_REAL *"]],
    "name": "HPDF_Font_MeasureText",
    "rtype": {
        "name": "HPDF_UINT",
        "type": "unsigned int"
    }
}
*/
static kx_obj_t *kxpdf_append_method_HPDF_EmbeddedFile(kx_context_t *ctx, void *r)
{

    /* HPDF_EmbeddedFile */
    KX_MAKE_VOIDP(rv, r);

    return rv;
}

int kxpdf_HPDF_AttachFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *file               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_AttachFile(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_EmbeddedFile(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_ExtGState(kx_context_t *ctx, void *r)
{

    /* HPDF_ExtGState */
    KX_MAKE_VOIDP(rv, r);
    KEX_SET_METHOD("SetAlphaStroke", rv, kxpdf_HPDF_ExtGState_SetAlphaStroke);
    KEX_SET_METHOD("SetAlphaFill", rv, kxpdf_HPDF_ExtGState_SetAlphaFill);
    KEX_SET_METHOD("SetBlendMode", rv, kxpdf_HPDF_ExtGState_SetBlendMode);

    return rv;
}

int kxpdf_HPDF_CreateExtGState(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_CreateExtGState(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_ExtGState(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_ExtGState_SetAlphaStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_ExtGState ext_gstate      */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_ExtGState_SetAlphaStroke(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_ExtGState_SetAlphaFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_ExtGState ext_gstate      */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_ExtGState_SetAlphaFill(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_ExtGState_SetBlendMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_ExtGState ext_gstate      */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_BlendMode mode            */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_ExtGState_SetBlendMode(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_TextWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *text               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_TextWidth(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["const char *", "text", "const char *"], ["float", "width", "HPDF_REAL"], ["signed int", "wordwrap", "HPDF_BOOL"], ["HPDF_REAL *", "real_width", "HPDF_REAL *"]],
    "name": "HPDF_Page_MeasureText",
    "rtype": {
        "name": "HPDF_UINT",
        "type": "unsigned int"
    }
}
*/
int kxpdf_HPDF_Page_GetWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetWidth(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetHeight(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetHeight(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetGMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint16_t r = HPDF_Page_GetGMode(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GetCurrentPos(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_Point r = HPDF_Page_GetCurrentPos(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_MAKE_POINT(rv, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["HPDF_Point *", "pos", "HPDF_Point *"]],
    "name": "HPDF_Page_GetCurrentPos2",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Page_GetCurrentTextPos(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    HPDF_Point r = HPDF_Page_GetCurrentTextPos(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_MAKE_POINT(rv, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["HPDF_Point *", "pos", "HPDF_Point *"]],
    "name": "HPDF_Page_GetCurrentTextPos2",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Page_GetCurrentFont(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    void *r = HPDF_Page_GetCurrentFont(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_Font(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_Page_GetCurrentFontSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetCurrentFontSize(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetTransMatrix",
    "rtype": {
        "name": "HPDF_TransMatrix",
        "type": null
    }
}
*/
int kxpdf_HPDF_Page_GetLineWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetLineWidth(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetLineCap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Page_GetLineCap(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GetLineJoin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Page_GetLineJoin(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GetMiterLimit(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetMiterLimit(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetDash",
    "rtype": {
        "name": "HPDF_DashMode",
        "type": null
    }
}
*/
int kxpdf_HPDF_Page_GetFlat(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetFlat(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetCharSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetCharSpace(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetWordSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetWordSpace(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetHorizontalScalling(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetHorizontalScalling(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetTextLeading(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetTextLeading(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetTextRenderingMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Page_GetTextRenderingMode(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GetTextRaise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetTextRaise(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetTextRise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetTextRise(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetRGBFill",
    "rtype": {
        "name": "HPDF_RGBColor",
        "type": null
    }
}
*/
/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetRGBStroke",
    "rtype": {
        "name": "HPDF_RGBColor",
        "type": null
    }
}
*/
/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetCMYKFill",
    "rtype": {
        "name": "HPDF_CMYKColor",
        "type": null
    }
}
*/
/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetCMYKStroke",
    "rtype": {
        "name": "HPDF_CMYKColor",
        "type": null
    }
}
*/
int kxpdf_HPDF_Page_GetGrayFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetGrayFill(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetGrayStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    float r = HPDF_Page_GetGrayStroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_d(ctx->stack, (double)r);
    return 0;
}

int kxpdf_HPDF_Page_GetStrokingColorSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Page_GetStrokingColorSpace(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GetFillingColorSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    int r = HPDF_Page_GetFillingColorSpace(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"]],
    "name": "HPDF_Page_GetTextMatrix",
    "rtype": {
        "name": "HPDF_TransMatrix",
        "type": null
    }
}
*/
int kxpdf_HPDF_Page_GetGStateDepth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    unsigned int r = HPDF_Page_GetGStateDepth(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetLineWidth(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL line_width           */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetLineWidth(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetLineCap(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_LineCap line_cap          */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetLineCap(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetLineJoin(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_LineJoin line_join        */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetLineJoin(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetMiterLimit(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL miter_limit          */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetMiterLimit(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["const HPDF_UINT16 *", "dash_ptn", "const HPDF_UINT16 *"], ["unsigned int", "num_param", "HPDF_UINT"], ["unsigned int", "phase", "HPDF_UINT"]],
    "name": "HPDF_Page_SetDash",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Page_SetFlat(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL flatness             */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetFlat(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetExtGState(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_ExtGState ext_gstate      */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetExtGState(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GSave(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_GSave(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_GRestore(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_GRestore(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Concat(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL a                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL b                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL c                    */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL d                    */ float v5 = (float)get_arg_dbl(5, args, ctx);
    /* HPDF_REAL x                    */ float v6 = (float)get_arg_dbl(6, args, ctx);
    /* HPDF_REAL y                    */ float v7 = (float)get_arg_dbl(7, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Concat(v1, v2, v3, v4, v5, v6, v7);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_MoveTo(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_MoveTo(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_LineTo(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_LineTo(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_CurveTo(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x1                   */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y1                   */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL x2                   */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL y2                   */ float v5 = (float)get_arg_dbl(5, args, ctx);
    /* HPDF_REAL x3                   */ float v6 = (float)get_arg_dbl(6, args, ctx);
    /* HPDF_REAL y3                   */ float v7 = (float)get_arg_dbl(7, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_CurveTo(v1, v2, v3, v4, v5, v6, v7);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_CurveTo2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x2                   */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y2                   */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL x3                   */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL y3                   */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_CurveTo2(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_CurveTo3(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x1                   */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y1                   */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL x3                   */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL y3                   */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_CurveTo3(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ClosePath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ClosePath(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Rectangle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL width                */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL height               */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Rectangle(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Stroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Stroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ClosePathStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ClosePathStroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Fill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Fill(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Eofill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Eofill(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_FillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_FillStroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_EofillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_EofillStroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ClosePathFillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ClosePathFillStroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ClosePathEofillStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ClosePathEofillStroke(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_EndPath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_EndPath(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Clip(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Clip(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Eoclip(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Eoclip(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_BeginText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_BeginText(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_EndText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_EndText(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetCharSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetCharSpace(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetWordSpace(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetWordSpace(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetHorizontalScalling(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetHorizontalScalling(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetTextLeading(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetTextLeading(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetFontAndSize(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Font font                 */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_REAL size                 */ float v3 = (float)get_arg_dbl(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetFontAndSize(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetTextRenderingMode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_TextRenderingMode mode    */ int64_t v2 = get_arg_int(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetTextRenderingMode(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetTextRise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetTextRise(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetTextRaise(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL value                */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetTextRaise(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_MoveTextPos(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_MoveTextPos(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_MoveTextPos2(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_MoveTextPos2(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetTextMatrix(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL a                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL b                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL c                    */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL d                    */ float v5 = (float)get_arg_dbl(5, args, ctx);
    /* HPDF_REAL x                    */ float v6 = (float)get_arg_dbl(6, args, ctx);
    /* HPDF_REAL y                    */ float v7 = (float)get_arg_dbl(7, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetTextMatrix(v1, v2, v3, v4, v5, v6, v7);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_MoveToNextLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_MoveToNextLine(v1);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ShowText(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *text               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ShowText(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ShowTextNextLine(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *text               */ const char *v2 = get_arg_str(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ShowTextNextLine(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ShowTextNextLineEx(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL word_space           */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL char_space           */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* const char *text               */ const char *v4 = get_arg_str(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ShowTextNextLineEx(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetGrayFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL gray                 */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetGrayFill(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetGrayStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL gray                 */ float v2 = (float)get_arg_dbl(2, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetGrayStroke(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetRGBFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL r                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL g                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL b                    */ float v4 = (float)get_arg_dbl(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetRGBFill(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetRGBStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL r                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL g                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL b                    */ float v4 = (float)get_arg_dbl(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetRGBStroke(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetCMYKFill(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL c                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL m                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL y                    */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL k                    */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetCMYKFill(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_SetCMYKStroke(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL c                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL m                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL y                    */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL k                    */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetCMYKStroke(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_ExecuteXObject(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_XObject obj               */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_ExecuteXObject(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["HPDF_Dict *", "new_stream", "HPDF_Dict *"]],
    "name": "HPDF_Page_New_Content_Stream",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Page_Insert_Shared_Content_Stream(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Dict shared_stream        */ KX_GET_VOIDP(args, ctx, v2, 2);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Insert_Shared_Content_Stream(v1, v2);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_DrawImage(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_Image image               */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_REAL x                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL y                    */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL width                */ float v5 = (float)get_arg_dbl(5, args, ctx);
    /* HPDF_REAL height               */ float v6 = (float)get_arg_dbl(6, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_DrawImage(v1, v2, v3, v4, v5, v6);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Circle(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL ray                  */ float v4 = (float)get_arg_dbl(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Circle(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Ellipse(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL xray                 */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL yray                 */ float v5 = (float)get_arg_dbl(5, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Ellipse(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_Arc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL x                    */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL y                    */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL ray                  */ float v4 = (float)get_arg_dbl(4, args, ctx);
    /* HPDF_REAL ang1                 */ float v5 = (float)get_arg_dbl(5, args, ctx);
    /* HPDF_REAL ang2                 */ float v6 = (float)get_arg_dbl(6, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_Arc(v1, v2, v3, v4, v5, v6);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

int kxpdf_HPDF_Page_TextOut(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_REAL xpos                 */ float v2 = (float)get_arg_dbl(2, args, ctx);
    /* HPDF_REAL ypos                 */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* const char *text               */ const char *v4 = get_arg_str(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_TextOut(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

/*
{
    "args": [["void *", "page", "HPDF_Page"], ["float", "left", "HPDF_REAL"], ["float", "top", "HPDF_REAL"], ["float", "right", "HPDF_REAL"], ["float", "bottom", "HPDF_REAL"], ["const char *", "text", "const char *"], ["int", "align", "HPDF_TextAlignment"], ["HPDF_UINT *", "len", "HPDF_UINT *"]],
    "name": "HPDF_Page_TextRect",
    "rtype": {
        "name": "HPDF_STATUS",
        "type": "uint32_t"
    }
}
*/
int kxpdf_HPDF_Page_SetSlideShow(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Page page                 */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_TransitionStyle type      */ int64_t v2 = get_arg_int(2, args, ctx);
    /* HPDF_REAL disp_time            */ float v3 = (float)get_arg_dbl(3, args, ctx);
    /* HPDF_REAL trans_time           */ float v4 = (float)get_arg_dbl(4, args, ctx);

    sg_error = sg_detail = 0;
    uint32_t r = HPDF_Page_SetSlideShow(v1, v2, v3, v4);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, (int64_t)r);
    return 0;
}

static kx_obj_t *kxpdf_append_method_HPDF_OutputIntent(kx_context_t *ctx, void *r)
{

    /* HPDF_OutputIntent */
    KX_MAKE_VOIDP(rv, r);

    return rv;
}

int kxpdf_HPDF_ICC_LoadIccFromMem(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* HPDF_MMgr mmgr                 */ KX_GET_VOIDP(args, ctx, v2, 2);
    /* HPDF_Stream iccdata            */ KX_GET_VOIDP(args, ctx, v3, 3);
    /* HPDF_Xref xref                 */ KX_GET_VOIDP(args, ctx, v4, 4);
    /* int numcomponent               */ int64_t v5 = get_arg_int(5, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_ICC_LoadIccFromMem(v1, v2, v3, v4, v5);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_OutputIntent(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}

int kxpdf_HPDF_LoadIccProfileFromFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    /* HPDF_Doc pdf                   */ KX_GET_VOIDP(args, ctx, v1, 1);
    /* const char *icc_file_name      */ const char *v2 = get_arg_str(2, args, ctx);
    /* int numcomponent               */ int64_t v3 = get_arg_int(3, args, ctx);

    sg_error = sg_detail = 0;
    void *r = HPDF_LoadIccProfileFromFile(v1, v2, v3);

    if (sg_error != 0 || sg_detail != 0) {
        KX_THROW_BLTIN_EXCEPTION("PdflibException", static_format("error code: %04X, (detail = %u)", sg_error, sg_detail));
    }
    kx_obj_t *rv = kxpdf_append_method_HPDF_OutputIntent(ctx, r);
    KX_ADJST_STACK();
    push_obj(ctx->stack, rv);
    return 0;
}


int kxpdf_create_HPDF_3DMeasure(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    KEX_SET_METHOD("3DMeasure_SetName", obj, kxpdf_HPDF_3DMeasure_SetName);
    /* KEX_SET_METHOD("3DMeasure_SetColor", obj, kxpdf_HPDF_3DMeasure_SetColor); */
    KEX_SET_METHOD("3DMeasure_SetTextSize", obj, kxpdf_HPDF_3DMeasure_SetTextSize);
    KEX_SET_METHOD("3DC3DMeasure_SetTextBoxSize", obj, kxpdf_HPDF_3DC3DMeasure_SetTextBoxSize);
    KEX_SET_METHOD("3DC3DMeasure_SetText", obj, kxpdf_HPDF_3DC3DMeasure_SetText);
    KEX_SET_METHOD("3DC3DMeasure_SetProjectionAnotation", obj, kxpdf_HPDF_3DC3DMeasure_SetProjectionAnotation);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}


int kxpdf_create_HPDF_Doc(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    kx_any_t *anyv = allocate_any(ctx);
    anyv->p = HPDF_New(kxpdf_error_handler, obj); HPDF_UseUTFEncodings(anyv->p);;
    anyv->any_free = HPDF_Free;

    KEX_SET_PROP_ANY(obj, "_voidp", anyv);

    /* KEX_SET_METHOD("SetErrorHandler", obj, kxpdf_HPDF_SetErrorHandler); */
    KEX_SET_METHOD("Free", obj, kxpdf_HPDF_Free);
    KEX_SET_METHOD("NewDoc", obj, kxpdf_HPDF_NewDoc);
    KEX_SET_METHOD("FreeDoc", obj, kxpdf_HPDF_FreeDoc);
    KEX_SET_METHOD("HasDoc", obj, kxpdf_HPDF_HasDoc);
    KEX_SET_METHOD("FreeDocAll", obj, kxpdf_HPDF_FreeDocAll);
    KEX_SET_METHOD("SaveToStream", obj, kxpdf_HPDF_SaveToStream);
    /* KEX_SET_METHOD("GetContents", obj, kxpdf_HPDF_GetContents); */
    KEX_SET_METHOD("GetStreamSize", obj, kxpdf_HPDF_GetStreamSize);
    /* KEX_SET_METHOD("ReadFromStream", obj, kxpdf_HPDF_ReadFromStream); */
    KEX_SET_METHOD("ResetStream", obj, kxpdf_HPDF_ResetStream);
    KEX_SET_METHOD("SaveToFile", obj, kxpdf_HPDF_SaveToFile);
    KEX_SET_METHOD("GetError", obj, kxpdf_HPDF_GetError);
    KEX_SET_METHOD("GetErrorDetail", obj, kxpdf_HPDF_GetErrorDetail);
    KEX_SET_METHOD("ResetError", obj, kxpdf_HPDF_ResetError);
    KEX_SET_METHOD("SetPagesConfiguration", obj, kxpdf_HPDF_SetPagesConfiguration);
    KEX_SET_METHOD("GetPageByIndex", obj, kxpdf_HPDF_GetPageByIndex);
    KEX_SET_METHOD("GetPageLayout", obj, kxpdf_HPDF_GetPageLayout);
    KEX_SET_METHOD("SetPageLayout", obj, kxpdf_HPDF_SetPageLayout);
    KEX_SET_METHOD("GetPageMode", obj, kxpdf_HPDF_GetPageMode);
    KEX_SET_METHOD("SetPageMode", obj, kxpdf_HPDF_SetPageMode);
    KEX_SET_METHOD("GetViewerPreference", obj, kxpdf_HPDF_GetViewerPreference);
    KEX_SET_METHOD("SetViewerPreference", obj, kxpdf_HPDF_SetViewerPreference);
    KEX_SET_METHOD("SetOpenAction", obj, kxpdf_HPDF_SetOpenAction);
    KEX_SET_METHOD("GetCurrentPage", obj, kxpdf_HPDF_GetCurrentPage);
    KEX_SET_METHOD("AddPage", obj, kxpdf_HPDF_AddPage);
    KEX_SET_METHOD("InsertPage", obj, kxpdf_HPDF_InsertPage);
    KEX_SET_METHOD("GetFont", obj, kxpdf_HPDF_GetFont);
    KEX_SET_METHOD("LoadType1FontFromFile", obj, kxpdf_HPDF_LoadType1FontFromFile);
    KEX_SET_METHOD("GetTTFontDefFromFile", obj, kxpdf_HPDF_GetTTFontDefFromFile);
    KEX_SET_METHOD("LoadTTFontFromFile", obj, kxpdf_HPDF_LoadTTFontFromFile);
    KEX_SET_METHOD("LoadTTFontFromFile2", obj, kxpdf_HPDF_LoadTTFontFromFile2);
    KEX_SET_METHOD("AddPageLabel", obj, kxpdf_HPDF_AddPageLabel);
    KEX_SET_METHOD("UseJPFonts", obj, kxpdf_HPDF_UseJPFonts);
    KEX_SET_METHOD("UseKRFonts", obj, kxpdf_HPDF_UseKRFonts);
    KEX_SET_METHOD("UseCNSFonts", obj, kxpdf_HPDF_UseCNSFonts);
    KEX_SET_METHOD("UseCNTFonts", obj, kxpdf_HPDF_UseCNTFonts);
    KEX_SET_METHOD("CreateOutline", obj, kxpdf_HPDF_CreateOutline);
    KEX_SET_METHOD("GetEncoder", obj, kxpdf_HPDF_GetEncoder);
    KEX_SET_METHOD("GetCurrentEncoder", obj, kxpdf_HPDF_GetCurrentEncoder);
    KEX_SET_METHOD("SetCurrentEncoder", obj, kxpdf_HPDF_SetCurrentEncoder);
    KEX_SET_METHOD("UseJPEncodings", obj, kxpdf_HPDF_UseJPEncodings);
    KEX_SET_METHOD("UseKREncodings", obj, kxpdf_HPDF_UseKREncodings);
    KEX_SET_METHOD("UseCNSEncodings", obj, kxpdf_HPDF_UseCNSEncodings);
    KEX_SET_METHOD("UseCNTEncodings", obj, kxpdf_HPDF_UseCNTEncodings);
    KEX_SET_METHOD("UseUTFEncodings", obj, kxpdf_HPDF_UseUTFEncodings);
    /* KEX_SET_METHOD("CreateXObjectFromImage", obj, kxpdf_HPDF_Page_CreateXObjectFromImage); */
    KEX_SET_METHOD("CreateXObjectAsWhiteRect", obj, kxpdf_HPDF_Page_CreateXObjectAsWhiteRect);
    KEX_SET_METHOD("CreateWidgetAnnot_WhiteOnlyWhilePrint", obj, kxpdf_HPDF_Page_CreateWidgetAnnot_WhiteOnlyWhilePrint);
    /* KEX_SET_METHOD("LoadPngImageFromMem", obj, kxpdf_HPDF_LoadPngImageFromMem); */
    KEX_SET_METHOD("LoadPngImageFromFile", obj, kxpdf_HPDF_LoadPngImageFromFile);
    KEX_SET_METHOD("LoadPngImageFromFile2", obj, kxpdf_HPDF_LoadPngImageFromFile2);
    KEX_SET_METHOD("LoadJpegImageFromFile", obj, kxpdf_HPDF_LoadJpegImageFromFile);
    /* KEX_SET_METHOD("LoadJpegImageFromMem", obj, kxpdf_HPDF_LoadJpegImageFromMem); */
    KEX_SET_METHOD("LoadU3DFromFile", obj, kxpdf_HPDF_LoadU3DFromFile);
    /* KEX_SET_METHOD("LoadU3DFromMem", obj, kxpdf_HPDF_LoadU3DFromMem); */
    /* KEX_SET_METHOD("LoadRaw1BitImageFromMem", obj, kxpdf_HPDF_Image_LoadRaw1BitImageFromMem); */
    KEX_SET_METHOD("LoadRawImageFromFile", obj, kxpdf_HPDF_LoadRawImageFromFile);
    /* KEX_SET_METHOD("LoadRawImageFromMem", obj, kxpdf_HPDF_LoadRawImageFromMem); */
    KEX_SET_METHOD("SetInfoAttr", obj, kxpdf_HPDF_SetInfoAttr);
    KEX_SET_METHOD("GetInfoAttr", obj, kxpdf_HPDF_GetInfoAttr);
    /* KEX_SET_METHOD("SetInfoDateAttr", obj, kxpdf_HPDF_SetInfoDateAttr); */
    KEX_SET_METHOD("SetPassword", obj, kxpdf_HPDF_SetPassword);
    KEX_SET_METHOD("SetPermission", obj, kxpdf_HPDF_SetPermission);
    KEX_SET_METHOD("SetEncryptionMode", obj, kxpdf_HPDF_SetEncryptionMode);
    KEX_SET_METHOD("SetCompressionMode", obj, kxpdf_HPDF_SetCompressionMode);
    KEX_SET_METHOD("AttachFile", obj, kxpdf_HPDF_AttachFile);
    KEX_SET_METHOD("CreateExtGState", obj, kxpdf_HPDF_CreateExtGState);
    KEX_SET_METHOD("ICC_LoadIccFromMem", obj, kxpdf_HPDF_ICC_LoadIccFromMem);
    KEX_SET_METHOD("LoadIccProfileFromFile", obj, kxpdf_HPDF_LoadIccProfileFromFile);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}


int kxpdf_create_HPDF_Error(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    KEX_SET_METHOD("CheckError", obj, kxpdf_HPDF_CheckError);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}


int kxpdf_create_HPDF_Error_Handler(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    /* KEX_SET_METHOD("NewEx", obj, kxpdf_HPDF_NewEx); */
    /* KEX_SET_METHOD("New", obj, kxpdf_HPDF_New); */

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}


int kxpdf_create_Main(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = allocate_obj(ctx);

    KEX_SET_METHOD("GetVersion", obj, kxpdf_HPDF_GetVersion);
    KEX_SET_METHOD("create3DMeasure", obj, kxpdf_create_HPDF_3DMeasure);
    KEX_SET_METHOD("create", obj, kxpdf_create_HPDF_Doc);
    KEX_SET_METHOD("createError", obj, kxpdf_create_HPDF_Error);
    KEX_SET_METHOD("createError_Handler", obj, kxpdf_create_HPDF_Error_Handler);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}



static kx_bltin_def_t kx_bltin_info[] = {
    { "create", kxpdf_create_Main },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, NULL, NULL);

