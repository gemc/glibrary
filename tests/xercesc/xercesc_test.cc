// xercesc
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/dom/DOM.hpp>


using namespace xercesc_3_2;

// c++ standard library
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n" << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    const char * xmlFile = "rga.xml";

    try {
        parser->parse(xmlFile);

        DOMDocument* doc = parser->getDocument();
        DOMElement* elementRoot = doc->getDocumentElement();
        if (!elementRoot) {
            cout << "empty XML document" << endl;
            return 1;
        }

        // Get the name of the root element
        char* message = XMLString::transcode(elementRoot->getTagName());
        cout << "Root element is: " << message << endl;
        XMLString::release(&message);

        // get name of first child element
        DOMNodeList* children = elementRoot->getChildNodes();
        const XMLSize_t nodeCount = children->getLength();
        for (XMLSize_t xx = 0; xx < nodeCount; ++xx) {
            DOMNode* currentNode = children->item(xx);
            if (currentNode->getNodeType() && currentNode->getNodeType() == DOMNode::ELEMENT_NODE) {
                // Found node which is an Element. Re-cast node as element
                DOMElement* currentElement = dynamic_cast< xercesc_3_2::DOMElement* >(currentNode);
                char* message = XMLString::transcode(currentElement->getTagName());
                cout << "First child element is: " << message << endl;
                XMLString::release(&message);
            }
        }


    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    } catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
        cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return -1;
    } catch (...) {
        cout << "Unexpected Exception \n";
        return -1;
    }

    cout << xmlFile << ": parse OK" << endl;

    delete parser;
    delete errHandler;

    return 0;

  }