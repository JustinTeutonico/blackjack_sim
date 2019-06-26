#include <iostream>
#include <string>
#include <queue>
#include <chrono>
#include <thread>
#include"Header.h"

using namespace std;

void menu(Card b[], bool shuf);
void wait(){
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds

	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(1));
}
void blackjack(Card b[], int ai){
	Hand h, e;//create h for player hand and e for enemy hand
	cls();

	queue<Card> q; //make queue
	for (int i = 0; i < 52; i++)
		q.push(b[i]);//enters whole deck in queue

	if (!ai){//if no computer (practice) 
		h.cards[0] = q.front();//add card
		q.pop();//remove inserted card from queue to force next card to front
		h.handsize += 1;
		h.addcard(q.front());
		q.pop();
	}
	else{//deal to player first card, enemy second, player third, enemy fourth
		h.cards[0] = q.front();
		q.pop();
		h.handsize += 1;
		
		e.cards[0] = q.front();
		q.pop();
		e.handsize += 1;

		h.addcard(q.front());
		q.pop();

		e.addcard(q.front());
		q.pop();
	}
	string ans = "0";
	bool playerdone = false; 
	bool enemydone = false; 
	if (!ai)
		enemydone = true;
	while (playerdone == false || enemydone == false){
		//this is the main loop for the program. will keep going as long as either player is not done hitting
		//
		cls();

		h.show();
		line();
		if (ai){//shows one card from opponent and how many cards they have total, like in real blackjack
			cout << "Your opponent has a ";
			e.cards[0].print();
			cout << ", and " << e.handsize << " cards total.\n";
			line();
		}
		if (h.value() > 21 || e.value() > 21){//busted, cannot do anymore
			playerdone = true; enemydone = true;
			if (h.value() > 21)
				c("You busted!");
			else
				c("Your opponent busted!");
			p();
		}
		else if(!playerdone){
			c("You may...");
			c("[1] Hit");
			c("[2] Stay");
			cin >> ans;
			if (ans == "1"){//add card
				cout << "You got a ";
				q.front().print();
				cout << "added to your hand.\n";
				h.addcard(q.front());
				q.pop();
				h.hits++;
				if (h.value() > 21){
					c("You busted!");
					enemydone = true; playerdone = true;
				}
				wait();
			}
			else if (ans == "2"){
				cout << "Your total: " << h.value() << ".\n\n";
				if (h.value() < 13)
					c("Played it pretty safe, huh?");
				else if (h.value() < 17)
					c("Nicely done.");
				else if (h.value() < 21)
					c("Very nicely done!");
				else if (h.value() == 21)
					c("BLACKJACK!");
				else
					c("Error.");
				playerdone = true;
			}
		}

		if (ai == 1 && enemydone == false){//easy ai - is more likely to take risks
			c("Opponent is thinking...");
			wait();
			if (e.value() >= 17){
				enemydone = true;
				c("Your opponent doesn't draw a card and will stay.");
				wait(); wait();
			}
			else if (e.value() < 17){
				e.addcard(q.front());
				q.pop();
				c("Your opponent draws a card.");
				wait(); wait();
			}
		}
		else if(ai==2 && enemydone==false){//hard AI is more conservative
			c("Opponent is thinking...");
			wait();
			if (e.value() >= 15){
				enemydone = true;
				c("Your opponent doesn't draw a card and will stay.");
				wait(); wait();
				}
			else if (e.value() < 15){
				e.addcard(q.front());
				q.pop();
				c("Your opponent draws a card.");
				wait(); wait();
				}
			}
			
		}
	cls();
	h.show();
	line();
	if (ai){
		if (h.value() > 21 && e.value() <= 21){//player busted and enemy wins on default
			c("You busted! Your opponent wins!");
		}
		else if (h.value() <= 21 && e.value() > 21){//enemy busted and enemy wins on default
			c("Your opponent busted! You win.");
		}
		else if (e.value() <= 21 && h.value() <= 21){//no one busted
			if (e.handsize == h.handsize && e.value() > h.value()){//same hand size but ai had higher value
				c("Your opponent wins.");
			}
			else if (e.handsize == h.handsize && e.value() < h.value()){//same hand size but you had higher value
				c("You win.");
			}
			else if (e.value() == h.value() && e.handsize > h.handsize){//same value but you had less cards
				c("You won (hand size was smaller)");
			}
			else if (e.value() == h.value() && e.handsize < h.handsize){//same value but you had more cards
				c("Opponent won (hand size was smaller)");
			}
			else if (e.value() > h.value()){
				c("Your opponent wins.");
			}
			else if (h.value() > e.value()){
				c("You win!");
			}
			else{
				c("A tie. A truly legendary moment.");
			}
		}
		
	}
	line();
	c("GAME OVER");
	line();
	if (ai){
		c("Opponents hand:\n");
		e.print();
		cout << "= " << e.value() << endl;
		line();
	}
	p();
	cls();
	makedeck(b);
	menu(b, true);//remake and randomize deck, go back to menu
		
}
void queue_test(Card b[]){
	cls();
	queue<Card> q;
	for (int i = 0; i < 52; i++)
		q.push(b[i]);
	while (!q.empty()){
		q.front().print(); cout << endl;
		q.pop();
	}
}
void menu(Card b[], bool shuf){
	if(shuf)//reshuffle deck
		shuffle(b);
	bool reshuffle = false;
	c("You may: ");
	c("[1] Play Blackjack");
	c("[2] Shuffle the deck.");
	c("[3] See the current layout of the deck.");
	c("[0] EXIT PROGRAM");
	string a; cin >> a;
	if (a == "1"){
		line();
		c("Choose an option for blackjack:");
		line();
		c("[1] Practice (vs self)");
		c("[2] Versus Easy AI");
		c("[3] Versus Hard AI");
		a = "a";
		while (a != "1" && a != "2" && a != "3")
			cin >> a;
		int ans = atoi(a.c_str());//convert string to int
		ans -= 1;
		blackjack(b,ans);
		
	}
	else if (a == "2")
		shuffle(b);
	else if (a == "3"){
		queue_test(b);
		p();
		c("Resuffle deck?\n[1] YES\n[2] NO");
		a = "a";
		while (a != "1" && a != "2")
			cin >> a;
		int ans = atoi(a.c_str());//convert string to int
		if (a == "1")
			reshuffle = true;
	}
	else if (a == "0")
		exit(1);

	p(); cls();
	menu(b, reshuffle);
}

int main(){
	srand(time(NULL));//seed randomness based on system clock
	
	Card b[52];//52 card deck
	makedeck(b);
	cout << "Welcome to the Blackjack program.\nIt has generated and shuffled a 52 card deck." << endl;
	p(); cls();
	menu(b, true);
	return 0;
}