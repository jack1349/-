#include "pch.h"
#include "CppUnitTest.h"
#include "CosineSimilarity.h"
#include "Ispunct.h"
#include "../Project_1/src/main.cpp"
#include "Jieba.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::vector<std::string> paper1, paper2, words;
			std::string p1= "今天是星期天，天气晴，今天晚上我要去看电影";
			std::string p2= "今天是周天，天气晴朗，我晚上要去看电影。";

			cppjieba::Jieba jieba("../../cppjieba/dict/jieba.dict.utf8",
				"../../cppjieba/dict/hmm_model.utf8",
				"../../cppjieba/dict/user.dict.utf8",
				"../../cppjieba/dict/idf.utf8",
				"../../cppjieba/dict/stop_words.utf8");
			words.push_back("，");
			words.push_back("。");
			words.push_back("？");
			for (std::string& word : words)
			{
				Assert::AreEqual(Ispunct(word), false);
			}
			words.clear();
			words.push_back(".");
			words.push_back(",");
			for (std::string& word : words)
			{
				Assert::AreEqual(Ispunct(word), true);
			}
			words.clear();
			jieba.Cut(p1, words, true);
			for (auto& word : words)
			{
				if (Ispunct(word))
				{
					std::cout << word << "/";
					paper1.push_back(word);
				}
			}
			std::cout << '\n';
			words.clear();

			jieba.Cut(p2, words, true);
			for (auto& word : words)
			{
				if (Ispunct(word))
				{
					std::cout << word << "/";
					paper2.push_back(word);
				}
			}
			double result = cosineSimilarity(paper1, paper2);
			Assert::AreEqual((result > 0.9), true);
		}
	};
}
