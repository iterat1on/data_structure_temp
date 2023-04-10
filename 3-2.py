import time
import asyncio

MAX_QSIZE = 8


class Queue:
    def __init__(self):
        self.front = 0
        self.rear = 0
        self.items = [None] * MAX_QSIZE

    def isEmpty(self):
        return self.front == self.rear

    def isFull(self):
        return self.front == (self.rear + 1) % MAX_QSIZE

    def clear(self):
        self.front = self.rear

    def enqueue(self, item):
        if not self.isFull():
            self.rear = (self.rear + 1) % MAX_QSIZE
            self.items[self.rear] = item

    def dequeue(self):
        if not self.isEmpty():
            self.front = (self.front + 1) % MAX_QSIZE
            return self.items[self.front]

    def peek(self):
        if not self.isEmpty():
            return self.items[(self.front + 1) % MAX_QSIZE]

    def display(self):
        out = []
        if self.front < self.rear:
            out = self.items[self.front + 1:self.rear + 1]
        else:
            out = self.items[self.front + 1:MAX_QSIZE] + self.items[0:self.rear + 1]
        print("[f=%s, r=%d] ->" % (self.front, self.rear), out)


que = Queue()
sec = 1


async def DeQue(Q):
    while True:
        if not Q.isEmpty():
            print(f"[{sec}]", end="")
            Q.dequeue()
            sec += 1
        await asyncio.sleep(1)


async def user_input():
    text = await asyncio.get_running_loop().run_in_executor(None, input, "입력값 ")
    return text


async def main():
    dq_task = asyncio.create_task(DeQue(que))
    text = user_input()
    dq_task.cancel()  # stop the DeQue task
    print(text)
    que.display()


loop = asyncio.get_event_loop()
loop.run_until_complete(main())
