package main

import (
	"fmt"
	"time"
)

// ref: https://juejin.cn/post/6943524790636544036

func asyncTask() {
	fmt.Println("This is an asynchronized task")
}

func syncTask() {
	fmt.Println("This is a synchronized task")
}

func deaploop() {
	for {

	}
}

func Test() {
	// 对于一个死循环，如果不采用
	// go deaploop()
	go asyncTask()
	// time.Sleep(time.Second * 1)
	syncTask()
	go asyncTask()
	time.Sleep(time.Second * 1)
}

func longTask(signal chan int) {

	fmt.Println("longTask is running")
	for {
		v := <-signal
		fmt.Printf("I have receive %d\n", v)

		// go longTask2(signal)
		if v == 1 {
			break
		}

		time.Sleep(1 * time.Second)
	}

	fmt.Println("longTask is finished")
}

func longTask2(signal chan int) {

	fmt.Println("longTask2 is running")
	for {
		v := <-signal
		fmt.Printf("He have receive %d\n", v)

		if v == 1 {
			break
		}

		time.Sleep(1 * time.Second)
	}

	fmt.Println("longTask2 is finished")
}

func ChannelTest() {
	// 声明通道
	sig := make(chan int)
	go longTask(sig)
	go longTask2(sig)

	time.Sleep(1 * time.Second)
	fmt.Println("After 1 seconds")

	for i := 5; i > 0; i-- {
		sig <- i
	}

	time.Sleep(1 * time.Second)
}
