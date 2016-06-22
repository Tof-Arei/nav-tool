#include "StdAfx.h"
#include "uploader.h"

Uploader::Uploader(void)
{
}

Socket^ Uploader::ConnectSocket( String^ server, int port )
{
   Socket^ s = nullptr;
   IPHostEntry^ hostEntry = nullptr;

   // Get host related information.
   hostEntry = Dns::GetHostEntry( server );

   // Loop through the AddressList to obtain the supported AddressFamily. This is to avoid
   // an exception that occurs when the host IP Address is not compatible with the address family
   // (typical in the IPv6 case).
   IEnumerator^ myEnum = hostEntry->AddressList->GetEnumerator();
   while ( myEnum->MoveNext() )
   {
      IPAddress^ address = safe_cast<IPAddress^>(myEnum->Current);
      IPEndPoint^ endPoint = gcnew IPEndPoint( address,port );
      Socket^ tmpS = gcnew Socket( endPoint->AddressFamily,SocketType::Stream,ProtocolType::Tcp );
      tmpS->Connect( endPoint );
      if ( tmpS->Connected )
      {
         s = tmpS;
         break;
      }
      else
      {
         continue;
      }
   }

   return s;
}

// This method requests the home page content for the specified server.
String^ Uploader::SocketSend(String^ server, int port, String^ request)
{
   request = String::Concat(request, "\r\n\r\n"); // add termination just in case
   array<Byte>^bytesSent = Encoding::ASCII->GetBytes( request );
   array<Byte>^bytesReceived = gcnew array<Byte>(256);

   // Create a socket connection with the specified server and port.
   Socket^ s = ConnectSocket( server, port );
   if ( s == nullptr )
      return ("Connection failed");


   // Send request to the server.
   s->Send( bytesSent, bytesSent->Length, static_cast<SocketFlags>(0) );

   // Receive the server home page content.
   int bytes = 0;
   String^ strRetPage;
   do
   {
      bytes = s->Receive( bytesReceived, bytesReceived->Length, static_cast<SocketFlags>(0) );
      strRetPage = String::Concat( strRetPage, Encoding::ASCII->GetString( bytesReceived, 0, bytes ) );
   }
   while ( bytes > 0 );

   return strRetPage;
}

// This method requests the home page content for the specified server.
String^ Uploader::SocketSendReceive( String^ server, int port )
{
   String^ request = String::Concat( "GET / HTTP/1.1\r\nHost: ", server, "\r\nConnection: Close\r\n\r\n" );
   array<Byte>^bytesSent = Encoding::ASCII->GetBytes( request );
   array<Byte>^bytesReceived = gcnew array<Byte>(256);

   // Create a socket connection with the specified server and port.
   Socket^ s = ConnectSocket( server, port );
   if ( s == nullptr )
      return ("Connection failed");


   // Send request to the server.
   s->Send( bytesSent, bytesSent->Length, static_cast<SocketFlags>(0) );

   // Receive the server home page content.
   int bytes = 0;
   String^ strRetPage = String::Concat( "Default HTML page on ", server, ":\r\n" );
   do
   {
      bytes = s->Receive( bytesReceived, bytesReceived->Length, static_cast<SocketFlags>(0) );
      strRetPage = String::Concat( strRetPage, Encoding::ASCII->GetString( bytesReceived, 0, bytes ) );
   }
   while ( bytes > 0 );

   return strRetPage;
}

String^ Uploader::ToHTML(String^ strIn)
{	// replace characters with HTML codes
	String^ strReturn = strIn->Replace(" ","%20");
	strReturn = strReturn->Replace("`","%60");
	strReturn = strReturn->Replace("'","%27");
	strReturn = strReturn->Replace("¬","%AC");
	strReturn = strReturn->Replace("\"","%22");
	strReturn = strReturn->Replace("£","%A3");
	strReturn = strReturn->Replace("<","%3C");
	strReturn = strReturn->Replace(">","%3E");
	return strReturn;
}