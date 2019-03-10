#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <string>
using namespace std;

/**
 * This exception is thrown for errors that may occur in XmlElement.
 */
class XmlException
{
	public:
		// class constructor
		XmlException( const char* p_Message )
		{
            m_Message = strdup( p_Message );
        }
        XmlException( const char* p_Message, const char* p_Info )
		{
            m_Message = new char[strlen(p_Message) + strlen(p_Info) + 3];
            strcpy( m_Message, const_cast<char*>( p_Message ) );
            strcat( m_Message, " - " );
            strcat( m_Message, const_cast<char*>( p_Info ) );
        }
        const char* getMessage()
        {
            return m_Message;
        }
		~XmlException() { delete m_Message; }


	private:
        XmlException() {}
        char* m_Message;
};

#endif // XMLEXCEPTION_H
