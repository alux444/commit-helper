# Commit helper

Small commit wrapper for enforcing standard git commit convention (cause I'm lazy af)

## Compiling with g++

`g++ -o gcommit gcommit.cpp CommitTypes.cpp`

## Adding to path

### Add binary to PATH
```bash
mkdir -p ~/.local/bin
mv gcommit ~/.local/bin/
chmod +x ~/.local/bin/gcommit
```

### Create .zshrc if needed
`touch ~/.zshrc`
`vim ~/.zshrc`

### Add this line to the .zshrc file
`export PATH="$HOME/.local/bin:$PATH"`

### Running
The binary should be able to be run through `gcommit` in a terminal