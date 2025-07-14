# Commit helper

Small commit wrapper for enforcing standard git commit convention (cause I'm lazy af)

## Compiling with g++

`g++ -o gcommit gcommit.cpp CommitTypes.cpp`

## Adding to path

### macOS/Linux

#### Add binary to PATH

```bash
mkdir -p ~/.local/bin
mv gcommit ~/.local/bin/
chmod +x ~/.local/bin/gcommit
```

#### Create .zshrc if needed

```bash
touch ~/.zshrc
vim ~/.zshrc
```

#### Add this line to the .zshrc file

`export PATH="$HOME/.local/bin:$PATH"`

### Windows

#### Add binary to PATH

1. Create a directory for your binaries (e.g., `C:\bin` or `%USERPROFILE%\bin`)
2. Move the `gcommit.exe` file to that directory
3. Add the directory to your system PATH:
   - Open System Properties (Win + Pause/Break or right-click Computer → Properties)
   - Click "Advanced system settings"
   - Click "Environment Variables"
   - Under "User variables", find "Path" and click "Edit"
   - Click "New" and add your binary directory path (e.g., `C:\bin`)
   - Click "OK" on all dialogs

#### Alternative: Add to PATH via Command Prompt

```cmd
setx PATH "%PATH%;C:\bin"
```

(Replace `C:\bin` with your actual binary directory path)

### Running

The binary should be able to be run through `gcommit` in a terminal (or `gcommit.exe` on Windows)
