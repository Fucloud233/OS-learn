package main

import "fmt"

var max_number = 10
var cur_number = 0

func compare(num int, cur_chan chan int) {
	cur := <-cur_chan

	// fmt.Println("Running")

	// 1. 如果不能整除 则是质数
	next_chan := make(chan int)
	if cur%num != 0 {
		fmt.Printf("%d, ", cur)
		go compare(cur, next_chan)
		cur_number++
	}

	// 2. 后续继续判断 (去掉条件判断)
	for {
		cur = <-cur_chan
		if cur%num != 0 {
			next_chan <- cur
		}
	}

	// <-cur_chan
}

func Solver() {
	cur_chan := make(chan int)
	start_num := 2
	go compare(start_num, cur_chan)

	for cur_number < max_number {
		start_num++
		cur_chan <- start_num
	}
}
