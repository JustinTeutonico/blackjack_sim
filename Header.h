//HEADER.H

#include <iostream>
#include <time.h>
#include <string>
using namespace std;
void c(string b){ cout << b << endl; }
void p(){ system("pause"); }
void line(){ c("---------"); }
void cls(){ system("cls"); }
struct Card{
	string type; int value; 
	Card(){ type = "Hearts"; value = 2; }
	Card(string a, int b){ type = a; value = b; }
	void print(){
		if (value == 11)
			cout << "Jack of ";
		else if (value == 12)
			cout << "Queen of ";
		else if (value == 13)
			cout << "King of ";
		else if (value == 14)
			cout << "Ace of ";
		else
			cout << value << " of ";
		cout << type << " ";
	}
};
struct Hand{
	int handsize=0;
	int hits=0;
	Card cards[11];//the highest amount of cards you could hypothetically have is 11; all aces (sum is 4), all 2's (sum is 12), three 3's (sum is 21)
	Hand(){ handsize = 0; }
	void addcard(Card add){ cards[handsize++] = add;/*handsize += 1;*/ }
	void show(){
		line();
		c("Your hand is as follows:");
		line();
		for (int i = 0; i < handsize; i++){
			cards[i].print(); cout << endl;
		}
		line();
		cout << "You have hit " << hits << " times.\n";
		cout << "Your total is " << value() << endl;
	}
	void print(){
		for (int i = 0; i < handsize; i++){
			cards[i].print(); cout << endl;
		}
	}
	int value(){
		int total = 0;	
		int num_aces = 0;
		for (int i = 0; i < handsize; i++){
			if (cards[i].value > 9 && cards[i].value < 14)
				total += 10;
			else if (cards[i].value == 14){
				num_aces++;
			}
			else
				total += cards[i].value;
		}
		if (num_aces > 0){
			while (num_aces > 0){
				if (total + 11 < 22)
					total += 11;
				else 
					total += 1;
				num_aces--;
			}
		}
		return total;
	}	
};
void makedeck(Card b[]){
	string types[4] = { "Hearts", "Diamonds", "Spades", "Clubs" };
	int typenum = 0;
	int j = 2;
	for (int k = 0; k < 52; k++){
		b[k].type = types[typenum];
		b[k].value = j++;
		if (j > 14){
			j = 2;
			typenum++;
		}
	}

}
void shuffle(Card b[]){
	for (int i = 0; i < 52; i++){
		int j = rand() % 52;
		swap(b[i].type, b[j].type);
		swap(b[i].value, b[j].value);
	}
}

