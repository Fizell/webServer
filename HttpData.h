//
// Created by parallels on 2020/1/21.
//

#ifndef WEB_SERVER1_1_HTTPDATA_H
#define WEB_SERVER1_1_HTTPDATA_H
#include "UtilFun.h"
#include "WebLimit.h"
#include "Task.h"
#include <unp.h>
#include <unistd.h>
#include <functional>
#include <string>
#include "UtilFun.h"
#include <map>
#include <sys/mman.h>
#include <sys/stat.h>

using namespace std;

enum ProcessState {
    STATE_PARSE_URI = 1,
    STATE_PARSE_HEADERS,
    STATE_RECV_BODY,
    STATE_ANALYSIS,
    STATE_FINISH
};

enum URIState {
    PARSE_URI_AGAIN = 1,
    PARSE_URI_ERROR,
    PARSE_URI_SUCCESS,
};

enum HeaderState {
    PARSE_HEADER_SUCCESS = 1,
    PARSE_HEADER_AGAIN,
    PARSE_HEADER_ERROR
};

enum AnalysisState { ANALYSIS_SUCCESS = 1, ANALYSIS_ERROR };

enum ParseState {
    H_START = 0,
    H_KEY,
    H_COLON,
    H_SPACES_AFTER_COLON,
    H_VALUE,
    H_CR,
    H_LF,
    H_END_CR,
    H_END_LF
};

enum ConnectionState { H_CONNECTED = 0, H_DISCONNECTING, H_DISCONNECTED };

enum HttpMethod { METHOD_POST = 1, METHOD_GET, METHOD_HEAD };

enum HttpVersion { HTTP_10 = 1, HTTP_11 };

class HttpData {
public:
    HttpData(EventLoop *loop, int fd);
    ~HttpData();
    void readHandle();
    void writeHandle();
    void errorHandle(int fd, int err_num, string short_msg);
    AnalysisState analysisRequest();
    HeaderState parseHeaders();
    URIState parseURI();
    void getTime();
    Task *getTask() {return task_;}
private:
    int fd_;
    char ipbuf_tmp_[50];
    int n;
    char receive_buff_[MAXLINE];
    char echo_buff_[MAXLINE];
    Task *task_;
    EventLoop *loop_;
    int nowReadPos_;
    ParseState hState_;
    std::string fileName_;
    HttpVersion HTTPVersion_;
    std::map<std::string, std::string> headers_;
    bool error_;
    HttpMethod method_;
    string in_buff;
    string out_buff;
    ProcessState state_;
};

class MimeType {
private:
    static void init();
    static std::map<std::string, std::string> mime;
    MimeType();
    MimeType(const MimeType &m);

public:
    static std::string getMime(const std::string &suffix);

private:
    static pthread_once_t once_control;
};




#endif //WEB_SERVER1_1_HTTPDATA_H
