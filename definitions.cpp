#include "cdrasn1.hpp"

#include <cstdio>

using namespace std;
using namespace cdrasn1;

cdrasn1::definitions::definitions() : data(nullptr)				{  }

cdrasn1::definitions::definitions(const char * filename) throw(const runtime_error&)
{
	try
	{
		load_file(filename);
	}
	catch (const runtime_error& err)
	{
		throw (err);
	}
	return;
}

void cdrasn1::definitions::load_file(const char * filename) throw(const runtime_error&)
{
	FILE * definitions_file(nullptr);
	size_t linenumber(0);
	vector<string> linefields;
	definitions_file=fopen(filename,"r");
	while (!feof(definitions_file))
	{
		string presenttype;
		size_t defpos(0);
		linefields=readline(definitions_file);
		linenumber++;
		if (linefields.size() == 0) continue;
		presenttype=linefields.front();
		for (size_t i=0;i!=linefields.size();++i)
		{
			if(linefields.at(i) == "::=")
			{
				defpos=i;
				break;
			}
			if(defpos == 0)
			{
				string message("An error was found on line ");
				message += std::to_string(linenumber) + ".\n";
				message += "The definition indicator (::=) was expected "
					"isolated, but that did'nt happen.\n";
				throw(message);
			}
		}
		
	}
	fclose(definitions_file);
}

vector<string> cdrasn1::definitions::readline(FILE * definitions_file)
{
	char byte(0);
	bool commenttrigger(false);
	vector<string> result;
	string partial_word;
	while (!feof(definitions_file))
	{
		fread(&byte,1,1,definitions_file);
		if (commenttrigger)
		{
			if (byte == '-')
			{
				partial_word.pop_back();
				result.push_back(partial_word);
				gotoendline(definitions_file);
				return result;
			}
			else commenttrigger=false;
		}
		else
		{
			commenttrigger=true;
		}
		if (byte == '\n')
		{
			if (partial_word.size() > 0) result.push_back(partial_word);
			return result;
		}
		if (byte == ' ')
		{
			if (partial_word.size()==0) continue;
			result.push_back(partial_word);
			partial_word.clear();
		}
		partial_word.push_back(byte);
	}
	if (partial_word.size() > 0) result.push_back(partial_word);
	return result;
}

string cdrasn1::definitions::readword(FILE * definitions_file)
{
	char byte(0);
	string result;
	bool commenttrigger;
	while (!feof(definitions_file))
	{
		fread(&byte,1,1,definitions_file);
		switch(byte)
		{
		case '-':
			if (commenttrigger)
			{
				result.pop_back();
				gotoendline(definitions_file);
				return result;
			}
			else
			{
				commenttrigger=true;
			}
		break;
		case ' ':
		case '\n':
			if (result.size() == 0) continue;
			return result;
		}
		result.push_back(byte);
	}
	return result;
}

void cdrasn1::definitions::gotoendline(FILE * definitions_file)
{
	char byte(0);
	while (!feof(definitions_file))
	{
		fread(&byte,1,1,definitions_file);
		if (byte == '\n') return;
	}
	return;
}
