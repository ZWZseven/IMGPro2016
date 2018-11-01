// ===========================================================================
// �ļ�����						INIFileRW.cpp
// ����������INI�ļ���д
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע���ο�NDI CombinedAPISample
// ===========================================================================

// ====================  ����  ====================
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

// ====================  ͷ�ļ�  ====================
#include "stdio.h"
#include "windows.h"
#include "io.h"

// ====================  ����  ====================
char	pszStringValue[256];
char	pszFileName[MAX_PATH];

// ====================  ����  ====================
void GetINIFileName();

// ================================================

// ==================================================
// ��������GetINIFileName
// ��������
// ����ֵ����
// ���ܣ����INI�ļ���
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
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
// ��������ReadINIParm
// ������char *pszSection, char *pszVariableName, 
//       char *pszDefaultValue, int *nValue 
// ����ֵ����
// ���ܣ���INI�ļ�����
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
// =================================================
void ReadINIParm( char *pszSection, char *pszVariableName, char *pszDefaultValue, int *nValue )
{
	GetINIFileName();
	GetPrivateProfileString( pszSection, pszVariableName, pszDefaultValue, pszStringValue, sizeof(pszStringValue), pszFileName);
	*nValue = atoi( pszStringValue );
} /* ReadINIParm */

// ==================================================
// ��������ReadINIParm
// ������char *pszSection, char *pszVariableName, 
//       char *pszDefaultValue, bool *bValue 
// ����ֵ����
// ���ܣ���INI�ļ�����
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
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
// ��������ReadINIParm
// ������char *pszSection, char *pszVariableName, 
//       char *pszDefaultValue, int nSize,
//       char *pszValue
// ����ֵ����
// ���ܣ���INI�ļ�����
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
// =================================================
void ReadINIParm( char *pszSection, char *pszVariableName, char *pszDefaultValue, int nSize, char *pszValue )
{
	GetINIFileName();
	GetPrivateProfileString( pszSection, pszVariableName, pszDefaultValue, pszValue, nSize, pszFileName);
} /* ReadINIParm */

// ==================================================
// ��������WriteINIParm
// ������char *pszSection, char *pszVariableName, 
//       char *pszValue
// ����ֵ����
// ���ܣ�дINI�ļ�����
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
// =================================================
void WriteINIParm( char *pszSection, char *pszVariableName, char *pszValue )
{
	GetINIFileName();
	WritePrivateProfileString(pszSection, pszVariableName, pszValue, pszFileName);
} /* WriteINIParm */

// ==================================================
// ��������WriteINIParm
// ������char *pszSection, char *pszVariableName, 
//       int nValue
// ����ֵ����
// ���ܣ�дINI�ļ�����
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
// =================================================
void WriteINIParm( char *pszSection, char *pszVariableName, int nValue )
{
	GetINIFileName();
	sprintf( pszStringValue, "%d", nValue );
	WritePrivateProfileString(pszSection, pszVariableName, pszStringValue, pszFileName);
} /* WriteINIParm */

// ==================================================
// ��������GetErrorResponse
// ������char *pszReply, char *pszErrorMsg
// ����ֵ����
// ���ܣ���ô�����Ӧ
// �������ڣ�2011-6-30
// �޸����ڣ�
// ��ע��
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

// ===============================  �ļ�����  ===============================

