#pragma once

#include "MWString.h"
#include "MWTString.h"

namespace Myway
{

struct IPropertyObj;

enum OPEN_MODE
{
	OM_READ						= 1,
	OM_WRITE					= 2,
	OM_READ_WRITE				= 3,
	OM_APPEND					= 4,
	OM_READ_WRITE_APPEND		= 5,

    OM_READ_BINARY              = 6,
    OM_WRITE_BINARY  			= 7,
    OM_READ_WRITE_BINARY  		= 8,
    OM_APPEND_BINARY  			= 9,
    OM_READ_WRITE_APPEND_BINARY = 10,
};

class MW_ENTRY File : public AllocObj
{
public:
	File();
	~File();

	bool			Open(const char * file, OPEN_MODE mode = OM_WRITE_BINARY);
	void			Close();
	bool			IsOpen();
	bool			Skip(int offset);
	bool			Seek(int pos);
	int			    Position();
	int			    Size();
    //int          Length();
    void            Flush();
    bool            eof();
	const TString128 &	FileName();

	File & operator >>(bool & data);
    File & operator >>(char & data);
	File & operator >>(int & data);
    File & operator >>(float & data);
    File & operator >>(double & data);
    File & operator >>(String & data);

	File & operator <<(bool data);
    File & operator <<(char data);
    File & operator <<(int data);
    File & operator <<(float data);
    File & operator <<(double data);
    File & operator <<(const char * data);
	File & operator <<(const String & data);

    int Write(const void * data, int esize, int count = 1);
    int Read(void * data, int esize, int count = 1);

    bool ReadLine(char * data);
    bool ReadLine(String & data);
    bool ReadString(String & data);
    bool WriteString(const String & data);
	
	void WriteProperty(IPropertyObj * obj);
	void ReadProperty(IPropertyObj * obj);

    static TString128 GetExternName(const TString128 & file);
	static TString128 GetFileDir(const TString128 & file);
    static TString128 GetBaseName(const TString128 & file);
    static TString128 RemoveExternName(const TString128 & file);
	static TString128 GetAbsoluteFileName(const TString128 & file);

	static bool Exist(const TString128 & file);

private:
	File(const File & file);
	File & operator =(const File & file);
	bool operator ==(const File & file);

public:
    static const char ENDL;

private:
	FILE *		mHandle;
	OPEN_MODE	mMode;
	TString128  mFile;
    bool        mEof;
};

#include "MWFile.inl"

} // end namespace Myway