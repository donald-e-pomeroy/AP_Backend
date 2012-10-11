//Donald Pomeroy
//DEP2127



#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include "DatabaseManipulations.h"
#include "Database.h"


using namespace std;

DatabaseManipulations::DatabaseManipulations()
{

}
//constructor

//adds a URL to the table
//s - the name of the URL
void DatabaseManipulations::addName(char*s)
{
	if(containsName(s))
	{
		return;
	}
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm = (char*)malloc(512*sizeof(char*));
	strcpy(comm, "insert into URLdata(name , categories, plusCounter, minusCounter, visits, comments, snapshotFile) values('");
	strcpy(buffer,comm);
	strcat(buffer,s);
	strcat(buffer, "',' ',0,0,0,' ',' ");
	db->query(strcat(buffer,"');"));
	db->close();
}

//checks to see if there is a URL with a specific name in the table
//s - the name of the URL
bool DatabaseManipulations::containsName(char*s)
{
	vector<vector<string> > res;
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	strcpy(comm, "select name from URLdata where name='");
	strcpy(buffer,comm);
	strcat(buffer,s);
	res = db->query(strcat(buffer,"'"));
	db->close();

	if(res.size()==0)
	{
		return false;
	}
	return true;
}


void DatabaseManipulations::addCategory(char*s)
{
	if(containsCategory(s))
	{
		return;
	}

	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm = (char*)malloc(512*sizeof(char*));
	strcpy(comm, "insert into Categories(categories, name) values('");
	strcpy(buffer,comm);
	strcat(buffer,s);
	db->query(strcat(buffer,"', ' ');"));
	db->close();
}

//s - the name of the URL
bool DatabaseManipulations::containsCategory(char*s)
{
	vector<vector<string> > res;
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	strcpy(comm, "select categories from Categories where categories='");
	strcpy(buffer,comm);
	strcat(buffer,s);
	res = db->query(strcat(buffer,"';"));
	db->close();

	if(res.size()==0)
	{
		return false;
	}
	return true;
}

void DatabaseManipulations::incrementVisits(char*s)
{
    if(!(containsName(s)))
    {
        return;
    }

    vector<vector<string> > res;
    Database* db;
    db = new Database("project2.db");
    char buffer[4096];
    char * comm=(char*)malloc(512*sizeof(char*));
    strcpy(comm, "select visits from URLdata where name='");
    strcpy(buffer,comm);
    strcat(buffer,s);
    res = db->query(strcat(buffer,"'"));
    db->close();

    string str;
    str = res.at(0).at(0);
    char *p;
    long int i = strtol(str.c_str(),&p,10);
    i++;
    char intBuffer[256];
    sprintf(intBuffer,"%d",i );

    Database* db2;
    db2 = new Database("project2.db");
    char buffer2[4096];
    char * comm2 = (char*)malloc(512*sizeof(char*));
    strcpy(comm2, "update URLdata set visits=");
    strcpy(buffer2,comm2);
    strcat(buffer2,intBuffer);
    strcat(buffer2, " ");
    strcat(buffer2, "where name='");
    strcat(buffer2, s);
    db2->query(strcat(buffer2,"'"));
    db2->close();
}


//str1 the name of category, str2 the name of the URL
void DatabaseManipulations::addCategoryToURL(char* str1,char* str2)
{
	if(!(containsName(str2)) || !(containsCategory(str1)))
	{
		return;
	}


	addURLToCategory(str1, str2);
/*	vector<vector<string> > res;
	Database* db;

	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	strcpy(comm, "select categories from URLdata where name='");
	strcpy(buffer,comm);
	strcat(buffer,str2);
	strcat(buffer,"'");
	res = db->query(buffer);
	db->close();

	string s;
	s = res.at(0).at(0);


	s+=" ";
	s+=str1;*/
	Database* db2;
	db2 = new Database("project2.db");
	char buffer2[4096];
	char * comm2 = (char*)malloc(512*sizeof(char*));
	strcpy(comm2, "update URLdata set categories ='");
	strcpy(buffer2,comm2);
	strcat(buffer2, str1);
	strcat(buffer2, "' ");
	strcat(buffer2, "where name='");
	strcat(buffer2, str2);
	db2->query(strcat(buffer2,"'"));
	db2->close();

}

void DatabaseManipulations::addURLToCategory(char* str1, char* str2)
{

	vector<vector<string> > res;
	Database* db;

	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));

	strcpy(comm, "select name from Categories where categories='");
	strcpy(buffer,comm);
	strcat(buffer,str1);
	strcat(buffer,"'");

	res = db->query(buffer);
	db->close();
	string s;

	s = res.at(0).at(0);





	char * cstr;
	cstr = new char[s.size()+1];
	char* tokenizecheck;
	strcpy(cstr,s.c_str());
	bool found = false;

	tokenizecheck = strtok(cstr," ");
	while(tokenizecheck!= NULL)
	{
		if(strcmp(tokenizecheck,str2)==0)
		{
			found = true;
		}
		tokenizecheck = strtok(NULL," ");
	}

	if(!found)
	{
		s+=" ";
		s+=str2;
	}
	Database* db2;
	db2 = new Database("project2.db");
	char buffer2[4096];
	char * comm2 = (char*)malloc(512*sizeof(char*));
	strcpy(comm2, "update Categories set name ='");
	strcpy(buffer2,comm2);
	strcat(buffer2, s.c_str());
	strcat(buffer2, "' ");
	strcat(buffer2, "where categories='");
	strcat(buffer2, str1);
	db2->query(strcat(buffer2,"';"));
	db2->close();
}

void DatabaseManipulations::incrementPlusCounter(char*s)
{
	if(!(containsName(s)))
	{
		return;
	}

	vector<vector<string> > res;
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	strcpy(comm, "select plusCounter from URLdata where name='");
	strcpy(buffer,comm);
	strcat(buffer,s);
	res = db->query(strcat(buffer,"'"));
	db->close();

	string str;
	str = res.at(0).at(0);
	char *p;
	long int i = strtol(str.c_str(),&p,10);
	i++;
	char intBuffer[256];
	sprintf(intBuffer,"%d",i );

	Database* db2;
	db2 = new Database("project2.db");
	char buffer2[4096];
	char * comm2 = (char*)malloc(512*sizeof(char*));
	strcpy(comm2, "update URLdata set plusCounter=");
	strcpy(buffer2,comm2);
	strcat(buffer2,intBuffer);
	strcat(buffer2, " ");
	strcat(buffer2, "where name='");
	strcat(buffer2, s);
	db2->query(strcat(buffer2,"'"));
	db2->close();
}

void DatabaseManipulations::incrementMinusCounter(char*s)
{
	if(!(containsName(s)))
	{
		return;
	}

	vector<vector<string> > res;
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	strcpy(comm, "select minusCounter from URLdata where name='");
	strcpy(buffer,comm);
	strcat(buffer,s);
	res = db->query(strcat(buffer,"'"));
	db->close();

	string str;
	str = res.at(0).at(0);
	char *p;
	long int i = strtol(str.c_str(),&p,10);
	i++;
	char intBuffer[256];
	sprintf(intBuffer,"%d",i );

	Database* db2;
	db2 = new Database("project2.db");
	char buffer2[4096];
	char * comm2 = (char*)malloc(512*sizeof(char*));
	strcpy(comm2, "update URLdata set minusCounter=");
	strcpy(buffer2,comm2);
	strcat(buffer2,intBuffer);
	strcat(buffer2, " ");
	strcat(buffer2, "where name='");
	strcat(buffer2, s);
	db2->query(strcat(buffer2,"'"));
	db2->close();
}


vector<string> DatabaseManipulations::getAllURLs()
{
			int i;
			vector<string> allurl;
			vector<vector<string> > res;
			Database* db;
			db = new Database("project2.db");
			char buffer[4096];
			char * comm=(char*)malloc(512*sizeof(char*));
			strcpy(comm, "select name from URLdata;");
			strcpy(buffer,comm);
			res = db->query(buffer);
			db->close();

			for(i=0; i<res.size(); i++)
			{
				allurl.push_back(res.at(i).at(0));
			}

			return allurl;
}


vector<string> DatabaseManipulations::getMostVisited()
{

	vector<vector<string> >res;
	vector<string>allcat;
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	res = db->query("select name from URLdata order by visits desc;");
	db->close();


	for(int i=0; i<res.size(); i++)
	{
		string s = res.at(i).at(0);
		allcat.push_back(s);
	}

	return allcat;
}

vector<string> DatabaseManipulations::getLeastVisited()
{

	vector<vector<string> >res;
	vector<string>allcat;
	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	res = db->query("select name from URLdata order by visits asc;");
	db->close();


	for(int i=0; i<res.size(); i++)
	{
		string s = res.at(i).at(0);
		allcat.push_back(s);
	}

	return allcat;
}

vector<string> DatabaseManipulations::randomizedURLs()
{
	vector<string> randomUrl  = getAllURLs();
	random_shuffle(randomUrl.begin(),randomUrl.end());
	return randomUrl;
}

//returns the URLs ordered by popularity
vector<string> DatabaseManipulations::getMostLiked()
{

			vector<string> allurl;
			vector<vector<string> > res;
			Database* db;
			db = new Database("project2.db");

			res = db->query("select name from URLdata order by (plusCounter-minusCounter) DESC;");
			db->close();

			for(int i=0; i<res.size(); i++)
			{
				allurl.push_back(res.at(i).at(0));
			}

			return allurl;
}

//returns the URLs ordered by least popularity
vector<string> DatabaseManipulations::getLeastLiked()
{
	vector<string> allurl;
	vector<vector<string> > res;
	Database* db;
	db = new Database("project2.db");

	res = db->query("select name from URLdata order by (plusCounter-minusCounter) ASC;");
	db->close();

	for(int i=0; i<res.size(); i++)
	{
		allurl.push_back(res.at(i).at(0));
	}

	return allurl;
}

vector<string> DatabaseManipulations::getAllCategories()
{
				int i;
				vector<string> allcat;
				vector<vector<string> > res;
				Database* db;
				db = new Database("project2.db");
				char buffer[4096];
				char * comm=(char*)malloc(512*sizeof(char*));
				strcpy(comm, "select distinct categories from Categories;");
				strcpy(buffer,comm);
				res = db->query(buffer);
				db->close();


				for(i=0; i<res.size(); i++)
				{
					string s = res.at(i).at(0);
					allcat.push_back(s);

				}

				return allcat;
}

vector<string> DatabaseManipulations::getAllURLsByCategory(char * url)
{
					int i;
					vector<string> allcat;
					vector<vector<string> > res;
					Database* db;
					db = new Database("project2.db");
					char buffer[4096];
					char * comm=(char*)malloc(512*sizeof(char*));
					strcpy(comm, "select name from Categories where categories ='");
								strcpy(buffer,comm);
								strcat(buffer, url);
								strcat(buffer, "';");
								res = db->query(buffer);
								db->close();


					for(i=0; i<res.size(); i++)
					{
						string s = res.at(i).at(0);
						allcat.push_back(s);

					}

					return allcat;
}
//gets the

vector<string> DatabaseManipulations::getCategoryByURL(char * url)
{
					int i;
					vector<string> allcat;
					vector<vector<string> > res;
					Database* db;
					db = new Database("project2.db");
					char buffer[4096];
					char * comm=(char*)malloc(512*sizeof(char*));
					strcpy(comm, "select categories from URLData where name ='");
					strcpy(buffer,comm);
					strcat(buffer, url);
					strcat(buffer, "';");
					res = db->query(buffer);
					db->close();


					for(i=0; i<res.size(); i++)
					{
						string s = res.at(i).at(0);
						allcat.push_back(s);

					}

					return allcat;
}

//returns the number of positive votes for a URL
//the name of the URL
int  DatabaseManipulations::getPlusCounter(char * str)
{

			int i, totalplus=0, size;
			vector<vector<string> > res;
			Database* db;
			db = new Database("project2.db");
			char buffer[4096];
			char * comm=(char*)malloc(512*sizeof(char*));
			strcpy(comm, "select plusCounter from URLdata where name ='");
			strcpy(buffer,comm);
			strcat(buffer, str);
			strcat(buffer, "';");
			res = db->query(buffer);
			db->close();
			size = res.size();
			for(i=0; i<size; i++)
			{
				totalplus += atoi(res.at(i).at(0).c_str());
			}

			return totalplus;
}

//returns the number of down votes
//str- the name of the URL
int  DatabaseManipulations::getMinusCounter(char * str)
{
				int i, totalminus=0, size;
				vector<vector<string> > res;
				Database* db;
				db = new Database("project2.db");
				char buffer[4096];
				char * comm=(char*)malloc(512*sizeof(char*));
				strcpy(comm, "select minusCounter from URLdata where name ='");
				strcpy(buffer,comm);
				strcat(buffer, str);
				strcat(buffer, "';");
				res = db->query(buffer);
				db->close();
				size = res.size();
				for(i=0; i<size; i++)
				{
					totalminus += atoi(res.at(i).at(0).c_str());
				}

				return totalminus;
}

//returns the number of visits
//str - the name of the URL
int  DatabaseManipulations::getVisits(char * str)
{
				int i, totalvisits=0, size;
				vector<vector<string> > res;
				Database* db;
				db = new Database("project2.db");
				char buffer[4096];
				char * comm=(char*)malloc(512*sizeof(char*));
				strcpy(comm, "select visits from URLdata where name ='");
				strcpy(buffer,comm);
				strcat(buffer, str);
				strcat(buffer, "';");
				res = db->query(buffer);
				db->close();
				size = res.size();
				for(i=0; i<size; i++)
				{
					totalvisits += atoi(res.at(i).at(0).c_str());
				}

				return totalvisits;
}


//Associates a comment with a specific URL
//str1 - the name of the URL, str2 - the comment to insert
void DatabaseManipulations::addComment(char*str1,char*str2)
{
	if(!(containsName(str1)))
	{
		return;
	}

	Database *db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm=(char*)malloc(512*sizeof(char*));
	strcpy(comm, "insert into CommentTable(content) values ('");
	strcpy(buffer,comm);
	strcat(buffer,str2);
	strcat(buffer,"');");
	db->query(buffer);
	db->close();

	vector<vector<string> >numberToInsert;

	Database *db2;
	db2 = new Database("project2.db");
	numberToInsert = db2->query("select count(num) from CommentTable");
	db2->close();


	vector<vector<string> >commentNumberString;
	Database *db3;
	db3 = new Database("project2.db");
	char buffer3[4096];
	char * comm3 = (char*)malloc(512*sizeof(char*));
	strcpy(comm3, "select comments from URLdata where name='");
	strcpy(buffer3,comm3);
	strcat(buffer3, str1);
	strcat(buffer3, "';");
	commentNumberString = db3->query(buffer3);
	db3->close();

	string insert = commentNumberString.at(0).at(0);
	insert+=" ";
	insert+=numberToInsert.at(0).at(0);

	Database *db4;
	db4 = new Database("project2.db");
	char buffer4[4096];
	char*comm4 = (char*)malloc(512*sizeof(char*));
	strcpy(comm4,"update URLdata set comments='");
	strcpy(buffer4,comm4);
	strcat(buffer4,insert.c_str());
	strcat(buffer4,"' where name='");
	strcat(buffer4, str1);
	db4->query(strcat(buffer4,"';"));
	db4->close();

}


//gets all the comments associated with a URL
//str - the URL name;
vector<string>  DatabaseManipulations::getComments(char * str)
{
	if(!(containsName(str)))
	{
		return (vector<string>)NULL;
	}
	vector<string> numbers;
	vector<vector<string> >res;

	Database* db;
	db = new Database("project2.db");
	char buffer[4096];
	char * comm = (char*)malloc(512*sizeof(char*));
	strcpy(comm,"select comments from URLdata where name='");
	strcpy(buffer,comm);
	strcat(buffer,str);
	res = db->query(strcat(buffer,"';"));
	db->close();

	string out = res.at(0).at(0);

	char * cstr;
	cstr = new char[out.size()+1];
	char* tokenizecheck;
	strcpy(cstr,out.c_str());

	tokenizecheck = strtok(cstr," ");
	while(tokenizecheck!= NULL)
	{
		numbers.push_back(string(tokenizecheck));
		tokenizecheck = strtok(NULL," ");
	}

	vector<string> comments;
	Database* db2;
	db2 = new Database("project2.db");
	for(int i = 0;i<numbers.size();i++)
	{
		string qString = "select content from CommentTable where num=";
		qString+=numbers.at(i);
		qString+=";";
		char * qcstr;
		qcstr = new char[qString.size()+1];
		strcpy(qcstr,qString.c_str());
		res = db2->query(qcstr);
		comments.push_back(res.at(0).at(0));
	}
	db2->close();
	return comments;
}

int DatabaseManipulations::getTotalVisits()// get all visits
{
		int i, totalvisits=0, size;
		vector<vector<string> > res;
		Database* db;
		db = new Database("project2.db");
		char buffer[4096];
		char * comm=(char*)malloc(512*sizeof(char*));
		strcpy(comm, "select visits from URLdata;");
		strcpy(buffer,comm);
		res = db->query(buffer);
		db->close();
		size = res.size();
		for(i=0; i<size; i++)
		{
			totalvisits += atoi(res.at(i).at(0).c_str());
		}

		return totalvisits;
}

int DatabaseManipulations::getTotalViewedUrls() // get number of viewed urls
{
				int i;
				vector<string> allurl;
				vector<vector<string> > res;
				Database* db;
				db = new Database("project2.db");
				char buffer[4096];
				char * comm=(char*)malloc(512*sizeof(char*));
				strcpy(comm, "select name from URLdata WHERE visits > 0;");
				strcpy(buffer,comm);
				res = db->query(buffer);
				db->close();
				int size = res.size();
				for(i=0; i<size; i++)
				{
					allurl.push_back(res.at(i).at(0));
				}

				return allurl.size();
}



