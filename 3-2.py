import time
import asyncio
import aioconsole
from collections import deque


max_size = 21


class Queue:
    def __init__(self, max_size):
        self.max_size = max_size
        self.queue = [None] * max_size
        self.front = -1
        self.rear = -1

    def is_empty(self):
        return self.front == -1

    def is_full(self):

        return max_size - 2 == self.rear

    def enqueue(self, data):
        if self.is_full():
            pass
        else :
            if self.is_empty():
                self.front = 0

            self.rear = (self.rear + 1) % self.max_size
            self.queue[self.rear] = data
            return  data

    def dequeue(self):
        if self.is_empty():
            raise Exception("Queue is empty")

        data = self.queue[self.front]

        if self.front == self.rear:
            self.front = -1
            self.rear = -1
        else:
            self.front = (self.front + 1) % self.max_size

        return data

    def display(self):

        if self.rear >= self.front:
            queue_range = range(self.front, self.rear+1)
        else:
            queue_range = range(self.front, self.max_size) + range(0, self.rear+1)
        for i in queue_range:
            print(self.queue[i], end=" ")

        print(f"[F={self.front}, R={self.rear}] ", end=" ")

        print()


que = Queue(max_size)
start_time = time.time()
sec = time.time()


async def EnQue(Q, start_time):
    while True:
        item = await aioconsole.ainput('')
        for i in range(len(item)):
            now_time = time.time()
            time_diff = int(now_time - start_time)
            print(f"[{time_diff}]", end="")
            print(f"ADDQUEUE() = {Q.enqueue(item[i])} : ", end="")
            Q.display()

        return Q


async def DeQue(Q, start_time):
    while True:
        while not Q.is_empty():
            now_time = time.time()
            time_diff = int(now_time - start_time)
            print(f"[{time_diff}]", end="")
            print(f"DEQUEUE() = {Q.dequeue()} : ", end="")
            Q.display()
            time.sleep(1)
        await asyncio.sleep(1)
        return Q


async def display_que(Q) :
    Q.display()

async def test():
    while True:
        now_time = time.time()
        time_diff = int(now_time - start_time)
        print(f"[{time_diff}]", end="")
        stop_event = asyncio.Event()

        await display_que(que)
        task1 = asyncio.create_task(DeQue(que, start_time))
        task2 = asyncio.create_task(EnQue(que, start_time))


        done, _ = await asyncio.wait({task2}, timeout=1.0)


        if task2 in done:
            response = await task2
        else:
            task2.cancel()
            response = None


        stop_event.set()




while True :
    asyncio.run(test())
