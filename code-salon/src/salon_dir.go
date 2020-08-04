package main

import (
	"os"
	"os/exec"
	"path/filepath"
	"strings"
	"sync"
)

const python string = "python3"
const script string = "salon.py"

func salonFile(inFile string, outFile string, wg *sync.WaitGroup) {
	defer wg.Done()

	py, _ := exec.LookPath(python)
	
	pyCmd := &exec.Cmd {
		Path: py,
		Args: []string {py, script, inFile, outFile},
		Stdout: os.Stdout,
		Stderr: os.Stdin,
	}
	pyCmd.Run()
}

func main() {
	inDir := os.Args[1]
	outDir := os.Args[2]
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
		outputFile := outDir + filename
		outputFiles = append(outputFiles, outputFile)
	}
	
	
	for i, inFile := range inputFiles {
		wg.Add(1)
		go salonFile(inFile, outputFiles[i], &wg)
	}
	wg.Wait()
}