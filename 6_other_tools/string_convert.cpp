/**
 * This file includes some functions, which perform char set converting between UTF-8 and GBK on Windows system.
 *
 * After testing, it seems that for Chinese charactor, on Windows system, its char set is UTF-16, and converting 
 * to GBK can also make it display correctly, while in Linux system, the default char set is UTF-8. Besides, in 
 * most database, like MySQL, default char set is also UTF-8.
 */
#include <Windows.h>
#include <codecvt>

/**
  Converting wide char string to std::string with UTF-8 charactor set.
 */
std::string wstring_to_utf8(const std::wstring& str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
}

/**
  Coverting C-style basic string to wide char string.
  NOTE : this function using Windows API, alternating methods have to be found in Linux.
 */
std::wstring cstring_to_wstring(const char * szBuf) {
	int nLenBytesRequire = ::MultiByteToWideChar(CP_ACP,
		0,
		szBuf,
		-1,
		NULL,
		0);
	wchar_t * szWbuf = new wchar_t[nLenBytesRequire];
	::MultiByteToWideChar(CP_ACP,
		0,
		szBuf,
		-1,
		szWbuf,
		nLenBytesRequire * (sizeof(wchar_t)));

	std::wstring ret_str = szWbuf;
	delete[] szWbuf;
	return ret_str;
}

/**
  Converting UTF-8 string to GBK char-set. This is mainly used for converting strings get 
  from MySQL database, whose char set is 'utf-8'. While if you want to show Chinese charactor 
  on Windows platform with no error, you have to convert strings with Chinese from UTF-8 to GBK.

  NOTE : this function using Windows API, alternating methods have to be found in Linux.
 */
std::string utf8_to_gbk(const char* szBuf) {
	int nLenBytesRequire = ::MultiByteToWideChar(CP_UTF8, 
		0, 
		szBuf, 
		-1, 
		NULL, 
		0);
	wchar_t *wszGBK = new wchar_t[nLenBytesRequire];
	memset(wszGBK, 0, nLenBytesRequire);

	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszGBK, nLenBytesRequire);
	nLenBytesRequire = WideCharToMultiByte(CP_ACP, 
		0, 
		wszGBK, 
		-1, 
		NULL, 
		0, 
		NULL, 
		NULL);
	char *szGBK = new char[nLenBytesRequire + 1];
	memset(szGBK, 0, nLenBytesRequire + 1);
	
	WideCharToMultiByte(CP_ACP, 
		0, 
		wszGBK, 
		-1, 
		szGBK, 
		nLenBytesRequire * sizeof(char), 
		NULL, 
		NULL);
	
	std::string str_gbk = std::string(szGBK);
	delete[] szGBK;
	delete[] wszGBK;

	return str_gbk;
}