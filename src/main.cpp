#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <iostream>
#include <vector>

int main() {
    try {
        ConverterJSON converter;

        std::vector<std::string> docs = converter.GetTextDocuments(); // may throw
        std::vector<std::string> requests = converter.GetRequests();   // returns empty if missing
        int max_responses = converter.GetResponsesLimit();

        InvertedIndex idx;
        idx.UpdateDocumentBase(docs);

        SearchServer srv(idx);
        std::vector<std::vector<RelativeIndex>> answers = srv.search(requests);

        // convert to expected format: vector<vector<pair<int,float>>>
        std::vector<std::vector<std::pair<int, float>>> out;
        out.reserve(answers.size());
        for (const auto& vec : answers) {
            std::vector<std::pair<int, float>> tmp;
            for (const auto& r : vec) {
                tmp.emplace_back(static_cast<int>(r.doc_id), r.rank);
            }
            out.push_back(std::move(tmp));
        }

        converter.putAnswers(out);

        std::cout << "Starting. Search completed. Check answers.json\n";
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
