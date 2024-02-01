## pipex

The PIPEx project is a part of the curriculum of the 42 School, which is aimed at helping students develop their skills in UNIX systems, file descriptors, processes, and interprocess communication.

The project involves the creation of a program called "pipex" that simulates the behavior of the shell command-line sequence.

```shell
< infile cmd1 | cmd2 > outfile
```
### Usage To use the pipex program, execute the following command:

```shell
./pipex file1 cmd1 cmd2 file2
```

### The parameters are described as follows:

- file1: the input file that contains the text to be processed
- cmd1: the first command that will be executed to process the input from file1
- cmd2: the second command that will be executed to process the output from cmd1
- file2: the output file where the final result will be stored

### Here is an example usage:

```shell
./pipex infile "ls -l" "grep pipex" outfile
````

This command will execute the ls -l command on the input file infile, and then execute the grep pipex command on the output of the previous command. Finally, the result will be written to the outfile.

## bonus
As for the bonus, the same thing is that it works on multiple pipes , and use here_doc

### Here is an example for multiple pipes

```shell
./pipex_bonus example.txt "cat" "grep -o old" "wc -l" test.txt
```
### Here is an example for here_doc

```shell
./pipex here_doc end cat cat file.txt
```


