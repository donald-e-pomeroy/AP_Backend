#include <iostream>
#include "DatabaseManipulations.h";
#include <string>
#include <vector>

int main()
{
	DatabaseManipulations man = DatabaseManipulations();
	man.addName("donny");
	man.addName("cole");

	man.addCategory("cheese");
	man.addCategoryToURL("cheese", "donny");
	man.addComment("donny", "hello world");


	man.incrementPlusCounter("donny");
	man.incrementMinusCounter("donny");
	man.incrementVisits("donny");

	int visits = man.getTotalVisits();
	int upvotes = man.getPlusCounter("donny");


	vector<string> urls = man.getAllURLs();
	vector<string> cat = man.getAllCategories();
	vector<string> urlsforcat = man.getMostVisited();
	vector<string> comments = man.getComments("donny");

	cout << visits << "\n" << upvotes << "\ncare: ";
	for(int i=0; i<urlsforcat.size(); i++)
		cout<< urlsforcat.at(i) << "";
	cout << "\n";
	for(int i=0; i<cat.size(); i++)
			cout << cat.at(i) << " categories here";
	cout << "\n"  << man.getTotalVisits() << "\n" << man.getTotalViewedUrls() << "\n";
	for(int i=0; i<urls.size(); i++)
			cout << urls.at(i) << " ";

	for(int i=0;i<comments.size();i++)
	{
		cout<<comments.at(i)<<"\n";
	}
	return 0;
}

