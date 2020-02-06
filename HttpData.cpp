//
// Created by parallels on 2020/1/21.
//

#include <sys/epoll.h>
#include "HttpData.h"
#include <time.h>
#include <cstring>
#include <arpa/inet.h>




pthread_once_t MimeType::once_control = PTHREAD_ONCE_INIT;
std::map<std::string, std::string> MimeType::mime;

char favicon[555] = {
        '\x89', 'P',    'N',    'G',    '\xD',  '\xA',  '\x1A', '\xA',  '\x0',
        '\x0',  '\x0',  '\xD',  'I',    'H',    'D',    'R',    '\x0',  '\x0',
        '\x0',  '\x10', '\x0',  '\x0',  '\x0',  '\x10', '\x8',  '\x6',  '\x0',
        '\x0',  '\x0',  '\x1F', '\xF3', '\xFF', 'a',    '\x0',  '\x0',  '\x0',
        '\x19', 't',    'E',    'X',    't',    'S',    'o',    'f',    't',
        'w',    'a',    'r',    'e',    '\x0',  'A',    'd',    'o',    'b',
        'e',    '\x20', 'I',    'm',    'a',    'g',    'e',    'R',    'e',
        'a',    'd',    'y',    'q',    '\xC9', 'e',    '\x3C', '\x0',  '\x0',
        '\x1',  '\xCD', 'I',    'D',    'A',    'T',    'x',    '\xDA', '\x94',
        '\x93', '9',    'H',    '\x3',  'A',    '\x14', '\x86', '\xFF', '\x5D',
        'b',    '\xA7', '\x4',  'R',    '\xC4', 'm',    '\x22', '\x1E', '\xA0',
        'F',    '\x24', '\x8',  '\x16', '\x16', 'v',    '\xA',  '6',    '\xBA',
        'J',    '\x9A', '\x80', '\x8',  'A',    '\xB4', 'q',    '\x85', 'X',
        '\x89', 'G',    '\xB0', 'I',    '\xA9', 'Q',    '\x24', '\xCD', '\xA6',
        '\x8',  '\xA4', 'H',    'c',    '\x91', 'B',    '\xB',  '\xAF', 'V',
        '\xC1', 'F',    '\xB4', '\x15', '\xCF', '\x22', 'X',    '\x98', '\xB',
        'T',    'H',    '\x8A', 'd',    '\x93', '\x8D', '\xFB', 'F',    'g',
        '\xC9', '\x1A', '\x14', '\x7D', '\xF0', 'f',    'v',    'f',    '\xDF',
        '\x7C', '\xEF', '\xE7', 'g',    'F',    '\xA8', '\xD5', 'j',    'H',
        '\x24', '\x12', '\x2A', '\x0',  '\x5',  '\xBF', 'G',    '\xD4', '\xEF',
        '\xF7', '\x2F', '6',    '\xEC', '\x12', '\x20', '\x1E', '\x8F', '\xD7',
        '\xAA', '\xD5', '\xEA', '\xAF', 'I',    '5',    'F',    '\xAA', 'T',
        '\x5F', '\x9F', '\x22', 'A',    '\x2A', '\x95', '\xA',  '\x83', '\xE5',
        'r',    '9',    'd',    '\xB3', 'Y',    '\x96', '\x99', 'L',    '\x6',
        '\xE9', 't',    '\x9A', '\x25', '\x85', '\x2C', '\xCB', 'T',    '\xA7',
        '\xC4', 'b',    '1',    '\xB5', '\x5E', '\x0',  '\x3',  'h',    '\x9A',
        '\xC6', '\x16', '\x82', '\x20', 'X',    'R',    '\x14', 'E',    '6',
        'S',    '\x94', '\xCB', 'e',    'x',    '\xBD', '\x5E', '\xAA', 'U',
        'T',    '\x23', 'L',    '\xC0', '\xE0', '\xE2', '\xC1', '\x8F', '\x0',
        '\x9E', '\xBC', '\x9',  'A',    '\x7C', '\x3E', '\x1F', '\x83', 'D',
        '\x22', '\x11', '\xD5', 'T',    '\x40', '\x3F', '8',    '\x80', 'w',
        '\xE5', '3',    '\x7',  '\xB8', '\x5C', '\x2E', 'H',    '\x92', '\x4',
        '\x87', '\xC3', '\x81', '\x40', '\x20', '\x40', 'g',    '\x98', '\xE9',
        '6',    '\x1A', '\xA6', 'g',    '\x15', '\x4',  '\xE3', '\xD7', '\xC8',
        '\xBD', '\x15', '\xE1', 'i',    '\xB7', 'C',    '\xAB', '\xEA', 'x',
        '\x2F', 'j',    'X',    '\x92', '\xBB', '\x18', '\x20', '\x9F', '\xCF',
        '3',    '\xC3', '\xB8', '\xE9', 'N',    '\xA7', '\xD3', 'l',    'J',
        '\x0',  'i',    '6',    '\x7C', '\x8E', '\xE1', '\xFE', 'V',    '\x84',
        '\xE7', '\x3C', '\x9F', 'r',    '\x2B', '\x3A', 'B',    '\x7B', '7',
        'f',    'w',    '\xAE', '\x8E', '\xE',  '\xF3', '\xBD', 'R',    '\xA9',
        'd',    '\x2',  'B',    '\xAF', '\x85', '2',    'f',    'F',    '\xBA',
        '\xC',  '\xD9', '\x9F', '\x1D', '\x9A', 'l',    '\x22', '\xE6', '\xC7',
        '\x3A', '\x2C', '\x80', '\xEF', '\xC1', '\x15', '\x90', '\x7',  '\x93',
        '\xA2', '\x28', '\xA0', 'S',    'j',    '\xB1', '\xB8', '\xDF', '\x29',
        '5',    'C',    '\xE',  '\x3F', 'X',    '\xFC', '\x98', '\xDA', 'y',
        'j',    'P',    '\x40', '\x0',  '\x87', '\xAE', '\x1B', '\x17', 'B',
        '\xB4', '\x3A', '\x3F', '\xBE', 'y',    '\xC7', '\xA',  '\x26', '\xB6',
        '\xEE', '\xD9', '\x9A', '\x60', '\x14', '\x93', '\xDB', '\x8F', '\xD',
        '\xA',  '\x2E', '\xE9', '\x23', '\x95', '\x29', 'X',    '\x0',  '\x27',
        '\xEB', 'n',    'V',    'p',    '\xBC', '\xD6', '\xCB', '\xD6', 'G',
        '\xAB', '\x3D', 'l',    '\x7D', '\xB8', '\xD2', '\xDD', '\xA0', '\x60',
        '\x83', '\xBA', '\xEF', '\x5F', '\xA4', '\xEA', '\xCC', '\x2',  'N',
        '\xAE', '\x5E', 'p',    '\x1A', '\xEC', '\xB3', '\x40', '9',    '\xAC',
        '\xFE', '\xF2', '\x91', '\x89', 'g',    '\x91', '\x85', '\x21', '\xA8',
        '\x87', '\xB7', 'X',    '\x7E', '\x7E', '\x85', '\xBB', '\xCD', 'N',
        'N',    'b',    't',    '\x40', '\xFA', '\x93', '\x89', '\xEC', '\x1E',
        '\xEC', '\x86', '\x2',  'H',    '\x26', '\x93', '\xD0', 'u',    '\x1D',
        '\x7F', '\x9',  '2',    '\x95', '\xBF', '\x1F', '\xDB', '\xD7', 'c',
        '\x8A', '\x1A', '\xF7', '\x5C', '\xC1', '\xFF', '\x22', 'J',    '\xC3',
        '\x87', '\x0',  '\x3',  '\x0',  'K',    '\xBB', '\xF8', '\xD6', '\x2A',
        'v',    '\x98', 'I',    '\x0',  '\x0',  '\x0',  '\x0',  'I',    'E',
        'N',    'D',    '\xAE', 'B',    '\x60', '\x82',
};

HttpData::HttpData(EventLoop *loop, int fd, std::shared_ptr<Task> task) :
    task_(task),
    fd_(fd),
    n(0),
    loop_(loop),
    state_(STATE_PARSE_URI),
    closed_(false),
    method_(METHOD_GET),
    HTTPVersion_(HTTP_11),
    nowReadPos_(0),
    hState_(H_START),
    mutex_()
{
    //task_->setConnHandle(std::bind(&HttpData::newConnHandle, this));
    task_->setReadHandle(std::bind(&HttpData::readHandle, this));
    task_->setWriteHandle(std::bind(&HttpData::writeHandle, this));
    task_->epoll_ = loop->epoll_;
    //loop->epoll_->removeEpoll(task);
    //loop->epoll_->addEpoll(task_);
}

HttpData::~HttpData() {
    if(DEBUG) {
        printf("http free\n");
        fflush(stdout);
    }
    if(fd_ != 0)
        close(fd_);
    task_.reset();
    //timer_->setQuit();
    //timer_.reset();
}

void HttpData::quit() {
    mutex_.lock();
    if(timer_.lock())
        timer_.lock()->setQuit();
    loop_->epoll_->removeEpoll(task_);
    closed_ = true;
    //close(fd_);
    mutex_.unlock();
}
void HttpData::readHandle() {
    struct sockaddr_in chiladdr;
    int sockfd;

    char ipbuf_tmp[50];
    struct epoll_event ev;
    error_ = false;
    ev.data.fd = fd_;
    ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, fd_, &ev);

    if ((sockfd = fd_) < 0) {
        ERR_MSG("fd_ error");
        return;
    }
    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    getpeername(sockfd, (sockaddr *) &chiladdr, &chillen);

    if ((n = read(sockfd, receive_buff_, MAXLINE)) < 0) {
        if (errno == ECONNRESET) {
            closed_ = true;
            bzero(&chiladdr, sizeof(chiladdr));
            socklen_t chillen = sizeof(chiladdr);
            getpeername(sockfd, (sockaddr *) &chiladdr, &chillen);
            //loop_->epoll_->removeEpoll(task_);
            //delete loop_;
            quit();
            close(fd_);
            fd_ = 0;
            if(DEBUG)
                printf("close connect [%s : %d]\n",inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),ntohs(chiladdr.sin_port));

        } else
            ERR_MSG("read error");
    } else if (n == 0) {
        closed_ = true;
        //loop_->epoll_->removeEpoll(task_);
        //delete loop_;
        quit();
        close(fd_);
        fd_ = 0;
        if(DEBUG)
            printf("close connect [%s : %d]\n",inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),ntohs(chiladdr.sin_port));
    } else {
        receive_buff_[n] = '\0';
        in_buff = string(receive_buff_);
        state_ = STATE_PARSE_URI;
        if(DEBUG) {
            getTime();
            printf("receive msg: %s from [%s : %d]\n", receive_buff_,inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),ntohs(chiladdr.sin_port));
        }
        if(state_ == STATE_PARSE_URI) {
            URIState flag = this->parseURI();
            if (flag == PARSE_URI_AGAIN) {
                /*
                ev.data.fd = sockfd;
                ev.events = EPOLLIN | EPOLLONESHOT;
                epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);
                 */
                return;
            }
            else if (flag == PARSE_URI_ERROR) {
                ERR_MSG("PARSE URI ERROR");
                errorHandle(fd_, 400, "Bad Request");
            }
            else state_ = STATE_PARSE_HEADERS;
        }
        if (state_ == STATE_PARSE_HEADERS) {
            HeaderState flag = this->parseHeaders();
            if (flag == PARSE_HEADER_AGAIN) {
                //
            }
            else if (flag == PARSE_HEADER_ERROR) {
                perror("3");
                error_ = true;
                errorHandle(fd_, 400, "Bad Request");
            }
            if (method_ == METHOD_POST) {
                // POST方法准备
                state_ = STATE_RECV_BODY;
            } else {
                state_ = STATE_ANALYSIS;
            }
        }

        if (state_ == STATE_RECV_BODY) {
            int content_length = -1;
            if (headers_.find("Content-length") != headers_.end()) {
                content_length = stoi(headers_["Content-length"]);
            } else {
                // cout << "(state_ == STATE_RECV_BODY)" << endl;
                error_ = true;
                errorHandle(fd_, 400, "Bad Request: Lack of argument (Content-length)");
            }
            if (static_cast<int>(in_buff.size()) < content_length)  {
                //
            }
            state_ = STATE_ANALYSIS;
        }
        if (state_ == STATE_ANALYSIS) {
            AnalysisState flag = this->analysisRequest();
            if (flag == ANALYSIS_SUCCESS) {
                state_ = STATE_FINISH;

                //
            } else {
                // cout << "state_ == STATE_ANALYSIS" << endl;
                error_ = true;
                //
            }
        }
        if(!error_)
            if (out_buff.size() > 0) {
                writeHandle();
                fflush(stdout);
                /*
                ev.data.fd = sockfd;
                ev.events = EPOLLOUT | EPOLLONESHOT;
                epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);
                 */
            }
    }



}

void HttpData::writeHandle() {
    int sockfd;
    char ipbuf_tmp[50];
    struct epoll_event ev;
    struct sockaddr_in chiladdr;
    sockfd = fd_;
    bzero(&chiladdr, sizeof(chiladdr));
    socklen_t chillen = sizeof(chiladdr);
    getpeername(sockfd, (sockaddr *) &chiladdr, &chillen);
    //write(sockfd, receive_buff_, n);
    if(DEBUG) {
        getTime();
        printf("echo msg: %s to [%s : %d]\n", out_buff.c_str(),inet_ntop(AF_INET, &chiladdr.sin_addr.s_addr, ipbuf_tmp, sizeof(ipbuf_tmp)),ntohs(chiladdr.sin_port));

    }

    if (writen(fd_, out_buff) < 0) {
        ERR_MSG("write outbuff error");
        error_ = true;
    }
    fflush(stdout);
    //close(fd_);
    //closed_ = true;
    ev.data.fd = sockfd;
    ev.events = EPOLLIN | EPOLLONESHOT;
    epoll_ctl(task_->epoll_->epollfd_, EPOLL_CTL_MOD, sockfd, &ev);
    //短连接
/*
    quit();
    close(fd_);
    fd_ = 0;
*/
    //更新活跃定时器
    //由于并发量大的时候，每一个请求都更新时间是严重的性能瓶颈，
    // 所以不更新，但是想了有一个办法是设置一个标志变量，
    // 如果在超时时间段内有请求就设置标志，只记录一个请求，
    // 在时间到达的时候去判断这个标记变量，如果设置了的话就重新开始计时，
    // 但是这种计时方法不精确，所以直接不更新时间吧，超时客户端也可以重新连接。
    //timer_->updateTime();
}

void HttpData::errorHandle(int fd, int err_num, string short_msg) {
    short_msg = " " + short_msg;
    error_ = true;
    char send_buff[4096];
    string body_buff, header_buff;
    body_buff += "<html><title>Error</title>";
    body_buff += "<body bgcolor=\"ffffff\">";
    body_buff += to_string(err_num) + short_msg;
    body_buff += "<hr><em> WebServer </em>\n</body></html>";

    header_buff += "HTTP/1.1 " + to_string(err_num) + short_msg + "\r\n";
    header_buff += "Content-Type: text/html\r\n";
    header_buff += "Connection: Close\r\n";
    header_buff += "Content-Length: " + to_string(body_buff.size()) + "\r\n";
    header_buff += "Server: WebServer\r\n";
    ;
    header_buff += "\r\n";
    getTime();
    printf("echo error\n");
    fflush(stdout);
    sprintf(send_buff, "%s", header_buff.c_str());
    writen2(fd, send_buff, strlen(send_buff));
    sprintf(send_buff, "%s", body_buff.c_str());
    writen2(fd, send_buff, strlen(send_buff));
    //close(fd_);
    //closed_ = true;
}

void MimeType::init() {
    mime[".html"] = "text/html";
    mime[".avi"] = "video/x-msvideo";
    mime[".bmp"] = "image/bmp";
    mime[".c"] = "text/plain";
    mime[".doc"] = "application/msword";
    mime[".gif"] = "image/gif";
    mime[".gz"] = "application/x-gzip";
    mime[".htm"] = "text/html";
    mime[".ico"] = "image/x-icon";
    mime[".jpg"] = "image/jpeg";
    mime[".png"] = "image/png";
    mime[".txt"] = "text/plain";
    mime[".mp3"] = "audio/mp3";
    mime[".css"] = "text/css";
    mime[".js"] = "text/javascript";
    mime["default"] = "text/html";
}

std::string MimeType::getMime(const std::string &suffix) {
    pthread_once(&once_control, MimeType::init);
    if (mime.find(suffix) == mime.end())
        return mime["default"];
    else
        return mime[suffix];
}

URIState HttpData::parseURI() {
    string &str = in_buff;
    string cop = str;
    // 读到完整的请求行再开始解析请求
    size_t pos = str.find('\r', nowReadPos_);
    if (pos < 0) {
        return PARSE_URI_AGAIN;
    }
    // 去掉请求行所占的空间，节省空间
    string request_line = str.substr(0, pos);
    if (str.size() > pos + 1)
        str = str.substr(pos + 1);
    else
        str.clear();
    // Method
    int posGet = request_line.find("GET");
    int posPost = request_line.find("POST");
    int posHead = request_line.find("HEAD");

    if (posGet >= 0) {
        pos = posGet;
        method_ = METHOD_GET;
    } else if (posPost >= 0) {
        pos = posPost;
        method_ = METHOD_POST;
    } else if (posHead >= 0) {
        pos = posHead;
        method_ = METHOD_HEAD;
    } else {
        return PARSE_URI_ERROR;
    }

    // filename
    pos = request_line.find("/", pos);
    if (pos < 0) {
        fileName_ = "index.html";
        HTTPVersion_ = HTTP_11;
        return PARSE_URI_SUCCESS;
    } else {
        size_t _pos = request_line.find(' ', pos);
        if (_pos < 0)
            return PARSE_URI_ERROR;
        else {
            if (_pos - pos > 1) {
                fileName_ = request_line.substr(pos + 1, _pos - pos - 1);
                size_t __pos = fileName_.find('?');
                if (__pos >= 0) {
                    fileName_ = fileName_.substr(0, __pos);
                }
            }

            else
                fileName_ = "index.html";
        }
        pos = _pos;
    }
    // cout << "fileName_: " << fileName_ << endl;
    // HTTP 版本号
    pos = request_line.find("/", pos);
    if (pos < 0)
        return PARSE_URI_ERROR;
    else {
        if (request_line.size() - pos <= 3)
            return PARSE_URI_ERROR;
        else {
            string ver = request_line.substr(pos + 1, 3);
            if (ver == "1.0")
                HTTPVersion_ = HTTP_10;
            else if (ver == "1.1")
                HTTPVersion_ = HTTP_11;
            else
                return PARSE_URI_ERROR;
        }
    }
    return PARSE_URI_SUCCESS;
}

HeaderState HttpData::parseHeaders() {
    string &str = in_buff;
    int key_start = -1, key_end = -1, value_start = -1, value_end = -1;
    int now_read_line_begin = 0;
    bool notFinish = true;
    hState_ = H_START;
    size_t i = 0;
    for (; i < str.size() && notFinish; ++i) {
        switch (hState_) {
            case H_START: {
                if (str[i] == '\n' || str[i] == '\r') break;
                hState_ = H_KEY;
                key_start = i;
                now_read_line_begin = i;
                break;
            }
            case H_KEY: {
                if (str[i] == ':') {
                    key_end = i;
                    if (key_end - key_start <= 0)
                        return PARSE_HEADER_ERROR;
                    hState_ = H_COLON;
                }
                break;
            }
            case H_COLON: {
                if (str[i] == ' ') {
                    hState_ = H_SPACES_AFTER_COLON;
                } else
                    return PARSE_HEADER_ERROR;
                break;
            }
            case H_SPACES_AFTER_COLON: {
                hState_ = H_VALUE;
                value_start = i;
                break;
            }
            case H_VALUE: {
                if (str[i] == '\r') {
                    hState_ = H_CR;
                    value_end = i;
                    if (value_end - value_start <= 0) return PARSE_HEADER_ERROR;
                } else if (i - value_start > 255)
                    return PARSE_HEADER_ERROR;
                break;
            }
            case H_CR: {
                if (str[i] == '\n') {
                    hState_ = H_LF;
                    string key(str.begin() + key_start, str.begin() + key_end);
                    string value(str.begin() + value_start, str.begin() + value_end);
                    headers_[key] = value;
                    now_read_line_begin = i;
                } else
                    return PARSE_HEADER_ERROR;
                break;
            }
            case H_LF: {
                if (str[i] == '\r') {
                    hState_ = H_END_CR;
                } else {
                    key_start = i;
                    hState_ = H_KEY;
                }
                break;
            }
            case H_END_CR: {
                if (str[i] == '\n') {
                    hState_ = H_END_LF;
                } else
                    return PARSE_HEADER_ERROR;
                break;
            }
            case H_END_LF: {
                notFinish = false;
                key_start = i;
                now_read_line_begin = i;
                break;
            }
        }
    }
    if (hState_ == H_END_LF) {
        str = str.substr(i);
        return PARSE_HEADER_SUCCESS;
    }
    str = str.substr(now_read_line_begin);
    return PARSE_HEADER_AGAIN;
}

AnalysisState HttpData::analysisRequest() {
    if (method_ == METHOD_POST) {
        // ------------------------------------------------------
        // My CV stitching handler which requires OpenCV library
        // ------------------------------------------------------
        // string header;
        // header += string("HTTP/1.1 200 OK\r\n");
        // if(headers_.find("Connection") != headers_.end() &&
        // headers_["Connection"] == "Keep-Alive")
        // {
        //     keepAlive_ = true;
        //     header += string("Connection: Keep-Alive\r\n") + "Keep-Alive:
        //     timeout=" + to_string(DEFAULT_KEEP_ALIVE_TIME) + "\r\n";
        // }
        // int length = stoi(headers_["Content-length"]);
        // vector<char> data(inBuffer_.begin(), inBuffer_.begin() + length);
        // Mat src = imdecode(data, CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR);
        // //imwrite("receive.bmp", src);
        // Mat res = stitch(src);
        // vector<uchar> data_encode;
        // imencode(".png", res, data_encode);
        // header += string("Content-length: ") + to_string(data_encode.size()) +
        // "\r\n\r\n";
        // outBuffer_ += header + string(data_encode.begin(), data_encode.end());
        // inBuffer_ = inBuffer_.substr(length);
        // return ANALYSIS_SUCCESS;
    } else if (method_ == METHOD_GET || method_ == METHOD_HEAD) {
        string header;
        header += "HTTP/1.1 200 OK\r\n";
        if (headers_.find("Connection") != headers_.end() &&
            (headers_["Connection"] == "Keep-Alive" ||
             headers_["Connection"] == "keep-alive")) {
            //keepAlive_ = true;
            header += string("Connection: Keep-Alive\r\n") + "Keep-Alive: timeout=" +
                      to_string(DEFAULT_KEEP_ALIVE_TIME) + "\r\n";
        }
        int dot_pos = fileName_.find('.');
        string filetype;
        if (dot_pos < 0)
            filetype = MimeType::getMime("default");
        else
            filetype = MimeType::getMime(fileName_.substr(dot_pos));

        // echo test
        if (fileName_ == "hello") {
            out_buff =
                    "HTTP/1.1 200 OK\r\nContent-type: text/plain\r\n\r\nHello World";
            return ANALYSIS_SUCCESS;
        }
        if (fileName_ == "favicon.ico") {
            fileName_ = "favicon.png";
            header += "Content-Type: image/png\r\n";


            struct stat sbuf;
            //默认图标
            if (stat(fileName_.c_str(), &sbuf) < 0) {
                header += "Content-Length: " + to_string(sizeof favicon) + "\r\n";
                header += "Server: Server\r\n";

                header += "\r\n";
                out_buff += header;
                out_buff += string(favicon, favicon + sizeof favicon);

                return ANALYSIS_SUCCESS;
            }
            int src_fd = open(fileName_.c_str(), O_RDONLY, 0);
            //默认图标
            if (src_fd < 0) {

                header += "Content-Length: " + to_string(sizeof favicon) + "\r\n";
                header += "Server: Server\r\n";

                header += "\r\n";
                out_buff += header;
                out_buff += string(favicon, favicon + sizeof favicon);

                return ANALYSIS_SUCCESS;
            }
            void *mmapRet = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
            close(src_fd);
            char *src_addr = static_cast<char *>(mmapRet);
            header += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
            header += "Server: Server\r\n";

            header += "\r\n";
            out_buff += header;
            out_buff += string(src_addr, src_addr + sbuf.st_size);
            munmap(mmapRet, sbuf.st_size);
            return ANALYSIS_SUCCESS;
        }

        struct stat sbuf;
        if (stat(fileName_.c_str(), &sbuf) < 0) {
            fileName_ = "index.html";
            if (stat(fileName_.c_str(), &sbuf) < 0) {
                    header.clear();
                    errorHandle(fd_, 404, "Not Found!");
                    return ANALYSIS_ERROR;
            }
        }
        header += "Content-Type: " + filetype + "\r\n";
        header += "Content-Length: " + to_string(sbuf.st_size) + "\r\n";
        header += "Server: Web Server\r\n";
        // 头部结束
        header += "\r\n";
        out_buff += header;

        if (method_ == METHOD_HEAD) return ANALYSIS_SUCCESS;

        int src_fd = open(fileName_.c_str(), O_RDONLY, 0);
        if (src_fd < 0) {
            //out_buff.clear();
            fileName_ = "index.html";
            src_fd = open(fileName_.c_str(), O_RDONLY, 0);
            if (src_fd < 0) {
                errorHandle(fd_, 404, "Not Found!");
                return ANALYSIS_ERROR;
            }

        }
        void *mmapRet = mmap(NULL, sbuf.st_size, PROT_READ, MAP_PRIVATE, src_fd, 0);
        close(src_fd);
        if (mmapRet == (void *)-1) {
            munmap(mmapRet, sbuf.st_size);
            out_buff.clear();
            errorHandle(fd_, 404, "Not Found!");
            return ANALYSIS_ERROR;
        }
        char *src_addr = static_cast<char *>(mmapRet);
        out_buff += string(src_addr, src_addr + sbuf.st_size);
        munmap(mmapRet, sbuf.st_size);
        return ANALYSIS_SUCCESS;
    }
    return ANALYSIS_ERROR;
}
void HttpData::getTime() {
    time_t tt;
    time( &tt );
    tt = tt + 8*3600;  // transform the time zone
    tm* t= gmtime( &tt );

    printf("%d-%02d-%02d %02d:%02d:%02d\n",
           t->tm_year + 1900,
           t->tm_mon + 1,
           t->tm_mday,
           t->tm_hour,
           t->tm_min,
           t->tm_sec);
    fflush(stdout);
}

