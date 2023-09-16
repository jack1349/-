#include <iostream>
#include <assert.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <locale>
#include <map>
#include <iomanip>
#include "./cppjieba/Jieba.hpp"

// D:\软工\jackchen1349\3121005204\Project_1\file\orig.txt
// D:\软工\jackchen1349\3121005204\Project_1\file\orig_0.8_add.txt 
// D:\软工\jackchen1349\3121005204\Project_1\file\result.txt

// 将文本分词，并去除标点符号
bool Ispunct(std::string str)
{
	std::vector<std::string> p;
	p.push_back("，");
	p.push_back("。");
	p.push_back("“");
	p.push_back("”");
	p.push_back("！");
	p.push_back("：");
	p.push_back("？");
	p.push_back("；");
	p.push_back("、");
	p.push_back("《");
	p.push_back("》");
	std::vector<std::string>::iterator it;
	for(it = p.begin(); it != p.end(); it++)
	{
		if(!str.compare(*it))
		{
			return 0;
		}
	}
	return 1;
}

// 计算两个文本的余弦相似度
double cosineSimilarity(const std::vector<std::string>& text1Tokens, const std::vector<std::string>& text2Tokens)
{
	using namespace std;

	// 创建两个词频表，用于存储每个文本中词汇的出现次数
	map<string, int> termFrequency1;
	map<string, int> termFrequency2;

	// 计算第一个文本中每个词汇的出现次数
	for (const string& token : text1Tokens) {
		termFrequency1[token]++;
	}

	// 计算第二个文本中每个词汇的出现次数
	for (const string& token : text2Tokens) {
		termFrequency2[token]++;
	}
	// 初始化余弦相似度的相关变量
	double dotProduct = 0.0;  // 向量点积
	double magnitude1 = 0.0;  // 向量1的模长
	double magnitude2 = 0.0;  // 向量2的模长

	// 计算向量点积和模长
	for (const auto& pair : termFrequency1) {
		const string& term = pair.first;
		int tf1 = pair.second;  // 第一个文本中的词频
		int tf2 = termFrequency2[term];  // 第二个文本中的词频

		dotProduct += double(tf1 * tf2);  // 计算点积
		magnitude1 += double(tf1 * tf1);  // 计算向量1的模长
		magnitude2 += double(tf2 * tf2);  // 计算向量2的模长
	}

	// 计算向量的模长
	magnitude1 = sqrt(magnitude1);
	magnitude2 = sqrt(magnitude2);

	// 避免除以零错误，如果模长为零，则相似度为零
	if (magnitude1 == 0 || magnitude2 == 0) {
		return 0.0;
	}

	// 计算余弦相似度
	return dotProduct / (magnitude1 * magnitude2);
}


int main(int argc, char* argv[])
{
	assert(argc == 4);

	std::string line;
	std::vector<std::string> paper1;
	std::vector<std::string> paper2;
	std::vector<std::string> token1;
	std::vector<std::string> token2;

	std::ifstream file_1(argv[1]); // /home/jcakchen/project/jackchen1349/3121005204/Project_1/file/orig.txt
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


