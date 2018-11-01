// ===========================================================================
// 文件名：						INIFileRW.h
// 功能描述：INI文件读写
// 创建日期：2011-6-30
// 修改日期：
// 备注：参考NDI CombinedAPISample
// ===========================================================================

// ====================  函数  ====================
void ReadINIParm( char *, char *, char *, int, char * );
void ReadINIParm( char *, char *, char *, int * );
void ReadINIParm( char *, char *, char *, bool * );

void WriteINIParm( char *, char *, int );
void WriteINIParm( char *, char *, char * );

void GetErrorResponse( char * pszReply, char * pszErrorMsg );

// ===============================  文件结束  ===============================
