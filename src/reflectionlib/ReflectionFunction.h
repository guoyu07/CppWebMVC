/*
 * ReflectionFunction.h
 *
 *  Created on: 14.06.2010
 *      Author: fkrauthan
 */

#ifndef REFLECTIONFUNCTION_H_
#define REFLECTIONFUNCTION_H_

#include "ReflectionParam.h"
#include "ReflectionAnotation.h"
#include <boost/any.hpp>
#include <string>
#include <vector>


class ReflectionFunction {
	public:
		ReflectionFunction(const std::string& name, const std::string& retType, const std::vector<ReflectionParam*>& params, boost::any (*invokeFunction)(void*, const std::vector<boost::any>&), const std::map<std::string, ReflectionAnotation*>& anotations);
		~ReflectionFunction();

		std::string& getName();
		std::string& getRetType();
		std::vector<ReflectionParam*>& getParams();

		void invoke(void* instance, const std::vector<boost::any>& params);
		template<typename T> T invoke(void* instance, const std::vector<boost::any>& params);

		const std::map<std::string, ReflectionAnotation*>& getAnotations();
		ReflectionAnotation* getAnotation(const std::string& name);

	private:
		std::string mName;
		std::string mRetType;
		std::vector<ReflectionParam*> mParams;

		boost::any (*mInvoke)(void*, const std::vector<boost::any>&);

		std::map<std::string, ReflectionAnotation*> mAnotations;
};


#include "ReflectionFunction.inl"

#endif /* REFLECTIONFUNCTION_H_ */
