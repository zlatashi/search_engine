#include "SearchServer.h"
#include <sstream>
#include <set>
#include <map>
#include <algorithm>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> results;
    results.reserve(queries_input.size());

    for (const auto& query : queries_input) {
        std::istringstream iss(query);
        std::string word;
        std::set<std::string> unique_words;

        while (iss >> word) {
            unique_words.insert(word);
        }

        std::map<size_t, float> doc_to_abs_relevance; // doc_id -> absolute relevance

        for (const auto& w : unique_words) {
            auto entries = _index.GetWordCount(w);
            for (const auto& e : entries) {
                doc_to_abs_relevance[e.doc_id] += static_cast<float>(e.count);
            }
        }

        std::vector<RelativeIndex> rels;
        if (!doc_to_abs_relevance.empty()) {
            float max_abs = 0.0f;
            for (const auto& p : doc_to_abs_relevance) {
                if (p.second > max_abs) max_abs = p.second;
            }
            for (const auto& p : doc_to_abs_relevance) {
                RelativeIndex ri;
                ri.doc_id = p.first;
                ri.rank = (max_abs > 0.f) ? (p.second / max_abs) : 0.f;
                rels.push_back(ri);
            }

            std::sort(rels.begin(), rels.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
                if (a.rank == b.rank) return a.doc_id < b.doc_id;
                return a.rank > b.rank;
                });

            if (rels.size() > TOP_RESULTS) rels.resize(TOP_RESULTS);
        }

        results.push_back(std::move(rels));
    }

    return results;
}
