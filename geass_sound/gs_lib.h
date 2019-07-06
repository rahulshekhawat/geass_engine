#pragma once

#ifndef GEASSSOUND_API

#ifdef GEASSSOUND_EXPORTS
#define GEASSSOUND_API __declspec(dllexport)
#else
#define GEASSSOUND_API __declspec(dllimport)
#endif

#endif // !GEASSSOUND_API


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
