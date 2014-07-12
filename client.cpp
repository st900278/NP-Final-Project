#include "client.h"
#include <QTextEdit>

extern "C"{
int sockfd;
char g_userID[MAXLINE+1];

pthread_mutex_t g_commandmutex;
static void *waitread(void *arg)
{
    pthread_detach(pthread_self());
    char recvline[MAXLINE];

    while(read(sockfd, recvline, MAXLINE)>0)
    {
        fputs(recvline, stdout);
        bzero(recvline,sizeof(recvline));
    }
}

void str_cli(FILE *fp_arg, int sockfd_arg)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    pthread_t tid,tid2;
    int sockfd;

    sockfd = sockfd_arg;   
    //pthread_create(&tid2,NULL,&waitread,NULL);
    /*bzero(sendline,sizeof(sendline));
    bzero(recvline,sizeof(recvline));
    while(read(sockfd, recvline, MAXLINE)>0)
    {
        fputs(recvline, stdout);
        bzero(recvline,sizeof(recvline));
    }*/
}
int logoutCommand(){
    char recvline[MAXLINE+1];
    char sendline[MAXLINE+1];
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"O %s\n",g_userID);
    printf("%s",sendline);
    //send command
    write(sockfd,sendline,strlen(sendline));
    //wait request
    read(sockfd,recvline,MAXLINE);
    pthread_mutex_unlock(&g_commandmutex);
    if(!strncmp("logout",recvline,6)){
        return 0;
    }else{
        return -1;
    }

}
int addFriendCommand(char *fri_userID){
    char recvline[MAXLINE+1];
    char sendline[MAXLINE+1];
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"ADD %s %s\n",g_userID,fri_userID);
    printf("%s",sendline);
    //send command
    write(sockfd,sendline,strlen(sendline));
    //wait request
    read(sockfd,recvline,MAXLINE);
    pthread_mutex_unlock(&g_commandmutex);
    if(!strncmp("success",recvline,7)){
        return 0;
    }else{
        return -1;
    }

}
int getFriendCommand(char *result,int size){
    char recvline[MAXLINE+1];
    char sendline[MAXLINE+1];
    char *inform;
    int n;
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"FL %s\n",g_userID);
    printf("%s",sendline);
    fflush(stdout);
    //send command
    write(sockfd,sendline,strlen(sendline));
    //read info
    read(sockfd,recvline,MAXLINE);
    if(recvline[0]=='\n'){
        result[0]= 0;
    }else{
        inform = strtok(recvline,"\n");
        strncpy(result,inform,size);
    }
    //split

    return 0;
}
int getFriendStatus(char *result,int size){
    char recvline[MAXLINE+1];
    char *inform;
    read(sockfd,recvline,MAXLINE);
    printf("%s",recvline);

    if(recvline[0]=='\n'){
        result[0]=0;
    }else{
        inform = strtok(recvline,"\n");
        strncpy(result,inform,size);
    }
    pthread_mutex_unlock(&g_commandmutex);
    //split
    return 0;

}
int getFriendList(char *result,int size){

}

int loginCommand(char* user,char *pwd){
    char recvline[MAXLINE+1];
    char sendline[MAXLINE+1];
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"I %s %s\n",user,pwd);
    printf("%s",sendline);
    //copy information
    strncpy(g_userID,user,MAXLINE);
    //send command
    write(sockfd,sendline,strlen(sendline));
    //wait request
    read(sockfd,recvline,MAXLINE);
    pthread_mutex_unlock(&g_commandmutex);
    if(!strncmp("login",recvline,5)){
        printf("Login ok");
        return 0;
    }else{
        return -1;
    }
    return -1;

}
int createCommand(char* user,char *pwd){
    char recvline[MAXLINE+1];
    char sendline[MAXLINE+1];
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"NA %s %s\n",user,pwd);
    printf("%s",sendline);
    write(sockfd,sendline,strlen(sendline));
    //wait request
    read(sockfd,recvline,MAXLINE);
    pthread_mutex_unlock(&g_commandmutex);
    if(!strncmp("success",recvline,7)){
        return 0;
    }else{
        return -1;
    }

}
int msgCommand(char* frienduser,char* msg){
    char sendline[MAXLINE+1];
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"PM %s %s %s\n",g_userID,frienduser,msg);
    printf("%s",sendline);
    write(sockfd,sendline,strlen(sendline));
    pthread_mutex_unlock(&g_commandmutex);
    return 0;
}
int roomCommand(char* frienduser){
    char sendline[MAXLINE+1];

    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"R %s %s\n",g_userID,frienduser);
    printf("%s",sendline);
    write(sockfd,sendline,strlen(sendline));
    pthread_mutex_unlock(&g_commandmutex);
    return 0;
}
int lrCommand(char* frienduser){
    char sendline[MAXLINE+1];
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"d\n");
    printf("%s",sendline);
    write(sockfd,sendline,strlen(sendline));
    pthread_mutex_unlock(&g_commandmutex);
    return 0;
}
int getmsgCommand(char* frienduser,char *result,int size){
    char sendline[MAXLINE+1];
    char recvline[MAXLINE+1];
    char *inform;
    pthread_mutex_lock(&g_commandmutex);
    sprintf(sendline,"GM %s %s\n",g_userID,frienduser);
    printf("%s",sendline);
    fflush(stdout);
    write(sockfd,sendline,strlen(sendline));
    read(sockfd,recvline,MAXLINE);
    pthread_mutex_unlock(&g_commandmutex);
    inform = strtok(recvline,"\n");
    strncpy(result,inform,size);
    return 0;
}
int closeClient(){
   close(sockfd);
}
int beginclient()
{
    pthread_mutex_destroy(&g_commandmutex);
    g_commandmutex=PTHREAD_MUTEX_INITIALIZER;
    struct sockaddr_in servaddr; /*declare server address*/

    if((sockfd=socket(AF_INET, SOCK_STREAM,0)) < 0)
        printf("socket error\n");

    /*create an Internet(AF_INET) stream(SOCK_STREAM) socket*/
    bzero(&servaddr,sizeof(servaddr)); /*reset address to zero*/
    servaddr.sin_family=AF_INET; /*IPv4*/
    servaddr.sin_port=htons(5566); /*Port: 12346*/

    if(inet_pton(AF_INET, "140.114.86.199", &servaddr.sin_addr) <= 0) //some pc in room 326
        printf("inet_ption error\n");

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        printf("connect error\n");
    printf(">>>%d",sockfd);
    fflush(stdout);
    str_cli(stdin,sockfd); /* do it all */
    fflush(stdout);
    return 0;
}}

VideoCapture capture;
Mat img, img1;
int is_data_ready = 0;
int listenSock, connectSock;
int clientSock;
int listenPort; // Server port
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_t tid,tid2;
pthread_t thread_s;

void* webcamCapture(void*arg){

    int width, height, key;
    width = 640;
    height = 480;
   // pthread_detach(pthread_self());
    listenPort = 9899; // Set up the port

    capture.open(0);
    if (!capture.isOpened()) {
        quit("\n--> cvCapture failed", 1);
    }

    capture >> img;
    img1 = Mat::zeros(img.rows, img.cols ,CV_8UC1);

    /* run the streaming server as a separate thread */
    if (pthread_create(&thread_s, NULL, streamSend, NULL)) {
        quit("pthread_create failed.", 1);
    }

    cout << "\n-->Press 'q' to quit." << endl;
    namedWindow("stream_server", CV_WINDOW_AUTOSIZE);
    flip(img, img, 1);
    img1 = img;
    //cvtColor(img, img1, CV_BGR2GRAY); // Transfer img to img1 by grayscale image

    cout << "-->Waiting for UDP connection on port ";

    while(key != 'q') {
        // Get a frame from camera
        capture >> img;
        if (img.empty()) {
            break;
        }
        pthread_mutex_lock(&mutex1);
        flip(img, img, 1);
        img1 = img;
        cvtColor(img, img1, CV_BGR2GRAY);
        is_data_ready = 1;
        pthread_mutex_unlock(&mutex1);
        imshow("stream_server", img);
        //key = waitKey(30);
        usleep(200);
        //cout << "Test";
        fflush(stdout);
    }

    if (pthread_cancel(thread_s)) {
        quit("pthread_cancel failed.", 1);
    }

    destroyWindow("stream_server");
    quit("NULL", 0);
    return 0;
}
void* streamSend(void* arg)
{
    struct sockaddr_in serverAddr, clientAddr, dest;
    //pthread_detach(pthread_self());

    /* make this thread cancellable using pthread_cancel() */
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    if ((connectSock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            quit("socket() failed.", 1);
    }

    // Set up server
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr("140.114.86.199");
    dest.sin_port = htons(9899);
    socklen_t destLen = sizeof(dest);
 /*
    if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        quit("bind() failed", 1);
    }

    if (listen(listenSock, 5) == -1) {
        quit("listen() failed.", 1);
    }
*/
    int imgSize = img1.total() * img1.elemSize();
    int bytes=0;
    /* start send images */
    while(1)
    {
        //cout << "-->Waiting for TCP connection on port " << listenPort << " ...\n\n";
    //connect(connectSock, (sockaddr*)&clientAddr, clientAddrLen);
        while(1){
            /* send the grayscaled frame, thread safe */
            if (is_data_ready) {

                pthread_mutex_lock(&mutex1);
                // Compress img1 frame to jpeg...
                vector<uchar>buff;
                vector<int> param = vector<int>(2);
                param[0] = CV_IMWRITE_JPEG_QUALITY;
                param[1] = 10; // default(95) 0 - 100
                imencode(".jpg", img1, buff, param); // encode img1 to jpeg format
                imgSize = (int)buff.size();
                // Get the frame spec = > note that buff: 255 216 (FFD8) and the end is 255 217 (FFD9) is the correct format for a JPEG file
                // Note that: we the imgsize is too large to send out, that is we should seperate the stream to send out
             /*   char len[10];
                sprintf(len, "%8d", imgSize);
                // Send Header
                if ((bytes = send(connectSock, len, 8, 0)) < 0){
                    cerr << "\n--> bytes = " << bytes << endl;
                    quit("\n--> send() failed", 1);
                }
                */
                // Send Data
                if ((bytes = sendto(connectSock, buff.data(), imgSize, 0, (struct sockaddr*)&dest, destLen)) < 0){
                    cerr << "\n--> bytes = " << bytes << endl;
                    quit("\n--> send() failed", 1);
                }

                // Succeed to send image bytes
                is_data_ready = 0;
                pthread_mutex_unlock(&mutex1);
                memset(&clientAddr, 0x0, sizeof(clientAddr));
            }
            usleep(500); //1000 Micro Sec

        }
    }

}
void* streamRead(void*arg){

    int sockfd;
    struct sockaddr_in cliaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    //pthread_detach(pthread_self());
    // connect with server
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    cliaddr.sin_port = htons(9899);
    bind(sockfd, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
    int i=0, j;
    printf("entry\n");
    while(1){
        char recvData[1024000];

        socklen_t  cliLen = sizeof(cliaddr);
        printf("test\n");
        int n = recvfrom(sockfd, recvData, 1024000, 0, (struct sockaddr*)&cliaddr, &cliLen);
        printf("hello\n");
        char fileName[1024];
        sprintf(fileName, "./tmp/pic%d.jpeg", i++);

        FILE* fp = fopen(fileName, "w");
        fwrite(recvData, 1, n, fp);
        fclose(fp);
        fflush(stdout);
    }
}
void quit(string msg, int retval)
{
    if (retval == 0) {
        cout << (msg == "NULL" ? "" : msg) << "\n" <<endl;
    } else {
        cerr << (msg == "NULL" ? "" : msg) << "\n" <<endl;
    }

    if (listenSock){
        close(listenSock);
    }

    if (connectSock){
        close(connectSock);
    }

    if (!img.empty()){
        (img.release());
    }

    if (!img1.empty()) {
        img1.release();
    }

    pthread_mutex_destroy(&mutex1);
    exit(retval);
}
void buildCamera(){

    pthread_create(&tid2, NULL, streamRead, NULL);
    pthread_create(&tid, NULL, webcamCapture, NULL);
}
void exitCamera(){
    pthread_cancel(thread_s);
    pthread_cancel(tid);
    pthread_cancel(tid2);
}

