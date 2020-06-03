//
// Created by ivan on 5/22/20.
//

#ifndef CODESHARE_MSGCONTEXT_H
#define CODESHARE_MSGCONTEXT_H

#include <string>
#include <cstring>

#define MAX_CHUNK_SIZE 65000
#define HEADER 5

class MsgContext {
private:
    char buf_str[MAX_CHUNK_SIZE + HEADER + 1]{};
    std::size_t body_size;
    char isLastChunk{};

public:
    MsgContext();

    static MsgContext createMessage(const std::string& chunkResponse, char isLastChunk);

    // Getters
    const char* data() const;

    char* getData();

    const char* body() const;

    char* getBody();

    std::size_t length() const;

    std::size_t getBodyLength() const;

    // Setters
    void setBodyLength(std::size_t new_length);

    void setLastChunk(char val);

    // Serializers
    void decodeHeader();

    void encodeHeader();

    char& isThisLastChunk();
};

#endif //CODESHARE_MSGCONTEXT_H