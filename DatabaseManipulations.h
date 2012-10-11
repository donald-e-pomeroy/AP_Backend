//Donald Pomeroy
//DEP2127


#include <string>
#include <vector>
using namespace std;

#ifndef DATABASEMANIPULATIONS_H
#define DATABASEMANIPULATIONS_H

class DatabaseManipulations
{
private:
	void addURLToCategory(char*,char*); //the name of the Category, the name of URL
public:
	DatabaseManipulations();
	void addName(char*);//the name of the URL
	void addCategory(char*);//the name of the URL
	void addCategoryToURL(char*,char*);//the name of the Category, the name of URL
	void incrementPlusCounter(char*);//the name of the URL
	void incrementMinusCounter(char*);//the name of the URL
	void incrementVisits(char*);//the name of the URL to add to
	void addComment(char*, char*);//the name of the URl to add to, the comment
	bool containsName(char*);//the name of the URL
	bool containsCategory(char*);//the name of the URL

	vector<string> getAllURLs();//the name of the URL
	vector<string> getAllCategories();//the name of the URL
	vector<string> getAllURLsByCategory(char*);//the name of the category
	vector<string> getCategoryByURL(char*);//the name of the category
	bool hasCategory(char*,char*);// the name of the URL and the name of the category
	vector<string>getURLsWithCategory(char*);//the name of the category
	int getPlusCounter(char*);//the name of the URL
	int getMinusCounter(char*);//the name of the URL
	int getVisits(char*);//the name of the URL
	vector<string>getComments(char*);//the name of the URL
	int getTotalVisits(); // get all visits
	int getTotalViewedUrls(); // get number of viewed urls

	vector<string> getMostVisited();//get the most visited URLS
	vector<string> getLeastVisited();//get the least visited URLs
	vector<string> getMostLiked();//get the most popular URLS
	vector<string> getLeastLiked();//get the least popular URLS
	vector<string> randomizedURLs();

};
#endif
