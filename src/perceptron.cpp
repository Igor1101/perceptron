//============================================================================
// Name        : perceptron.cpp
// Author      : Igor
// Version     :
// Copyright   : Copyright (c) Igor Muravyov
// Description : C++, Ansi-style
//============================================================================

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <cstdbool>
using namespace std;

class Perceptron {
private:
	float w1;
	float w2;
	float speed;
	// trigger threshold
	float trig;
public:
	float f(int x1, int x2)
	{
		return (w1*x1+w2*x2);
	}
	Perceptron(float trig, float speed) {
		w1 = 0;
		w2 = 0;
		this->trig = trig;
		this->speed = speed;
	}
	bool result(float x1, float x2) {
		return (f(x1, x2) > trig);
	}
	void print_w() {
		printf("w1=%f, w2=%f\n", w1, w2);
	}
	void learn(float x1, float x2, float res) {
		if((res > trig && result(x1, x2) > trig) &&
			(res <= trig && result(x1, x2) <= trig)
				) {
			return;
		} else {
			float delta = trig - f(x1,x2);
			w1 += speed * delta * x1;
			w2 += speed * delta * x2;
		}
	}
};
struct point_t {
	float x;
	float y;
};
int main() {
	point_t A = {
			.x=0,
			.y=6
	};
	point_t B= {
			.x=1,
			.y=5
	};
	point_t C= {
			.x=3,
			.y=3
	};
	point_t D = {
			.x=2,
			.y=4
	};
	const double speeds[] =  {0.001, 0.01, 0.05, 0.1, 0.2, 0.3};
	printf("for different speeds:\n");
	for(int i=0; i< sizeof speeds / sizeof speeds[0]; i++) {
		Perceptron p = Perceptron(4, speeds[i]);
		clock_t start_p = clock();
		for(int i=0; i<100 ; i++) {
			p.learn(A.x, A.y, 5);
			p.learn(B.x, B.y, 5);
			p.learn(C.x, C.y, 5);
			p.learn(D.x, D.y, 5);
		}
		clock_t end_p = clock();
		double clk_p = (double)(end_p - start_p) / CLOCKS_PER_SEC;
		printf("p1, 100 times speed=%f, timespent=%f\n", speeds[i], clk_p);
		p.print_w();
	}
	printf("for different amount of iterations:\n");
	const int it[] = { 100, 200, 500, 1000};
	for(int i=0; i< sizeof it/ sizeof it[0]; i++) {
		Perceptron p = Perceptron(4, 0.001);
		clock_t start_p = clock();
		for(int i=0; i<it[i]; i++) {
			p.learn(A.x, A.y, 5);
			p.learn(B.x, B.y, 5);
			p.learn(C.x, C.y, 5);
			p.learn(D.x, D.y, 5);
		}
		clock_t end_p = clock();
		double clk_p = (double)(end_p - start_p) / CLOCKS_PER_SEC;
		printf("p1, %d times speed=%f, timespent=%f\n", it[i],0.001, clk_p);
		p.print_w();
	}

	return 0;
}
