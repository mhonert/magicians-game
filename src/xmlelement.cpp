#include "xmlelement.h" // class's header file

XmlElement::XmlElement( TiXmlElement* p_XmlElement )
{
    if ( ! p_XmlElement )
        throw XmlException( "XML: expecting element" );
    m_XmlElement = p_XmlElement;
    m_Doc = NULL;
}

XmlElement::XmlElement( const char* p_File, const char* p_Root )
{
    m_Doc = new TiXmlDocument( p_File );
    if (! m_Doc->LoadFile() )
        throw XmlException( "XML: cannot load the file!", p_File );
    
    TiXmlHandle xmlRoot( m_Doc );
    TiXmlElement* xmlFirst = xmlRoot.FirstChildElement( p_Root ).Element();    
    if ( ! xmlFirst )
        throw XmlException( "XML: root element not found!", p_Root );
    m_XmlElement = xmlFirst;
}

const char* XmlElement::getValue()
{
    Assert ( m_XmlElement, "m_XmlElement is NULL!" );
    TiXmlNode* tmp = m_XmlElement->FirstChild();
    if ( ! tmp )
        throw XmlException( "XML: text value not available!" );
    const char* val = tmp->Value();
    if ( ! val || strlen( val ) == 0 )
        throw XmlException( "XML: text value not available!" );
    return val;
}

const char* XmlElement::getAttribute( const char* p_Name )
{
    Assert( p_Name, "parameter is NULL!" );
    Assert ( m_XmlElement, "m_XmlElement is NULL!" );    
    const char* val = m_XmlElement->Attribute( p_Name );
    if ( ! val || strlen( val ) == 0 )
        throw XmlException( "XML: attribute not available (or empty)!", p_Name );
    return val;    
}

TiXmlElement* XmlElement::getFirstChild( const char* p_Name )
{
    Assert( p_Name, "parameter is NULL!" );
    Assert ( m_XmlElement, "m_XmlElement is NULL!" );  
    
    TiXmlElement* child = m_XmlElement->FirstChildElement( p_Name );
    if ( ! child )
        throw XmlException( "XML: no child element found!", p_Name );
    return child;
}

void XmlElement::iterateChildren( const char* p_Name ) 
{
    Assert( p_Name, "parameter is NULL!" );
    Assert ( m_XmlElement, "m_XmlElement is NULL!" );  
    m_NextChild = m_XmlElement->FirstChildElement( p_Name );
}
TiXmlElement* XmlElement::nextChild()
{
    Assert ( m_XmlElement, "m_XmlElement is NULL!" );      
    Assert( m_NextChild, "m_NextChild is NULL!" );
    TiXmlElement* child = m_NextChild;
    m_NextChild = child->NextSiblingElement();
    return child;
}

bool XmlElement::isNext()
{
    Assert ( m_XmlElement, "m_XmlElement is NULL!" );
    return m_NextChild;
}

int XmlElement::getValueInt()
{
    char* val = const_cast<char*>( getValue() );
    return static_cast<int>( strtol( val, NULL, 10 ) );
}

float XmlElement::getValueFloat()
{
    char* val = const_cast<char*>( getValue() );
    return static_cast<float>( strtod( val, NULL ) );
}

int XmlElement::getAttributeInt( const char* p_Name )
{
    char* val = const_cast<char*>( getAttribute( p_Name ) );
    return static_cast<int>( strtol( val, NULL, 10 ) );
}

float XmlElement::getAttributeFloat( const char* p_Name )
{
    char* val = const_cast<char*>( getAttribute( p_Name ) );
    return static_cast<float>( strtod( val, NULL ) );
}

// class destructor
XmlElement::~XmlElement()
{
    if ( m_Doc )
    {
        delete m_Doc;
        m_Doc = NULL;
    }
}
