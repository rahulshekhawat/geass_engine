#pragma once

#ifndef GEASSENGINE_API

#ifdef GEASSENGINE_EXPORTS
#define GEASSENGINE_API __declspec(dllexport)
#else
#define GEASSENGINE_API __declspec(dllimport)
#endif

#endif // !GEASSENGINE_API


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif
