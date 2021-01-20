# class Xml

## Overview

### Parsing DOM

Build a DOM tree using `Xml.parseFile()` or `Xml.parseString()`. To read the file, do the following.

```javascript
var doc = Xml.parseFile("xmlfile.xml");
```

The following is an example of directly parsing a string.

```xml
var doc = Xml.parseString(%{
<?xml version="1.0" encoding="UTF-8" ?>
<artists>
  <product country="US" id="1">
    <name>Power Snack</name>
    <price>2400</price>
    <img file="powersnack.jpg"/>
  </product>
  <product country="US" id="2">
    <name>Babystar Icecream</name>
    <price>21000</price>
    <img file="babystar.jpg"/>
  </product>
  <product country="DE" id="3">
    <name>Panic! Panic! Panic!</name>
    <price>2400</price>
    <img file="panic.jpg"/>
  </product>
</artists>
});
```

The returned document object has the following methods.

|                   Method                    |                            Content                             |
| ------------------------------------------- | -------------------------------------------------------------- |
| `documentElement()`                         | Gets the root document                                         |
| `createElement(tagname)`                    | Creates an Element node                                        |
| `createTextNode(text)`                      | Creates a Text node                                            |
| `createComment(comment)`                    | Creates a Comment node                                         |
| `createCdataSection(content)`               | Creates a CDATA Section node                                   |
| `createProcessingInstruction(target, data)` | Creates a Processing Instruction node                          |
| `createEntityReference(name)`               | Creates an Entity Reference node                               |
| `createElementNS(nsUri, qname)`             | Creates an Element node by specifying the namespace            |
| `getElementById(id)`                        | Search for a node by specifying id                             |
| `getElementsByTagName(tagName)`             | Returns the node of tagName as an array                        |
| `xpath(expr)`                               | Evaluates the XPATH of expr and returns the result as an array |


### Root node

The root node is obtained using the `documentElement()` method as follows.

```javascript
var root = doc.documentElement();
```

#### XML node

XML nodes, including the root node, have the following properties and methods.

##### Properties

|   Properties   |    Content    |
| -------------- | ------------- |
| `type`         | Node type     |
| `name`         | QName         |
| `tagName`      | Tag name      |
| `localName`    | Local name    |
| `namespaceURI` | Namespace URI |
| `prefix`       | Prefix        |

#### Methods

|                Method                 |                            Content                             |
| ------------------------------------- | -------------------------------------------------------------- |
| `attributes()`                        | Returns an attribute list as an array.                         |
| `setAttribute(qname, value)`          | Set the attribute.                                             |
| `setAttributeNS(nsUri, qname, value)` | Set the attribute by specifying the namespace.                 |
| `removeAttribute(qname)`              | Removes an attribute.                                          |
| `removeAttributeNS(nsUri, localName)` | Removes the attribute by specifying the namespace.             |
| `getAttribute(qname)`                 | Get the attribute.                                             |
| `getAttributeNS(nsUri, qname)`        | Get the attribute by specifying the namespace.                 |
| `parentNode()`                        | Returns the parent node.                                       |
| `children()`                          | Returns the child nodes as an array.                           |
| `firstChild()`                        | Returns the first child node.                                  |
| `lastChild()`                         | Returns the last child node.                                   |
| `nextSibling()`                       | Returns the next node.                                         |
| `previousSibling()`                   | Returns the previous node.                                     |
| `appendChild(node)`                   | Adds a node to the child node.                                 |
| `removeChild(node)`                   | Removes a node from child nodes.                               |
| `replaceChild(node1, node2)`          | Replaces the child node.                                       |
| `replaceNode(node)`                   | Replaces one's own node with another node.                     |
| `insertBefore(node)`                  | Add a node as the previous node.                               |
| `insertAfter(node)`                   | Add a node as the next node.                                   |
| `remove()`                            | Removes the node.                                              |
| `textContent()`                       | Gets the text.                                                 |
| `innerText()`                         | Gets the text.                                                 |
| `hasChildren()`                       | Returns 1 if a child node exists.                              |
| `hasAttributes()`                     | Returns 1 if there are attributes.                             |
| `getElementById(id)`                  | Search for a node by specifying id                             |
| `getElementsByTagName(tagName)`       | Returns the node of tagName as an array                        |
| `xpath(expr)`                         | Evaluates the XPATH of expr and returns the result as an array |

### XPath

XPath returns the nodes that match the XPATH expression in the form of a node set (array). The node set also has an `xpath()` method, and you can use it by chaining XPATH to the narrowed down nodes.

Run the following with the sample XML document above.

```javascript
var nodes = doc.xpath("//product")
               .xpath("price")
               .map(&(p) => p.innerText());

nodes.each(&(text) => {
    System.println(text);
});
```

Result.

```
2400
21000
2400
```

By the way, using a block syntax and a numbered parameter supported recently, you can also write the following.

```javascript
var nodes = doc.xpath("//product")
               .xpath("price")
               .map { => _1.innerText() };

nodes.each {
    System.println(_1);
};
```

## Examples

### Example 1. Parsing Xml

#### Code

```javascript
function displayXml(doc, node, indent) {
    System.print("  " * indent);
    if (node.type == Xml.ELEMENT_NODE) {
        System.print("ELEM %s" % node.name);
    } else if (node.type == Xml.TEXT_NODE) {
        System.print("TEXT %s" % node.value.trim());
    }

    var attr = node.attributes();
    for (var i = 0, len = attr.length(); i < len; ++i) {
        System.print("[%s=%s]" % attr[i].name % attr[i].value);
    }
    System.println("");

    var child = node.firstChild();
    while (child) {
        displayXml(doc, child, indent + 1);
        child = child.nextSibling();
    }
}

var doc = Xml.parseString(%{
<?xml version="1.0" encoding="UTF-8" ?>
<artists>
  <product country="US" id="1">
    <name>Power Snack</name>
    <price>2400</price>
    <img file="powersnack.jpg"/>
  </product>
  <product country="US" id="2">
    <name>Babystar Icecream</name>
    <price>21000</price>
    <img file="babystar.jpg"/>
  </product>
  <product country="DE" id="3">
    <name>Panic! Panic! Panic!</name>
    <price>2400</price>
    <img file="panic.jpg"/>
  </product>
</artists>
});

var root = doc.documentElement();
displayXml(doc, root);
```

#### Result

```
ELEM artists
  TEXT
  ELEM product[country=US][id=1]
    TEXT
    ELEM name
      TEXT Power Snack
    TEXT
    ELEM price
      TEXT 2400
    TEXT
    ELEM img[file=powersnack.jpg]
    TEXT
  TEXT
  ELEM product[country=US][id=2]
    TEXT
    ELEM name
      TEXT Babystar Icecream
    TEXT
    ELEM price
      TEXT 21000
    TEXT
    ELEM img[file=babystar.jpg]
    TEXT
  TEXT
  ELEM product[country=DE][id=3]
    TEXT
    ELEM name
      TEXT Panic! Panic! Panic!
    TEXT
    ELEM price
      TEXT 2400
    TEXT
    ELEM img[file=panic.jpg]
    TEXT
  TEXT
```

### Example 2. DOM methods

#### Code

```javascript
function displayXml(doc, node, indent) {
    System.print("  " * indent);
    if (node.type == Xml.ELEMENT_NODE) {
        System.print("ELEM %s" % node.name);
    } else if (node.type == Xml.TEXT_NODE) {
        System.print("TEXT %s" % node.value.trim());
    }

    var attr = node.attributes();
    for (var i = 0, len = attr.length(); i < len; ++i) {
        System.print("[%s=%s]" % attr[i].name % attr[i].value);
    }
    System.println("");

    var child = node.firstChild();
    while (child) {
        displayXml(doc, child, indent + 1);
        child = child.nextSibling();
    }
}

var doc = Xml.parseString(%{
<?xml version="1.0" encoding="UTF-8" ?>
<artists>
  <product country="US" id="1">
    <name>Power Snack</name>
    <price>2400</price>
    <img file="powersnack.jpg"/>
  </product>
  <product country="US" id="2">
    <name>Babystar Icecream</name>
    <price>21000</price>
    <img file="babystar.jpg"/>
  </product>
  <product country="DE" id="3">
    <name>Panic! Panic! Panic!</name>
    <price>2400</price>
    <img file="panic.jpg"/>
  </product>
</artists>
});

var root = doc.documentElement();
var el = root.getElementById("3");
if (el) {
    el.remove();
}

System.println("getElementByTagName:");
var els = root.getElementsByTagName("img");
if (els.isArray) {
    els.each(&(el) => displayXml(doc, el));
}
```

#### Result

```
getElementByTagName:
ELEM img[file=powersnack.jpg]
ELEM img[file=babystar.jpg]
```

### Example 3. XPath

#### Code

```javascript
function displayXml(doc, node, indent) {
    System.print("  " * indent);
    if (node.type == Xml.ELEMENT_NODE) {
        System.print("ELEM %s" % node.name);
    } else if (node.type == Xml.TEXT_NODE) {
        System.print("TEXT %s" % node.value.trim());
    }

    var attr = node.attributes();
    for (var i = 0, len = attr.length(); i < len; ++i) {
        System.print("[%s=%s]" % attr[i].name % attr[i].value);
    }
    System.println("");

    var child = node.firstChild();
    while (child) {
        displayXml(doc, child, indent + 1);
        child = child.nextSibling();
    }
}

var doc = Xml.parseString(%{
<?xml version="1.0" encoding="UTF-8" ?>
<artists>
  <product country="US" id="1">
    <name>Power Snack</name>
    <price>2400</price>
    <img file="powersnack.jpg"/>
  </product>
  <product country="US" id="2">
    <name>Babystar Icecream</name>
    <price>21000</price>
    <img file="babystar.jpg"/>
  </product>
  <product country="DE" id="3">
    <name>Panic! Panic! Panic!</name>
    <price>2400</price>
    <img file="panic.jpg"/>
  </product>
</artists>
});

var root = doc.documentElement();
var el = root.getElementById("3");
if (el) {
    el.remove();
}

System.println("XPath:");
var nodes = doc.xpath("//product").xpath("price");
if (nodes.isArray) {
    nodes.each(&(el) => displayXml(doc, el));
}
```

#### Result

```
XPath:
ELEM price
  TEXT 2400
ELEM price
  TEXT 21000
```

### Example 4. XmlWriter

#### Code

I introduce the sample source included in the repo.
There is `Xml.Writer` which is not explained,
but it will be helpful for displaying DOM.

```javascript
var doc = Xml.parseString(%{
<?xml version="1.0" encoding="UTF-8" ?>
<artists>
  <product country="US" id="1">
    <name>Power Snack</name>
    <price>2400</price>
    <img file="powersnack.jpg"/>
  </product>
  <product country="US" id="2">
    <name>Babystar Icecream</name>
    <price>21000</price>
    <img file="babystar.jpg"/>
  </product>
  <product country="DE" id="3">
    <name>Panic! Panic! Panic!</name>
    <price>2400</price>
    <img file="panic.jpg"/>
  </product>
</artists>
});

var root = doc.documentElement();
var el = root.getElementById("3");
if (el) {
    el.remove();
}

var xmlWriter = new Xml.Writer(System, { tab: "        " });
xmlWriter.write(doc);
xmlWriter.write(root);
```

#### Result

```
<artists>
        <product country="US" id="1">
                <name>Power Snack</name>
                <price>2400</price>
                <img file="powersnack.jpg" />
        </product>
        <product country="US" id="2">
                <name>Babystar Icecream</name>
                <price>21000</price>
                <img file="babystar.jpg" />
        </product>
</artists>
<artists>
        <product country="US" id="1">
                <name>Power Snack</name>
                <price>2400</price>
                <img file="powersnack.jpg" />
        </product>
        <product country="US" id="2">
                <name>Babystar Icecream</name>
                <price>21000</price>
                <img file="babystar.jpg" />
        </product>
</artists>
```
