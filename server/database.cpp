#include "database.h"

Database::Database(string fpath)
{
    string ext = fpath.substr(fpath.find(".") + 1);

    if (ext == "json") {
        ifstream fin(fpath);
        json database_json = json::parse(fin);
        for (auto& k : database_json) {
            this->keywords.emplace_back(k["keyword"], k["description"]);
        }
    } else if (ext == "txt") {
        ifstream fin(fpath);
        string numKeywordsStr;
        getline(fin, numKeywordsStr);
        int numKeywords = stoi(numKeywordsStr);

        for(int i = 0; i < numKeywords; i++) {
            string keyword, desc;
            getline(fin, keyword);
            getline(fin, desc);
            this->keywords.emplace_back(keyword, desc);
        }

    }
}

pair<string, string> Database::getKeyword(int idx)
{
    if (idx == -1) {
        srand(time(NULL));
        // Randomize from the databse
        idx = rand() % (int) this->keywords.size();
    }
    return this->keywords[idx];
}
