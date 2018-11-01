// ===========================================================================
// 文件名：						INIFileRW.cpp
// 功能描述：INI文件读写
// 创建日期：2011-6-30
// 修改日期：
// 备注：参考NDI CombinedAPISample
// ===========================================================================

// ====================  定义  ====================
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

// ====================  头文件  ====================
#include "stdio.h"
#include "windows.h"
#include "io.h"

// ====================  变量  ====================
char	pszStringValue[256];
char	pszFileName[MAX_PATH];

// ====================  函数  ====================
void GetINIFileName();

// ================================================

// ==================================================
// 函数名：GetINIFileName
// 参数：无
// 返回值：无
// 功能：获得INI文件名
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void GetINIFileName()
{
	char
		cExecPath[MAX_PATH];
	char 
		*pszPathofFile;

	/*
	 * Get the path of the program executable since this is where the ini
	 * files are stored
	 */
	 
	if(GetModuleFileName( (HMODULE)GetModuleHandle(NULL),  cExecPath, sizeof(cExecPath)))
	{	
		pszPathofFile = strrchr(cExecPath, '\\'); /* remove the current EXE name from the path */
		if(pszPathofFile)
		{		
			*(pszPathofFile + 1) = '\0';		
		} /* if */
	} /* if */

	sprintf( pszFileName, "%sIMGRead.ini", cExecPath );
	if ( _access( pszFileName , 02 ) == -1 )
	{
		/*
		 * because we can't write to the INI file (i.e. if the executable is on a CD)
		 * we will use the Windows default, else we use the executable's path as our
		 * INI file directory.
		 */
		sprintf( pszFileName, "IMGRead.ini" );
	} /* if */
} /* GetINIFileName */

// ==================================================
// 函数名：ReadINIParm
// 参数：char *pszSection, char *pszVariableName, 
//       char *pszDefaultValue, int *nValue 
// 返回值：无
// 功能：读INI文件参数
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void ReadINIParm( char *pszSection, char *pszVariableName, char *pszDefaultValue, int *nValue )
{
	GetINIFileName();
	GetPrivateProfileString( pszSection, pszVariableName, pszDefaultValue, pszStringValue, sizeof(pszStringValue), pszFileName);
	*nValue = atoi( pszStringValue );
} /* ReadINIParm */

// ==================================================
// 函数名：ReadINIParm
// 参数：char *pszSection, char *pszVariableName, 
//       char *pszDefaultValue, bool *bValue 
// 返回值：无
// 功能：读INI文件参数
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void ReadINIParm( char *pszSection, char *pszVariableName, char *pszDefaultValue, bool *bValue )
{
	int	nValue;
	GetINIFileName();
	GetPrivateProfileString( pszSection, pszVariableName, pszDefaultValue, pszStringValue, sizeof(pszStringValue), pszFileName);
	nValue = atoi( pszStringValue );
	*bValue = ( nValue == 1 ? TRUE : FALSE );
} /* ReadINIParm */

// ==================================================
// 函数名：ReadINIParm
// 参数：char *pszSection, char *pszVariableName, 
//       char *pszDefaultValue, int nSize,
//       char *pszValue
// 返回值：无
// 功能：读INI文件参数
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void ReadINIParm( char *pszSection, char *pszVariableName, char *pszDefaultValue, int nSize, char *pszValue )
{
	GetINIFileName();
	GetPrivateProfileString( pszSection, pszVariableName, pszDefaultValue, pszValue, nSize, pszFileName);
} /* ReadINIParm */

// ==================================================
// 函数名：WriteINIParm
// 参数：char *pszSection, char *pszVariableName, 
//       char *pszValue
// 返回值：无
// 功能：写INI文件参数
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void WriteINIParm( char *pszSection, char *pszVariableName, char *pszValue )
{
	GetINIFileName();
	WritePrivateProfileString(pszSection, pszVariableName, pszValue, pszFileName);
} /* WriteINIParm */

// ==================================================
// 函数名：WriteINIParm
// 参数：char *pszSection, char *pszVariableName, 
//       int nValue
// 返回值：无
// 功能：写INI文件参数
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void WriteINIParm( char *pszSection, char *pszVariableName, int nValue )
{
	GetINIFileName();
	sprintf( pszStringValue, "%d", nValue );
	WritePrivateProfileString(pszSection, pszVariableName, pszStringValue, pszFileName);
} /* WriteINIParm */

// ==================================================
// 函数名：GetErrorResponse
// 参数：char *pszReply, char *pszErrorMsg
// 返回值：无
// 功能：获得错误响应
// 创建日期：2011-6-30
// 修改日期：
// 备注：
// =================================================
void GetErrorResponse( char *pszReply, char *pszErrorMsg )
{
	char
		chErrorToSearchFor[8],
		chReturnedMsg[256],
		cExecPath[MAX_PATH],
		*pszPathofFile;

	/* 
	 * get the programs executable's path 
	 * this is also the path that will contain the ini files
	 * for this project
	 */

	if(GetModuleFileName( (HMODULE)GetModuleHandle(NULL),  cExecPath, sizeof(cExecPath)))
	{	
		pszPathofFile = strrchr(cExecPath, '\\'); /* remove the current EXE name from the path */
		if(pszPathofFile)
		{		
			*(pszPathofFile + 1) = '\0';		
		} /* if */
	} /* if */

	/* search for the specified error message */
	sprintf( pszFileName, "%sCombinedAPIErrors.ini", cExecPath );
	
	if (!_strnicmp(pszReply, "ERROR",5))
	{
		pszReply += 5;
		sprintf( chErrorToSearchFor, "0x%c%c", pszReply[0], pszReply[1] );
		GetPrivateProfileString( "Error Messages", chErrorToSearchFor, "Unknown Error", 
								 chReturnedMsg, sizeof( chReturnedMsg ), pszFileName );
	} /* if */
	else if (!_strnicmp(pszReply, "WARNING", 7 ))
	{
		pszReply += 7;
		sprintf( chErrorToSearchFor, "0x%c%c", pszReply[0], pszReply[1] );
		GetPrivateProfileString( "Warning Messages", chErrorToSearchFor,
								 "A non-fatal tool error has been encountered", 
								 chReturnedMsg, sizeof( chReturnedMsg ), pszFileName );
	} /* else if */
	else
		sprintf( chReturnedMsg, "Unknown Error response" );

	sprintf( pszErrorMsg, chReturnedMsg );
} /* GetErrorResponse */

// ===============================  文件结束  ===============================

