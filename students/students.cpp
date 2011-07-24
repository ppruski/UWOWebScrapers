// PerlProgram.cpp : Defines the entry point for the console application.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
using namespace std;


string setCMD(string param1, string param2);


int main()
{
	string cmd;
	string param1;
	string param2;

	int status;
	int exit7=0, exit13=0, exit13_f=0, exit0=0, exitUnknown=0;
	list<string> failedCMDs;
	list<string> unknownExits;

	string alphabet[26] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
		"n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };

	for (int i=14; i<15; i++)
	{
		for (int j=0; j<26; j++)
		{
			for (int k=0; k<26; k++)
			{
				cmd.clear();

				param1.clear();
				param1.append(alphabet[i]);
				param2.clear();
				param2.append(alphabet[j]);
				param2.append(alphabet[k]);

				cmd = setCMD(param1, param2);

				//execute perl command
				status = system(cmd.c_str());

				//check exit code
				if (status == 0) {
					exit0++;
				} else if (status == 1792) {
					exit7++;
				} else if (status == 3328) { //if there are too many results...
					for (int l=0; l<26; l++)
					{
						cmd.clear();
						
						param1.clear();
						param1.append(alphabet[i]);
						param1.append(alphabet[l]);
						param2.clear();
						param2.append(alphabet[j]);
						param2.append(alphabet[k]);

						cmd = setCMD(param1, param2);

						//execute perl command
						status = system(cmd.c_str());

						if (status == 13) { //if there are too many results...
							failedCMDs.push_back(cmd);
							exit13_f++;
						}
					}
					exit13++;
				} else {
					cout << "unknown exit code: " << status << endl;
					exitUnknown++;
					unknownExits.push_back(cmd);
				}
			}
		}
	}

	cout << "----------------------------" << endl;
	cout << "-----Summary:---------------" << endl;
	cout << "-Successful queries: " << exit0 << endl;
	cout << "-More than 250 results found: " << exit13 << endl;
	cout << "-No matches found: " << exit7 << endl << endl;
	if (exitUnknown)
	{
		cout << "-Rouge results: " << exitUnknown << endl << endl;
		
		for(list<string>::const_iterator it = unknownExits.begin(); it != unknownExits.end(); ++it)
                {
                        cout << *it << endl;
                }
	}
	if (exit13_f) {
		cout << "-# queries to repeat: " << exit13_f << endl;
		cout << "Queries to repeat: " << endl;
		for(list<string>::const_iterator it = failedCMDs.begin(); it != failedCMDs.end(); ++it)
		{
			cout << *it << endl;
		}
	}

	return 0;
}

string setCMD(string param1, string param2)
{
	string cmd;

	string perl = "perl";
	string space = " ";
	string script = "students.pl";
	string redirection = ">> students.txt";

	cmd.append(perl);
	cmd.append(space);
	cmd.append(script);
	cmd.append(space);
	cmd.append(param1);
	cmd.append(space);
	cmd.append(param2);
	cmd.append(space);
	cmd.append(redirection);

	return cmd;
}
