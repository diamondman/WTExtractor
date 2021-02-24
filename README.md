# WTExtractor
Tools to work with WildTanget game assets
## Pywtools
Requires Python 3, pip, and cabextract.

    sudo apt update
    sudo apt install python3 python3-pip cabextract -y
### Decompile wtxt to txt
    git clone https://github.com/diamondman/WTExtractor.git
    cd WTextractor/pywtools/
    pip install -r requirements.txt
    ./wtextract.py /path/to/wtxtfile.wtxt /path/to/newtxtfile.txt

Not specifying a txt file will output its text in the terminal.
    
## Compile txt to wtxt
This requires WildCompress, which is only available on Windows.
* Download the WildTanget SDK under releases, and navigate to SDK/tools/ and run WildCompress Setup.exe to install WildCompress
* open WildCompress
if it says 'd3drm.dll not found,' place d3drm.dll in the WildCompress install directory: C:\Program Files (x86)\WildTangent\WildCompress
* Go to file > open, and open the txt file. If it says 'unable to delete file,' reopen WildCompress ad administrator
* Configure as you would like, though not necessary, then click OK. The compiled wtxt file will be located in the same directory as the txt file.
