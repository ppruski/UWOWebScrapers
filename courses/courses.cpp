#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
using namespace std;


string setCMD(string subject);


int main()
{
	string cmd;

	int status;
	int exit0=0, exitUnknown=0;

	string subject[123] = {"ACTURSCI", "AMERICAN", "ANATCELL", 
		"ANTHRO", "APPLMATH", "ARABIC", "ASTRONOM", "BIBLSTUD", "BIOCHEM", 
		"BIOLOGY", "BIOMED", "MTP-RADO", "MTP-TVSN", "MTP-FLDP", "BUSINESS", 
		"CALCULUS", "CANADIAN", "CGS", "CBE", "CHEM", "CSI", 
		"CHINESE", "CHURCH", "CHURLAW", "CEE", "CLASSICS", "CMBPROG", 
		"COMMSCI", "COMPLIT", "COMPSCI", "DOL", "DANCE", "EARTHSCI", 
		"ECONOMIC", "EDUC", "ECE", "ENGSCI", "ENGLISH", "ENVIRSCI", 
		"EPIDEMIO", "FAMLYSTU", "FLDEDUC", "FILM", "FRSTNATN", "FOODNUTR", 
		"FRENCH", "GEOGRAPH", "GEOPHYS", "GERMAN", "GREEK", "GPE", 
		"HEALTSCI", "HEBREW", "HINDI", "HISTTHEO", "HISTORY", "HISTSCI", 
		"HOMILET", "HUMANECO", "INTERDIS", "INTREL", "ITALIAN", "JAPANESE", 
		"MTP-BRJR", "KINESIOL", "KOREAN", "LATIN", "LAW", "LOP", 
		"LINGUIST", "LITURST", "LITURGIC", "MTP-MKTG", "MOS", "MATSCI", 
		"MATH", "MME", "MIT", "MEDBIO", "MEDSCIEN", "MICROIMM", 
		"MORALTHE", "MTP-MMED", "MUSIC", "NURSING", "EXCHANGE", "PASTTHEO", 
		"PATHOL", "PATHTOX", "PHARM", "PHILST", "PHILOSOP", "PHYSICS", 
		"PHYSIOL", "PLANETSC", "POLISCI", "PORTUGSE", "PSYCHOL", "REHABSCI", 
		"RELEDUC", "RELSTUD", "RUSSIAN", "SACRTHEO", "SCHOLARS", "SCIENCE", 
		"SOCLJUST", "SOCWORK", "SOCIOLOG", "SE", "SPANISH", "SPEECH", 
		"SPIRTHEO", "STATS", "SYSTHEO", "THANAT", "THEOETH", "THEOLST", 
		"THESIS", "VAHISTRY", "VASTUDIO", "MTP-WRIT", "WOMENST", "WRITING" };

	list<string> unknownExits;
	

	for (int i=0; i<123; i++)
	{
		cmd.clear();

		cmd = setCMD(subject[i]);

		//execute perl command
		status = system(cmd.c_str());
		//cout << i+1 << ": "<< cmd << endl; status = 0;
		//check exit code
		if (status == 0) {
			exit0++;
		} else {
			cout << "unknown exit code: " << status << endl;
			exitUnknown++;
			unknownExits.push_back(cmd);
		}
	}

	cout << "----------------------------" << endl;
	cout << "-----Summary:---------------" << endl;
	cout << "-Successful queries: " << exit0 << endl;
	if (exitUnknown)
	{
		cout << "-Rouge results: " << exitUnknown << endl << endl;
		
		for(list<string>::const_iterator it = unknownExits.begin(); it != unknownExits.end(); ++it)
        {
                cout << *it << endl;
        }
	}

	return 0;
}

string setCMD(string subject)
{
	string cmd;

	string perl = "perl";
	string space = " ";
	string script = "courses.pl";
	string redirection = ">> courses.txt";

	cmd.append(perl);
	cmd.append(space);
	cmd.append(script);
	cmd.append(space);
	cmd.append(subject);
	cmd.append(space);
	cmd.append(redirection);

	return cmd;
}
