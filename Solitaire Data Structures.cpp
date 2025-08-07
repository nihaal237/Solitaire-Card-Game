#include<iostream>
#include <windows.h>
#include<cstdlib>
#include<ctime>

#define RED 12
#define RESET 7 
using namespace std;

bool StringCompare(char* ptr, const char* ptr1) //Comparison for Printing Suits of Cards
{
	for (int i = 0; ptr[i] != '\0'; i++)
		if (ptr[i] != ptr1[i])
			return false;

	return true;
}
bool StringCompare(char* ptr1, char* ptr2) //Compairison for Suits of Cards
{
	int Length1 = strlen(ptr1);
	int Length2 = strlen(ptr2);
	if (Length1 != Length2)
		return false;

	for (int i = 0; ptr1[i] != '\0'; i++)
	{
		if (ptr1[i] != ptr2[i])
			return false;
	}

	return true;
}

class Command
{
private:
	char* command;
	char action;
	char destination;
	char source;
	int destinationIndex;
	int sourceIndex;
	int count; //number of cards to be moved
public:

	Command() //default constructor
	{
		command = 0;
		action = 0;
		destination = 0;
		source = 0;
		destinationIndex = 0;
		sourceIndex = 0;
		count = 0;
	}

	Command(char* ptr) //paramaterized constructor
	{
		int Length = strlen(ptr);
		command = new char[Length + 1];
		for (int i = 0; i < Length; i++)
		{
			command[i] = ptr[i];
		}

		command[Length] = '\0';
		action = 0;
		destination = 0;
		source = 0;
		destinationIndex = 0;
		sourceIndex = 0;
		count = 0;
	}

	Command& operator=(const Command& other) //Assignment Operator
	{
		if (this != &other)
		{
			if (command)
			{
				delete[] command;
			}

			if (other.command != nullptr)
			{
				int Length = strlen(other.command);
				command = new char[Length + 1];
				for (int i = 0; i < Length; ++i)
				{
					command[i] = other.command[i];
				}
				command[Length] = '\0';
			}
			else
			{
				command = nullptr;
			}

			action = other.action;
			destination = other.destination;
			source = other.source;
			destinationIndex = other.destinationIndex;
			sourceIndex = other.sourceIndex;
			count = other.count;
		}
		return *this;
	}

	Command(const Command& other) //Copy Constructor
	{
		if (other.command != nullptr)
		{
			int Length = strlen(other.command);
			command = new char[Length + 1];
			for (int i = 0; i < Length; ++i)
			{
				command[i] = other.command[i];
			}
			command[Length] = '\0';
		}
		else
		{
			command = nullptr;
		}


		action = other.action;
		destination = other.destination;
		source = other.source;
		destinationIndex = other.destinationIndex;
		sourceIndex = other.sourceIndex;
		count = other.count;

	}

	char GetAction()
	{
		return action;
	}

	char GetDestination()
	{
		return destination;
	}
	char GetSource()
	{
		return source;
	}
	int GetDestinationIndex()
	{
		return destinationIndex;
	}
	int GetSourceIndex()
	{
		return sourceIndex;
	}

	int GetNumberOfCards()
	{
		return count;
	}

	bool ParseCommand()
	{
		int index = 0;
		while (command[index] == ' ') //skip all spaces
			index++;

		if (command[index] != 's' && command[index] != 'm' && command[index] != 'z')
		{
			return false;
		}

		if (command[index] == 's' || command[index] == 'z')
		{
			action = command[index];

			index++;

			while (command[index] == ' ') //skip all spaces
				index++;

			if (command[index] == '\0') //if command is just s or z and followed by nothing then return true
			{
				return true;
			}
			else
				return false;
		}

		if (command[index] == 'm')
		{
			action = command[index];

			index++;

			while (command[index] == ' ') //skip all spaces 
				index++;

			if (command[index] != 'w' && command[index] != 'f' && command[index] != 'c') //invalid command
				return false;
			else
			{
				source = command[index];

				if (source == 'c')
				{
					index++;
					if (command[index] <= '7' && command[index] >= '1') //columns can only be in between 1 or 7 
					{
						sourceIndex = command[index] - '0';
						sourceIndex--; //for index of column
					}
					else
					{
						return false;
					}
				}
				else if (source == 'f')
				{
					index++;
					if (command[index] <= '4' && command[index] >= '1')
					{
						sourceIndex = command[index] - '0';
						sourceIndex--; //for index of foundation 
					}
					else
					{
						return false;
					}
				}

				index++;

				if (command[index] != ',') //iif source not followed by , return false
					return false;

				index++;

				while (command[index] == ' ')
					index++; //skip all spaces

				if (command[index] != 'f' && command[index] != 'c') //if destination is not foundation or column return false
					return false;

				destination = command[index];

				index++;
				if (destination == 'c')
				{
					if (command[index] <= '7' && command[index] >= '1')
					{
						destinationIndex = command[index] - '0';
						destinationIndex--; //column index
					}
					else
						return false;
				}

				else if (destination == 'f')
				{
					if (command[index] <= '4' && command[index] >= '1')
					{
						destinationIndex = command[index] - '0';
						destinationIndex--; //foundation index
					}
					else
						return false;
				}

				index++;

				if (source == destination)
				{
					if (source != 'c' && destination != 'c') //if source and des are same only can be column to column
					{
						return false;
					}
				}
				while (command[index] == ' ')
				{
					index++; //skip all spaces
				}

				if (command[index] != ',')
				{
					return false; //if not followed by a comma return false
				}
				index++;

				while (command[index] == ' ')
				{
					index++; //skip all spaces
				}

				if (command[index] <= '9' && command[index] >= '1')  //number of cards
				{
					count = command[index] - '0';
				}
				else
					return false; //number of cards not specified

				if (source != destination)
				{
					if (count != 1) // we can only move more one than card if source and des are same
					{
						return false;
					}
				}

				index++;

				while (command[index] == ' ') //skip all spaces
				{
					index++;
				}

				if (command[index] != 0) //if followed by something else return false
					return false;
			}
		}

		return true;
	}

	~Command()
	{
		if (command)
			delete[]command;
	}
};

class Card
{
	friend ostream& operator<<(ostream& out, const Card& obj);

private:
	char* suit;
	int rank;
public:

	Card() : suit(nullptr), rank(0) {} //default constructor

	Card(char* _suit, int _rank) //parametrized constructor
	{
		if (_suit != 0)
		{
			int Length = strlen(_suit);

			suit = new char[Length + 1];
			for (int i = 0; i < Length; i++)
				suit[i] = _suit[i];

			suit[Length] = '\0';
		}
		else
			suit = _suit;

		rank = _rank;
	}

	bool CompareRankAndSuitForCol(const Card& other) //Comparison for moving card to Column
	{
		if (StringCompare(other.suit, "Diamonds") || StringCompare(other.suit, "Hearts"))
		{
			if (StringCompare(suit, "Spades") || StringCompare(suit, "Clubs"))
			{
				if (rank - 1 == other.rank)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else if (StringCompare(other.suit, "Spades") || StringCompare(other.suit, "Clubs"))
		{
			if (StringCompare(suit, "Diamonds") || StringCompare(suit, "Hearts"))
			{
				if (rank - 1 == other.rank)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

	}

	bool CheckIfAce() //Comparison for moving first card into foundation stack
	{
		if (rank == 1)
			return true;
		return false;
	}

	bool CheckIfKing() //Comparison for moving a card into the empty column
	{
		if (rank == 13)
			return true;
		return false;
	}


	bool CompareRankAndSuitForFoundation(const Card& other)//Comparison for moving card to Foundation
	{
		if (StringCompare(suit, other.suit))
		{
			if (rank + 1 == other.rank)
				return true;
			else
				return false;
		}
		else
			return false;
	}

	Card& operator=(const Card& other) //Assignment Operator
	{
		if (this != &other)
		{
			if (suit)
			{
				delete[] suit;
			}

			if (other.suit != nullptr)
			{
				int Length = strlen(other.suit);
				suit = new char[Length + 1];
				for (int i = 0; i < Length; ++i)
				{
					suit[i] = other.suit[i];
				}
				suit[Length] = '\0';
			}
			else
			{
				suit = nullptr;
			}

			rank = other.rank;
		}
		return *this;
	}

	Card(const Card& other) //Copy Constructor
	{
		if (other.suit != nullptr)
		{
			int Length = strlen(other.suit);
			suit = new char[Length + 1];
			for (int i = 0; i < Length; ++i)
			{
				suit[i] = other.suit[i];
			}
			suit[Length] = '\0';
		}
		else
		{
			suit = nullptr;
		}

		rank = other.rank;
	}


	~Card()
	{
		if (suit)
			delete[]suit;

	}
};

ostream& operator<<(ostream& out, const Card& obj) //cout operator
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (StringCompare(obj.suit, "Hearts") == true || StringCompare(obj.suit, "Diamonds") == true) {
		SetConsoleTextAttribute(hConsole, RED);
	}

	// Print rank
	if (obj.rank == 1)
		out << "A";
	else if (obj.rank == 11)
		out << "J";
	else if (obj.rank == 12)
		out << "Q";
	else if (obj.rank == 13)
		out << "K";
	else
		out << obj.rank;

	if (StringCompare(obj.suit, "Spades") == true)
		cout << "\u2660";
	if (StringCompare(obj.suit, "Hearts") == true)
		cout << "\u2665";
	if (StringCompare(obj.suit, "Clubs") == true)
		cout << "\u2663";
	if (StringCompare(obj.suit, "Diamonds") == true)
		cout << "\u2666";

	if (obj.rank % 10 != 0)
	{
		out << " ";
	}
	else
	{
		out << "  ";
	}

	// Reset color
	SetConsoleTextAttribute(hConsole, RESET);

	return out;
}

template<class T>
class DLL {
private:
	class Node {
	public:

		Node* next;
		Node* previous;
		T CardData;

		Node(Node* _next = nullptr, Node* _previous = nullptr) //default constructor
			: next(_next), previous(_previous), CardData() {}


		Node(const T& data, Node* _next = nullptr, Node* _previous = nullptr)  // Parameterized constructor
			: next(_next), previous(_previous), CardData(data) {}

		~Node()
		{
			next = 0;
			previous = 0;

		}
	};

	class ListIterator //nested class
	{
	private:
		Node* current;
	public:
		friend class DLL;

		ListIterator(Node* curr = 0)
		{
			current = curr;
		}

		ListIterator& operator++()  //Pre-fix increment
		{
			if (current)
			{
				current = current->next;
			}
			return *this;
		}

		ListIterator operator++(int)   //Post-fix increment
		{
			ListIterator old(current);
			if (current)
			{
				current = current->next;
			}
			return old;
		}

		ListIterator& operator--()   //Pre-fix decrement
		{
			if (current)
			{
				current = current->previous;
			}
			return *this;
		}

		ListIterator operator--(int)   //Post-fix decrement
		{
			ListIterator old(current);
			if (current)
			{
				current = current->previous;
			}
			return old;;
		}

		T operator*() //used to get the node data
		{

			return current->CardData;

		}

		bool operator==(const ListIterator& l) const
		{

			return current == l.current;

		}

		bool operator!=(const ListIterator& l) const
		{

			return !(current == l.current);

		}


		Node* getData() //used to access the node within the iterator
		{
			return current;
		}

	};

	Node* head;
	Node* tail;
	int size;

public:

	typedef ListIterator Iterator; //to access in main

	ListIterator begin()
	{
		Iterator I(head->next);
		return I;
	}

	ListIterator end()
	{
		Iterator I(tail->previous);
		return I;
	}

	DLL() {
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->previous = head;
		size = 0;
	}

	Card ReturnCardData() //return topmost card
	{
		return head->next->CardData;
	}

	void AddNode(T data) //creates new node at the start
	{
		Node* newNode = new Node(data, head->next, head);
		head->next->previous = newNode;
		head->next = newNode;
		size++;

	}

	T ReturnTop() //returns topmost data
	{
		if (head->next != tail)
		{
			return head->next->CardData;
		}
	}

	Node* FindNode(int index) //sub function for shuffling
	{
		Node* temp = head->next;

		for (int i = 1; i < index; i++)
		{
			temp = temp->next;
		}
		return temp;
	}

	void Swap(int LeftIndex, int RightIndex) //for cards shuffling
	{

		Node* temp1 = FindNode(LeftIndex);
		Node* temp2 = FindNode(RightIndex);

		if (LeftIndex + 1 == RightIndex) //for consective
		{
			temp1->next = temp2->next;
			temp2->previous = temp1->previous;
			temp1->previous->next = temp2;
			temp1->previous = temp2;
			temp2->next->previous = temp1;
			temp2->next = temp1;
		}
		else
		{
			Node* temp3 = temp2->previous;
			Node* temp4 = temp1->next;
			temp3->next = temp1;
			temp2->previous = temp1->previous;
			temp1->previous->next = temp2;
			temp1->previous = temp3;
			temp1->next = temp2->next;
			temp2->next->previous = temp1;
			temp2->next = temp4;
			temp4->previous = temp2;
		}
	}

	bool isEmpty()
	{
		if (head->next == tail)
			return true;

		return false;
	}

	void InsertAtStart(T const card)
	{
		Node* newNode = new Node(card, head->next, head);
		head->next->previous = newNode;
		head->next = newNode;
		size++;

	}

	void Push(Iterator& Ptr) //push data into dll using iterator
	{
		Node* Insert = Ptr.getData();

		Insert->previous = 0;
		Insert->next = 0;

		Node* temp = head->next;

		if (head->next != tail)
		{
			head->next = Insert;
			Insert->next = temp;
			Insert->previous = head;
			temp->previous = Insert;
		}

		else
		{
			head->next = Insert;
			Insert->next = tail;
			tail->previous = Insert;
			Insert->previous = head;
		}
		size++;
	}

	Iterator& Pop() //pop data from dll using iterator
	{
		if (head->next != tail)
		{
			Node* pop = head->next;
			head->next = pop->next;
			pop->next->previous = head;


			pop->next = 0;
			pop->previous = 0;

			size--;

			Iterator Return(pop);
			return Return;

		}
	}

	void Print() //print all the nodes of dll
	{
		Node* temp = head->next;
		while (temp != tail)
		{
			cout << temp->CardData;
			cout << endl;
			temp = temp->next;
		}
	}
	~DLL()
	{
		Node* temp = 0;
		while (head != 0)
		{
			temp = head;
			head = head->next;
			delete temp;
		}
	}

};

template<typename T>
class Stack
{
private:
	DLL<T>* List;
	int size;

public:

	Stack() //default construcor
	{
		List = new DLL<T>();
		size = 0;

	}

	bool isEmpty()
	{
		if (size == 0)
			return true;

		return false;
	}

	void PushIntoStack(typename DLL<T>::Iterator I) //push into stack using iterator
	{
		List->Push(I);
		size++;
	}

	Card ReturnCardData()
	{
		return List->ReturnCardData();

	}
	void push(T element) //pushing element by calling the InsertAtSTart function in list to add a node at the start of list
	{
		List->InsertAtStart(element);
		size++;
	}

	typename DLL<T>::Iterator& PopFromStack() //remove and return data using iterator
	{
		typename DLL<T>::Iterator Data = List->Pop();
		size--;

		return Data;

	}

	bool CheckIfEmpty()
	{
		return (List->isEmpty());
	}

	void PrintTop() //print topmost card of stack
	{
		if (size != 0)
		{
			cout << List->ReturnTop(); //returns the top without removing it
		}
		else
			cout << '\t';
	}

	~Stack()
	{
		if (List)
		{
			delete List;
		}
	}
};


class Game
{
private:
	DLL<Card> Deck; //stores the deck initially
	Stack<Command> CommandHistory;
	Stack<Card>* Foundation;
	Stack<Card> WastePile;
	Stack <Card> Stock;
	DLL<Card>* Columns;
	int* Colsize;
	int* ExposedCardsSize;
	int StockSize;
	int WastePileSize;
	int* FoundationSize;
	int numberofcommands;


public:

	void InitializeCards() //create cards,initialize them and add in deck
	{
		int rank = 1;
		char array[20] = "Hearts";
		for (int i = 0; i < 13; i++)
		{
			Card card(array, rank++);
			Deck.AddNode(card);
		}
		rank = 1;
		char array1[20] = "Spades";
		for (int i = 13; i < 26; i++)
		{
			Card card(array1, rank++);
			Deck.AddNode(card);
		}
		rank = 1;
		char array2[20] = "Clubs";
		for (int i = 26; i < 39; i++)
		{
			Card card(array2, rank++);
			Deck.AddNode(card);
		}
		rank = 1;
		char array3[20] = "Diamonds";
		for (int i = 39; i < 52; i++)
		{
			Card card(array3, rank++);
			Deck.AddNode(card);
		}

	}

	void ShuffleCards()
	{
		srand(time(0));
		for (int i = 0; i < 30; i++) //shuffle 30 times
		{
			int firstindex = rand() % 53;
			if (firstindex == 0)
				firstindex++;

			int secondindex = rand() % 53;
			if (secondindex == 0)
				secondindex++;

			Deck.Swap(firstindex, secondindex);
		}
	}

	void DistributeCards() //distribute cards in stock and columns
	{
		int count = 1;
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < count; j++)
			{
				Columns[i].Push(Deck.Pop());
			}
			Colsize[i] = count;
			count++;
		}

		for (int i = 0; i < 7; i++) //initially set exposed cards size to 1 of every column
		{
			ExposedCardsSize[i] = 1;
		}


		for (int j = 28; j < 52; j++) //push remaining cards in stock pile
		{

			Stock.PushIntoStack(Deck.Pop());
			StockSize++;
		}
	}

	void PrintGameInterface() //printing game interface using iterators
	{
		cout << "Stock" << '\t' << '\t' << "Waste" << '\t' << '\t' << "Foundation 1" << '\t' << "Foundation 2" << '\t' << "Foundation 3" << '\t' << "Foundation 4" << endl;


		if (StockSize != 0)
		{
			cout << "[ ]" << '\t';
		}
		else
			cout << '\t';

		cout << '\t';

		if (WastePileSize)
		{
			WastePile.PrintTop();

		}
		cout << '\t';
		cout << '\t';

		for (int i = 0; i < 4; i++)
		{
			if (FoundationSize[i] > 0)
			{
				Foundation[i].PrintTop();
				cout << '\t';

			}
			else
				cout << '\t';

			cout << '\t';
		}
		cout << endl;

		cout << "(" << StockSize << " cards" << ")" << '\t';
		cout << "(" << WastePileSize << " cards" << ")" << '\t';
		for (int i = 0; i < 4; i++)
		{
			cout << "(" << FoundationSize[i] << " cards" << ")" << '\t';
			cout << " ";
		}
		cout << endl << endl;

		cout << "Column 1" << '\t' << "Column 2" << '\t' << "Column 3" << '\t' << "Column 4" << '\t' << "Column 5" << '\t' << "Column 6" << '\t' << "Column 7";
		cout << endl;

		for (int i = 0; i < 7; i++)
		{
			cout << "(";
			cout << Colsize[i];
			cout << " cards" << ")" << '\t';

		}

		cout << endl;

		typename DLL<Card>::Iterator IteratorCol1 = Columns[0].end();
		typename DLL<Card>::Iterator IteratorCol2 = Columns[1].end();
		typename DLL<Card>::Iterator IteratorCol3 = Columns[2].end();
		typename DLL<Card>::Iterator IteratorCol4 = Columns[3].end();
		typename DLL<Card>::Iterator IteratorCol5 = Columns[4].end();
		typename DLL<Card>::Iterator IteratorCol6 = Columns[5].end();
		typename DLL<Card>::Iterator IteratorCol7 = Columns[6].end();

		int* exposedcards = new int[7];

		for (int i = 0; i < 7; i++)
		{
			exposedcards[i] = ExposedCardsSize[i];
		}

		int* unexposedcards = new int[7];

		for (int i = 0; i < 7; i++)
		{
			unexposedcards[i] = Colsize[i] - exposedcards[i];

		}


		bool repeat = true;
		int k = 0; //for column index

		while (repeat == true) //print each row of cards of cols until no cards are left to be displayed
		{
			repeat = false;
			k = 0;

			if (unexposedcards[k] > 0)
			{
				cout << "[" << " " << "]" << '\t' << '\t';
				IteratorCol1--;
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol1 << '\t' << '\t';
				IteratorCol1--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';
			k++;

			if (unexposedcards[k] > 0)
			{
				IteratorCol2--;
				cout << "[" << " " << "]" << '\t' << '\t';
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol2 << '\t' << '\t';
				IteratorCol2--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';
			k++;

			if (unexposedcards[k] > 0)
			{
				IteratorCol3--;
				cout << "[" << " " << "]" << '\t' << '\t';
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol3 << '\t' << '\t';
				IteratorCol3--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';
			k++;

			if (unexposedcards[k] > 0)
			{
				IteratorCol4--;
				cout << "[" << " " << "]" << '\t' << '\t';
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol4 << '\t' << '\t';
				IteratorCol4--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';
			k++;

			if (unexposedcards[k] > 0)
			{
				IteratorCol5--;
				cout << "[" << " " << "]" << '\t' << '\t';
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol5 << '\t' << '\t';
				IteratorCol5--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';
			k++;
			if (unexposedcards[k] > 0)
			{
				IteratorCol6--;
				cout << "[" << " " << "]" << '\t' << '\t';
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol6 << '\t' << '\t';
				IteratorCol6--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';
			k++;

			if (unexposedcards[k] > 0)
			{
				IteratorCol7--;
				cout << "[" << " " << "]" << '\t' << '\t';
				unexposedcards[k] = unexposedcards[k] - 1;
				repeat = true;
			}
			else if (exposedcards[k] > 0)
			{
				cout << *IteratorCol7 << '\t' << '\t';
				IteratorCol7--;
				exposedcards[k] = exposedcards[k] - 1;
				repeat = true;
			}
			else
				cout << '\t' << '\t';

			cout << endl;

		}

		cout << endl << endl << endl;

	}

	bool MoveCardsFromWastePileToStockPile() //push all cards from waste pile to stock pile after stock is empty
	{
		int check = 0;

		while (WastePileSize > 0)
		{
			Stock.PushIntoStack(WastePile.PopFromStack());
			WastePileSize--;
			StockSize++;
			check++;
		}

		if (check == 0) //if no cards in wastepile then return false
			return false;

		return true;

	}

	void undo() //undo command function
	{
		char action = 0;
		char source = 0;
		char destination = 0;
		int count = 0;
		int sourceindex = 0;
		int destinationindex = 0;


		if (!CommandHistory.isEmpty())
		{
			typename DLL<Command>::Iterator undo = CommandHistory.PopFromStack();

			action = (*undo).GetAction();
			source = (*undo).GetSource();
			destination = (*undo).GetDestination();
			count = (*undo).GetNumberOfCards();
			sourceindex = (*undo).GetSourceIndex();
			destinationindex = (*undo).GetDestinationIndex();


			if (action == 's') //undo of draw
			{
				if (!WastePile.isEmpty())
				{
					typename DLL<Card>::Iterator Data = WastePile.PopFromStack();
					Stock.PushIntoStack(Data);
					WastePileSize--;
					StockSize++;
				}
				else
				{
					while (!Stock.isEmpty())
					{
						WastePile.PushIntoStack(Stock.PopFromStack());
						WastePileSize++;
						StockSize--;
					}
				}
			}
			else if (action == 'm')
			{
				if (source == 'w')
				{
					if (destination == 'c') //undo of move waste to col
					{
						UndoMoveWasteToColumn(destinationindex);
					}
					else if (destination == 'f') //undo of move waste to foundation
					{
						UndoMoveWasteToFoundation(destinationindex);
					}
				}
				else if (source == 'c')
				{
					if (destination == 'c')
					{
						UndoMoveColToCol(destinationindex, sourceindex, count); //undo of move column to column
					}
					else if (destination == 'f')
					{
						UndoMoveColumnToFoundation(destinationindex, sourceindex); //undo of move column to foundation
					}

				}

				else if (source == 'f')
				{
					if (destination == 'c')
					{
						UndoFoundationToColumn(destinationindex, sourceindex); //undo of foundation to column
					}
				}
			}

		}
	}

	bool DrawCard() //move card from stock to waste pile
	{
		if (StockSize == 0)
		{
			if (!MoveCardsFromWastePileToStockPile()) //once the cards are empty in stock pile move all the cards from wastepile to stockpile
				return false;
		}

		if (StockSize > 0) //then draw card
		{
			WastePile.PushIntoStack(Stock.PopFromStack());
			StockSize--;
			WastePileSize++;


			return true;
		}

		return false;

	}

	//Undo Commands Functions

	void UndoMoveWasteToColumn(int srcindex) //move col to waste
	{
		WastePile.PushIntoStack(Columns[srcindex].Pop());
		WastePileSize++;
		Colsize[srcindex]--;
		ExposedCardsSize[srcindex]--;
	}

	void UndoMoveWasteToFoundation(int srcindex) //move foundation to waste
	{
		WastePile.PushIntoStack(Foundation[srcindex].PopFromStack());
		WastePileSize++;
		FoundationSize[srcindex]--;
	}

	void UndoFoundationToColumn(int srcindex, int dscindex) //column to foundation
	{
		Foundation[dscindex].PushIntoStack(Columns[srcindex].Pop());
		FoundationSize[dscindex]++;
		ExposedCardsSize[srcindex]--;


		Colsize[srcindex]--;
	}

	void UndoMoveColToCol(int srcindex, int dscindex, int number) //col to col
	{

		typename DLL<Card>::Iterator IteratorColSource = Columns[srcindex].begin();
		typename DLL<Card>::Iterator IteratorColDes = Columns[dscindex].begin();

		for (int i = 1; i < number; i++)
			IteratorColSource++;

		Card CardSource = *IteratorColSource;
		Card CardDestination = *IteratorColDes;


		Stack<Card> Temp;

		for (int i = 1; i <= number; i++)
		{
			Temp.PushIntoStack(Columns[srcindex].Pop());
		}

		for (int i = 1; i <= number; i++)
		{
			Columns[dscindex].Push(Temp.PopFromStack());
		}

		if (number == 1)
		{
			Colsize[dscindex]++;
			Colsize[srcindex]--;

			if (ExposedCardsSize[dscindex] == 0)
			{

				ExposedCardsSize[srcindex]--;
				ExposedCardsSize[dscindex]++;
			}
			else
			{
				ExposedCardsSize[srcindex]--;

			}
		}

		else
		{
			Colsize[dscindex] = Colsize[dscindex] + number;
			Colsize[srcindex] = Colsize[srcindex] - number;

			if (ExposedCardsSize[dscindex] == 0)
			{
				ExposedCardsSize[dscindex] = ExposedCardsSize[dscindex] + number;
				ExposedCardsSize[dscindex] = ExposedCardsSize[dscindex] - number;

			}
			else
			{
				ExposedCardsSize[dscindex] = ExposedCardsSize[dscindex] + number - 1;
				ExposedCardsSize[srcindex] = ExposedCardsSize[srcindex] - number;
			}
		}

	}

	void UndoMoveColumnToFoundation(int srcindex, int dscindex)
	{
		Columns[dscindex].Push(Foundation[srcindex].PopFromStack());
		FoundationSize[srcindex]--;
		Colsize[dscindex]++;

		if (ExposedCardsSize[dscindex] == 0)
			ExposedCardsSize[dscindex]++;
	}

	//Commands Functions

	bool MoveWasteToColumn(int desindex)
	{
		if (WastePileSize <= 0)
			return false;


		Card WasteCard = WastePile.ReturnCardData();
		Card ColCard = Columns[desindex].ReturnCardData();

		if (Colsize[desindex] == 0) //if col is empty only king can be moved
		{
			if (!WasteCard.CheckIfKing())
				return false;
		}

		else if (!ColCard.CompareRankAndSuitForCol(WasteCard)) //check condition for col movemement

			return false;


		Columns[desindex].Push(WastePile.PopFromStack());
		Colsize[desindex]++;
		ExposedCardsSize[desindex]++;


		WastePileSize--;

		return true;
	}

	bool MoveWasteToFoundation(int desindex)
	{
		if (WastePileSize <= 0)
			return false;

		Card data = WastePile.ReturnCardData();
		Card foundationdata = Foundation[desindex].ReturnCardData();

		if (FoundationSize[desindex] == 0) //if foundation is empty only ace can be moved
		{

			if (data.CheckIfAce())
			{
				Foundation[desindex].PushIntoStack(WastePile.PopFromStack());
				FoundationSize[desindex]++;
			}
			else
				return false;
		}
		else
		{
			if (foundationdata.CompareRankAndSuitForFoundation(data)) //check condition for movemeent to foundation
			{
				Foundation[desindex].PushIntoStack(WastePile.PopFromStack());
				FoundationSize[desindex]++;
			}
			else
				return false;
		}



		WastePileSize--;


		return true;
	}

	bool MoveColumntoColumn(int srcindex, int dscindex, int number)
	{
		if (Colsize[srcindex] < number)
			return false;

		if (ExposedCardsSize[srcindex] < number)
			return false;

		typename DLL<Card>::Iterator IteratorColSource = Columns[srcindex].begin();
		typename DLL<Card>::Iterator IteratorColDes = Columns[dscindex].begin();

		for (int i = 1; i < number; i++)
			IteratorColSource++;

		Card CardSource = *IteratorColSource;
		Card CardDestination = *IteratorColDes;

		if (Colsize[dscindex] == 0) //if col is empty only king can be moved
		{
			if (!CardSource.CheckIfKing())
				return false;
		}

		else if (!CardDestination.CompareRankAndSuitForCol(CardSource)) //check conditions for movement to col
			return false;


		Stack<Card> Temp;

		for (int i = 1; i <= number; i++)
		{
			Temp.PushIntoStack(Columns[srcindex].Pop());
		}


		for (int i = 1; i <= number; i++)
		{
			Columns[dscindex].Push(Temp.PopFromStack());
		}

		Colsize[srcindex] = Colsize[srcindex] - number;
		Colsize[dscindex] = Colsize[dscindex] + number;
		ExposedCardsSize[dscindex] = ExposedCardsSize[dscindex] + number;


		ExposedCardsSize[srcindex] = ExposedCardsSize[srcindex] - number;
		if (ExposedCardsSize[srcindex] == 0 && Colsize[srcindex] != 0)
			ExposedCardsSize[srcindex] = 1;

		return true;
	}

	bool MoveFoundationToColumn(int srcindex, int dscindex)
	{
		if (FoundationSize[srcindex] <= 0)
			return false;


		Card Foundationcard = Foundation[srcindex].ReturnCardData();
		Card ColCard = Columns[dscindex].ReturnCardData();

		if (Colsize[dscindex] == 0) //if col is empty ony king can be moved
		{
			if (!Foundationcard.CheckIfKing())
				return false;
		}

		else if (!ColCard.CompareRankAndSuitForCol(Foundationcard)) //check conditions for movemenet to col
			return false;


		Columns[dscindex].Push(Foundation[srcindex].PopFromStack());
		FoundationSize[srcindex]--;
		Colsize[dscindex]++;
		ExposedCardsSize[dscindex]++;

		return true;
	}

	bool MoveColumnToFoundation(int srcindex, int dscindex)
	{
		if ((Colsize[srcindex]) <= 0)
			return false;

		Card data = Columns[srcindex].ReturnCardData();
		Card foundationdata = Foundation[dscindex].ReturnCardData();

		if (FoundationSize[dscindex] == 0) //if initially foundation is empty
		{
			if (data.CheckIfAce()) //if foundation is empty only ace can be moved
			{
				Foundation[dscindex].PushIntoStack(Columns[srcindex].Pop());
				Colsize[srcindex]--;
				ExposedCardsSize[srcindex]--;
				FoundationSize[dscindex]++;
			}
			else
				return false;
		}
		else
		{
			if (foundationdata.CompareRankAndSuitForFoundation(data)) //check conditions for movement to foundation
			{
				Foundation[dscindex].PushIntoStack(Columns[srcindex].Pop());
				Colsize[srcindex]--;
				ExposedCardsSize[srcindex]--;
				FoundationSize[dscindex]++;
			}
			else
				return false;
		}

		return true;

	}

	bool ProcessCommand(char* ptr)
	{
		Command Process(ptr);

		bool Valid = Process.ParseCommand();
		if (Valid == false)
			return false;

		if (Valid)
		{
			if (Process.GetAction() == 's')
			{
				if (DrawCard())
				{
					CommandHistory.push(Process);
					numberofcommands++;

					return true;
				}
				else
					return false;

			}
			else if (Process.GetAction() == 'm')
			{
				if (Process.GetSource() == 'w')
				{
					if (Process.GetDestination() == 'c')
					{

						if (MoveWasteToColumn(Process.GetDestinationIndex()))
						{
							CommandHistory.push(Process);
							numberofcommands++;  //if the command is carried out , store it in command list
							return true;
						}
						else
						{
							return false;
						}
					}
					else if (Process.GetDestination() == 'f')
					{
						if (MoveWasteToFoundation(Process.GetDestinationIndex()))
						{
							CommandHistory.push(Process);
							numberofcommands++;
							return true;
						}
						else
							return false;
					}
					else
						return false;
				}
				else if (Process.GetSource() == 'c')
				{
					if (Process.GetDestination() == 'c')
					{
						if (MoveColumntoColumn(Process.GetSourceIndex(), Process.GetDestinationIndex(), Process.GetNumberOfCards()))
						{

							if (ExposedCardsSize[Process.GetSourceIndex()] == 0 && Colsize[Process.GetSourceIndex()] > 0) //chances for source col to have flipped card
							{
								ExposedCardsSize[Process.GetSourceIndex()]++;
							}

							CommandHistory.push(Process);
							numberofcommands++;
							return true;
						}
						else
							return false;
					}
					else if (Process.GetDestination() == 'f')
					{
						if (MoveColumnToFoundation(Process.GetSourceIndex(), Process.GetDestinationIndex()))
						{
							if (ExposedCardsSize[Process.GetSourceIndex()] == 0 && Colsize[Process.GetSourceIndex()] > 0) //chances for source col to have flipped cards
							{
								ExposedCardsSize[Process.GetSourceIndex()]++;

							}

							CommandHistory.push(Process);
							numberofcommands++;
							return true;
						}
						else
							return false;
					}
					else
						return false;

				}

				else if (Process.GetSource() == 'f')
				{
					if (MoveFoundationToColumn(Process.GetSourceIndex(), Process.GetDestinationIndex()))
					{
						CommandHistory.push(Process);
						numberofcommands++;
						return true;
					}
					else
						return false;
				}
				else
					return false; //return false if source is neither f nor w nor c
			}

			else if (Process.GetAction() == 'z')
			{
				undo();

			}
		}

		return true;
	}

	bool CheckWinCondition() //all foundations size should be 13 for game to be won
	{
		if (FoundationSize[0] == 13 && FoundationSize[1] == 13 && FoundationSize[2] == 13 && FoundationSize[3] == 13)
			return true;
		else
			return false;
	}

	void Input()
	{
		bool Continue = true;
		char command[100];

		while (Continue == true)
		{

			cout << "Enter Move:";
			cin.getline(command, 100);



			if (StringCompare(command, "quit"))
			{
				Continue = false;
				cout << "Game is Over" << endl;
			}

			else if (CheckWinCondition())
			{
				Continue = false;
				cout << "Congrats! You have won the game" << endl;
			}

			if (Continue == true)
			{

				if (ProcessCommand(command) == false)
					cout << "Invalid Command.Enter Move again" << endl << endl;


				PrintGameInterface();
				cout << endl;
			}


		}

		cout << endl;
	}

	Game()
	{
		Foundation = new Stack<Card>[4]; //4 foundation piles
		Columns = new DLL<Card>[7]; //7 columns
		StockSize = 0;
		WastePileSize = 0;
		numberofcommands = 0;
		FoundationSize = new int[4];

		for (int i = 0; i < 4; i++)
		{
			FoundationSize[i] = 0;
		}

		Colsize = new int[7];

		ExposedCardsSize = new int[7];
		InitializeCards();
		ShuffleCards();
		DistributeCards();
		PrintGameInterface();
	}

	~Game()
	{
		if (Foundation)
		{
			delete Foundation;
		}
		if (Columns)
		{
			delete Columns;
		}

		if (Colsize)
			delete[]Colsize;

		if (ExposedCardsSize)
			delete[]ExposedCardsSize;

		if (FoundationSize)
			delete[]FoundationSize;

	}
};

void main()
{
	SetConsoleOutputCP(CP_UTF8);
	Game myGame;
	myGame.Input();


}