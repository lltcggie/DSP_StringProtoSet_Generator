#include <iostream>
#include "StringProtoSet.h"
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>


std::vector<uint8_t> readFile(const char* fname)
{
	FILE* fp = fopen(fname, "rb");
	if (!fp) {
		return std::vector<uint8_t>();
	}

	fseek(fp, 0, SEEK_END);
	const auto size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	std::vector<uint8_t> buf;
	buf.resize(size);
	fread(buf.data(), 1, size, fp);
	fclose(fp);

	return buf;
}

bool writeFile(const char* fname, const std::vector<uint8_t>& data)
{
	FILE* fp = fopen(fname, "wb");
	if (!fp) {
		return false;
	}

	fwrite(data.data(), 1, data.size(), fp);
	fclose(fp);

	return true;
}

std::vector<std::string> split(const std::string& input, char delimiter)
{
	std::istringstream stream(input);
	std::string field;
	std::vector<std::string> result;
	while (std::getline(stream, field, delimiter)) {
		result.push_back(field);
	}
	return result;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
	size_t startPos = 0;
	while ((startPos = str.find(from, startPos)) != std::string::npos) {
		str.replace(startPos, from.length(), to);
		startPos += to.length();
	}
	return str;
}

int main(int argc, char* argv[])
{
	if (argc != 4) {
		printf("%s src_StringProtoSet src_text out_StringProtoSet\n", argv[0]);
		return 1;
	}

	DSP::StringProtoSet src;

	{
		std::vector<uint8_t> buf = readFile(argv[1]);
		Deserializer d;
		d.setData(buf);
		d >> src;
	}

	// IDからsrc.dataArrayのインデックスへの変換マップ
	std::unordered_map<int32_t, size_t> IDtoSetIndexMap;
	IDtoSetIndexMap.reserve(src.dataArray.size());

	for (size_t i = 0; i < src.dataArray.size(); i++) {
		IDtoSetIndexMap[src.dataArray[i].ID] = i;
	}

	DSP::StringProtoSet dst = src;

	// [CRLF]は\r\nに、[CR]は\rに、[LF]は\nに変換する
	// テキストを書き換える
	dst.dataArray = src.dataArray;
	{
		std::ifstream input_file(argv[2]);
		if (!input_file.is_open()) {
			std::cerr << "Could not open the file: "
				<< argv[2] << std::endl;
			return EXIT_FAILURE;
		}

		int64_t lineCounter = 0;
		std::string line;
		while (std::getline(input_file, line)) {
			lineCounter++;
			if (lineCounter <= 4) { // ヘッダは飛ばす
				continue;
			}

			auto v = split(line, '\t');
			const auto ID = atoi(v[1].c_str());
			std::string japanese = v[3];

			japanese = replaceAll(japanese, "[CR]", "\r");
			japanese = replaceAll(japanese, "[LF]", "\n");
			japanese = replaceAll(japanese, "[CRLF]", "\n");

			auto it = IDtoSetIndexMap.find(ID);
			if (it == IDtoSetIndexMap.end()) {
				continue;
			}

			dst.dataArray[it->second].ZHCN = japanese;
		}
	}
	{
		Serializer s;
		s << dst;
		writeFile(argv[3], s.getData());
	}

	return 0;
}
