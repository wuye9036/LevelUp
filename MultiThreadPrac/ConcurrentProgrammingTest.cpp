// ConcurrentProgrammingTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <boost/thread.hpp>
#include <iostream>
#include <time.h>
using namespace boost;

int CONCURRENT_NUM = 5;//并发数量
int BUFFER_SIZE = 10;//缓冲大小
int INPUT_DATA_NUM = 100;//测试数据的数量
int sleep_time = 200; //设置测试程序的休眠时间长度

mutex mtx;
condition cond;

volatile int get_pos = 0;  //当前读取位置
volatile int put_pos = 0;  //当前输出位置
volatile int blank_num = BUFFER_SIZE; //缓冲的可用区域的大小
volatile int updated_pos = -1;  //已经更新的位置
volatile int updating_pos = 0; //正在更新的位置
double total_updating_time = 0.0;

int buffer[1024]; //

//单线程
void get()
{
	for(int i = 0; i < INPUT_DATA_NUM; ++i)
	{
		{
			mutex::scoped_lock lock(mtx);
			while(blank_num == 0){
				cond.wait(lock);
			}
		}

		//读取值,此步在随机读取的情况下可以实现并发
		buffer[get_pos % BUFFER_SIZE] = get_pos;

		{
			mutex::scoped_lock lock(mtx);
			++get_pos;
			--blank_num;
		}

		cond.notify_all();
	}

	//退出前，将get_pos至于最大的序号的后一位，这样可以让后面的标示找到正确的结尾。
	{
			mutex::scoped_lock lock(mtx);
			get_pos = INPUT_DATA_NUM;
	}
}

//单线程
void put()
{
	int put_start;

	while(1){
		{
			mutex::scoped_lock lock(mtx);

			put_start = put_pos % BUFFER_SIZE;
			while(put_pos > updated_pos){
				if(put_pos >= INPUT_DATA_NUM)
				{
					//std::cout << "Thread 'put' Terminated seccessful!" << std::endl; 
					cond.notify_all();
					return;
				}
				cond.wait(lock);
			}
		}

		//读取值,此步在随机读取的情况下可以实现并发
		//std::cout << buffer[put_start] << " ";

		{
			mutex::scoped_lock lock(mtx);
			++put_pos;
			++blank_num;
			//std::cout << blank_num << " " << put_pos << " " << updated_pos << std::endl;
		}

		cond.notify_all();
	}
}

//并发的模型
void update()
{
	int current_updating_pos;
	while(1) {
		//第一次阻塞，读阻塞
		{
			mutex::scoped_lock lock(mtx);

			//判断是否有数据可供更新
			while(updating_pos >= get_pos){
				if(updating_pos >= INPUT_DATA_NUM){
					//std::cout << "Thread 'update' Terminated seccessful!" << std::endl; 
					cond.notify_all();
					return;
				}
				cond.wait(lock);
			}
			current_updating_pos = updating_pos++;
		}

		clock_t start = clock();
		//更新
		Sleep(sleep_time);
		buffer[current_updating_pos % BUFFER_SIZE] *= 2;
		clock_t end = clock();
		//第二次阻塞，写阻塞，保证顺序的写到缓冲中
		{
			mutex::scoped_lock lock(mtx);
			total_updating_time += double(end - start)/double(CLOCKS_PER_SEC);
			while(current_updating_pos > updated_pos + 1){
				cond.wait(lock);
			}
			++updated_pos;
			//std::cout << current_updating_pos << " " << updated_pos << std::endl;
		}

		cond.notify_all();
	}
}

void InitData()
{
	get_pos = 0;
	put_pos = 0;
	blank_num = BUFFER_SIZE;
	updated_pos = -1;
	updating_pos = 0;
	total_updating_time = 0.0;
}

int _tmain(int argc, _TCHAR* argv[])
{	
	double st_eval_time, mt_eval_time, test_time;
	FILE* f = fopen("data.txt", "a");
	while(1){
		//接受数据
		std::cout << "请依次输入并发数、测试数据数量、单次更新耗时、缓冲大小：" << std::endl;
		std::cin >> CONCURRENT_NUM >> INPUT_DATA_NUM >> sleep_time >> BUFFER_SIZE;
		
		if(CONCURRENT_NUM == 0){ break; }

		InitData();
		HANDLE hProc = GetCurrentProcess();
		SetPriorityClass(hProc, REALTIME_PRIORITY_CLASS);
		clock_t start, end;

		//测试开始-------------------------------------
		start = clock();

		thread_group tg;
		tg.create_thread(&get);
		for(int i = 0; i < CONCURRENT_NUM; ++i){
			tg.create_thread(&update);
		}
		tg.create_thread(&put);
		tg.join_all();

		end = clock();
		//测试结束-------------------------------------

		//输出结果
		test_time = double (end - start) / double(CLOCKS_PER_SEC);
		st_eval_time = double(INPUT_DATA_NUM * sleep_time / 1000.0);
		mt_eval_time = double(INPUT_DATA_NUM * sleep_time) / double(CONCURRENT_NUM) / 1000.0;
		std::cout << "测试耗时 " << test_time << "s"<< std::endl;
		std::cout << "单线程预计时间： " << st_eval_time << "s" << std::endl;
		std::cout << "并发估算时间： " << mt_eval_time << "s" << std::endl;
		std::cout << "更新部分占用时间和：" << total_updating_time << "s" << std::endl;

		fprintf(f, "%d    %d    %d    %d    %.3f    %.3f    %.3f    %.3f\n",  CONCURRENT_NUM, INPUT_DATA_NUM, sleep_time, BUFFER_SIZE, test_time, st_eval_time, mt_eval_time, total_updating_time);
;
		SetPriorityClass(hProc, NORMAL_PRIORITY_CLASS);
	}
	fclose(f);
	system("pause");
	return 0;
}

