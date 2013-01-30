#include "UnixDomainSocketManager.h"
#include <stddef.h>

UnixDomainSocketManager::UnixDomainSocketManager(const string socketName)
{
	mSocketPath = SOCKET_DIR_PATH;
	mSocketPath += socketName;
}

UnixDomainSocketManager::~UnixDomainSocketManager()
{
}

int UnixDomainSocketManager::connectSocket(){
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","connect to : %s\n" , mSocketPath.c_str());
#endif
	struct sockaddr_un server;
//	bzero((char *)&server, sizeof(server));
	server.sun_family = AF_LOCAL;
	server.sun_path[0] = '\0';
	strcpy(&server.sun_path[1], mSocketPath.c_str());
	socklen_t len = offsetof(struct sockaddr_un, sun_path) + 1 + strlen(&server.sun_path[1]);

	if( ( mSocketFd = socket(PF_LOCAL, SOCK_STREAM, 0)) == ERR){
		perror("client: socket");
		return -1;
	}
	if(connect(mSocketFd, (struct sockaddr *)&server, len) == ERR){
//		perror("client: connect");
		__android_log_print(ANDROID_LOG_DEBUG, "UnixDomainSocketManager","fail: connect()\n");
		return -1;
	}
	return 0;
}

void UnixDomainSocketManager::closeSocket(){
	close(mSocketFd);
}

string UnixDomainSocketManager::start(string data)
{
	pthread_t thread;
	void *rslt;
	int status;

	/* initialize */
	CallBackArgs *args = new CallBackArgs();
	args->socketFd = mSocketFd;
	args->socketPath = mSocketPath;
	args->sendData = data + "\n";
	args->returnData = "";

	/* start communication */
	status = pthread_create(&thread, NULL, callBack, (void*) args);
#ifdef DEBUG
	if(status != 0){
		__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","Failed pthread_create");
	}else{
		__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","OK pthread_create");
	}
#endif
	pthread_join(thread, &rslt);
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","returnData : %s\n",args->returnData.c_str());
#endif
	string retData = args->returnData;
	/* finalize */
	delete(args);

	return retData;
}

void* callBack(void *arg)
{
//	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","Client Start : ID : (main)\n");
	CallBackArgs* args = (CallBackArgs*)arg;
	char buf[BUFFSIZE];
	char ret[BUFFSIZE];
	int socket_fd = args->socketFd;
	const char* message = args->sendData.c_str();
	int message_len = strlen(message);

	// send data
	if(write(socket_fd, message, message_len) == ERR){
		perror("client: write");
		close(socket_fd);
		return NULL;
	}
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","Client send : %s\n", message);
#endif
	sleep(1);

	// read data
	int bufSize = 0;
	if((bufSize = read(socket_fd, buf, BUFFSIZE)) == ERR){
		perror("client: read");
		close(socket_fd);
		return NULL;
	}

	StrChomp(buf);
//	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","bufSize:%d\n",bufSize);
//	strcpy(ret, "");
//	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","ret:%s\n",ret);
	strncpy(ret, buf, bufSize);
#ifdef DEBUG
	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","<CLIENT>message from server : %s\n", ret);
#endif
	args->returnData = ret;

//	__android_log_print(ANDROID_LOG_DEBUG,"UnixDomainSocket","Client end\n");

	return NULL;
}

char *StrChomp(char *str)
{
  char   *str_p;;

  for (str_p = str; *str_p; ++str_p)
    ;

  if (*(str_p - 1) == '\n') {
    *(str_p - 1) = '\0';
  }

  return str;
}
