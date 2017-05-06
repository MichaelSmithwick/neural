#ifndef _VERSION_H_
#define _VERSION_H_

namespace AutoVersion{
	
	//Date Version Types
	static const char _ver_DATE[] = "05";
	static const char _ver_MONTH[] = "05";
	static const char _ver_YEAR[] = "2017";
	static const char _ver_UBUNTU_VERSION_STYLE[] =  "17.05";
	
	//Software Status
	static const char _ver_STATUS[] =  "Alpha";
	static const char _ver_STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long _ver_MAJOR  = 0;
	static const long _ver_MINOR  = 1;
	static const long _ver_BUILD  = 3;
	static const long _ver_REVISION  = 0;
	
	//Miscellaneous Version Types
	static const long _ver_BUILDS_COUNT  = 241;
	#define _ver_RC_FILEVERSION 0,1,3,0
	#define _ver_RC_FILEVERSION_STRING "0, 1, 3, 0\0"
	static const char _ver_FULLVERSION_STRING [] = "0.1.3.0";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long _ver_BUILD_HISTORY  = 12;
	

}
#endif //_VERSION_H_
