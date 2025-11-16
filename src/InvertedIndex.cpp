#include "InvertedIndex.h"
#include <sstream>
#include <map>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    std::lock_guard<std::mutex> guard(mtx);

    docs = std::move(input_docs);
    freq_dictionary.clear();

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        std::istringstream iss(docs[doc_id]);
        std::string word;
        std::map<std::string, size_t> local_count;

        while (iss >> word) {
            local_count[word] += 1;
        }

        for (const auto& p : local_count) {
            freq_dictionary[p.first].push_back({ doc_id, p.second });
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::lock_guard<std::mutex> guard(mtx);
    auto it = freq_dictionary.find(word);
    if (it == freq_dictionary.end()) return {};
    return it->second;
}
