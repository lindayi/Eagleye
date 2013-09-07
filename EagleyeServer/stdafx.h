// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



#include "Bin/Skins/EagleyeServer/Resource.h"
#include <LibUIDK.h>
using namespace LibUIDK;

#if(_MSC_VER == 1200) // VC6.0
	#ifdef _DEBUG
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK60ud.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs60ud.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK60d.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs60d.lib")
			#endif
		#endif // end _UNICODE
	#else // Release
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK60u.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs60u.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK60.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs60.lib")
			#endif
		#endif // end _UNICODE
	#endif
#endif
#if (_MSC_VER == 1310) // VC2003
	#ifdef _DEBUG
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK71ud.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs71ud.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK71d.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs71d.lib")
			#endif
		#endif // end _UNICODE
	#else // Release
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK71u.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs71u.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK71.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs71.lib")
			#endif
		#endif // end _UNICODE
	#endif
#endif
#if (_MSC_VER == 1400)	// VC2005
	#ifdef _DEBUG
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK80ud.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs80ud.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK80d.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs80d.lib")
			#endif
		#endif // end _UNICODE
	#else // Release
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK80u.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs80u.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK80.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs80.lib")
			#endif
		#endif // end _UNICODE
	#endif
#endif
#if (_MSC_VER == 1500)	// VC2008
	#ifdef _DEBUG
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK90ud.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs90ud.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK90d.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs90d.lib")
			#endif
		#endif // end _UNICODE
	#else // Release
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK90u.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs90u.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK90.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs90.lib")
			#endif
		#endif // end _UNICODE
	#endif
#endif
#if (_MSC_VER == 1600)	// VC2010
	#ifdef _DEBUG
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK100ud.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs100ud.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK100d.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs100d.lib")
			#endif
		#endif // end _UNICODE
	#else // Release
		#ifdef _UNICODE
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK100u.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs100u.lib")
			#endif
		#else // ANSI
			#ifdef _AFXDLL
				#pragma comment (lib, "LibUIDK100.lib")
			#else // Static
				#pragma comment (lib, "LibUIDKs100.lib")
			#endif
		#endif // end _UNICODE
	#endif
#endif
