#ifndef THREAD_H_
#define THREAD_H_

class Thread {
public:

	Thread();
	virtual ~Thread();

    int turn[10] = {0};

	void lock(int id);
	void unlock(int id);
	bool comp(int a1, int a2, int b1, int b2);

};

#endif /* CARRO_H_ */
