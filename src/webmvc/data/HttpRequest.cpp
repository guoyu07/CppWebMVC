/*
 * HttpRequest.cpp
 *
 *  Created on: 18.06.2010
 *      Author: fkrauthan
 */

#include "HttpRequest.h"
#include "../exceptions/CookieNotFoundException.h"
#include "../exceptions/HeaderFieldNotFoundException.h"
#include "../exceptions/AttributeNotFoundException.h"
#include "../exceptions/SessionNotFoundException.h"


HttpRequest::HttpRequest(const std::vector<HttpCookie>& cookies, const std::map<std::string, std::string>& headerFields,
					const std::string& method, const HttpClientInfo& clientInfo, const std::map<std::string, std::string>& attributes,
					const std::string& uri, const std::string& query) :
	mCookies(cookies),
	mHeaderFields(headerFields),
	mMethod(method),
	mClientInfo(clientInfo),
	mAttributes(attributes),
	mUri(uri),
	mQuery(query),
	mApplication(NULL),
	mSession(NULL) {
}

HttpRequest::HttpRequest(const HttpRequest& request) :
	mCookies(request.mCookies),
	mHeaderFields(request.mHeaderFields),
	mMethod(request.mMethod),
	mClientInfo(request.mClientInfo),
	mAttributes(request.mAttributes),
	mUri(request.mUri),
	mQuery(request.mQuery),
	mApplication(request.mApplication),
	mSession(request.mSession) {

}

const HttpCookie& HttpRequest::getCookie(const std::string& name) const {
	for(unsigned int i=0; i<mCookies.size(); i++) {
		if(mCookies[i].getName() == name) {
			return mCookies[i];
		}
	}

	throw CookieNotFoundException("The cookie with name \""+name+"\" was not found");
}

const std::vector<HttpCookie>& HttpRequest::getCookies() const {
	return mCookies;
}

bool HttpRequest::containsCookie(const std::string& name) const {
	for(unsigned int i=0; i<mCookies.size(); i++) {
		if(mCookies[i].getName() == name) {
			return true;
		}
	}

	return false;
}

const std::string& HttpRequest::getHeader(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator iter = mHeaderFields.find(name);
	if(iter == mHeaderFields.end()) {
		throw HeaderFieldNotFoundException("The header field with name \""+name+"\" was not found");
	}

	return iter->second;
}

std::vector<std::string> HttpRequest::getHeaderNames() const {
	std::vector<std::string> tmpRet;
	std::map<std::string, std::string>::const_iterator iter;
	for(iter=mHeaderFields.begin(); iter!=mHeaderFields.end(); ++iter) {
		tmpRet.push_back(iter->first);
	}

	return tmpRet;
}

const std::map<std::string, std::string>& HttpRequest::getHeaders() const {
	return mHeaderFields;
}

bool HttpRequest::containsHeader(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator iter = mHeaderFields.find(name);
	if(iter == mHeaderFields.end()) {
		return false;
	}

	return true;
}

const std::string& HttpRequest::getMethod() const {
	return mMethod;
}

const HttpClientInfo& HttpRequest::getClientInfo() const {
	return mClientInfo;
}

const std::string& HttpRequest::getAttribute(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		throw AttributeNotFoundException("The attribute with name \""+name+"\" was not found");
	}

	return iter->second;
}

std::vector<std::string> HttpRequest::getAttributeNames() const {
	std::vector<std::string> tmpRet;
	std::map<std::string, std::string>::const_iterator iter;
	for(iter=mAttributes.begin(); iter!=mAttributes.end(); ++iter) {
		tmpRet.push_back(iter->first);
	}

	return tmpRet;
}

bool HttpRequest::hasAttribute(const std::string& name) const {
	std::map<std::string, std::string>::const_iterator iter = mAttributes.find(name);
	if(iter == mAttributes.end()) {
		return false;
	}

	return true;
}

const std::string& HttpRequest::getRequestURI() const {
	return mUri;
}

const std::string& HttpRequest::getRequestQuery() const {
	return mQuery;
}

IApplication* HttpRequest::getApplicationContext() const {
	return mApplication;
}

HttpSession& HttpRequest::getSession() const {
	if(!mSession) {
		throw SessionNotFoundException("There is no session bound to this request");
	}

	return *mSession;
}

bool HttpRequest::hasSession() const {
	return mSession != NULL;
}

void HttpRequest::setApplicationContext(IApplication* context) {
	mApplication = context;
}

void HttpRequest::setSession(HttpSession* session) {
	mSession = session;
}

void HttpRequest::addAttribute(const std::string& name, const std::string& value) {
	mAttributes[name] = value;
}
