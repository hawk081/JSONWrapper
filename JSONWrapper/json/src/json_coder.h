#ifndef LIB_JSONCPP_JSON_CODER_H_INCLUDED
#define LIB_JSONCPP_JSON_CODER_H_INCLUDED

namespace Json {

/// Converts a UTF-8 code-point to unicode.
#if defined(_MSC_VER)
std::wstring UTF8ToUnicode(const std::string szCodePage);

/// Converts a unicode code-point to UTF-8.
std::string UnicodeToUTF8(const std::wstring szUnicode);
#endif

} // namespace Json {

#endif // LIB_JSONCPP_JSON_CODER_H_INCLUDED
