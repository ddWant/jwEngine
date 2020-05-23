#pragma once
/************************************************************************
* @file      HttpConnect.h
* @brief     HttpConnect
* @author    jiangwang
* @data      2020-5-20
* @version   0.1
************************************************************************/

#include "TcpSocket.h"
#include "HttpEvent.h"
#include "PoolObject.h"

enum http_content_type
{
	hct_text_html ,	//HTML��ʽ
	hct_text_plain,	//���ı���ʽ
	hct_text_xml,	//XML��ʽ
	hct_text_json,	//json��ʽ
	hct_image_gif,	//gifͼƬ��ʽ
	hct_image_jpeg,	//jpgͼƬ��ʽ
	hct_image_png,	//pngͼƬ��ʽ

};

class BasePacket;
class MessageBuffer;
struct http_parser;
struct http_parser_url;
class HttpConnect : public TcpSocket
{
public:
	HttpConnect();
	~HttpConnect();

	void zero();
	void setEvent(HttpEvent * e) { m_event = e; }
	void sendMsg(std::string_view sv);
	void autoMsg(std::string_view sv, enum http_content_type type = hct_text_html);
	static const char *getContentTypeStr(enum http_content_type type);
protected:
	virtual void on_msgbuffer(MessageBuffer * buffer);
	virtual void on_clsesocket();
	virtual void on_writecomplete();

private:
	static int on_url(http_parser*, const char *at, size_t length);

	bool parser(const char *, int);
	void complete();
private:
	HttpEvent * m_event = NULL;
	http_parser * m_parser;
	http_parser_url * m_url;
	BasePacket * m_readPacket;
	BasePacket * m_writePacket;
	const char * m_urlp;	//urlָ��
	const char * m_content;	//post����ָ��
	int m_residue;
	bool m_close = true;

	INCLUDE_POOL_OBJECT
};
