#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>

#include "001-TwoSum.h"
#include "143-ReorderList.h"

using namespace std;

typedef std::function<bool ()> Tester;

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

void setupTest(shared_ptr<vector<Tester>>& tests)
{
	shared_ptr<TwoSum> s001 = make_shared<TwoSum>();
	Tester fn = bind(&TwoSum::Test, *s001);
	tests->push_back(fn);

	shared_ptr<ReorderList> s143 = make_shared<ReorderList>();
	fn = bind(&ReorderList::Test, *s143);
	tests->push_back(fn);
}

void runTest(shared_ptr<vector<Tester>>& tests)
{
	for (auto it = tests->begin(); it != tests->end(); ++it)
	{
		Tester tester = (*it);
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
	shared_ptr<vector<Tester>> allTests = make_shared<vector<Tester>>();
	
	setupTest(allTests);
	runTest(allTests);

	system("pause");
	return 0;
}