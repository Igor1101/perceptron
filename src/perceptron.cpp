//============================================================================
// Name        : perceptron.cpp
// Author      : Igor
// Version     :
// Copyright   : Copyright (c) Igor Muravyov
// Description : Hello World in C++, Ansi-style
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
	const float speed = 0.1;
	// trigger threshold
	float trig;
public:
	float f(int x1, int x2)
	{
		return (w1*x1+w2*x2);
	}
	Perceptron(float trig) {
		w1 = 0;
		w2 = 0;
		this->trig = trig;
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
	Perceptron p = Perceptron(4);
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
	for(int i=0; i<100 ; i++) {
		p.learn(A.x, A.y, 5);
		p.learn(B.x, B.y, 5);
		p.learn(C.x, C.y, 5);
		p.learn(D.x, D.y, 5);
		p.print_w();
	}
	return 0;
}
