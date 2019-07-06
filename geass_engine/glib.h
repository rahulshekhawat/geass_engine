#pragma once

#ifndef GEASS_API

#ifdef GEASSENGINE_EXPORTS
#define GEASS_API __declspec(dllexport)
#else
#define GEASS_API __declspec(dllimport)
#endif

#endif // !GEASS_API


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
