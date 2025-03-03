// 
// AYA version 5
//
// 外部ライブラリを扱うクラス　CLib/CLib1
// written by umeici. 2004
// 
// CLibが全体を管理します。個々のDLLはCLib1で管理します。
//

#ifndef	LIBH
#define	LIBH

//----

#if defined(WIN32)
# include "stdafx.h"
#endif

#include <list>

#include "aya5.h"
#include "globaldef.h"
#include "manifest.h"

class CAyaVM;


#if defined(WIN32)
	typedef HMODULE	module_t;
#elif defined(POSIX)
	typedef void*	module_t;
#endif


class	CLib1
{
protected:
	yaya::string_t	name;
	yaya::global_t (*requestlib)(yaya::global_t h, long *len);

	module_t hDLL;
	bool    isAlreadyLoaded;
	int		charset;

private:
	CLib1(void);

	CAyaVM &vm;

public:
	CLib1(CAyaVM &vmr, const yaya::string_t &n, int cs) : vm(vmr)
	{
		name    = n;
		charset = cs;
		hDLL    = NULL;
		requestlib = NULL;
		isAlreadyLoaded = false;
	}

	~CLib1(void) { Unload(); Release(); }

	yaya::string_t	GetName(void) { return name; }

	int		LoadLib(void);
	int		Load(void);
	int		Unload(void);
	void	Release(void);

	void	SetCharset(int cs) { charset = cs; }
	int		GetCharset(void) { return charset; }

	int		Request(const yaya::string_t &istr, yaya::string_t &ostr);
};

//----

typedef std::map<yaya::string_t,int> charset_map;

class	CLib
{
protected:
	std::list<CLib1>	liblist;
	charset_map charset_temp_map;
	int			charset;

private:
	CAyaVM &vm;

	CLib(void);

public:
	CLib(CAyaVM &vmr) : vm(vmr) {
		charset = CHARSET_UTF8;
	}
	~CLib(void) { DeleteAll(); }

	void	SetCharset(int cs) { charset = cs; }
	int		SetCharsetDynamic(const yaya::string_t &name,int cs);

	int		GetCharset(void) { return charset; }
	int		GetCharsetDynamic(const yaya::string_t &name);

	int		Add(const yaya::string_t &name);
	int		Delete(const yaya::string_t &name);
	void	DeleteAll(void);

	int		Request(const yaya::string_t &name, const yaya::string_t &istr, yaya::string_t &ostr);
};

//----

#endif
