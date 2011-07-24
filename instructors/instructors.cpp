// PerlProgram.cpp : Defines the entry point for the console application.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
using namespace std;


string setCMD(string firstname, string lastname);


int main()
{
	string cmd;
	string firstname;
	string lastname;

	int status;
	int exit0=0, exitUnknown=0;

	list<string> failedCMDs;

	string alphabet[26] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

	for (int i=0; i<26; i++)
	{
		for (int j=0; j<26; j++)
		{
			cmd.clear();

			firstname.clear();
			firstname.append(alphabet[i]);
			lastname.clear();
			lastname.append(alphabet[j]);

			cmd = setCMD(firstname, lastname);

			//execute perl command
			status = system(cmd.c_str());
			//cout << cmd << endl; status=0;

			//check exit code
			if (status == 0) {
				exit0++;
			} else {
				exitUnknown++;
			}
			
		}
	}

	cout << "----------------------------" << endl;
	cout << "-----Summary:---------------" << endl;
	cout << "-Successful queries: " << exit0 << endl;
	if (exitUnknown)
		cout << "-Rouge results: " << exitUnknown << endl << endl;

	return 0;
}

string setCMD(string firstname, string lastname)
{
	string cmd;

	string perl = "perl";
	string space = " ";
	string script = "instructors.pl";
	string redirection = ">> instructors.txt";

	cmd.append(perl);
	cmd.append(space);
	cmd.append(script);
	cmd.append(space);
	cmd.append(firstname);
	cmd.append(space);
	cmd.append(lastname);
	cmd.append(space);
	cmd.append(redirection);

	return cmd;
}
