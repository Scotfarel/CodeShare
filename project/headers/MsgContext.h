//
// Created by ivan on 5/22/20.
//

#ifndef CODESHARE_MSGCONTEXT_H
#define CODESHARE_MSGCONTEXT_H

#include <string>
#define MAX_CHUNK_SIZE 65000

class MsgContext {

public:
    enum { header_length = 5 };

    MsgContext();
    static MsgContext constructMsg(const std::string& chunkResponse, char isLastChunk);

    const char* data() const;
    char* getData();
    std::size_t length() const;
    const char* body() const;
    char* getBody();
    std::size_t getBodyLength() const;

    void setBodyLength(std::size_t new_length);
    void setLastChunk(char val);

    void decode_header();
    void encode_header();

    char& isThisLastChunk();

private:
    char buf_str[MAX_CHUNK_SIZE + header_length + 1]{};
    std::size_t body_size;
    char isLastChunk{};
};

#endif //CODESHARE_MSGCONTEXT_H
