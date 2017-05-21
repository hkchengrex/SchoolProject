package main

import (
	"fmt"
	"io/ioutil"
	"math"
	"os"
	"strconv"
	"strings"
	"sync"
	"time"
)

var averageWindow int
var watch int
var tax int

type returnData struct {
	money      float64
	code       string
	startPrice float64
	endPrice   float64
}

func main() {
	inputDir := os.Args[1]
	averageWindow, _ = strconv.Atoi(os.Args[2])
	watch, _ = strconv.Atoi(os.Args[3])
	tax, _ = strconv.Atoi(os.Args[4])

	start := time.Now()

	files, err := ioutil.ReadDir(inputDir)

	if err == nil {
		fmt.Printf("Looking for files in %v... %d Found.\n", inputDir, len(files))

		controlSigSlice := make([]chan bool, len(files))
		dataSlice := make([]chan returnData, len(files))
		var wg sync.WaitGroup

		for i, f := range files {
			controlSigSlice[i] = make(chan bool)
			dataSlice[i] = make(chan returnData)
			fmt.Printf("Eating the %dth file. %v.\n", i, f.Name())
			wg.Add(1)
			go startStockAgent(i, inputDir+string(os.PathSeparator)+f.Name(), controlSigSlice[i], dataSlice[i], &wg)
		}

		wg.Wait()

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

		finalData := make([]returnData, len(files))
		max := 0.0
		min := 100000000.0
		mean := 0.0
		for i := 0; i < len(files); i++ {
			finalData[i] = <-dataSlice[i]
			if finalData[i].money > max {
				max = finalData[i].money
			}
			if finalData[i].money < min {
				min = finalData[i].money
			}
			mean += finalData[i].money / float64(len(files))
		}

		fmt.Printf("\nMax: %f \nMin: %f \nMean: %f\n", max, min, mean)

		outputFile, err := os.Create("." + string(os.PathSeparator) + "output" +
			string(os.PathSeparator) + strconv.Itoa(averageWindow) +
			"_t" + strconv.Itoa(tax) + ".csv")

		if err != nil {
			fmt.Println("Error in creating output file.")
			panic(err)
		}

		for i, d := range finalData {
			line := fmt.Sprintf("%d,%s,%.0f,%f,%f\n", i, d.code, d.money, (d.money-1000000.0)/1000000.0, (d.endPrice-d.startPrice)/d.startPrice)
			outputFile.WriteString(line)
		}

		outputFile.Sync()

	} else {
		fmt.Printf("Failed to look at %v\n", inputDir)
		panic(err)
	}

	fmt.Println("Took ", time.Since(start))
}

func startStockAgent(i int, f string, sig chan bool, data chan returnData, wg *sync.WaitGroup) {
	money := 1000000.0
	stock := 0
	day := 0
	startPrice := 0.0

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

	openPrice := 0.0
	closePrice := 0.0

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

		openPrice, _ = strconv.ParseFloat(items[2], 64)
		closePrice, _ = strconv.ParseFloat(items[5], 64)

		if startPrice == 0 {
			startPrice = openPrice
		}

		//Take the tax into account
		openPrice *= (1.0 + float64(tax)/1000.0)
		closePrice *= (1.0 - float64(tax)/1000.0)

		actionTaken := false
		if day > averageWindow {
			//Determine buy/sell
			averagePrice := 0.0
			for _, p := range movingAverage {
				averagePrice += p
			}

			//Buy with open price
			buyTendency := (averagePrice - openPrice) / averagePrice
			if buyTendency > 1 {
				buyTendency = 1
			}
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
			if sellTendency > 1 {
				sellTendency = 1
			}
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

	//Done. Convert all stocks back to money.
	money += float64(stock) * closePrice

	lastIndex := strings.LastIndex(f, "_")
	stockCode := f[lastIndex+1 : len(f)-4]

	data <- returnData{money: money, code: stockCode, startPrice: startPrice, endPrice: closePrice}
}
