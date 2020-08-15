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
	var args []string = []string {py, script}
	args = append(args, options...)
	args = append(args, inFile)
	args = append(args, outFile)
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

func singleMode(inFile string, outFile string, options []string, lang string) {
	if !strings.HasSuffix(inFile, "." + lang) {
		fmt.Println("WARNING: " + inFile + " is not a ." + lang + " file.")
	}
	salonFile(inFile, outFile, options)
}

func concurrentMode(inDir string, outDir string, options []string, lang string) {
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
		if strings.HasSuffix(inFile, "." + lang) {
			wg.Add(1)
			go salonFileConcurrent(inFile, outputFiles[i], options, &wg)
		} else {
			fmt.Println(inFile + " is not a ." + lang + " file, ignoring.")
		}
	}
	wg.Wait()
}

func main() {
	ex, _  := os.Executable()
	pwd := filepath.Dir(ex)
	script = pwd + "/code-salon-deps/salon.py"
	
	newLine := flag.String("new-line", "0", "if you want a new line before parentheses")
	deleteEmptyLines := flag.String("delete-empty-lines", "0", "if you want to delete empty lines")
	indent := flag.String("indent", "0", "number of spaces for an indent. If this is 0, then a tab is used.")
	input := flag.String("in", "", "the input file/directory")
	output := flag.String("out", "", "the output file/directory")
	lang := flag.String("lang", "cpp", "the programming language of the source file, default is cpp")
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
	options = append(options, []string{"--indent", string(*indent)}...)
	options = append(options, []string{"--lang", string(*lang)}...)
	
	fi, err := os.Stat(in)
	if err != nil {
		panic(err)
	}
	switch mode := fi.Mode(); {
	case mode.IsDir():
		concurrentMode(in, out, options, string(*lang))
	case mode.IsRegular():
		singleMode(in, out, options, string(*lang))
	}
}