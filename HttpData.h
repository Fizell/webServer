//
// Created by parallels on 2020/1/21.
//

#ifndef WEB_SERVER1_1_HTTPDATA_H
#define WEB_SERVER1_1_HTTPDATA_H
#include "UtilFun.h"
#include "WebLimit.h"
#include "Task.h"
#include <unistd.h>
#include <string.h>
#include <functional>
#include <string>
#include <fcntl.h>
#include "UtilFun.h"
#include "Timer.h"

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

class Task;
class EventLoop;
class Timer;
class HttpData {
public:
    HttpData(EventLoop *loop, int fd, std::shared_ptr<Task> task);
    ~HttpData();
    void readHandle();
    void writeHandle();
    void quit();
    void errorHandle(int fd, int err_num, string short_msg);
    void linkTimer(std::weak_ptr<Timer> timer) {timer_ = timer;}
    AnalysisState analysisRequest();
    HeaderState parseHeaders();
    URIState parseURI();
    //打印时间戳
    void getTime();
    std::shared_ptr<Task> getTask() {return task_;}
    bool isClose() {return closed_;}

private:
    std::shared_ptr<Task> task_;
    EventLoop *loop_;
    int fd_;
    bool closed_;
    int n;
    char receive_buff_[MAXLINE];
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
    std::weak_ptr<Timer> timer_;
    MutexLock mutex_;
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
