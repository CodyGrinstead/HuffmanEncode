//Cody Grinstead
// CSCI 480
// Huffman Encode
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <bitset>
 
using namespace std;
const int totalchar = 128;
struct charFequ
{
public:
	char character;
	int frequency;

	bool operator<(const charFequ& c) const
	{
		return frequency > c.frequency;
	}
};

struct table
{
public:
	char c;
	string b;
};

struct HuffmanTree {
	char character;
	int frequency;
	string codetable;
	struct HuffmanTree *left;
	struct HuffmanTree *right;

	HuffmanTree(char c, int f, struct HuffmanTree *left = NULL,
		struct HuffmanTree *right = NULL) :
		character(c), frequency(f), left(left), right(right) {
	}

	class Compare {
	public:
		bool operator()(HuffmanTree *a, HuffmanTree *b) {
			return a->frequency > b->frequency;
		}

	};
};

void readin(deque<string> &s)
{
	ifstream inf;
	int lineCount = 0;
	string getl;
	inf.open("Text.txt");
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

bitset<8> string_to_bit(string byte)
{
	bitset<8> ans(byte);
	return ans;
}

void write_file(string docbit,ofstream &outf)
{
	int bit_mod = docbit.size() % 8;
	string bytes;

	for (int i = 0; i < docbit.size(); i += 8)
	{
		bytes = "";
		bytes += docbit[i];
		bytes += docbit[i + 1];
		bytes += docbit[i + 2];
		bytes += docbit[i + 3];
		bytes += docbit[i + 4];
		bytes += docbit[i + 5];
		bytes += docbit[i + 6];
		bytes += docbit[i + 7];
		outf << string_to_bit(bytes);
	}
	bytes = "";
	if (bit_mod == 1)
	{
		bytes = docbit[docbit.size() - 1];
		bytes += "0000000";
		outf << string_to_bit(bytes);
	}
	else if (bit_mod == 2)
	{
		bytes = docbit[docbit.size() - 2];
		bytes += docbit[docbit.size() - 1];
		bytes += "000000";
		outf << string_to_bit(bytes);
	}
	else if (bit_mod == 3)
	{
		bytes = docbit[docbit.size() - 3];
		bytes += docbit[docbit.size() - 2];
		bytes += docbit[docbit.size() - 1];
		bytes += "00000";
		outf << string_to_bit(bytes);
	}
	else if (bit_mod == 4)
	{
		bytes = docbit[docbit.size() - 4];
		bytes += docbit[docbit.size() - 3];
		bytes += docbit[docbit.size() - 2];
		bytes += docbit[docbit.size() - 1];
		bytes += "0000";
		outf << string_to_bit(bytes);
	}
	else if (bit_mod == 5)
	{
		bytes = docbit[docbit.size() - 5];
		bytes += docbit[docbit.size() - 4];
		bytes += docbit[docbit.size() - 3];
		bytes += docbit[docbit.size() - 2];
		bytes += docbit[docbit.size() - 1];
		bytes += "000";
		outf << string_to_bit(bytes);
	}
	else if (bit_mod == 6)
	{
		bytes = docbit[docbit.size() - 6];
		bytes += docbit[docbit.size() - 5];
		bytes += docbit[docbit.size() - 4];
		bytes += docbit[docbit.size() - 3];
		bytes += docbit[docbit.size() - 2];
		bytes += docbit[docbit.size() - 1];
		bytes += "00";
		outf << string_to_bit(bytes);
	}
	else
	{
		bytes = docbit[docbit.size() - 7];
		bytes += docbit[docbit.size() - 6];
		bytes += docbit[docbit.size() - 5];
		bytes += docbit[docbit.size() - 4];
		bytes += docbit[docbit.size() - 3];
		bytes += docbit[docbit.size() - 2];
		bytes += docbit[docbit.size() - 1];
		bytes += "0";
		outf << string_to_bit(bytes);
	}
	
}

void print_tree(HuffmanTree *t) {
	deque< pair<HuffmanTree *, int> > q;
	int i = 0;
	q.push_back(make_pair(t, 0));
	int curlevel = -1;
	while (!q.empty()) {
		HuffmanTree *parent = q.front().first;
		int level = q.front().second;
		q.pop_front();
		if (curlevel != level) {
			curlevel = level;
			cout << "Level " << curlevel << endl;

		}
		cout << parent->frequency << " " << parent->character << " " << parent->codetable << endl;

		if (parent->left)
			q.push_back(make_pair(parent->left, level + 1));
		if (parent->right)
			q.push_back(make_pair(parent->right, level + 1));
	}
}

void leafpad(HuffmanTree *left)
{
	//print_tree(left);
	HuffmanTree *newleaf, *newleft, *newright;
	while (left)
	{
		newleaf = left;
		newleft = newleaf->left;
		newright = newleaf->right;
		if (!newleft)break;
		cout << newright->character << " " << newleft->character << endl;
		system("pause");
		newleft->codetable += "0";
		newright->codetable += "1";
		
		leafpad(newleft);
		leafpad(newright);
		cout << "exitwhile" << endl;
	}
	//cout << "exit leafpad" << endl;
}

HuffmanTree *build_tree(priority_queue<charFequ> &in)
{
	priority_queue<HuffmanTree *, vector<HuffmanTree *>, HuffmanTree::Compare> heap;
	charFequ xfer;
	string leftc = "0", rightc = "1";
	while (!in.empty())
	{
		xfer = in.top();
		in.pop();
		HuffmanTree *leaf = new HuffmanTree(xfer.character, xfer.frequency);
		heap.push(leaf);
	}
	HuffmanTree *root = NULL;
	while (heap.size() > 1)
	{
		HuffmanTree *left, *right; 
		HuffmanTree *newleft, *newright;
		left = heap.top();
		left->codetable = "0";
		heap.pop();	
		leafpad(left);
		cout << "leaf left " << endl;
		right = heap.top();
		right->codetable = "1";
		heap.pop();
		leafpad(right);
		cout << "leaf right" << endl;
		root = new HuffmanTree('`', left->frequency + right->frequency, left, right);
		
		
		heap.push(root);
	}
	return root;
}



string table_bit(table t[], char l, int elements)
{
	for (int i = 0; i < elements; i++)
	{
		if (l == t[i].c)return t[i].b;
	}
}

string bit_stream(table t[], string doc, int elements)
{
	string doc_bit = "";
	char cl;
	for (int i = 0; i < doc.size(); i++)
	{
		cl = doc[i];
		doc_bit += table_bit(t, cl, elements);
	}
	return doc_bit;
}

string search_tree(HuffmanTree *t)
{
	string ans;

	return ans;
}

void create_table(HuffmanTree *t, table tab[],int elements,charFequ inl[])
{
	string code;
	int level;
	
	for (int i = 0; i < elements; i++)
	{
		tab[i].c = inl[i].character;
		tab[i].b = search_tree(t);
	}
		
}


int main(int argc, char *argv[])
{
	charFequ this_file[totalchar];
	deque<string> File_In;
	charFequ encode[totalchar];
	readin(File_In);
	string getl, document;
	ifstream inf;
	inf.open("Text.txt");
	int lineCount = 0;

	while (!inf.eof())
	{
		getline(inf, getl);
		document += getl;
		File_In.push_back(getl);
	}
	inf.close();//*/
	priority_queue<charFequ> pq_file_in;
	int array_elements = 0, num_chars = 0;
	charFequ temp_xfer;

	
	get_freq(File_In, this_file,array_elements);	
	for (int i = 0; i < array_elements; i++)
	{
		pq_file_in.push(this_file[i]);
	}
	HuffmanTree *root= build_tree(pq_file_in);
	//print_tree(root);
	/* testing count
	while (!pq_file_in.empty())
	{
		temp_xfer = pq_file_in.top();
		pq_file_in.pop();
		cout << temp_xfer.character <<" "<< temp_xfer.frequency << endl;
	}
	*/
	cout << document.size() << endl;
	
	system("pause");
	return 0;
}