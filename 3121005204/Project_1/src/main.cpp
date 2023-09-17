#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include "CosineSimilarity.h"
#include "Ispunct.h"
#include "Jieba.hpp"

// D:\软工\jackchen1349\3121005204\Project_1\file\orig.txt
// D:\软工\jackchen1349\3121005204\Project_1\file\orig_0.8_add.txt 
// D:\软工\jackchen1349\3121005204\Project_1\file\result.txt


int main(int argc, char* argv[])
{
	assert(argc == 4);

	std::string line;
	std::vector<std::string> paper1;
	std::vector<std::string> paper2;
	std::vector<std::string> token1;
	std::vector<std::string> token2;
	//文件的读取
	std::ifstream file_1(argv[1]);
	if (!file_1)
	{
		std::cerr << "file1 bad\n";
		return -1;
	}
	while (file_1 >> line)
	{
		paper1.push_back(line);
	}
	file_1.close();

	std::ifstream file_2(argv[2]);
	if (!file_2)
	{
		std::cerr << "file2 bad\n";
		return -1;
	}
	while (file_2 >> line)
	{
		paper2.push_back(line);
	}
	file_2.close();

	//汉语分词
	cppjieba::Jieba jieba("../../cppjieba/dict/jieba.dict.utf8",
						  "../../cppjieba/dict/hmm_model.utf8",
						  "../../cppjieba/dict/user.dict.utf8",
						  "../../cppjieba/dict/idf.utf8",
						  "../../cppjieba/dict/stop_words.utf8");
	std::vector<std::string> words;
	std::cout << "原本：" << '\n';
	for(auto it = paper1.begin(); it != paper1.end(); it++)
	{
		words.clear();
		jieba.Cut(*it, words, true);
		for (auto& word : words)
		{
			if(Ispunct(word))
			{
				std::cout << word << "/";
				token1.push_back(word);
			}
		}  
		std::cout << "\n";
	}
	std::cout << '\n' << "副本：" << '\n';
	for(auto it = paper2.begin(); it != paper2.end(); it++)
	{
		words.clear();
		jieba.Cut(*it, words, true);
		for (auto& word : words)
		{
			if(Ispunct(word))
			{
				std::cout << word << "/";
				token2.push_back(word);
			}
		}
		std::cout << "\n";
	}
	double similarity = cosineSimilarity(token1, token2);
	std::cout << "相似度："<< similarity << '\n';
	std::ofstream file_3(argv[3]);
	if (!file_3)
	{
		std::cerr << "file3 bad\n";
		return -1;
	}
	file_3 << std::fixed << std::setprecision(2) << similarity << '\n';
	file_3.close();
	return 0;
}


