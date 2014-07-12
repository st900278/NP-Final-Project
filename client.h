#ifndef SERVER_H
#define SERVER_H
#include <QTextEdit>

#include <iostream>
#include <string>
#include </usr/include/unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
using namespace std;
using namespace cv;
extern "C"{
#define MAXLINE 1024
int beginclient();
void str_cli(FILE *fp_arg, int sockfd_arg);
static void *command(void *arg);
static void *waitread(void *arg);
int loginCommand(char* user,char *pwd);
int getFriendCommand(char *result,int size);
int getFriendStatus(char *result,int size);
int getFriendList(char *result,int size);
int getmsgCommand(char* frienduser, char *result, int size);
int addFriendCommand(char *fri_userID);
int msgCommand(char* frienduser,char* msg);
int createCommand(char* user,char *pwd);
int readline (int sockfd, char *res , int size);
int roomCommand(char* frienduser);
int lrCommand(char* frienduser);
int logoutCommand();

}
void* streamSend(void* arg);
void* webcamCapture(void*arg);
void* streamRead(void* arg);
void quit(string msg, int retval);
void buildCamera();
void exitCamera();

#endif // SERVER_H
