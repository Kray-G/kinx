#include <dbg.h>
#define KX_DLL
#include <kinx.h>
#include <kxthread.h>
#include "libmodules/libs/libxml2/include/libxml2/libxml/xmlreader.h"
#include "libmodules/libs/libxml2/include/libxml2/libxml/xpath.h"

KX_DECL_MEM_ALLOCATORS();

#define KX_XML_GET_DOC(r, obj) \
kx_xml_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_doc"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Invalid XML object"); \
    } \
    r = (kx_xml_t *)(val->value.av->p); \
} \
/**/
#define KX_XML_GET_NODE(r, obj) \
kx_xmlnode_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_node"); \
    if (!val || val->type != KX_ANY_T) { \
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Invalid XML Node object"); \
    } \
    r = (kx_xmlnode_t *)(val->value.av->p); \
} \
/**/
#define KX_XML_GET_NODE_NOERR(r, obj) \
kx_xmlnode_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_node"); \
    if (val && val->type == KX_ANY_T) { \
        r = (kx_xmlnode_t *)(val->value.av->p); \
    } \
} \
/**/
#define KX_XML_GET_HOST(r, obj) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_host"); \
    if (val && val->type == KX_OBJ_T) { \
        r = val->value.ov; \
    } \
} \
/**/
#define KX_XML_GET_CHILDREN(r, obj) \
kx_obj_t *r = NULL; \
if (obj) { \
    kx_val_t *val = NULL; \
    KEX_GET_PROP(val, obj, "_children"); \
    if (val && val->type == KX_OBJ_T) { \
        r = val->value.ov; \
    } \
} \
/**/

typedef struct kx_xml_ {
    xmlDocPtr doc;
    int ref;
} kx_xml_t;

typedef struct kx_xmlnode_ {
    kx_xml_t *xml;
    xmlNodePtr p;
} kx_xmlnode_t;

static kx_obj_t *create_node(kx_context_t *ctx, kx_xml_t *xml, xmlNodePtr cur);
static int XML_nodeset_xpath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx);

static void xml_initialize(void)
{
    LIBXML_TEST_VERSION;
}

static void xml_finalize(void)
{
    xmlCleanupParser();
}

static void free_doc_impl(kx_xml_t *xml)
{
    if (--(xml->ref) == 0) {
        xmlFreeDoc(xml->doc);
        kx_free(xml);
    }
}

static void free_old_node(xmlNodePtr old)
{
    xmlNodePtr children = old->children;
    while (children) {
        free_old_node(children);
        children = children->next;
    }
    xmlFree(old);
}

static kx_xml_t *parseFile(int args, kx_context_t *ctx, const char *filename)
{
    kx_xml_t *xml = (kx_xml_t *)kx_calloc(1, sizeof(kx_xml_t));
    xml->doc = xmlParseFile(filename);
    if (xml->doc == NULL) {
        kx_free(xml);
        return NULL;
    }
    xml->ref = 1;
    return xml;
}

static kx_xml_t *parseDoc(int args, kx_context_t *ctx, const char *xml_text)
{
    kx_xml_t *xml = (kx_xml_t *)kx_calloc(1, sizeof(kx_xml_t));
    xml->doc = xmlParseDoc(xml_text);
    if (xml->doc == NULL) {
        kx_free(xml);
        return NULL;
    }
    xml->ref = 1;
    return xml;
}

static void free_doc(void *xml)
{
    free_doc_impl(xml);
}

static void free_node(void *node)
{
    free_doc_impl(((kx_xmlnode_t *)node)->xml);
    kx_free(node);
}

static int XML_node_parentNode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    kx_obj_t *nn = create_node(ctx, node->xml, node->p->parent);

    KX_ADJST_STACK();
    push_obj(ctx->stack, nn);
    return 0;
}

static int get_element_by_id_r(kx_obj_t **robj, int args, kx_context_t *ctx, kx_xml_t *xml, xmlNodePtr node, const char *id)
{
    char *attr = xmlGetProp(node, "id");
    if (attr && !strcmp(id, attr)) {
        xmlFree(attr);
        *robj = create_node(ctx, xml, node);
        return 0;
    }

    xmlNodePtr children = node->children;
    while (children) {
        int r = get_element_by_id_r(robj, args, ctx, xml, children, id);
        if (!r) {
            return 0;
        }
        children = children->next;
    }

    return 1;
}

static int get_element_by_id(int args, kx_context_t *ctx, kx_xml_t *xml, xmlNodePtr node, const char *id)
{
    kx_obj_t *robj = NULL;
    get_element_by_id_r(&robj, args, ctx, xml, node, id);

    KX_ADJST_STACK();
    if (robj) {
        push_obj(ctx->stack, robj);
    } else {
        push_undef(ctx->stack);
    }

    return 0;
}

static void get_elements_by_tagname_r(kx_obj_t *robj, int args, kx_context_t *ctx, kx_xml_t *xml, xmlNodePtr node, const char *tagname)
{
    if (!strcmp(tagname, node->name)) {
        kx_obj_t *n = create_node(ctx, xml, node);
        KEX_PUSH_ARRAY_OBJ(robj, n);
    }

    xmlNodePtr children = node->children;
    while (children) {
        get_elements_by_tagname_r(robj, args, ctx, xml, children, tagname);
        children = children->next;
    }
}

static int get_elements_by_tagname(int args, kx_context_t *ctx, kx_xml_t *xml, xmlNodePtr node, const char *tagname)
{
    kx_obj_t *robj = allocate_obj(ctx);
    get_elements_by_tagname_r(robj, args, ctx, xml, node, tagname);

    KX_ADJST_STACK();
    push_obj(ctx->stack, robj);
    return 0;
}

static void make_xpath_result(kx_obj_t *obj, kx_context_t *ctx, kx_xml_t *xml, xmlNodeSetPtr nodes)
{
    int size = (nodes) ? nodes->nodeNr : 0;
    for (int i = 0; i < size; ++i) {
        if (nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
            xmlNodePtr cur = nodes->nodeTab[i];
            kx_obj_t *node = create_node(ctx, xml, cur);
            KEX_PUSH_ARRAY_OBJ(obj, node);
        }
    }
}

static int XML_nodeset_xpath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *nodeset = get_arg_obj(1, args, ctx);
    KX_XML_GET_HOST(obj, nodeset);
    KX_XML_GET_NODE(node, obj);
    const char *expr = get_arg_str(2, args, ctx);

    xmlXPathContextPtr xpathctx = xmlXPathNewContext(node->xml->doc);
    if (xpathctx == NULL) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to create an XPath context");
    }

    kx_obj_t *ret = allocate_obj(ctx);
    int len = kv_size(nodeset->ary);
    for (int i = 0; i < len; ++i) {
        kx_val_t *v = &kv_A(nodeset->ary, i);
        if (v->type == KX_OBJ_T) {
            kx_obj_t *nobj = v->value.ov;
            KX_XML_GET_NODE_NOERR(node, nobj);
            if (node) {
                xpathctx->node = node->p;
                xmlXPathObjectPtr xpathobj = xmlXPathEvalExpression(expr, xpathctx);
                if (xpathobj) {
                    make_xpath_result(ret, ctx, node->xml, xpathobj->nodesetval);
                    xmlXPathFreeObject(xpathobj);
                }
            }
        }
    }
    KEX_SET_PROP_OBJ(ret, "_host", obj);
    KEX_SET_METHOD("xpath", ret, XML_nodeset_xpath);

    xmlXPathFreeContext(xpathctx);

    KX_ADJST_STACK();
    push_obj(ctx->stack, ret);
    return 0;
}

static int XML_node_xpath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *expr = get_arg_str(2, args, ctx);

    xmlXPathContextPtr xpathctx = xmlXPathNewContext(node->xml->doc);
    if (xpathctx == NULL) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to create an XPath context");
    }

    xpathctx->node = node->p;
    xmlXPathObjectPtr xpathobj = xmlXPathEvalExpression(expr, xpathctx);
    if (xpathobj == NULL) {
        xmlXPathFreeContext(xpathctx);
        xmlFreeDoc(node->xml->doc);
        KX_THROW_BLTIN_EXCEPTION("XmlException", static_format("Failed to evaluate xpath expression(%s)", expr));
    }

    kx_obj_t *ret = allocate_obj(ctx);
    make_xpath_result(ret, ctx, node->xml, xpathobj->nodesetval);
    KEX_SET_PROP_OBJ(ret, "_host", obj);
    KEX_SET_METHOD("xpath", ret, XML_nodeset_xpath);

    xmlXPathFreeObject(xpathobj);
    xmlXPathFreeContext(xpathctx);

    KX_ADJST_STACK();
    push_obj(ctx->stack, ret);
    return 0;
}

static int XML_xpath(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *expr = get_arg_str(2, args, ctx);

    xmlXPathContextPtr xpathctx = xmlXPathNewContext(xml->doc);
    if (xpathctx == NULL) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to create an XPath context");
    }

    xmlXPathObjectPtr xpathobj = xmlXPathEvalExpression(expr, xpathctx);
    if (xpathobj == NULL) {
        xmlXPathFreeContext(xpathctx);
        xmlFreeDoc(xml->doc);
        KX_THROW_BLTIN_EXCEPTION("XmlException", static_format("Failed to evaluate xpath expression(%s)", expr));
    }

    kx_obj_t *ret = allocate_obj(ctx);
    make_xpath_result(ret, ctx, xml, xpathobj->nodesetval);
    kx_obj_t *root = create_node(ctx, xml, xmlDocGetRootElement(xml->doc));
    KEX_SET_PROP_OBJ(ret, "_host", root);
    KEX_SET_METHOD("xpath", ret, XML_nodeset_xpath);

    xmlXPathFreeObject(xpathobj);
    xmlXPathFreeContext(xpathctx);

    KX_ADJST_STACK();
    push_obj(ctx->stack, ret);
    return 0;
}

static kx_obj_t *update_children(kx_context_t *ctx, kx_xml_t *xml, kx_obj_t *obj, xmlNodePtr p)
{
    if (!obj) {
        return NULL;
    }

    KX_XML_GET_CHILDREN(chld, obj);
    if (!chld) {
        chld = allocate_obj(ctx);
        KEX_SET_PROP_OBJ(obj, "_children", chld);
    }

    kv_shrinkto(chld->ary, 0);
    xmlNodePtr children = p->children;
    while (children) {
        kx_obj_t *nn = create_node(ctx, xml, children);
        KEX_PUSH_ARRAY_OBJ(chld, nn);
        children = children->next;
    }

    return chld;
}

static int XML_node_children(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    kx_obj_t *ret = update_children(ctx, node->xml, obj, node->p);
    KX_ADJST_STACK();
    if (ret) {
        push_obj(ctx->stack, ret);
    } else {
        push_undef(ctx->stack);
    }
    return 0;
}

static int XML_node_firstChild(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    if (node->p->children) {
        kx_obj_t *nn = create_node(ctx, node->xml, node->p->children);
        KX_ADJST_STACK();
        push_obj(ctx->stack, nn);
        return 0;
    }

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

static int XML_node_lastChild(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    if (node->p->last) {
        kx_obj_t *nn = create_node(ctx, node->xml, node->p->last);
        KX_ADJST_STACK();
        push_obj(ctx->stack, nn);
        return 0;
    }

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

static int XML_node_nextSibling(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    if (node->p->next) {
        kx_obj_t *nn = create_node(ctx, node->xml, node->p->next);
        KX_ADJST_STACK();
        push_obj(ctx->stack, nn);
        return 0;
    }

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

static int XML_node_previousSibling(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    if (node->p->prev) {
        kx_obj_t *nn = create_node(ctx, node->xml, node->p->prev);
        KX_ADJST_STACK();
        push_obj(ctx->stack, nn);
    }

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

static int XML_node_removeChild(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);

    for (xmlNodePtr cur = node->p->children; cur; cur = cur->next) {
        if (cur == n1->p) {
            xmlUnlinkNode(cur);
            free_old_node(cur);
            break;
        }
    }

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

static int XML_node_remove(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);

    xmlUnlinkNode(node->p);
    free_old_node(node->p);

    KX_ADJST_STACK();
    push_undef(ctx->stack);
    return 0;
}

static int XML_node_replaceChild(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    kx_obj_t *a2 = get_arg_obj(3, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);
    KX_XML_GET_NODE(n2, a2);

    for (xmlNodePtr cur = node->p->children; cur; cur = cur->next) {
        if (cur == n1->p) {
            xmlNodePtr old = xmlReplaceNode(cur, n2->p);
            free_old_node(old);
            break;
        }
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int XML_node_replaceNode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);

    xmlNodePtr old = xmlReplaceNode(node->p, n1->p);
    free_old_node(old);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int XML_node_appendChild(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);

    xmlNodePtr nnp = xmlAddChild(node->p, n1->p);
    if (!nnp) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to append a child");
    }

    kx_obj_t *nn = create_node(ctx, node->xml, nnp);

    KX_ADJST_STACK();
    push_obj(ctx->stack, nn);
    return 0;
}

static int XML_node_insertBefore(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);

    xmlNodePtr nnp = xmlAddPrevSibling(node->p, n1->p);
    if (!nnp) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to insert a node to a previous sibling");
    }

    kx_obj_t *nn = create_node(ctx, node->xml, nnp);

    KX_ADJST_STACK();
    push_obj(ctx->stack, nn);
    return 0;
}

static int XML_node_insertAfter(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);

    xmlNodePtr nnp = xmlAddNextSibling(node->p, n1->p);
    if (!nnp) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to insert a node to a next sibling");
    }

    kx_obj_t *nn = create_node(ctx, node->xml, nnp);

    KX_ADJST_STACK();
    push_obj(ctx->stack, nn);
    return 0;
}

static int XML_node_content(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    kx_obj_t *a1 = get_arg_obj(2, args, ctx);
    KX_XML_GET_NODE(node, obj);
    KX_XML_GET_NODE(n1, a1);

    char *textcontent = xmlNodeGetContent(node->p);
    if (!textcontent) {
        KX_ADJST_STACK();
        push_undef(ctx->stack);
        return 0;
    }

    kstr_t *sv = allocate_str(ctx);
    ks_append(sv, textcontent);
    xmlFree(textcontent);

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

static kstr_t *build_qname(kx_context_t *ctx, const char *ncname, xmlNsPtr ns)
{
    kstr_t *sv = allocate_str(ctx);
    if (!ncname) {
        return sv;
    }
    if (ns && ns->prefix) {
        ks_appendf(sv, "%s:", ns->prefix);
    }
    ks_appendf(sv, "%s", ncname);
    return sv;
}

static int XML_node_attributes(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    kx_obj_t *ret = allocate_obj(ctx);
    xmlAttrPtr attr = node->p->properties;
    while (attr) {
        kx_obj_t *a = allocate_obj(ctx);

        xmlChar* value = xmlNodeListGetString(node->xml->doc, attr->children, 1);
        KEX_SET_PROP_CSTR(a, "name", attr->name);
        KEX_SET_PROP_CSTR(a, "value", value ? (const char *)value : "");
        KEX_PUSH_ARRAY_OBJ(ret, a);

        xmlFree(value);
        attr = attr->next;
    }

    KX_ADJST_STACK();
    push_obj(ctx->stack, ret);
    return 0;
}

static int XML_node_getAttribute(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *name = get_arg_str(2, args, ctx);
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to set attribute because of no name");
    }

    kstr_t *sv = allocate_str(ctx);
    const char *value = xmlGetProp(node->p, name);
    if (value) {
        ks_append(sv, value);
    }

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

static int XML_node_getAttributeNS(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *name = get_arg_str(2, args, ctx);
    const char *ns = get_arg_str(3, args, ctx);
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to set attribute because of no name");
    }

    kstr_t *sv = allocate_str(ctx);
    const char *value = xmlGetNsProp(node->p, name, ns);
    if (value) {
        ks_append(sv, value);
    }

    KX_ADJST_STACK();
    push_sv(ctx->stack, sv);
    return 0;
}

static int XML_node_setAttribute(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *qname = get_arg_str(2, args, ctx);
    const char *value = get_arg_str(3, args, ctx);
    if (!qname) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to set attribute because of no name");
    }

    xmlSetProp(node->p, qname, value);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int XML_node_setAttributeNS(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *namespaceURI = get_arg_str(2, args, ctx);
    const char *qname = get_arg_str(3, args, ctx);
    const char *value = get_arg_str(4, args, ctx);
    if (!qname) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to set attribute because of no name");
    }

    char *buf = kx_strdup(qname);
    char *prefix = buf;
    char *localName = buf;
    while (*localName) {
        if (*localName == ':') {
            *localName = 0;
            ++localName;
            break;
        }
        ++localName;
    }
    if (!localName) {
        kx_free(buf);
        KX_THROW_BLTIN_EXCEPTION("XmlException", "QName must have ':' to separate a namespace and a name");
    }

    xmlNsPtr ns = xmlNewNs(node->p, namespaceURI, prefix);
    xmlSetNsProp(node->p, ns, localName, value);
    kx_free(buf);

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int XML_node_removeAttribute(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *qname = get_arg_str(2, args, ctx);
    if (!qname) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to remove attribute because of no name");
    }

    xmlAttrPtr attr = node->p->properties;
    while (attr) {
        kstr_t *qn = build_qname(ctx, attr->name, attr->ns);
        if (!strcmp(ks_string(qn), qname)) {
            break;
        }
        attr = attr->next;
    }
    if (attr) {
        xmlRemoveProp(attr);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int XML_node_removeAttributeNS(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *namespaceURI = get_arg_str(2, args, ctx);
    const char *localName = get_arg_str(3, args, ctx);
    if (!namespaceURI || !localName) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to remove attribute because of no name");
    }

    xmlAttrPtr attr = node->p->properties;
    while (attr) {
        if (!attr->ns) {
            continue;
        }
        if (!strcmp(attr->ns->href, namespaceURI) && !strcmp(attr->name, localName)) {
            break;
        }
        attr = attr->next;
    }
    if (attr) {
        xmlRemoveProp(attr);
    }

    KX_ADJST_STACK();
    push_i(ctx->stack, 0);
    return 0;
}

static int XML_node_hasChildren(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    int chk = node->p->children != NULL;

    KX_ADJST_STACK();
    push_i(ctx->stack, chk);
    return 0;
}

static int XML_node_hasAttributes(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);

    int chk = node->p->properties != NULL;

    KX_ADJST_STACK();
    push_i(ctx->stack, chk);
    return 0;
}

static int XML_node_getElementById(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *id = get_arg_str(2, args, ctx);

    return get_element_by_id(args, ctx, node->xml, node->p, id);
}

static int XML_node_getElementsByTagName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_NODE(node, obj);
    const char *id = get_arg_str(2, args, ctx);

    return get_elements_by_tagname(args, ctx, node->xml, node->p, id);
}

static kx_obj_t *create_node(kx_context_t *ctx, kx_xml_t *xml, xmlNodePtr cur)
{
    if (!cur) {
        return NULL;
    }

    kx_xmlnode_t *n = (kx_xmlnode_t *)kx_calloc(1, sizeof(kx_xmlnode_t));
    ++(xml->ref);
    n->xml = xml;
    n->p = cur;

    kx_any_t *node = allocate_any(ctx);
    node->p = n;
    node->any_free = free_node;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(obj, "_node", node);

    KEX_SET_PROP_INT(obj, "type", n->p->type);
    KEX_SET_PROP_STR(obj, "name", build_qname(ctx, n->p->name, n->p->ns));
    KEX_SET_PROP_CSTR(obj, "tagName", n->p->name ? (const char *)n->p->name : "");
    KEX_SET_PROP_CSTR(obj, "localName", n->p->name ? (const char *)n->p->name : "");
    KEX_SET_PROP_CSTR(obj, "namespaceURI", (n->p->ns && n->p->ns->href) ? (const char *)n->p->ns->href : "");
    KEX_SET_PROP_CSTR(obj, "prefix", (n->p->ns && n->p->ns->prefix) ? (const char *)n->p->ns->prefix : "");
    char *content = NULL;
    switch (n->p->type) {
    case XML_TEXT_NODE:
    case XML_ATTRIBUTE_NODE:
    case XML_PI_NODE:
    case XML_COMMENT_NODE:
        content = xmlNodeGetContent(n->p);
        break;
    default:
        break;
    }
    if (content) {
        KEX_SET_PROP_CSTR(obj, "value", content);
        xmlFree(content);
    }

    KEX_SET_METHOD("attributes", obj, XML_node_attributes);
    KEX_SET_METHOD("getAttribute", obj, XML_node_getAttribute);
    KEX_SET_METHOD("getAttributeNS", obj, XML_node_getAttributeNS);
    KEX_SET_METHOD("setAttribute", obj, XML_node_setAttribute);
    KEX_SET_METHOD("setAttributeNS", obj, XML_node_setAttributeNS);
    KEX_SET_METHOD("removeAttribute", obj, XML_node_removeAttribute);
    KEX_SET_METHOD("removeAttributeNS", obj, XML_node_removeAttributeNS);

    KEX_SET_METHOD("parentNode", obj, XML_node_parentNode);
    KEX_SET_METHOD("children", obj, XML_node_children);
    KEX_SET_METHOD("firstChild", obj, XML_node_firstChild);
    KEX_SET_METHOD("lastChild", obj, XML_node_lastChild);
    KEX_SET_METHOD("nextSibling", obj, XML_node_nextSibling);
    KEX_SET_METHOD("previousSibling", obj, XML_node_previousSibling);

    KEX_SET_METHOD("appendChild", obj, XML_node_appendChild);
    KEX_SET_METHOD("removeChild", obj, XML_node_removeChild);
    KEX_SET_METHOD("replaceChild", obj, XML_node_replaceChild);
    KEX_SET_METHOD("replaceNode", obj, XML_node_replaceNode);
    KEX_SET_METHOD("insertBefore", obj, XML_node_insertBefore);
    KEX_SET_METHOD("insertAfter", obj, XML_node_insertAfter);
    KEX_SET_METHOD("remove", obj, XML_node_remove);

    KEX_SET_METHOD("textContent", obj, XML_node_content);
    KEX_SET_METHOD("innerText", obj, XML_node_content);

    KEX_SET_METHOD("hasChildren", obj, XML_node_hasChildren);
    KEX_SET_METHOD("hasAttributes", obj, XML_node_hasAttributes);

    KEX_SET_METHOD("getElementById", obj, XML_node_getElementById);
    KEX_SET_METHOD("getElementsByTagName", obj, XML_node_getElementsByTagName);

    KEX_SET_METHOD("xpath", obj, XML_node_xpath);

    return obj;
}

static int XML_documentElement(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);

    kx_obj_t *node = create_node(ctx, xml, xmlDocGetRootElement(xml->doc));

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createElement(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *tagname = get_arg_str(2, args, ctx);
    if (!tagname) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Needs a tagname to create an element");
    }

    xmlNodePtr cur = xmlNewNode(NULL, tagname);
    kx_obj_t *node = create_node(ctx, xml, cur);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createTextNode(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *content = get_arg_str(2, args, ctx);

    xmlNodePtr cur = xmlNewText(content);
    kx_obj_t *node = create_node(ctx, xml, cur);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createProcessingInstruction(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *target = get_arg_str(2, args, ctx);
    const char *content = get_arg_str(3, args, ctx);
    if (!target) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Needs a target to create a PI node");
    }

    xmlNodePtr cur = xmlNewDocPI(NULL, target, content);
    kx_obj_t *node = create_node(ctx, xml, cur);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createComment(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *content = get_arg_str(2, args, ctx);

    xmlNodePtr cur = xmlNewComment(content);
    kx_obj_t *node = create_node(ctx, xml, cur);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createCdataSection(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *content = get_arg_str(2, args, ctx);

    xmlNodePtr cur = xmlNewCDataBlock(NULL, content, content ? strlen(content) : 0);
    kx_obj_t *node = create_node(ctx, xml, cur);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createEntityReference(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *name = get_arg_str(2, args, ctx);
    if (!name) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Needs a name to create an entity reference node");
    }

    xmlNodePtr cur = xmlNewCharRef(NULL, name);
    kx_obj_t *node = create_node(ctx, xml, cur);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_createElementNS(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *namaespace_uri = get_arg_str(2, args, ctx);
    const char *qname = get_arg_str(3, args, ctx);
    if (!namaespace_uri || !qname) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Needs a namespaceURI and a qname to create an element");
    }

    char *buf = kx_strdup(qname);
    char *prefix = buf;
    char *tagname = buf;
    while (*tagname) {
        if (*tagname == ':') {
            *tagname = 0;
            ++tagname;
            break;
        }
        ++tagname;
    }
    if (!tagname) {
        kx_free(buf);
        KX_THROW_BLTIN_EXCEPTION("XmlException", "QName must have ':' to separate a namespace and a name");
    }

    xmlNsPtr ns = xmlNewNs(NULL, namaespace_uri, prefix);
    xmlNodePtr cur = xmlNewNode(ns, tagname);
    kx_obj_t *node = create_node(ctx, xml, cur);
    kx_free(buf);

    KX_ADJST_STACK();
    push_obj(ctx->stack, node);
    return 0;
}

static int XML_getElementById(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *id = get_arg_str(2, args, ctx);

    xmlNodePtr node = xmlDocGetRootElement(xml->doc);
    return get_element_by_id(args, ctx, xml, node, id);
}

static int XML_getElementsByTagName(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    kx_obj_t *obj = get_arg_obj(1, args, ctx);
    KX_XML_GET_DOC(xml, obj);
    const char *tagname = get_arg_str(2, args, ctx);

    xmlNodePtr node = xmlDocGetRootElement(xml->doc);
    return get_elements_by_tagname(args, ctx, xml, node, tagname);
}

static int xml_parse(int args, kx_context_t *ctx, kx_xml_t *xml)
{
    kx_any_t *doc = allocate_any(ctx);
    doc->p = xml;
    doc->any_free = free_doc;

    kx_obj_t *obj = allocate_obj(ctx);
    KEX_SET_PROP_ANY(obj, "_doc", doc);
    KEX_SET_METHOD("documentElement", obj, XML_documentElement);
    KEX_SET_METHOD("createElement", obj, XML_createElement);
    KEX_SET_METHOD("createTextNode", obj, XML_createTextNode);
    KEX_SET_METHOD("createComment", obj, XML_createComment);
    KEX_SET_METHOD("createCdataSection", obj, XML_createCdataSection);
    KEX_SET_METHOD("createProcessingInstruction", obj, XML_createProcessingInstruction);
    KEX_SET_METHOD("createEntityReference", obj, XML_createEntityReference);
    KEX_SET_METHOD("createElementNS", obj, XML_createElementNS);

    KEX_SET_METHOD("getElementById", obj, XML_getElementById);
    KEX_SET_METHOD("getElementsByTagName", obj, XML_getElementsByTagName);

    KEX_SET_METHOD("xpath", obj, XML_xpath);

    KX_ADJST_STACK();
    push_obj(ctx->stack, obj);
    return 0;
}

static int XML_parseString(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *xml_text = get_arg_str(1, args, ctx);
    if (!xml_text) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to parse because of no xml text");
    }
    while (*xml_text != '\0' && (*xml_text == '\n' || *xml_text == '\r' || *xml_text == ' ' || *xml_text == '\t')) {
        ++xml_text;
    }
    if (*xml_text == '\0') {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to parse because of no xml text");
    }
    kx_xml_t *xml = parseDoc(args, ctx, xml_text);
    if (!xml) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", "Failed to parse a document string");
    }
    return xml_parse(args, ctx, xml);
}

static int XML_parseFile(int args, kx_frm_t *frmv, kx_frm_t *lexv, kx_context_t *ctx)
{
    const char *filename = get_arg_str(1, args, ctx);
    kx_xml_t *xml = parseFile(args, ctx, filename);
    if (!xml) {
        KX_THROW_BLTIN_EXCEPTION("XmlException", static_format("Failed to parse the file(%s)", filename));
    }
    return xml_parse(args, ctx, xml);
}

static kx_bltin_def_t kx_bltin_info[] = {
    { "parseString", XML_parseString },
    { "parseFile", XML_parseFile },
};

KX_DLL_DECL_FNCTIONS(kx_bltin_info, xml_initialize, xml_finalize);
