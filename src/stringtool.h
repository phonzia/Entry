/// @file StringTool.h
/// @简介    string字符串处理工具函数
/// @author 杨丰嘉
/// @version
/// @date 2013-04-09
#ifndef _STRINGTOOL_H_
#define _STRINGTOOL_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>

namespace cppbase {
namespace stringtool {
/// @简介    去除字串左边空白
///
/// @参数    source 原始字符串
///
/// @返回值    去除空白之后的字符串
std::string trimLeft(const std::string &source,
    const std::string &trimchars = "\r\n\t ");

/// @简介    去除字串右边空白
///
/// @参数    source 原始字符串
///
/// @返回值  去除空白之后的字符串
std::string trimRight(const std::string &source,
    const std::string &trimchars = "\r\n\t ");

/// @简介    去除字串首尾空白
///
/// @参数    source 原始字符串
///
/// @返回值  去除空白之后的字符串
std::string trimAll(const std::string &source,
    const std::string &trimchars = "\r\n\t ");

/// @简介    转换字串为小写
///
/// @参数    source  原始字符串
///
/// @返回值    转换为小写的字符串
std::string lowerCase(const std::string &source);

/// @简介    转换字串为大写
///
/// @参数    source  原始字符串
///
/// @返回值   转换为大写的字符串
std::string upperCase(const std::string &source);

/// @简介    替换匹配到的第一个指定子串为用于替换的子串
///
/// @参数    source  原始字符串
/// @参数    substring  要匹配的子串
/// @参数    repstring  用于替换的子串
///
/// @返回值  返回替换后的字符串
std::string replaceFirstSubStr(const std::string &source,
    const std::string &substring,
    const std::string &repstring);

/// @简介    替换匹配到的最后一个指定子串为用于替换的子串
///
/// @参数    source  原始字符串
/// @参数    substring  要匹配的子串
/// @参数    repstring  用于替换的子串
///
/// @返回值   返回替换后的字符串
std::string replaceLastSubStr(const std::string &source,
    const std::string &substring,
    const std::string &repstring);

/// @简介    替换所有找到的指定子串为用于替换的子串
///
/// @参数    source   原始字符串
/// @参数    substring  要匹配的子串
/// @参数    repstring  用于替换的子串
///
/// @返回值  返回替换后的字符串
std::string replaceAllSubStr(const std::string &source,
    const std::string &substring,
    const std::string &repstring);

/// @简介    替换匹配到的第一个指定子串为用于替换的子串,此方法会改变原始字符串
///
/// @参数    source  原始字符串
/// @参数    substring  要匹配的子串
/// @参数    repstring  用于替换的子串
///
/// @返回值  返回替换后的字符串
void replaceFirstSubStrM(std::string &source,
    const std::string &substring,
    const std::string &repstring);

/// @简介    替换匹配到的最后一个指定子串为用于替换的子串,此方法会改变原始字符串
///
/// @参数    source  原始字符串
/// @参数    substring  要匹配的子串
/// @参数    repstring  用于替换的子串
///
/// @返回值   返回替换后的字符串
void replaceLastSubStrM(std::string &source,
    const std::string &substring,
    const std::string &repstring);

/// @简介    替换所有找到的指定子串为用于替换的子串,此方法会改变原始字符串
///
/// @参数    source   原始字符串
/// @参数    substring  要匹配的子串
/// @参数    repstring  用于替换的子串
void replaceAllSubStrM(std::string &source,
    const std::string &substring,
    const std::string &repstring);

/// @简介    字符串转换函数模板,对于自定义类，需要重载operator<<
///
/// @参数    value 要转换为字符串的值
///
/// @返回值    装换后的字符串
template<typename T>
std::string toString(const T& value) {
  std::ostringstream os;
  os << value;
  return os.str();
}

/// @简介    转换字符串为整数
///
/// @参数    source  整数字符串
///
/// @返回值  如果字符串是整数，返回转换后的整数，否则返回0
int64_t strToInt(const std::string &source);

/// @简介    转换字符串为数字
///
/// @参数    source  数字字符串
///
/// @返回值   如果字符串是数字，返回转换后的浮点数，否则返回0
double strToFloat(const std::string &source);

/// @简介    转换整形数字为字符串
///
/// @参数    value
///
/// @返回值   转换后的字符串
std::string intToStr(const int64_t &value);

/// @简介    根据所给出精度转换浮点数为字符串
///
/// @参数    value  浮点数
/// @参数    precision  精度
///
/// @返回值    装换后的字符串
std::string floatToStr(const double &value,
    const int &precision = 2);

/// @简介    判断一个字符串是否为实数
///
/// @参数    source  原始字符串
///
/// @返回值    字符串为实数返回true，否则返回false
bool isNumber(const std::string &source);

/// @简介    判断一个字符串是否为整数
///
/// @参数    source  原始字符串
///
/// @返回值    字符串为整数返回true，否则返回false
bool isIntegerNumber(const std::string &source);

/// @简介    计算字符串中某个字符出现的次数
///
/// @参数    source  原始字符串
/// @参数    c  要匹配的字符
///
/// @返回值    返回匹配到c的次数
long countChar(const std::string &source, const char &c);

/// @简介    根据分隔符分割字符串
///         WARNING!!!! This function will modify the source string
///
/// @参数    source  原始字符串，分割结束后,变成分割后半段的字符串,
///                  如果原始串不包含分割字符串，分割结束，会变成空串。
/// @参数    delim  用于分割的字符串
///
/// @返回值    分割后前半段的字符串, 如果原始串不包含分割字符串，则返回原始串
std::string stringTok(std::string &source, const std::string &delim);

/// @简介    根据分隔符分割字符串，并返回分割后的字符串列表
///
/// @参数    source 原始字符串
/// @参数    delim 分割符
///
/// @返回值    存有分割后的字符串列表的vector
std::vector<std::string> stringSplit(const std::string &source,
    const std::string &delim);

/// @简介    去除字符串中多余空白
///
/// @参数    source 原始字符串
///
/// @返回值    去除多余空白之后的字符串
std::string trimOverSpace(const std::string &source);

/* @简介    截取指定长度的utf8编码的字符串
 * @参数    name 原始的utf8编码的字符串
 *          clength 要取的字数
 * @返回值  返回前clength的字符串
 */
std::string captureUTF8string(const std::string &source, const int clength=20);

}; // end namespace stringtool
}; // end namespace cppbase
#endif
