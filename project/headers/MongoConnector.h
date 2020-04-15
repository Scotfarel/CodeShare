//
// Created by ivan on 4/15/20.
//

#ifndef CODESHARE_MONGOCONNECTOR_H
#define CODESHARE_MONGOCONNECTOR_H

#include <string>

class MongoConnector {
public:
    MongoConnector(std::string db, std::string coll) : dbName(db), collName(coll);
    std::string getCurrText();
    bool saveDiff();

private:
    std::string dbName;
    std::string collName;

    mongocxx::instance instance;
    mongocxx::client client;
    mongocxx::database database;
    mongocxx::collection collection;

    bool createTextTable(std::string tableName);
};

#endif //CODESHARE_MONGOCONNECTOR_H
