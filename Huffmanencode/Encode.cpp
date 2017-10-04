//Cody Grinstead
// CSCI 480
// Huffman Encode
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
 
using namespace std;
const int totalchar = 128;
//phnz.jcnf.xmmd.nafp.xwna.rwfa.hfzn.cjpn

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
	struct HuffmanTree *left;
	struct HuffmanTree *right;
	HuffmanTree(char c, int f, struct HuffmanTree *left = NULL,
		struct HuffmanTree *right = NULL) :
		character(c), frequency(f), left(left), right(right) {
	}
	~HuffmanTree() {
		delete left, delete right;
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



void write_file()
{
	//Create file with exten.
	//print idenitfier
	//print array of char to compression value
}

HuffmanTree *build_tree(priority_queue<charFequ> &in)
{
	priority_queue<HuffmanTree *, vector<HuffmanTree *>, HuffmanTree::Compare> heap;
	charFequ xfer;
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
		left = heap.top();
		heap.pop();
		right = heap.top();
		heap.pop();
		root = new HuffmanTree('-', left->frequency + right->frequency, left, right);
		heap.push(root);
	}
	return root;
}

void print_tree(HuffmanTree *t) {
	deque< pair<HuffmanTree *, int> > q;

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
		cout << parent->frequency << " " << parent->character << endl;
		if (parent->left)
			q.push_back(make_pair(parent->left, level + 1));
		if (parent->right)
			q.push_back(make_pair(parent->right, level + 1));
	}
}

void create_table(HuffmanTree *t, table tab[],int elements)
{
	while (t->left != NULL)
	{

	}
}

int main(int argc, char *argv[])
{
	charFequ this_file[totalchar];
	deque<string> File_In;
	charFequ encode[totalchar];
	readin(File_In);
	/*ifstream inf;
	inf.open(argv[0]);
	int lineCount = 0;	
	while (!inf.eof())
	{
		getline(inf, getl);
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
	
	system("pause");
	return 0;
}