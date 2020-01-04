#ifndef TRICK_H
#define TRICK_H

void init_trickhelper(TrickHelper *trickhelper);
void print_trickhelper(TrickHelper *trickhelper);
void set_trickhelper(TrickHelper *trickhelper, Card cards[], int n);
void set_doubles_ph(TrickHelper *trickhelper, int value, int count);
void set_doubles_r(TrickHelper *trickhelper, int value, int count);
void set_triples_ph(TrickHelper *trickhelper, int value, int count);
void set_triples_r(TrickHelper *trickhelper, int value, int count);

void init_trick(Trick *trick);
void print_trick(Trick *trick);
void set_trick(Trick *trick, int type, int length, int num_cards, int high,
	int low, int has_phoenix, Card *cards);
void copy_trick(Trick *dest, Trick *src);

void init_trickset(TrickSet *trickset);
void print_trickset(TrickSet *trickset);
void add_trick(TrickSet *trickset, Trick *trick);

void make_singles(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_single(TrickSet *trickset, Card card);

void make_doubles(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_double(TrickSet *trickset, Card cards[]);

void make_triples(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_triple(TrickSet *trickset, Card cards[]);

void make_quads(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_quad(TrickSet *trickset, Card cards[]);

void make_straights(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_straights(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper);
void add_straights_ph(TrickSet *trickset, int low, int length, int val,
	TrickHelper *trickhelper);
void add_straights_r(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper);
int sum_straight(int low, int length, TrickHelper *trickhelper, int *val);
void inc_counters(int *counters, int length, int *limits);

void make_dstraights(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_dstraights(TrickSet *trickset, int low, int length,
	TrickHelper *trickhelper);
int sum_dstraight(int low, int length, TrickHelper *trickhelper);

void make_fulls(TrickSet *trickset, Trick *top, Card cards[], int n);
void add_fulls(TrickSet *trickset, int trip, int doub,
	TrickHelper *trickhelper);

#endif // TRICK_H
