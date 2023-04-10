import asyncio
import aioconsole


async def say_hi(message):
    await asyncio.sleep(1)
    print(message)


async def loop_say_hi(message, interval, event):
    while not event.is_set():
        await say_hi(message)
        await asyncio.sleep(interval)


async def test():
    stop_event = asyncio.Event()
    task1 = asyncio.create_task(say_hi("hello"))
    task2 = asyncio.create_task(aioconsole.ainput('Is this your line? '))
    task3 = asyncio.create_task(loop_say_hi("world", 2, stop_event))

    # Run task1 and task3 concurrently, and run task2 separately
    done, _ = await asyncio.wait([task1, task2])

    # Stop the loop_say_hi task and get the user's response
    stop_event.set()
    response = await task2

    print("response was", response)

while True :
    asyncio.run(test())
