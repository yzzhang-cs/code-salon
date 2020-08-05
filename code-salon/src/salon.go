package main

import (
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"sync"
	"flag"
	"fmt"
)

const python string = "python3"
var script string
var pwd string

func salonFile(inFile string, outFile string, options []string) {
	py, _ := exec.LookPath(python)
	var args []string = []string {py, script, inFile, outFile}
	args = append(args, options...)
	pyCmd := &exec.Cmd {
		Path: py,
		Args: args,
		Stdout: os.Stdout,
		Stderr: os.Stdin,
	}
	pyCmd.Run()
}

func salonFileConcurrent(inFile string, outFile string, options []string, wg *sync.WaitGroup) {
	defer wg.Done()
	salonFile(inFile, outFile, options)
}

func singleMode(inFile string, outFile string, options []string) {
	salonFile(inFile, outFile, options)
}

func concurrentMode(inDir string, outDir string, options []string) {
	var wg sync.WaitGroup
	
	var inputFiles []string
	filepath.Walk(inDir, func(path string, info os.FileInfo, err error) error {
		inputFiles = append(inputFiles, path)
		return nil
	})
	inputFiles = inputFiles[1:]
	
	var filenames []string
	for _, file := range inputFiles {
		tmp := strings.Split(file, "/")
		filename := tmp[len(tmp) - 1]
		filenames = append(filenames, filename)
	}
	
	var outputFiles []string
	for _, filename := range filenames {
		outputFile := outDir + "/" + filename
		outputFiles = append(outputFiles, outputFile)
	}
	
	
	for i, inFile := range inputFiles {
		wg.Add(1)
		go salonFileConcurrent(inFile, outputFiles[i], options, &wg)
	}
	wg.Wait()
}

func main() {
	ex, _  := os.Executable()
	pwd := filepath.Dir(ex)
	script = pwd + "/code-salon-deps/salon.py"
	
	newLine := flag.String("new-line", "0", "if you want a new line before parentheses")
	deleteEmptyLines := flag.String("delete-empty-lines", "0", "if you want to delete empty lines")
	input := flag.String("in", "", "the input file/directory")
	output := flag.String("out", "", "the output file/directory")
	flag.Parse()
	in := string(*input)
	out := string(*output)
	
	if in == "" || out == "" {
		fmt.Fprintf(os.Stderr, "Usage: %s -in=<input_file> -out=<output_file>\n", os.Args[0])
		flag.PrintDefaults()
		os.Exit(1)
	}
	
	var options []string
	options = append(options, []string{"--new-line", string(*newLine)}...)
	options = append(options, []string{"--delete-empty-lines", string(*deleteEmptyLines)}...)
	
	fi, _ := os.Stat(in)
	switch mode := fi.Mode(); {
	case mode.IsDir():
		concurrentMode(in, out, options)
	case mode.IsRegular():
		singleMode(in, out, options)
	}
}