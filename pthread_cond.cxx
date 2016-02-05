/*
 * pthread_cond.cxx
 * 
 * Copyright 2016 olegartys <olegartys@olegartys-HP-Pavilion-15-Notebook-PC>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>

#include <unistd.h>
#include <pthread.h>

using std::cout;

pthread_cond_t thr_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t bp;

void* f(void*) {
	pthread_cond_wait(&thr_cond, &mutex);
	cout << "1 is free!\n";
	return NULL;
}

void* f1(void*) {
	sleep(5);
	pthread_barrier_wait(&bp);
	cout << "2 is free!\n";
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_barrier_init(&bp, NULL, 1);
	
	pthread_t t, t1;
	pthread_create(&t, NULL, f, NULL);
	pthread_create(&t1, NULL, f1, NULL);
	
	sleep(5);
	pthread_cond_signal(&thr_cond);
	
	//pthread_cond_wait(&thr_cond, &mutex);
	
	cout << "Now main is free!\n";
		
	return 0;
}

