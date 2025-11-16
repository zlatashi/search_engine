#include "ConverterJSON.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

using json = nlohmann::json;

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream ifs(config_path);
    if (!ifs.is_open()) {
        throw std::runtime_error("config file is missing");
    }

    json j;
    ifs >> j;

    if (!j.contains("config") || !j.contains("files")) {
        throw std::runtime_error("config file is empty");
    }

    // version check
    if (j["config"].contains("version")) {
        std::string ver = j["config"]["version"].get<std::string>();
        if (ver != expected_version) {
            throw std::runtime_error("config.json has incorrect file version");
        }
    }
    else {
        throw std::runtime_error("config file is empty");
    }

    if (j["config"].contains("max_responses")) {
        max_responses = j["config"]["max_responses"].get<int>();
    }
    else {
        max_responses = 5;
    }

    std::vector<std::string> docs;
    for (auto& p : j["files"]) {
        std::string path = p.get<std::string>();
        std::ifstream docfs(path);
        if (!docfs.is_open()) {
            std::cout << "File not found: " << path << std::endl;
            docs.push_back("");
            continue;
        }
        std::string content;
        std::string line;
        while (std::getline(docfs, line)) {
            if (!content.empty()) content += " ";
            content += line;
        }
        docs.push_back(content);
    }

    return docs;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream ifs(requests_path);
    if (!ifs.is_open()) {
        return {};
    }

    json j;
    ifs >> j;
    if (!j.contains("requests")) return {};
    return j["requests"].get<std::vector<std::string>>();
}

int ConverterJSON::GetResponsesLimit() const {
    return max_responses;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json out;
    out["answers"] = json::object();

    for (size_t i = 0; i < answers.size(); ++i) {
        std::ostringstream idstream;
        idstream << "request" << std::setw(3) << std::setfill('0') << (i + 1);
        std::string id = idstream.str();

        const auto& res = answers[i];
        if (res.empty()) {
            out["answers"][id]["result"] = "false";
        }
        else {
            out["answers"][id]["result"] = "true";
            if (res.size() == 1) {
                out["answers"][id]["docid"] = res[0].first;
                out["answers"][id]["rank"] = res[0].second;
            }
            else {
                json relev = json::object();
                int count = 0;
                for (const auto& pr : res) {
                    if (count++ >= max_responses) break;
                    relev[std::to_string(pr.first)] = pr.second;
                }
                if (!relev.empty())
                    out["answers"][id]["relevance"] = relev;
            }
        }
    }

    std::ofstream ofs(answers_path, std::ofstream::trunc);
    ofs << std::setw(4) << out;
}
