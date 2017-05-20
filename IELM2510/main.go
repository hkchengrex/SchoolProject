package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"math"
	"os"
	"strconv"
	"strings"
	"sync"
)

var averageWindow int
var watch int

func main() {
	inputDir := os.Args[1]
	averageWindow, _ = strconv.Atoi(os.Args[2])
	watch, _ = strconv.Atoi(os.Args[3])
	files, err := ioutil.ReadDir(inputDir)

	if err == nil {
		fmt.Printf("Looking for files in %v... %d Found.\n", inputDir, len(files))

		controlSigSlice := make([]chan bool, len(files))
		dataSlice := make([]chan float64, len(files))
		var wg sync.WaitGroup

		for i, f := range files {
			controlSigSlice[i] = make(chan bool)
			dataSlice[i] = make(chan float64)
			fmt.Printf("Eating the %dth file. %v.\n", i, f.Name())
			wg.Add(1)
			go startStockAgent(i, inputDir+string(os.PathSeparator)+f.Name(), controlSigSlice[i], dataSlice[i], &wg)
		}

		wg.Wait()
		fmt.Println("All agents Ready. Press Enter to proceed.")

		enterEater := bufio.NewReader(os.Stdin)
		enterEater.ReadString('\n')

		//Kickstart
		iterations := 0
		agentsRemaining := len(files)
		for agentsRemaining > 0 {
			fmt.Printf("\nThis is the %d-th day. Stocks remaining: %d.\n\n", iterations, agentsRemaining)

			for i := 0; i < len(files); i++ {
				controlSigSlice[i] <- true
			}

			remaining := 0
			for i := 0; i < len(files); i++ {
				result := <-controlSigSlice[i]
				if result == true {
					remaining++
				}
			}
			agentsRemaining = remaining
			iterations++
		}

		for i := 0; i < len(files); i++ {
			controlSigSlice[i] <- false
		}
		fmt.Printf("All completed.\n")

	} else {
		fmt.Printf("Failed to look at %v\n", inputDir)
		panic(err)
	}
}

func startStockAgent(i int, f string, sig chan bool, data chan float64, wg *sync.WaitGroup) {
	money := 1000000.0
	stock := 0
	day := 0

	movingAverage := make([]float64, averageWindow)
	movingPointer := 0

	raw, err := ioutil.ReadFile(f)
	if err != nil {
		panic(err)
	}

	rawString := string(raw)
	lines := strings.Split(rawString, "\n")
	fmt.Printf("Agent %d ready. Number of data set: %d\n", i, len(lines))

	wg.Done()

	for {
		//Wait for the start signal
		signal := <-sig

		//Not signal means all businesses have to end
		if !signal {
			break
		}

		if day > len(lines)-1 {
			sig <- false
			continue
		}

		items := strings.Split(lines[day], ",")

		if len(items) < 6 {
			sig <- false
			continue
		}

		openPrice, _ := strconv.ParseFloat(items[2], 64)
		closePrice, _ := strconv.ParseFloat(items[5], 64)

		actionTaken := false
		if day > averageWindow {
			//Determine buy/sell
			averagePrice := 0.0
			for _, p := range movingAverage {
				averagePrice += p
			}

			//Buy with open price
			buyTendency := (averagePrice - openPrice) / averagePrice
			if buyTendency*money > openPrice {
				bought := math.Floor(buyTendency * money / openPrice)
				money -= bought * openPrice
				stock += int(bought)
				if watch == -1 || watch == i {
					fmt.Printf("Agent %d bought %d at %v.\n", i, int(bought), openPrice)
				}
				actionTaken = true
			}

			//Sell with close price
			sellTendency := (closePrice - averagePrice) / averagePrice
			if sellTendency*float64(stock) > 0 {
				sold := math.Floor(sellTendency * float64(stock))
				money += sold * closePrice
				stock -= int(sold)
				if watch == -1 || watch == i {
					fmt.Printf("Agent %d sold %d at %v.\n", i, int(sold), closePrice)
				}
				actionTaken = true
			}
		}

		if !actionTaken {
			//Keep watching
			if watch == -1 || watch == i {
				fmt.Printf("Agent %d took a rest today.\n", i)
			}
		}

		//Report current status
		if watch == -1 || watch == i {
			fmt.Printf("Agent %3d: $%11.2f, Stock: %9d\n", i, money, stock)
		}

		//Update moving average
		movingAverage[movingPointer] = (openPrice + closePrice) / 2 / float64(averageWindow)
		movingPointer = (movingPointer + 1) % averageWindow

		day++

		//Show that I'm done and still ok
		sig <- true
	}
}
