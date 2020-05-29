#include <windows.h>
#include <conio.h>
#include <random>
#include <time.h>
#include <iostream>
using namespace std;
#define N 10 //  кол-во сообщений в 1 пакете дл€ передаче
class message
{
public:
	message();
	~message();
	bool isEmpty() { return this->empty; };
	void send(int *Mssg_pack);
	int* extract() { return  this->m; };
private:
	int m[N];
	bool empty;
	
};

message::message()
{
	this->empty = true;
	for (size_t i = 0; i < N; i++)
	{
		this->m[i] = -1;
	}
}

message::~message()
{

}
void message::send(int *Mssg_pack)
{
	for (size_t i = 0; i < N; i++)
	{
		this->m[i] = Mssg_pack[i];
	}
	this->empty = !this->empty;
}
#define N 10
void producer(message &m)
{
	srand(time(NULL));
	int Message_pack[N];
	while (1)
	{

		if (m.isEmpty()) // провер€ем наличие пустого сообщени€ 
		{
			cout << "ѕроизводитель: получил пустые сообщение начинаю подготовку " << endl << "ѕроизводитель: ";
			for (size_t i = 0; i < N; i++) // подготавливаем данные дл€ отправки 
			{	
				 Message_pack[i] = rand() % 10;
				 cout << Message_pack[i];
				 
				 Sleep((rand() % 5 + 1) * 100);
			}
			m.send(Message_pack);
		}
		else
		{
			
		}
	}
}
void consumer(message &m)
{
	int* Extract_data;
	while (1)
	{
		if (!m.isEmpty()) // провер€ем наличие сообщени€ 
		{
			cout << endl << "ѕолучатель: ќбрабатываю полученное ->";
			Extract_data = m.extract(); // обрабатываем полученное
			for (size_t i = 0; i < N; i++)
			{
				cout << Extract_data[i];
				Extract_data[i] = -1;
				Sleep((rand()%10+1)*100);
				
			}
			cout << endl << "ѕолучатель: ¬озвращаю пустые сообщение" << endl;
			m.send(m.extract()); // возвращаем пустое 
			
		}
		else
		{	
			
		}
	}
}
int main()
{
	message m; //буфер сообщений 
	system("chcp 1251");
	system("cls");

	HANDLE ThreadConsumer;
	DWORD dwThreadConsumer;

	HANDLE ThreadProducer;
	DWORD dwThreadProducer;
	

	ThreadProducer = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer, &m, 0, &dwThreadProducer);
	ThreadConsumer = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, &m, 0, &dwThreadConsumer);
	
	
	WaitForSingleObject(ThreadConsumer, 0xFFFFFFFF);

	WaitForSingleObject(ThreadProducer, 0xFFFFFFFF);
	_getch();
}