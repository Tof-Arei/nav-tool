#pragma once
using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections;

ref class Uploader
{
private:
	Socket^ scktConnection;
	
public:
	Uploader(void);
	Socket^ ConnectSocket( String^ server, int port );
	String^ SocketSend(String^ server, int port, String^ request);
	String^ SocketSendReceive( String^ server, int port );
	String^ ToHTML(String^ strIn);
};
