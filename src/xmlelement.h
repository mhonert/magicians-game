/** @description Wrapper for the TinyXML parser, adds exceptions and makes the
 *  use much easier.
 *  @author mhonert
 *  @version 1.0
 */

#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <tinyxml.h>
#include "xmlexception.h"
#include "debug.h"

class XmlElement
{
	public:
		XmlElement( TiXmlElement* p_XmlElement );
		XmlElement( const char* p_File, const char* p_Root );
        
        // Values
        const char* getValue();
        int getValueInt();
        float getValueFloat();
        
        // Attribute
        const char* getAttribute( const char* p_Name );
        int getAttributeInt( const char* p_Name );
        float getAttributeFloat( const char* p_Name );
        
        // Children
        TiXmlElement* getFirstChild( const char* p_Name );
        void iterateChildren( const char* p_Name );
        TiXmlElement* nextChild();
        bool isNext();
        
		~XmlElement();
	private:
        XmlElement() {}
        TiXmlElement* m_XmlElement;
        TiXmlElement* m_NextChild;
        TiXmlDocument* m_Doc;
};

#endif // XMLELEMENT_H
