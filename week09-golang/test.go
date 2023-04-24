package main

import (
	"fmt"
	"net"
	"time"
)

// TCP连接的处理函数
func handler(c net.Conn) {
	c.Write([]byte("ok"))
	c.Close()
}

func Test1() {
	l, err := net.Listen("tcp", ":8000")
	if err != nil {
		panic(err)
	}

	for {
		c, err := l.Accept()
		if err != nil {
			panic(err)
		}

		go handler(c)
	}
}

func tick(d time.Duration) <-chan int {
	var c chan int
	go func() {
		time.Sleep(d)
		c <- 1
	}()
	return c
}

func Test2() {
	for i := 0; i < 24; i++ {
		// 从tick函数中接收管道
		c := tick(1 * time.Second)
		// 并将管道的值 取出来交给result
		result := <-c
		fmt.Println(i, " : ", result)
	}
}

// ping-pong
type Ball struct {
	hits int
}

func player(name string, table chan *Ball) {
	for {
		ball := <-table
		ball.hits++
		fmt.Println(name, ball.hits)
		time.Sleep(1 * time.Second)
		table <- ball
	}
}

func Test3() {
	table := make(chan *Ball)
	go player("ping", table)
	go player("pong", table)
	go player("ping2", table)
	table <- new(Ball)
	time.Sleep(10 * time.Second)
	close(table)
}

func handler_int(name string, number chan int) {
	for {
		cur := <-number
		fmt.Println(name, cur)
		cur++
		// 写不进去就阻塞住了
		for i := 0; i < 2; i++ {
			time.Sleep(1 * time.Second)
			number <- cur
			cur++
		}
	}
}

func Test4() {
	ch := make(chan int)
	go handler_int("thread1", ch)
	go handler_int("thread2", ch)
	// go handler_int("thread3", ch)
	ch <- 1
	time.Sleep(10 * time.Second)
	close(ch)
}
