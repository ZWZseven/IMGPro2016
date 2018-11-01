/*

  Ultra-lightweight std::string additions. (Should be) UNICODE compatible.
  
(C) Jerry Evans 2002
jerry@chordia.co.uk	
		 		  
*/

#ifndef STRINGEX_H
#define STRINGEX_H

#include <string>
#include <algorithm>
#include <vector>
#include <stdio.h>

#ifndef UNICODE
#ifndef _TEXT
#define _TEXT(T) T
#endif
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

class CStringEx : public std::string
{
	// size of Format() buffer.
	enum { _MAX_CHARS = 8096 };
	
public:
	
	CStringEx(){}
	~CStringEx(){}
	
	// various constructor flavours
	CStringEx(const CStringEx& arg)	{ assign(arg.c_str()); }
	CStringEx(const std::string& arg)	{ assign(arg); }
	CStringEx(const TCHAR* pArg)		{ assign(pArg); }
	
	// various assignment operator flavours
	CStringEx& operator=(const TCHAR* pArg)		{ assign(pArg); return (*this); }
	CStringEx& operator=(const std::string& arg)	{ assign(arg); return (*this); }
	CStringEx& operator=(const CStringEx& arg)	{ assign(arg.c_str()); return (*this); }
	
	// the essential MFC member functions
	int Format(const TCHAR* szFormat,...)
	{
		std::vector<TCHAR> _buffer(_MAX_CHARS);
		va_list argList;
		va_start(argList,szFormat);
#ifdef _UNICODE
		int ret = _vsnwprintf(&_buffer[0],_MAX_CHARS,szFormat,argList);
#else
		int ret = _vsnprintf(&_buffer[0],_MAX_CHARS,szFormat,argList);
#endif
		va_end(argList);
		assign(&_buffer[0],ret);
		return ret;
	}
	
	// this returns a reference so you can do things like this:
	// CStringEx query = "abc";
	// query += CStringEx().Format("%d %s",1,"abc");
	CStringEx& FormatEx(const TCHAR* szFormat,...)
	{
		std::vector<TCHAR> _buffer(_MAX_CHARS);
		va_list argList;
		va_start(argList,szFormat);
#ifdef _UNICODE
		int ret = _vsnwprintf(&_buffer[0],_MAX_CHARS,szFormat,argList);
#else
		int ret = _vsnprintf(&_buffer[0],_MAX_CHARS,szFormat,argList);
#endif
		va_end(argList);
		assign(&_buffer[0],ret);
		return (*this);
	}
	// trim the right hand of the string of whitespace characters
	CStringEx& TrimRight(const TCHAR* pszDelimiters = _TEXT(" \t\r\n"))
	{
		size_type idx = find_last_not_of(pszDelimiters);
		if (idx != std::string::npos)
		{
			erase(++idx);
		}
		return *this;
	}
	
    // trim the right hand of the string of whitespace characters
    CStringEx& TrimLeft(const TCHAR* pszDelimiters = _TEXT(" \t\r\n"))
    {
        size_type idx = find_first_not_of(pszDelimiters);
        if (idx != std::string::npos)
        {
            erase(0,idx);
        }
        else
        {
			erase();
        }
        return *this;
    }
	
	CStringEx& GetField(const TCHAR* delim,int fieldnum)
	{
		int lenDelim=lstrlen(delim);
		
		size_type idx;
		
		while (--fieldnum>=0)
		{
			idx=find(delim);
			erase(0,lenDelim+idx);						
		}
		
		idx=find(delim);
		if (idx != std::string::npos)
		{
			erase(idx,this->npos);
			return *this;
		}
		else 
			return *this;
	}
	
	CStringEx& Replace(const TCHAR* oldstr,const TCHAR* newstr)
	{
		CStringEx oldone(oldstr);

		size_type idx=0;
		while ((idx=find(oldstr))!=npos){
			erase(idx,oldone.length());
			insert(idx,newstr);
		}
		return *this;
		
	}
	
	
    // trim leading and trailing whitespace
    CStringEx& TrimAll(const TCHAR* pszDelimiters = _TEXT(" \t\r\n"))
    {
		return TrimLeft(pszDelimiters).TrimRight(pszDelimiters);
    }
	
	// convert to upper and lower case
	CStringEx& MakeUpper()	{ std::transform(begin(),end(),begin(),toupper); return (*this); }
	CStringEx& MakeLower()	{ std::transform(begin(),end(),begin(),tolower); return (*this); }
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------


#endif
