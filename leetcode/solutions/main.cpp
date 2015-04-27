#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

#include "001-TwoSum.h"

using namespace std;

typedef bool (*Tester)();

// class std::_Bind<1,bool,struct std::_Pmf_wrap<bool (__thiscall ClassName::*)(void),bool,class ClassName>,class ClassName &>
void parseClassName(const string& typeName, string& className)
{
	unsigned found = typeName.rfind("class");
	if (found)
	{
		className = typeName.substr(found + 6, typeName.length() - 3 - found - 6);
	}
	else
	{
		className = typeName;
	}
}

void setupTest(shared_ptr<vector<function<bool()>>>& tests, shared_ptr<vector<void*>> objects)
{
	shared_ptr<TwoSum> s001 = make_shared<TwoSum>();
	objects->push_back((void*)(s001.get()));
	function<bool()> fn = bind(&TwoSum::Test, *s001);
	tests->push_back(fn);
}

void runTest(shared_ptr<vector<function<bool()>>>& tests)
{
	for (auto it = tests->begin(); it != tests->end(); ++it)
	{
		function<bool()> tester = (*it);
		tester();
		const type_info& type = tester.target_type();
		string typeName(type.name());
		string className;
		parseClassName(typeName, className);
		cout << className << " test successful" << endl;
	}
}

int main()
{
	shared_ptr<vector<function<bool()>>> allTests = make_shared<vector<function<bool()>>>();
	shared_ptr<vector<void*>> allObjects = make_shared<vector<void*>>();
	
	setupTest(allTests, allObjects);
	runTest(allTests);

	system("pause");
	return 0;
}