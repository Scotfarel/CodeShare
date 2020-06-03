#ifndef HEADERS_MESSAGE_H_
#define HEADERS_MESSAGE_H_
#include <string>
#include <iostream>
#define MAX_CHUNK_LENGTH 65000

class Message {
 public:
    enum { header_length = 5 };
    Message();
    const char* data() const;
    char* data();
    std::size_t length() const;
    const char* body() const;
    char* body();
    std::size_t body_length() const;
    void body_length(std::size_t new_length);
    void decode_header();
    void encode_header();
    void reset_data();
    char& is_last_chunk();
    void set_last_chunk(char val);
    static Message construct_msg(const std::string& chunkResponse, char isLastChunk);

 private:
    char data_[MAX_CHUNK_LENGTH + header_length + 1];
    std::size_t body_length_;
    char isLastChunk;
};
#endif  // HEADERS_MESSAGE_H_
