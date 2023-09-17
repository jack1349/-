#include "CosineSimilarity.h"


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

		dotProduct += (double)tf1 * (double)tf2;  // 计算点积
		magnitude1 += (double)tf1 * (double)tf1;  // 计算向量1的模长
		magnitude2 += (double)tf2 * (double)tf2;  // 计算向量2的模长
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