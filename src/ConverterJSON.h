#pragma once

#include <string>
#include <vector>

class ConverterJSON {
public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    std::vector<std::string> GetRequests();

    int GetResponsesLimit() const;

    void putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

private:
    std::string config_path = "config.json";
    std::string requests_path = "requests.json";
    std::string answers_path = "answers.json";

    std::string expected_version = "0.1";
    mutable int max_responses = 5;
};
