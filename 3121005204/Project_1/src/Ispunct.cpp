﻿#include "Ispunct.h"

std::string Utf8ToGbk(const char* src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}

// 将文本分词，并去除标点符号
bool Ispunct(std::string str)
{
	std::vector<std::string> p;
	p.push_back(Utf8ToGbk("，"));
	p.push_back(Utf8ToGbk("。"));
	p.push_back(Utf8ToGbk("“"));
	p.push_back(Utf8ToGbk("”"));
	p.push_back(Utf8ToGbk("！"));
	p.push_back(Utf8ToGbk("："));
	p.push_back(Utf8ToGbk("？"));
	p.push_back(Utf8ToGbk("；"));
	p.push_back(Utf8ToGbk("、"));
	p.push_back(Utf8ToGbk("《"));
	p.push_back(Utf8ToGbk("》"));
	for (auto it = p.begin(); it != p.end(); it++)
	{
		if (!str.compare(*it))
		{
			return false;
		}
	}
	return true;
}