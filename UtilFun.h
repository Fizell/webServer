//
// Created by parallels on 2020/1/16.
//

#include <errno.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include "WebLimit.h"

#ifndef WEB_SERVER_UTILFUN_H
#define WEB_SERVER_UTILFUN_H

#define ERR_MSG(tmp) printf("File:%s\n|Line:%d\tinfo: %s\n", __FILE__, __LINE__, (char *)tmp);
#define INFO_MSG(tmp) printf("%s\n", (char *)tmp);

ssize_t readn(int fd, void *buff, size_t n);
ssize_t readn(int fd, std::string &inBuffer, bool &zero);
ssize_t writen2(int fd, void *buff, size_t n);
ssize_t writen(int fd, std::string &sbuff);

class UtilFun {

};


#endif //WEB_SERVER_UTILFUN_H
