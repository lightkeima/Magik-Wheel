#ifndef DATABASE_H
#define DATABASE_H

#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


class Database
{
private:
    vector<pair<string, string>> keywords;
public:
    Database() = delete;

    Database(string fpath);

    /**
     * @brief getKeyword : return the 0-index idx-th keyword and description from the database
     * @param idx: index of keyword, -1 means random keyword
     * @return tuple of string - the keyword and its description
     */
    pair<string, string> getKeyword(int idx);
};

#endif // DATABASE_H
