//Cody Grinstead
// CSCI 480
// Huffman Encode
#include <fstream>
#include <iomanip>
#include<iostream>
#include <string>
#include<queue>

using namespace std;
const int totalchar = 128;


struct charFequ
{
	char character;
	int frequency;
	bool operator<(const charFequ& c) const
	{
		return frequency > c.frequency;
	}
};


void readin(deque<string> &s)
{
	ifstream inf;
	int lineCount = 0;
	string getl;
	inf.open("test.txt");
	while (!inf.eof()) 
	{
		getline(inf, getl);
		s.push_back(getl);
	}
	inf.close();

}

void get_freq(deque<string> s,charFequ cf[],int &cf_elemnts)
{
	
	string current_line;
	int line_length;
	int elements_array = 0;
	bool doesExist = true;
	while (!s.empty())
	{
		current_line = s.front();
		s.pop_front();
		line_length = current_line.size();
		for (int i = 0; i < line_length; i++)
		{			
			if (elements_array == 0) 
			{
				cf[0].character = current_line[0];
				cf[0].frequency = 1;
				elements_array++;
				doesExist = true;
			}
			else
			{
				for (int j = 0; j < elements_array; j++)
				{
					if (cf[j].character == current_line[i])
					{
						cf[j].frequency++;
						doesExist = true;
						break;
					}
					else
						doesExist = false;
				}

			}
			if (!doesExist)
			{
				cf[elements_array].character = current_line[i];
				cf[elements_array].frequency = 1;
				elements_array++;
				doesExist=true;
			}
		}
	}
	cf_elemnts = elements_array;
}

int main()
{
	charFequ this_file[totalchar];
	deque<string> File_In;
	priority_queue<charFequ> pq_file_in;
	int array_elements = 0;
	charFequ temp_xfer;

	readin(File_In);
	get_freq(File_In, this_file,array_elements);

	for (int i = 0; i < array_elements; i++)
	{
		pq_file_in.push(this_file[i]);
	}
	while (!pq_file_in.empty())
	{
		temp_xfer = pq_file_in.top();
		pq_file_in.pop();
		cout << temp_xfer.character <<" "<< temp_xfer.frequency << endl;
	}

	//TODO create binary tree

	system("pause");
	return 0;
}