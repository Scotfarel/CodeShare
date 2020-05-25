//
// Created by ivan on 5/22/20.
//

#include <MsgContext.h>
#include <cstring>

MsgContext::MsgContext() : body_size(0) {}

const char *MsgContext::data() const {
    return buf_str;
}

char *MsgContext::getData() {
    return buf_str;
}

std::size_t MsgContext::length() const {
    return header_length + body_size;
}

const char *MsgContext::body() const {
    return buf_str + header_length;
}

char *MsgContext::getBody() {
    return buf_str + header_length;
}

std::size_t MsgContext::getBodyLength() const {
    return body_size;
}

void MsgContext::setBodyLength(std::size_t new_length) {
    body_size = new_length;
}

void MsgContext::decode_header() {
    char header[header_length + 2] = "";
    std::strncat(header, buf_str + 1, header_length);
    body_size = std::atoi(header);
    this->setLastChunk(*buf_str);
}

void MsgContext::encode_header() {
    char header[header_length + 1] = "";
    std::sprintf(header, "%5d", static_cast<int>(body_size));
    std::memcpy(buf_str + 1, header, header_length);
}

char& MsgContext::isThisLastChunk() {
    return isLastChunk;
}

void MsgContext::setLastChunk(char val) {
    this->isLastChunk = val;
}

MsgContext MsgContext::constructMsg(const std::string& chunkResponse, char isLastChunk) {
    //Send data (header and body)
    MsgContext msg;
    msg.setLastChunk(isLastChunk);
    msg.setBodyLength(chunkResponse.size());
    std::memcpy(msg.getBody()+1, chunkResponse.data(), msg.getBodyLength());
    msg.setBodyLength(chunkResponse.size());
    msg.getBody()[msg.getBodyLength()+1] = '\0';
    msg.encode_header();
    std::memcpy(msg.getData(), &msg.isThisLastChunk(), 1);
    return msg;
}


